//
// Created by paul on 7/30/19.
//

#ifndef YUMI
#define YUMI

#include "Robot.h"

class Yumi: public Robot {

public:
    std::vector<std::string> RvizJointnames = {"yumi_joint_1_r", "yumi_joint_2_r", "yumi_joint_7_r", "yumi_joint_3_r",
                                               "yumi_joint_4_r", "yumi_joint_5_r", "yumi_joint_6_r", "yumi_joint_1_l",
                                               "yumi_joint_2_l", "yumi_joint_7_l", "yumi_joint_3_l","yumi_joint_4_l",
                                               "yumi_joint_5_l", "yumi_joint_6_l"};
    Yumi(ros::NodeHandle n): Robot("Yumi"){
        auto q = this->dynamics->getPosition();
        q[0] = (46.0/180.0)*3.14;
        q[1] = (-121.0/180.0)*3.14;
        q[2] = (-87.0/180.0)*3.14;
        q[3] = (4.0/180.0)*3.14;
        q[4] = (44.0/180.0)*3.14;
        q[5] = (54.0/180.0)*3.14;
        q[6] = (-3.0/180.0)*3.14;
        this->dynamics->setPosition(q);

    // service setters
    auto setAccelerationsCallback = this->getServiceCallBack(&Yumi::setAccelerations);
    ros::ServiceServer setJointAccelerationService = n.advertiseService("setJointAccelerations", setAccelerationsCallback);

    auto setArmVelocityCallback = this->getServiceCallBack(&Yumi::setArmVelocity);
    ros::ServiceServer setArmVelocityService = n.advertiseService("setArmVelocities", setArmVelocityCallback);

    auto setTorquesCallback = this->getServiceCallBack(&Yumi::setTorques);
    ros::ServiceServer setJointTorqueService = n.advertiseService("setJointTorques", setTorquesCallback);

    auto StaticTorquesCallback = this->getServiceCallBack(&Yumi::getStaticTorques);
    ros::ServiceServer getStaticJointTorqueService = n.advertiseService("getStaticJointTorques", StaticTorquesCallback);

    // service getters
    auto getTrajTorquesCallback = this->getServiceCallBack(&Yumi::getTrajTorques);
    ros::ServiceServer getTrajTorqueService = n.advertiseService("getTrajTorques", getTrajTorquesCallback);

    auto getMCallback = this->getServiceCallBack(&Yumi::getM);
    ros::ServiceServer getMService = n.advertiseService("getM", getMCallback);

    auto getJCallback = this->getServiceCallBack(&Yumi::getJ);
    ros::ServiceServer getJService = n.advertiseService("getJ", getJCallback);

    auto getCCallback = this->getServiceCallBack(&Yumi::getC);
    ros::ServiceServer getCService = n.advertiseService("getC", getCCallback);

    auto getTCallback = this->getServiceCallBack(&Yumi::getT);
    ros::ServiceServer getTService = n.advertiseService("getT", getTCallback);

    auto getGCallback = this->getServiceCallBack(&Yumi::getG);
    ros::ServiceServer getGService = n.advertiseService("getG", getGCallback);

    // publishers
    ros::Publisher operationalPosPubL = n.advertise<std_msgs::Float32MultiArray>("operational_position_L",1);
    ros::Publisher operationalPosPubR = n.advertise<std_msgs::Float32MultiArray>("operational_position_R",1);
    auto operationalPosPubLMsg = new std_msgs::Float32MultiArray();
    auto operationalPosPubRMsg = new std_msgs::Float32MultiArray();
    this->addPublisherPair(operationalPosPubR,operationalPosPubRMsg);
    this->addPublisherPair(operationalPosPubL,operationalPosPubLMsg);

    ros::Publisher jointVelPubL = n.advertise<std_msgs::Float32MultiArray>("joint_velocity_command_L",1);
    ros::Publisher jointVelPubR = n.advertise<std_msgs::Float32MultiArray>("joint_velocity_command_R",1);
    auto jointVelPubRMsg = new std_msgs::Float32MultiArray();
    auto jointVelPubLMsg = new std_msgs::Float32MultiArray();
    this->addPublisherPair(jointVelPubR,jointVelPubRMsg);
    this->addPublisherPair(jointVelPubL,jointVelPubLMsg);
    std::vector<std_msgs::Float32MultiArray*> jointVelPubRMsgs;
    jointVelPubRMsgs.push_back(jointVelPubRMsg);jointVelPubRMsgs.push_back(jointVelPubLMsg);

    ros::Publisher jointRvizPub = n.advertise<sensor_msgs::JointState>("rviz/joint_states",1);
    sensor_msgs::JointState* jointRvizMsg = new sensor_msgs::JointState();
    this->addPublisherPair(jointRvizPub,jointRvizMsg);

    ros::Publisher jointStatePub = n.advertise<std_msgs::Float32MultiArray>("joint_states",1);
    std_msgs::Float32MultiArray* jointStateMsg = new std_msgs::Float32MultiArray();
    this->addPublisherPair(jointStatePub,jointStateMsg);

    ros::Publisher jointStateVelPub = n.advertise<std_msgs::Float32MultiArray>("joint_states_vel",1);
    std_msgs::Float32MultiArray* jointStateVelMsg = new std_msgs::Float32MultiArray();
    this->addPublisherPair(jointStateVelPub,jointStateVelMsg);

    // subscribers
    std::vector<std_msgs::Float32MultiArray*> msgs;msgs.push_back(operationalPosPubRMsg);msgs.push_back(operationalPosPubLMsg);
    auto updateOpPositionCallback = this->getSubscriberCallBackPublishers(this->operationalPositionCallback,msgs);
    ros::Subscriber jointStateSubscriber = n.subscribe("joint_states",1,updateOpPositionCallback);

    auto jointVelSubLCallback = this->getSubscriberCallBack(EGMVelocityLCallback);
    ros::Subscriber jointVelSubL = n.subscribe("joint_velocity_command_L",1,jointVelSubLCallback);

    auto jointVelSubRCallback = this->getSubscriberCallBack(EGMVelocityRCallback);
    ros::Subscriber jointVelSubR = n.subscribe("joint_velocity_command_R",1,jointVelSubRCallback);

    auto opVelCallback = this->getSubscriberCallBackPublishers(sendOpJointVelocities,jointVelPubRMsgs);
    ros::Subscriber opVelSubscriber = n.subscribe("/operational_velocity_command",1,opVelCallback);

    std::vector<std_msgs::Float32MultiArray*> msgs2;msgs2.push_back(jointVelPubRMsg);msgs2.push_back(jointVelPubLMsg);
    auto sendJointVelCallback = this->getSubscriberCallBackPublishers(sendOpJointVelocities,msgs2);

    auto rvizUpdateJointsCallback = this->getSubscriberCallBackPublisher(rvizUpdateJoints,jointRvizMsg);
    ros::Subscriber jointStateSubscriberrviz = n.subscribe("joint_states",1,rvizUpdateJointsCallback);
    }

