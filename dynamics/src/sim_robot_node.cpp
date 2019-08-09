//
// Created by paul on 7/26/19.
//
#include <iostream>
#include "ros/ros.h"
#include "dynamics/getStaticTorques.h"
#include "dynamics/setTorques.h"
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

void updateKE(const std_msgs::Float32MultiArray::ConstPtr& msg,std_msgs::Float32MultiArray* KEMsg, Robot*& robot){ //subpub
    //KEMsg->data = msg->data
    KEMsg->data = robot->getKE();
}
void updatePE(const std_msgs::Float32MultiArray::ConstPtr& msg,std_msgs::Float32MultiArray* PEMsg, Robot*& robot){ //subpub
    //KEMsg->data = msg->data
    PEMsg->data = robot->getPE();
}

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

    auto StaticTorquesCallback = robot->getServiceCallBackRobot(getStaticTorques,robot);
    ros::ServiceServer getStaticJointTorqueService = n.advertiseService("getStaticJointTorques", StaticTorquesCallback);

    auto setTorquesCallback = robot->getServiceCallBackRobot(setTorques,robot);
    ros::ServiceServer setJointTorqueService = n.advertiseService("setJointTorques", setTorquesCallback);

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

    ros::Rate loop_rate(200);
    auto tau0 = rl::math::Vector::Zero(14);
    robot->dynamics->setTorque(tau0);
    float realTimeFactor = .5;
    while (ros::ok()) {
        //auto t1 = Clock::now();
        jointStateMsg->data = robot->getPosition();
        jointStateVelMsg->data = robot->getVelocity();
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
