//
// Created by paul on 7/30/19.
//

#ifndef YUMI_WS_ROBOT_H
#define YUMI_WS_ROBOT_H

#include <rl/math/Transform.h>
#include <rl/math/Vector.h>
#include <rl/math/Matrix.h>
#include <rl/math/Unit.h>
#include <rl/mdl/Dynamic.h>
#include <rl/mdl/Model.h>
#include <rl/mdl/Body.h>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <string>
#include "rl/mdl/UrdfFactory.h"
#include <ros/ros.h>
#include "std_msgs/Float32.h"
#include "rl/mdl/Joint.h"
#include <boost/function.hpp>


struct PublisherPair{
    ros::Publisher publisher;
    void* msg;
    boost::function<void (ros::Publisher pub,void* msg)> publish;
};

class Robot {

public:
    Robot(std::string name){
        using namespace rl;
        this->name = name;
        std::string urdf_file_name = name+".urdf";
        this->model = new mdl::Model();
        this->loadModel(urdf_file_name);
        this->dynamics = (mdl::Dynamic*) this->model;
        int numEE = this->dynamics->getOperationalDof();
        int numDof = this->dynamics->getDof();
        this->J =rl::math::Matrix(6*numEE, numDof);
        this->M =rl::math::Matrix(numDof,numDof);
        for (int n=0;n<numEE;n++){
            this->Ji.push_back(rl::math::Matrix(6, numDof/numEE));
            this->invJi.push_back(rl::math::Matrix(6, numDof/numEE));
            this->xdi.push_back(rl::math::Vector(6));
        }
        this->tau0 = rl::math::Vector::Zero(numDof);
    }
    ~Robot(){
        delete this->model;
    }
    rl::math::Vector floatVec2MathVec(std::vector<float> fv){
        rl::math::Vector mv =rl::math::Vector(fv.size());
        for (int i =0;i<fv.size();i++){
            mv[i]=fv[i];
        }
        return mv;
    }
    std::vector<float> mathVec2FloatVec(rl::math::Vector mv){
        std::vector<float> fv;
        for (int i =0;i<mv.size();i++){
            fv.push_back(mv[i]);
        }
        return fv;
    }
    std::vector<float> getPosition(){
        rl::math::Vector j = this->dynamics->getPosition();
        return this->mathVec2FloatVec(j);
    }
    std::vector<float> getVelocity(){
        rl::math::Vector j = this->dynamics->getVelocity();
        return this->mathVec2FloatVec(j);
    }
    std::vector<float> getKE(){
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
    std::vector<float> getPE(){
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
    std::vector<float> xd2jd(int EE, std::vector<float> xdf){
        rl::math::Vector xd =this->floatVec2MathVec(xdf);
        rl::math::Vector jd = this->xd2jd(EE,xd);
        return this->mathVec2FloatVec(jd);

    }

    rl::math::Vector xd2jd(int EE, rl::math::Vector xd){
        this->dynamics->calculateJacobian(this->J);
        rl::math::Matrix Ji = this->Ji[EE];
        rl::math::Matrix invJi = this->invJi[EE];
        int numEE = this->dynamics->getOperationalDof();
        int numDof = this->dynamics->getDof();
        int offseti = EE*6;
        int offsetj=EE*numDof/numEE;
        for (int i =0;i<6;i++){
            for (int j=0;j<7;j++){
                Ji(i,j) = J(i+offseti,j+offsetj);
            }
        }
        this->dynamics->calculateJacobianInverse(Ji,invJi,0.01f,true);
        rl::math::Vector jd = invJi*xd;
        return jd;
    }
    std::vector<float> getOperationalPosition(int EE){
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
    void step(float dt, int numsteps){
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
    void generateURDF(std::string myRobotstr){
        std::ofstream myfile;
        myfile.open (this->name+".urdf");
        myfile<<myRobotstr;
        myfile.close();
    }

    void loadModel(std::string urdf_file_name){
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
    template<typename T>
    void publishOne(T msgIn){
        PublisherPair pp = this->msgMap[msgIn];
        void* msg = pp.msg;
        ros::Publisher pub = pp.publisher;
        pp.publish(pub,msg);
    }

    void publishOne(int i){
        void* msg = this->publisherPairs[i].msg;
        ros::Publisher pub = this->publisherPairs[i].publisher;
        this->publisherPairs[i].publish(pub,msg);
    }

    void publishAll(){
        for (int i =0;i<this->publisherPairs.size();i++){
            publishOne(i);
        }
    }

    template<typename T>
    void publisher(ros::Publisher pub,void* msg){
        T* msg2 =(T*) msg;
        pub.publish(*msg2);
    }

    template<typename T>
    void addPublisherPair(ros::Publisher pub,T* msg) {
        PublisherPair pp;
        pp.publisher=pub;
        pp.msg = (void*) msg;
        //boost::function<void (ros::Publisher pub,void* msg)> func = [=](ros::Publisher pub,void* msg) {this->publisher<T>(pub,msg);};
        boost::function<void (ros::Publisher pub,void* msg)> publish = [=](ros::Publisher pub,void* msg) {publisher<T>(pub,msg);};
        pp.publish= publish;
        this->publisherPairs.push_back(pp);
        this->msgMap[pp.msg] = pp;
    }
    template<typename T>
    boost::function<void (T msg)> getSubscriberCallBack(void (*userFunc)(T)){
        boost::function<void (T msg)> callBack = [=](T msg) {userFunc(msg);};
        return callBack;
    }
    template<typename T,typename T2>
    boost::function<void (T msg)> getSubscriberCallBackPublisher(void (*userFunc)(T,T2*),T2* pubMsg){
        boost::function<void (T msg)> callBack = [=](T msg) {userFunc(msg,pubMsg);};
        return callBack;
    }
    template<typename T,typename T2>
    boost::function<void (T msg)> getSubscriberCallBackPublisherRobot(void (*userFunc)(T,T2*,Robot*&),T2* pubMsg,Robot*& robot){
        boost::function<void (T msg)> callBack = [=,&robot](T msg) {userFunc(msg,pubMsg,robot);};
        return callBack;
    }
    template<typename T,typename T2>
    boost::function<void (T msg)> getSubscriberCallBackPublishersRobot(void (*userFunc)(T,std::vector<T2*>,Robot*&),std::vector<T2*> pubMsgs,Robot*& robot){
        boost::function<void (T msg)> callBack = [=,&robot](T msg) {userFunc(msg,pubMsgs,robot);};
        return callBack;
    }

    template<typename T1, typename T2, typename T3>
    boost::function<bool (T1,T2)> getServiceCallBack(bool(*userFunc)(T1,T2)){
        boost::function<bool (T1 req,T2 res)> callBack = [=](T1 req,T2 res) {return userFunc(req,res);};
        return callBack;
    }
    template<typename T1, typename T2, typename T3>
    boost::function<bool (T1,T2)> getServiceCallBackPublisher(bool (*userFunc)(T1,T2,T3*),T3* msg){
        boost::function<bool (T1 req,T2 res)> callBack = [=](T1 req,T2 res) {return userFunc(req,res,msg);};
        return callBack;
    }
    template<typename T1, typename T2, typename T3>
    boost::function<bool (T1,T2)> getServiceCallBackPublisherRobot(bool (*userFunc)(T1,T2,T3*,Robot*&),T3* msg, Robot*& robot){
        boost::function<bool (T1 req,T2 res)> callBack = [=,&robot](T1 req,T2 res) { return userFunc(req,res,msg,robot);};
        return callBack;
    }
    template<typename T1, typename T2>
    boost::function<bool(T1,T2)> getServiceCallBackRobot(bool (*userFunc)(T1,T2,Robot*&), Robot*& robot){
        boost::function<bool(T1 req,T2 res)> callBack = [=,&robot](T1 req,T2 res) {return  userFunc(req,res,robot);};
        return callBack;
    }
    rl::mdl::Dynamic* dynamics;
    std::string name;
private:
    std::vector<ros::ServiceServer> services;
    std::vector<PublisherPair> publisherPairs;
    rl::mdl::Model* model;
    rl::math::Matrix J;
    rl::math::Matrix M;
    std::vector<rl::math::Matrix> Ji;
    std::vector<rl::math::Matrix> invJi;
    std::vector<rl::math::Vector> xdi;
    std::map<void*,PublisherPair> msgMap;
    rl::math::Vector tau0;
};

/*
class Robot {

public:
    Robot(std::string name);
    ~Robot();
    rl::math::Vector xd2jd(int , rl::math::Vector );
    std::vector<float> xd2jd(int, std::vector<float>);
    std::vector<float> getOperationalPosition(int);
    void publishAll();
    template<typename T>
    void publishOne(T);
    void publishOne(int);
    template<typename T>
    void addPublisherPair(ros::Publisher, T* msg);
    //boost::function<void (T msg)> getSubscriberPublisherCallBack( int pub,boost::function<void (T msg,ros::Publisher pub)>);
    template<typename T>
    boost::function<void (T)> getSubscriberCallBack(void (*userFunc)(T));
    template<typename T,typename T2>
    boost::function<void (T)> getSubscriberCallBackPublisher(void (*userFunc)(T,T2*),T2*);
    template<typename T, typename T2>
    boost::function<void (T)> getSubscriberCallBackPublisherRobot(void (*userFunc)(T,T2*,Robot*),T2*, Robot* );
    template<typename T, typename T2>
    boost::function<void (T)> getSubscriberCallBackPublishersRobot(void (*userFunc)(const T,std::vector<T2*>,Robot*),std::vector<T2*>, Robot* );
    template<typename T1, typename T2, typename T3>
    boost::function<bool (T1,T2)> getServiceCallBack(bool (*userFunc)(T1,T2));
    template<typename T1, typename T2, typename T3>
    boost::function<bool (T1,T2)> getServiceCallBackPublisher(bool(*userFunc)(T1,T2,T3*),T3*);
    template<typename T1, typename T2, typename T3>
    boost::function<bool (T1,T2)> getServiceCallBackPublisherRobot(bool (*userFunc)(T1,T2,T3*,Robot*),T3*, Robot* );
    template<typename T1, typename T2>
    boost::function<bool (T1,T2)> getServiceCallBackRobot(bool (*userFunc)(T1,T2,Robot*), Robot*);
    template<typename T>
    void publisher(ros::Publisher pub,void* msg);
    rl::math::Vector floatVec2MathVec(std::vector<float>);
    std::vector<float> mathVec2FloatVec(rl::math::Vector);
    rl::mdl::Dynamic* dynamics;
    std::string name;
private:
    void generateURDF(std::string myRobotstr);
    void loadModel(std::string urdf_file_name);
    std::vector<ros::ServiceServer> services;
    std::vector<PublisherPair> publisherPairs;
    rl::mdl::Model* model;
    rl::math::Matrix J;
    std::vector<rl::math::Matrix> Ji;
    std::vector<rl::math::Matrix> invJi;
    std::vector<rl::math::Vector> xdi;
    std::map<void*,PublisherPair> msgMap;
};


*/


#endif //YUMI_WS_ROBOT_H
