//
// Created by paul on 7/26/19.
//
#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
#include "sensor_msgs/JointState.h"
#include "dynamics/getStaticTorques.h"
#include "dynamics/setTorques.h"
#include "dynamics/getM.h"
#include "dynamics/getG.h"
#include "dynamics/getC.h"
#include "dynamics/getJ.h"
#include "dynamics/getT.h"
#include "dynamics/getTrajTorques.h"
#include <rl/mdl/Body.h>

#include <iostream>
#include "Robot.h"
#include <iostream>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

bool addMass(dynamics::getM::Request  &req, dynamics::getM::Response &res, Robot*& robot) { // serviceRobot
    auto mass = req.q[0];
    auto b = robot->dynamics->getBody(8); // 8 is right finger
    std::cout<< b->m <<std::endl;
    b->m=b->m+mass;
    //rl::mdl::Model* model = new rl::mdl::Model();
    //model = robot->dynamics->clone();
    //robot->dynamics =(rl::mdl::Dynamic*) model;
    robot->dynamics->forwardDynamics();
    return true;
}

bool getM(dynamics::getM::Request  &req, dynamics::getM::Response &res, Robot*& robot) { // serviceRobot
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
    std::cout<< b->m <<std::endl;
    robot->dynamics->setPosition(qtmp);
    std::cout<< M <<std::endl;
    return true;
}
bool getC(dynamics::getC::Request  &req, dynamics::getC::Response &res, Robot*& robot) { // serviceRobot
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
    std::cout<< c <<std::endl;
    return true;
}
bool getT(dynamics::getT::Request  &req, dynamics::getT::Response &res, Robot*& robot) { // serviceRobot
    auto q = robot->dynamics->getPosition();
    auto qtmp = robot->dynamics->getPosition();
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
bool getG(dynamics::getG::Request  &req, dynamics::getG::Response &res, Robot*& robot) { // serviceRobot
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
    std::cout<< g <<std::endl;
    return true;
}
bool getJ(dynamics::getJ::Request  &req, dynamics::getJ::Response &res, Robot*& robot) { // serviceRobot
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
    std::cout<< J <<std::endl;
    return true;
}

bool getStaticTorques(dynamics::getStaticTorques::Request  &req, dynamics::getStaticTorques::Response &res, Robot*& robot){ // serviceRobot
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

void updateOpPosition(const std_msgs::Float32MultiArray::ConstPtr& msg,std::vector<std_msgs::Float32MultiArray*> opPostionMsgs, Robot*& robot){ //subpub
    std::vector<float> data = msg->data;
    auto q = robot->floatVec2MathVec(data);
    for (int i=0;i<data.size();i++) {
        q[i] = data[i];
    }
    opPostionMsgs[0]->data = robot->getOperationalPosition(0);
    opPostionMsgs[1]->data = robot->getOperationalPosition(1);
}
std::vector<std::string> names = {"yumi_joint_1_r", "yumi_joint_2_r", "yumi_joint_7_r", "yumi_joint_3_r", "yumi_joint_4_r", "yumi_joint_5_r", "yumi_joint_6_r", "yumi_joint_1_l", "yumi_joint_2_l", "yumi_joint_7_l", "yumi_joint_3_l","yumi_joint_4_l", "yumi_joint_5_l", "yumi_joint_6_l"};
void rvizUpdateJoints(const std_msgs::Float32MultiArray::ConstPtr& msg,sensor_msgs::JointState* rvizMsgs){ //subpub
    std::vector<double> tmp;
    for (int i=0;i<msg->data.size();i++) {
        double val = msg->data[i];
        tmp.push_back(val);
    }
    rvizMsgs->position=tmp;
    rvizMsgs->name = names;
    rvizMsgs->header.stamp = ros::Time::now();
}
void updateJoints(const std_msgs::Float32MultiArray::ConstPtr& msg, Robot*& robot ){ //subpub
    std::vector<double> tmp;
    auto q = robot->floatVec2MathVec(msg->data);
    robot->dynamics->setPosition(q);
}
void updateJointsVel(const std_msgs::Float32MultiArray::ConstPtr& msg, Robot*& robot ){ //subpub
    std::vector<double> tmp;
    auto q = robot->floatVec2MathVec(msg->data);
    robot->dynamics->setVelocity(q);
}
bool getTrajTorques(dynamics::getTrajTorques::Request  &req, dynamics::getTrajTorques::Response &res,Robot*& robot){ // serviceRobot
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
    //for (int i = req.q.size();i<q.size();i++){
     //   q[i]=0;
     //   qd[i]=0;
     //   qdd[i]=0;
    //}
    robot->dynamics->setPosition(q);
    robot->dynamics->setVelocity(qd);
    rl::math::Vector V = robot->getCentrifugalCoriolis();
    robot->dynamics->setAcceleration(qdd);
    robot->dynamics->forwardPosition();
    robot->dynamics->forwardVelocity();
    robot->dynamics->inverseDynamics();
    //robot->dynamics->forwardDynamics();
    rl::math::Matrix J = robot->getJacobian();
    auto tau = robot->dynamics->getTorque();
    tau-=((J.transpose())*Fext);
    std::cout<< J<<std::endl;

    //auto Tauext = Jinv*Fext;
    //for (int i=0;i<Tauext.size();i++){
    //    tau[i]+=Tauext[i];
    //}
            //auto g = robot->getGravity();
    //auto Ma = robot->getMassMatrix();

    //std::cout<< tau<<std::endl;
    //std::cout<< g<<std::endl;
    //std::cout<< V+Ma+g<<std::endl;
    //std::cout<< V+g+Ma*qdd<<std::endl;
    //std::cout<< Ma<<std::endl;
    //std::cout<< qd<<std::endl;
    //std::cout<< Ma<<std::endl;
    //tau=tau-g;
    //res.Tau=req.q;
    for (int i=0;i<req.q.size();i++) {
        //res.Tau[i] = tau[i];
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
rl::math::Vector3 cross(rl::math::Vector3 a,rl::math::Vector3 b){
    rl::math::Vector3 r =rl::math::Vector3::Zero();
    r[0] = a[1]*b[2]-a[2]*b[1];
    r[1] = a[2]*b[0]-a[0]*b[2];
    r[2] = a[0]*b[1]-a[1]*b[0];
    return r;
}
bool setArmVelocity(dynamics::setTorques::Request  &req, dynamics::setTorques::Response &res,Robot*& robot) { // serviceRobot
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
        D << d1, d2;
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
        D << d1, d2;
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
        ///std::cout<<e1.norm()+e2.norm()<<std::endl;
    }
    while(e1.norm()+e2.norm()>0.005);

    auto tau = robot->dynamics->getPosition();
    for (int i = 0; i < tau.size(); i++) {
        res.qdd.push_back(tau[i]);
    }
    return true;
}


int main(int argc, char *argv[]) {
    ros::init(argc, argv, "sim_robot_node");
    ros::NodeHandle n;
    Robot* robot =new Robot("yumi");
    auto q = robot->dynamics->getPosition();
    robot->dynamics->setWorldGravity(0,0,1);
    q[0] = (46.0/180.0)*3.14;
    q[1] = (-121.0/180.0)*3.14;
    q[2] = (-87.0/180.0)*3.14;
    q[3] = (4.0/180.0)*3.14;
    q[4] = (44.0/180.0)*3.14;
    q[5] = (54.0/180.0)*3.14;
    q[6] = (-3.0/180.0)*3.14;
    robot->dynamics->setPosition(q);

    auto getTrajTorquesCallback = robot->getServiceCallBackRobot(getTrajTorques,robot);
    ros::ServiceServer getTrajTorqueService = n.advertiseService("getTrajTorques", getTrajTorquesCallback);

    auto setArmVelocityCallback = robot->getServiceCallBackRobot(setArmVelocity,robot);
    ros::ServiceServer setArmVelocityService = n.advertiseService("setArmVelocities", setArmVelocityCallback);

    auto addMCallback = robot->getServiceCallBackRobot(addMass,robot);
    ros::ServiceServer addMService = n.advertiseService("addM", addMCallback);

    auto getMCallback = robot->getServiceCallBackRobot(getM,robot);
    ros::ServiceServer getMService = n.advertiseService("getM", getMCallback);

    auto getJCallback = robot->getServiceCallBackRobot(getJ,robot);
    ros::ServiceServer getJService = n.advertiseService("getJ", getJCallback);

    auto getCCallback = robot->getServiceCallBackRobot(getC,robot);
    ros::ServiceServer getCService = n.advertiseService("getC", getCCallback);

    auto getTCallback = robot->getServiceCallBackRobot(getT,robot);
    ros::ServiceServer getTService = n.advertiseService("getT", getTCallback);

    auto getGCallback = robot->getServiceCallBackRobot(getG,robot);
    ros::ServiceServer getGService = n.advertiseService("getG", getGCallback);


    ros::Publisher operationalPosPubL = n.advertise<std_msgs::Float32MultiArray>("operational_position_L",1);
    ros::Publisher operationalPosPubR = n.advertise<std_msgs::Float32MultiArray>("operational_position_R",1);
    auto operationalPosPubLMsg = new std_msgs::Float32MultiArray();
    auto operationalPosPubRMsg = new std_msgs::Float32MultiArray();
    robot->addPublisherPair(operationalPosPubR,operationalPosPubRMsg);
    robot->addPublisherPair(operationalPosPubL,operationalPosPubLMsg);

    std::vector<std_msgs::Float32MultiArray*> msgs;msgs.push_back(operationalPosPubRMsg);msgs.push_back(operationalPosPubLMsg);
    auto updateOpPositionCallback = robot->getSubscriberCallBackPublishersRobot(updateOpPosition,msgs,robot);
    ros::Subscriber jointStateSubscriber = n.subscribe("joint_states",1,updateOpPositionCallback);

    auto updateJointsCallback = robot->getSubscriberCallBackRobot(updateJoints,robot);
    ros::Subscriber updateJointsSubscriber = n.subscribe("joint_states",1,updateJointsCallback);

    auto updateJointsVelCallback = robot->getSubscriberCallBackRobot(updateJointsVel,robot);
    ros::Subscriber updateJointsVelSubscriber = n.subscribe("joint_states_vel",1,updateJointsVelCallback);

    ros::Publisher jointRvizPub = n.advertise<sensor_msgs::JointState>("rviz/joint_states",1);
    sensor_msgs::JointState* jointRvizMsg = new sensor_msgs::JointState();
    robot->addPublisherPair(jointRvizPub,jointRvizMsg);
    auto rvizUpdateJointsCallback = robot->getSubscriberCallBackPublisher(rvizUpdateJoints,jointRvizMsg);
    ros::Subscriber jointStateSubscriberrviz = n.subscribe("joint_states",1,rvizUpdateJointsCallback);

    ros::Publisher jointStatePub = n.advertise<std_msgs::Float32MultiArray>("joint_states",1);
    std_msgs::Float32MultiArray* jointStateMsg = new std_msgs::Float32MultiArray();
    robot->addPublisherPair(jointStatePub,jointStateMsg);


    ros::Rate loop_rate(200);
    auto tau0 = rl::math::Vector::Zero(14);
    robot->dynamics->setTorque(tau0);
    float realTimeFactor = .5;
    while (ros::ok()) {
        //auto t1 = Clock::now();
        jointStateMsg->data = robot->getPosition();
        robot->publishAll();
        ros::spinOnce();
        robot->step(1/(200.0)*realTimeFactor,5);
        loop_rate.sleep();
        //auto t2 = Clock::now();
       // std::cout << "Delta t2-t1: "
         //         << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()
          //        << " microseconds" << std::endl;
    }
    return 0;
}