    bool getM(dynamics::getM::Request  &req, dynamics::getM::Response &res) { // serviceRobot
        auto q = robot->dynamics->getPosition();
        auto qtmp = robot->dynamics->getPosition();
        for (int i=0;i<req.q.size();i++) {
            q[i] = req.q[i];
        }
        robot->dynamics->setPosition(q);
        auto M = robot->getMassMatrix();
        for (int i=0;i<M.rows();i++){
            for (int j=0;j<M.cols();j++){
                res.M.push_back(M(i,j));
            }
        }
        auto b = robot->dynamics->getBody(8); // 8 is right finger
        //std::cout<< b->m <<std::endl;
        robot->dynamics->setPosition(qtmp);
        //std::cout<< M <<std::endl;
        return true;
    }

    bool getC(dynamics::getC::Request  &req, dynamics::getC::Response &res) { // serviceRobot
        auto q = robot->dynamics->getPosition();
        auto qd = robot->dynamics->getVelocity();
        auto qtmp = robot->dynamics->getPosition();
        auto qdtmp = robot->dynamics->getVelocity();
        for (int i=0;i<req.q.size();i++) {
            q[i] = req.q[i];
            qd[i] = req.qd[i];
        }
        robot->dynamics->setPosition(q);
        robot->dynamics->setVelocity(qd);
        auto c = robot->getCentrifugalCoriolis();
        for (int i=0;i<c.size();i++){
            res.c.push_back(c(i));
        }
        robot->dynamics->setPosition(qtmp);
        robot->dynamics->setVelocity(qdtmp);
        //std::cout<< c <<std::endl;
        return true;
    }

