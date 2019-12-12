//
// Created by paul on 7/26/19.
//
#include <iostream>
#include "ros/ros.h"
#include "dynamics/getStaticTorques.h"
#include "dynamics/setTorques.h"
#include "dynamics/getTrajTorques.h"
#include "std_msgs/Float32MultiArray.h"
#include "sensor_msgs/JointState.h"
#include "Robot.h"

#include <iostream>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

bool getStaticTorques(dynamics::getStaticTorques::Request  &req, dynamics::getStaticTorques::Response &res,Robot*& robot){ // serviceRobot
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
bool getTrajTorques(dynamics::getTrajTorques::Request  &req, dynamics::getTrajTorques::Response &res,Robot*& robot){ // serviceRobot
    auto q = robot->dynamics->getPosition();
    auto qd = robot->dynamics->getVelocity();
    auto qdd = robot->dynamics->getAcceleration();
    auto qtmp = robot->dynamics->getPosition();
    auto qdtmp = robot->dynamics->getVelocity();
    auto qddtmp = robot->dynamics->getAcceleration();
    for (int i=0;i<req.q.size();i++){
        q[i]=req.q[i];
        qd[i]=req.qd[i];
        qdd[i]=req.qdd[i];
    }
    robot->dynamics->setPosition(q);
    robot->dynamics->setVelocity(qd);
    robot->dynamics->setAcceleration(qdd);
    robot->dynamics->inverseDynamics();
    auto tau = robot->dynamics->getTorque();
    res.Tau=req.q;
    for (int i=0;i<req.q.size();i++) {
        res.Tau[i] = tau[i];
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
bool setTorques(dynamics::setTorques::Request  &req, dynamics::setTorques::Response &res,Robot*& robot){ // serviceRobot
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
bool setAccelerations(dynamics::setTorques::Request  &req, dynamics::setTorques::Response &res,Robot*& robot){ // serviceRobot
    auto qdd = robot->dynamics->getTorque();
    for (int i=0;i<req.tau.size();i++){
        qdd[i]=req.tau[i];
    }
    robot->dynamics->setAcceleration(qdd);
    robot->dynamics->inverseDynamics();
    auto tau = robot->dynamics->getTorque();
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
/*
void updateKE(const std_msgs::Float32MultiArray::ConstPtr& msg,std_msgs::Float32MultiArray* KEMsg, Robot*& robot){ //subpub
    //KEMsg->data = msg->data
    KEMsg->data[0] = robot->getKE();
}
void updatePE(const std_msgs::Float32MultiArray::ConstPtr& msg,std_msgs::Float32MultiArray* PEMsg, Robot*& robot){ //subpub
    //KEMsg->data = msg->data
    PEMsg->data = robot->getPE();
}
 */

void updateOpPosition(const std_msgs::Float32MultiArray::ConstPtr& msg,std::vector<std_msgs::Float32MultiArray*> opPostionMsgs, Robot*& robot){ //subpub
    std::vector<float> data = msg->data;
    auto q = robot->floatVec2MathVec(data);
    for (int i=0;i<data.size();i++) {
        q[i] = data[i];
    }
    //robot->dynamics->setPosition(q);
    //robot->dynamics->forwardPosition();
    opPostionMsgs[0]->data = robot->getOperationalPosition(0);
    opPostionMsgs[1]->data = robot->getOperationalPosition(1);
    //robot->publishOne(opPostionMsgs[0]);
    //robot->publishOne(opPostionMsgs[1]);
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



int main(int argc, char *argv[]) {
    ros::init(argc, argv, "sim_robot_node");
    ros::NodeHandle n;
    Robot* robot =new Robot("yumi");
    //robot->dynamics->setWorldGravity(0,0,0);
    auto q = robot->dynamics->getPosition();
    q[0] = (46.0/180.0)*3.14;
    q[1] = (-121.0/180.0)*3.14;
    q[2] = (-87.0/180.0)*3.14;
    q[3] = (4.0/180.0)*3.14;
    q[4] = (44.0/180.0)*3.14;
    q[5] = (54.0/180.0)*3.14;
    q[6] = (-3.0/180.0)*3.14;
    robot->dynamics->setPosition(q);

    auto StaticTorquesCallback = robot->getServiceCallBackRobot(getStaticTorques,robot);
    ros::ServiceServer getStaticJointTorqueService = n.advertiseService("getStaticJointTorques", StaticTorquesCallback);

    auto getTrajTorquesCallback = robot->getServiceCallBackRobot(getTrajTorques,robot);
    ros::ServiceServer getTrajTorqueService = n.advertiseService("getTrajTorques", getTrajTorquesCallback);

    auto setTorquesCallback = robot->getServiceCallBackRobot(setTorques,robot);
    ros::ServiceServer setJointTorqueService = n.advertiseService("setJointTorques", setTorquesCallback);

    auto setArmVelocityCallback = robot->getServiceCallBackRobot(setArmVelocity,robot);
    ros::ServiceServer setArmVelocityService = n.advertiseService("setArmVelocities", setArmVelocityCallback);

    auto setAccelerationsCallback = robot->getServiceCallBackRobot(setAccelerations,robot);
    ros::ServiceServer setJointAccelerationService = n.advertiseService("setJointAccelerations", setAccelerationsCallback);

    ros::Publisher operationalPosPubL = n.advertise<std_msgs::Float32MultiArray>("operational_position_L",1);
    ros::Publisher operationalPosPubR = n.advertise<std_msgs::Float32MultiArray>("operational_position_R",1);
    auto operationalPosPubLMsg = new std_msgs::Float32MultiArray();
    auto operationalPosPubRMsg = new std_msgs::Float32MultiArray();
    robot->addPublisherPair(operationalPosPubR,operationalPosPubRMsg);
    robot->addPublisherPair(operationalPosPubL,operationalPosPubLMsg);
    std::vector<std_msgs::Float32MultiArray*> msgs;msgs.push_back(operationalPosPubRMsg);msgs.push_back(operationalPosPubLMsg);
    auto updateOpPositionCallback = robot->getSubscriberCallBackPublishersRobot(updateOpPosition,msgs,robot);
    ros::Subscriber jointStateSubscriber = n.subscribe("joint_states",1,updateOpPositionCallback);


    ros::Publisher jointRvizPub = n.advertise<sensor_msgs::JointState>("rviz/joint_states",1);
    sensor_msgs::JointState* jointRvizMsg = new sensor_msgs::JointState();
    robot->addPublisherPair(jointRvizPub,jointRvizMsg);
    auto rvizUpdateJointsCallback = robot->getSubscriberCallBackPublisher(rvizUpdateJoints,jointRvizMsg);
    ros::Subscriber jointStateSubscriberrviz = n.subscribe("joint_states",1,rvizUpdateJointsCallback);

    ros::Publisher jointStatePub = n.advertise<std_msgs::Float32MultiArray>("joint_states",1);
    std_msgs::Float32MultiArray* jointStateMsg = new std_msgs::Float32MultiArray();
    robot->addPublisherPair(jointStatePub,jointStateMsg);

    ros::Publisher jointStateVelPub = n.advertise<std_msgs::Float32MultiArray>("joint_states_vel",1);
    std_msgs::Float32MultiArray* jointStateVelMsg = new std_msgs::Float32MultiArray();
    robot->addPublisherPair(jointStateVelPub,jointStateVelMsg);
/*
    ros::Publisher KEPub = n.advertise<std_msgs::Float32MultiArray>("kinetic_energy",1);
    auto KEPubMsg = new std_msgs::Float32MultiArray();
    robot->addPublisherPair(KEPub,KEPubMsg);
    auto updateKECallback = robot->getSubscriberCallBackPublisherRobot(updateKE,KEPubMsg,robot);
    ros::Subscriber KESubscriber = n.subscribe("joint_states_vel",1,updateKECallback);

    ros::Publisher PEPub = n.advertise<std_msgs::Float32MultiArray>("potential_energy",1);
    auto PEPubMsg = new std_msgs::Float32MultiArray();
    robot->addPublisherPair(PEPub,PEPubMsg);
    auto updatePECallback = robot->getSubscriberCallBackPublisherRobot(updatePE,PEPubMsg,robot);
    ros::Subscriber PESubscriber = n.subscribe("joint_states",1,updatePECallback);
*/
    ros::Rate loop_rate(200);
    auto tau0 = rl::math::Vector::Zero(14);
    robot->dynamics->setTorque(tau0);
    float realTimeFactor = .01;
    while (ros::ok()) {
        //auto t1 = Clock::now();
        jointStateMsg->data = robot->getPosition();
        jointStateVelMsg->data = robot->getVelocity();
        robot->publishAll();
        ros::spinOnce();
        robot->step(1/(200.0)*realTimeFactor,5);
        loop_rate.sleep();
        auto J =robot->getJacobian();
        std::cout<< J<<std::endl;
        //auto t2 = Clock::now();
       // std::cout << "Delta t2-t1: "
         //         << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()
          //        << " microseconds" << std::endl;
    }
    return 0;
}
