//
// Created by paul on 7/30/19.
//

#ifndef ROBOT_C
#define ROBOT_C

#include "Robot.h"
#include "RobotFactory.h"

    Robot::Robot(){
        init("");
    }

    Robot::Robot(std::string name){
        init(name);
    }

    void Robot::init(std::string name){
        using namespace rl;
        this->name = name;
        std::string urdf_file_name = name+".urdf";
        this->model = new mdl::Model();
        this->loadModel(urdf_file_name);
        this->dynamics = (mdl::Dynamic*) this->model;
        for (int i = 0; i < this->model->getJoints(); i++){
            auto joint = this->model->getJoint(i);
            string name = joint->getName();
            jointNames.push_back(name);
            jointNames2Ind[name] = i;
        }
        int numEE = this->dynamics->getOperationalDof();
        int numDof = this->dynamics->getDof();
        this->J = rl::math::Matrix(6*numEE, numDof);
        this->M = rl::math::Matrix(numDof,numDof);
        for (int n=0;n<numEE;n++){
            this->Ji.push_back(rl::math::Matrix(6, numDof));
            this->invJi.push_back(rl::math::Matrix(6, numDof));
            this->xdi.push_back(rl::math::Vector(6));
        }
        this->tau0 = rl::math::Vector::Zero(numDof);
    }

    Robot::~Robot(){
        delete this->model;
    }

    rl::math::Vector Robot::floatVec2MathVec(std::vector<float> fv){
        rl::math::Vector mv =rl::math::Vector(fv.size());
        for (int i =0;i<fv.size();i++){
            mv[i]=fv[i];
        }
        return mv;
    }
    std::vector<float> Robot::mathVec2FloatVec(rl::math::Vector mv){
        std::vector<float> fv;
        for (int i =0;i<mv.size();i++){
            fv.push_back(mv[i]);
        }
        return fv;
    }
    std::vector<float> Robot::getPosition(){
        rl::math::Vector j = this->dynamics->getPosition();
        return this->mathVec2FloatVec(j);
    }
    std::vector<float> Robot::getVelocity(){
        rl::math::Vector j = this->dynamics->getVelocity();
        return this->mathVec2FloatVec(j);
    }
    std::vector<float> Robot::getKE(){
        auto qd=this->dynamics->getVelocity();
        auto tau=this->dynamics->getTorque();
        this->dynamics->calculateMassMatrix(this->M);
        this->dynamics->setVelocity(qd);
        this->dynamics->setTorque(tau);
        rl::math::Vector KE = .5*this->M*qd;
        for (int i=0;i<qd.size();i++){
            KE[i] =KE[i]*qd[i];
        }
        return this->mathVec2FloatVec(KE);
    }
    std::vector<float> Robot::getPE(){
        auto qd=this->dynamics->getVelocity();
        for (int i=0;i<this->dynamics->getBodies();i++){
            auto b0 = this->dynamics->getBody(i); // 3 is 2
            auto b1 = this->dynamics->getBody(i+1);
            float mass = b0->m;
            auto T0 = b0->t;
            float h0 = T0(2,3);
            auto T1 = b1->t;
            float h1 = T1(2,3);
            std::cout<<h0<<std::endl;
            std::cout<<h1<<std::endl;
            std::cout<<.5*(h1+h0)<<std::endl;
        }
        return this->mathVec2FloatVec(qd);
    }
    std::vector<float> Robot::xd2jd(int EE, std::vector<float> xdf){
        rl::math::Vector xd =this->floatVec2MathVec(xdf);
        rl::math::Vector jd = this->xd2jd(EE,xd);
        return this->mathVec2FloatVec(jd);

    }

    rl::math::Vector Robot::xd2jd(int EE, rl::math::Vector xd){
        this->dynamics->calculateJacobian(this->J);
        rl::math::Matrix Ji = this->Ji[EE];
        rl::math::Matrix invJi = this->invJi[EE];
        int numEE = this->dynamics->getOperationalDof();
        int numDof = this->dynamics->getDof();
        int offseti = EE*6;
        for (int i =0;i<6;i++){
            for (int j=0;j<J.cols();j++){
                Ji(i,j) = J(i+offseti,j);
            }
        }
        invJi.transposeInPlace();
       this->dynamics->calculateJacobianInverse(Ji,invJi,0.001f, true);
        rl::math::Vector jd = invJi*xd;
        return jd;
    }
    std::vector<float> Robot::getOperationalPosition(int EE){
        this->dynamics->forwardPosition();
        rl::math::Transform T = this->dynamics->getOperationalPosition(EE);
        std::vector<float> p;
        for (int i =0;i<3;i++){
            p.push_back(T(i,3));
        }
        rl::math::Vector z0 = rl::math::Vector::Zero(3);
        z0[2]=1;
        rl::math::Vector z = T.inverse().rotation()*z0;
        for (int i =0;i<3;i++){
            p.push_back(z[i]);
        }
        return p;
    }
    void Robot::step(float dt, int numsteps){
        auto appliedTau = this->dynamics->getTorque();
        auto q = this->dynamics->getPosition();
        auto qd = this->dynamics->getVelocity();
        auto tau = this->dynamics->getTorque();
        for (int i=0;i<numsteps;i++){
            for (int i=0;i<tau.size();i++){
                tau[i]=appliedTau[i]-qd[i];
            }
            this->dynamics->setTorque(tau);
            this->dynamics->forwardDynamics();
            this->dynamics->rungeKuttaNystrom(dt/numsteps);
            //q = this->dynamics->getPosition();
            qd = this->dynamics->getVelocity();
            //this->dynamics->setPosition(q);
            //this->dynamics->setVelocity(qd);
        }
        //this->dynamics->setTorque(this->tau0);
        this->dynamics->setTorque(appliedTau);

    }
    void Robot::generateURDF(std::string myRobotstr){
        std::ofstream myfile;
        myfile.open (this->name+".urdf");
        myfile<<myRobotstr;
        myfile.close();
    }

    void Robot::loadModel(std::string urdf_file_name){
        std::ifstream f(urdf_file_name.c_str());
        if(f.good()){
            std::remove(urdf_file_name.c_str()) ;
        }
        std::string myRobotstr;
        ros::param::get("robot_description",myRobotstr);
        this->generateURDF(myRobotstr);
        rl::mdl::UrdfFactory urdf;
        urdf.load(urdf_file_name, this->model);

    }


#endif //YUMI_WS_ROBOT_H