    bool getT(dynamics::getT::Request  &req, dynamics::getT::Response &res) { // serviceRobot
        auto q = robot->dynamics->getPosition();
        auto qtmp = robot->dynamics->getPosition();    //robot->publishOne(jointVelMsgs[0]);
        //robot->publishOne(jointVelMsgs[1]);amics->getPosition();
        for (int i=0;i<req.q.size();i++) {
            q[i] = req.q[i];
        }
        robot->dynamics->setPosition(q);
        auto M = robot->getMassMatrix();
        for (int k=0;k<q.size();k++) {
            q[k]=q[k]+0.001;
            robot->dynamics->setPosition(q);
            robot->M = robot->getMassMatrix()-M;
            auto Ti = robot->M;
            for (int i = 0; i < Ti.rows(); i++) {
                for (int j = 0; j < Ti.cols(); j++) {
                    res.T.push_back(Ti(i, j)/0.001);
                }
            }
            q[k]=q[k]-0.001;
        }
        //std::cout<< Ti <<std::endl;
        robot->dynamics->setPosition(qtmp);
        return true;
    }

    bool getG(dynamics::getG::Request  &req, dynamics::getG::Response &res) { // serviceRobot
        auto q = robot->dynamics->getPosition();
        auto qtmp = robot->dynamics->getPosition();
        for (int i=0;i<req.q.size();i++) {
            q[i] = req.q[i];
        }
        robot->dynamics->setPosition(q);
        auto g = robot->getGravity();
        for (int i=0;i<g.size();i++){
            res.g.push_back(g(i));
        }
        robot->dynamics->setPosition(qtmp);
        //std::cout<< g <<std::endl;
        return true;
    }

    bool getJ(dynamics::getJ::Request  &req, dynamics::getJ::Response &res) { // serviceRobot
        auto q = robot->dynamics->getPosition();
        auto qtmp = robot->dynamics->getPosition();
        for (int i=0;i<req.q.size();i++) {
            q[i] = req.q[i];
        }
        robot->dynamics->setPosition(q);
        robot->dynamics->forwardPosition();
        auto J = robot->getJacobian();
        for (int i=0;i<J.rows();i++){
            for (int j=0;j<J.cols();j++){
                res.J.push_back(J(i,j));
            }
        }
        robot->dynamics->setPosition(qtmp);
        //std::cout<< J <<std::endl;
        return true;
    }

    bool getStaticTorques(dynamics::getStaticTorques::Request  &req, dynamics::getStaticTorques::Response &res){ // serviceRobot
        auto q = robot->dynamics->getPosition();
        auto qd = robot->dynamics->getVelocity();
        auto qdd = robot->dynamics->getAcceleration();
        auto qtmp = robot->dynamics->getPosition();
        auto qdtmp = robot->dynamics->getVelocity();
        auto qddtmp = robot->dynamics->getAcceleration();
        for (int i=0;i<req.q.size();i++){
            q[i]=req.q[i];
            qd[i]=0;
            qdd[i]=0;
        }
        robot->dynamics->setPosition(q);
        robot->dynamics->setVelocity(qd);
        robot->dynamics->setAcceleration(qdd);
        robot->dynamics->inverseDynamics();
        auto tau = robot->dynamics->getTorque();
        res.tau=req.q;
        for (int i=0;i<req.q.size();i++) {
            res.tau[i] = tau[i];
        }
        robot->dynamics->setPosition(qtmp);
        robot->dynamics->setVelocity(qdtmp);
        robot->dynamics->setAcceleration(qddtmp);
        robot->dynamics->forwardDynamics();
        return true;
    }

    bool getTrajTorques(dynamics::getTrajTorques::Request  &req, dynamics::getTrajTorques::Response &res){ // serviceRobot
        auto q = robot->dynamics->getPosition();
        auto qd = robot->dynamics->getVelocity();
        auto qdd = robot->dynamics->getAcceleration();
        rl::math::Vector Fext =rl::math::Vector::Zero(12);
        auto qtmp = robot->dynamics->getPosition();
        auto qdtmp = robot->dynamics->getVelocity();
        auto qddtmp = robot->dynamics->getAcceleration();
        for (int i=0;i<req.q.size();i++){
            q[i]=req.q[i];
            qd[i]=req.qd[i];
            qdd[i]=req.qdd[i];
        }
        for (int i=0;i<req.Fext.size();i++){
            Fext[i] = req.Fext[i];
        }
        robot->dynamics->setPosition(q);
        robot->dynamics->setVelocity(qd);
        rl::math::Vector V = robot->getCentrifugalCoriolis();
        robot->dynamics->setAcceleration(qdd);
        robot->dynamics->forwardPosition();
        robot->dynamics->forwardVelocity();
        robot->dynamics->inverseDynamics();
        rl::math::Matrix J = robot->getJacobian();
        auto tau = robot->dynamics->getTorque();
        tau-=((J.transpose())*Fext);
        //std::cout<< J<<std::endl;
        for (int i=0;i<req.q.size();i++) {
            res.Tau.push_back(tau[i]);
        }
        auto M = robot->getMassMatrix();
        double KE = robot->getKE();
        res.KE=KE;
        robot->dynamics->setPosition(qtmp);
        robot->dynamics->setVelocity(qdtmp);
        robot->dynamics->setAcceleration(qddtmp);
        robot->dynamics->forwardDynamics();
        return true;
    }

    bool setTorques(dynamics::setTorques::Request  &req, dynamics::setTorques::Response &res){ // serviceRobot
        auto tau = robot->dynamics->getTorque();
        for (int i=0;i<req.tau.size();i++){
            tau[i]=req.tau[i];
        }
        robot->dynamics->setTorque(tau);
        robot->dynamics->forwardDynamics();
        auto qdd = robot->dynamics->getAcceleration();
        for (int i=0;i<req.tau.size();i++) {
            res.qdd.push_back(qdd[i]);
        }
        return true;
    }

    bool setAccelerations(dynamics::setTorques::Request  &req, dynamics::setTorques::Response &res){ // serviceRobot
        auto qdd = this->dynamics->getTorque();
        for (int i=0;i<req.tau.size();i++){
            qdd[i]=req.tau[i];
        }
        this->dynamics->setAcceleration(qdd);
        this->dynamics->inverseDynamics();
        auto tau = this->dynamics->getTorque();
        for (int i=0;i<req.tau.size();i++) {
            res.qdd.push_back(tau[i]);
        }
        return true;
    }

    rl::math::Vector3 cross(rl::math::Vector3 a,rl::math::Vector3 b){
        rl::math::Vector3 r =rl::math::Vector3::Zero();
        r[0] = a[1]*b[2]-a[2]*b[1];
        r[1] = a[2]*b[0]-a[0]*b[2];
        r[2] = a[0]*b[1]-a[1]*b[0];
        return r;
    }

    bool setArmVelocity(dynamics::setTorques::Request  &req, dynamics::setTorques::Response &res) { // serviceRobot
        rl::math::Vector3 gax = rl::math::Vector3::Zero();
        rl::math::Vector3 gaxS = rl::math::Vector3::Zero();
        for (int i = 0; i < 3; i++) {
            gaxS[i] = req.tau[i]; // this is goal axis
        }
        for (int i = 0; i < 3; i++) {
            gax[i] = req.tau[i+3]; // this is goal axis
        }
        double theta = req.tau[6];
        rl::math::Vector3 z0 = rl::math::Vector3::Zero();
        z0[2]=1;
        rl::math::Vector3 e1 =  rl::math::Vector3::Zero();
        rl::math::Vector3 e2 = rl::math::Vector3::Zero();
        do {
            auto f3 = robot->dynamics->getBody(5);
            auto R3 = f3->t.rotation();
            rl::math::Vector3 z3 = R3 * z0;
            rl::math::Vector3 p3 = f3->t.translation();
            auto f2 = robot->dynamics->getBody(4);
            auto R2 = f2->t.rotation();
            rl::math::Vector3 z2 = R2 * z0;
            rl::math::Vector3 p2 = f2->t.translation();
            auto f1 = robot->dynamics->getBody(3);
            auto R1 = f1->t.rotation();
            rl::math::Vector3 z1 = R1 * z0;
            rl::math::Vector3 p1 = f1->t.translation();
            auto d1 = cross(z1, p3 - p1);
            d1.normalize();
            auto d2 = cross(z2, p3 - p2);
            d2.normalize();
            rl::math::Matrix D = rl::math::Matrix(3, 2);
            //D << d1, d2;
            rl::math::Vector3 g = gax - z3;
            rl::math::Matrix22 lambdaM = rl::math::Matrix22::Identity() * 0.0001;
            rl::math::Matrix22 DD = rl::math::Matrix22::Zero();
            DD = D.transpose() * D + lambdaM;
            rl::math::Vector2 x = DD.inverse() * D.transpose() * g;
            x.normalize();
            auto f3S = robot->dynamics->getBody(3);
            auto R3S = f3S->t.rotation();
            rl::math::Vector3 z3S = R3S * z0;
            rl::math::Vector3 p3S = f3S->t.translation();
            auto f2S = robot->dynamics->getBody(2);
            auto R2S = f2S->t.rotation();
            rl::math::Vector3 z2S = R2S * z0;
            rl::math::Vector3 p2S = f2S->t.translation();
            auto f1S = robot->dynamics->getBody(1);
            auto R1S = f1S->t.rotation();
            rl::math::Vector3 z1S = R1S * z0;
            rl::math::Vector3 p1S = f1S->t.translation();
            d1 = cross(z1S, p3S - p1S);
            d1.normalize();
            d2 = cross(z2S, p3S - p2S);
            d2.normalize();
            D = rl::math::Matrix(3, 2);
            //D << d1, d2;
            g = gaxS - z3S;
            DD = D.transpose() * D + lambdaM;
            rl::math::Vector2 xS = DD.inverse() * D.transpose() * g;
            xS.normalize();
            auto q = robot->dynamics->getPosition();
            q[0]+=xS[0]*theta;
            q[1]+=xS[1]*theta;
            q[2]+=x[0]*theta;
            q[3]+=x[1]*theta;
            robot->dynamics->setPosition(q);
            robot->dynamics->forwardPosition();
            e1 =  gax - z3;
            e2 =  gaxS - z3S;
        }
        while(e1.norm()+e2.norm()>0.005);
        auto tau = robot->dynamics->getPosition();
        for (int i = 0; i < tau.size(); i++) {
            res.qdd.push_back(tau[i]);
        }
        return true;
    }


    void operationalPositionCallback(const std_msgs::Float32MultiArray::ConstPtr& msg,std::vector<std_msgs::Float32MultiArray*> opPostionMsgs, Yumi*& robot){ //subpub
        std::vector<float> data = msg->data;
        auto q = robot->floatVec2MathVec(data);
        for (int i=0;i<data.size();i++) {
            q[i] = data[i];
        }
        opPostionMsgs[0]->data = robot->getOperationalPosition(0);
        opPostionMsgs[1]->data = robot->getOperationalPosition(1);
    }
    void EGMVelocityLCallback(const std_msgs::Float32MultiArray::ConstPtr& msg, Yumi*& robot){ //fake egm
        std::vector<float> data = msg->data;
        auto qd = robot->dynamics->getVelocity();
        for (int i=0;i<data.size();i++) {
            qd[i+data.size()] = data[i];
        }
        robot->dynamics->setVelocity(qd);
    }
    void EGMVelocityRCallback(const std_msgs::Float32MultiArray::ConstPtr& msg, Yumi*& robot){ //fake egm
        std::vector<float> data = msg->data;
        auto qd = robot->dynamics->getVelocity();
        for (int i=0;i<data.size();i++) {
            qd[i] = data[i];
        }
        robot->dynamics->setVelocity(qd);
    }

    void sendOpJointVelocities(const std_msgs::Float32MultiArray::ConstPtr& opVelMsg,std::vector<std_msgs::Float32MultiArray*> jointVelMsgs,Yumi*& robot){ //subpub
        std::vector<float> opvelL;
        std::vector<float> opvelR;
        for (int i=0;i<6;i++){
            opvelR.push_back(opVelMsg->data[i]);
            opvelL.push_back(opVelMsg->data[i+6]);
        }
        jointVelMsgs[0]->data = robot->xd2jd(0,opvelR);
        jointVelMsgs[1]->data = robot->xd2jd(1,opvelL);
    }

    void rvizUpdateJoints(const std_msgs::Float32MultiArray::ConstPtr& msg,sensor_msgs::JointState* rvizMsgs,Yumi*& robot){ //subpub
        std::vector<double> tmp;
        for (int i=0;i<msg->data.size();i++) {
            double val = msg->data[i];
            tmp.push_back(val);
        }
        rvizMsgs->position=tmp;
        rvizMsgs->name = robot->RvizJointnames;
        rvizMsgs->header.stamp = ros::Time::now();
    }

};



#endif
