//
// Created by paul on 7/26/19.
//
#include <iostream>
#include "ros/ros.h"
#include "simulator/getStaticTorques.h"
#include "std_msgs/Float32MultiArray.h"
#include "Robot.h"

bool getStaticTorques(simulator::getStaticTorques::Request  &req, simulator::getStaticTorques::Response &res,Robot* robot){ // serviceRobot
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



void updateJoints(const std_msgs::Float32MultiArray::ConstPtr& msg,std::vector<std_msgs::Float32MultiArray*> opPostionMsgs, Robot* robot){ //subpub
    std::vector<float> data = msg->data;
    auto q = robot->floatVec2MathVec(data);
    for (int i=0;i<data.size();i++) {
        q[i] = data[i];
    }
    robot->dynamics->setPosition(q);
    robot->dynamics->forwardPosition();
    opPostionMsgs[0]->data = robot->getOperationalPosition(0);
    opPostionMsgs[1]->data = robot->getOperationalPosition(1);
    //robot->publishOne(opPostionMsgs[0]);
    //robot->publishOne(opPostionMsgs[1]);
}

void sendOpJointVelocities(const std_msgs::Float32MultiArray::ConstPtr& opVelMsg,std::vector<std_msgs::Float32MultiArray*> jointVelMsgs,Robot* robot){ //subpub
    std::vector<float> opvelL;
    std::vector<float> opvelR;
    for (int i=0;i<6;i++){
        opvelR.push_back(opVelMsg->data[i]);
        opvelL.push_back(opVelMsg->data[i+6]);
    }
    jointVelMsgs[0]->data = robot->xd2jd(0,opvelR);
    jointVelMsgs[1]->data = robot->xd2jd(1,opvelL);
    //robot->publishOne(jointVelMsgs[0]);
    //robot->publishOne(jointVelMsgs[1]);
}


int main(int argc, char *argv[]) {
    ros::init(argc, argv, "dynamics_node");
    ros::NodeHandle n;
    Robot* robot =new Robot("yumi");
    auto StaticTorquesCallback = robot->getServiceCallBackRobot(getStaticTorques,robot);
    ros::ServiceServer getStaticJointTorqueService = n.advertiseService("getStaticJointTorques", StaticTorquesCallback);
    ros::Publisher operationalPosPubL = n.advertise<std_msgs::Float32MultiArray>("operational_position_L",1);
    ros::Publisher operationalPosPubR = n.advertise<std_msgs::Float32MultiArray>("operational_position_R",1);
    auto operationalPosPubLMsg = new std_msgs::Float32MultiArray();
    auto operationalPosPubRMsg = new std_msgs::Float32MultiArray();
    robot->addPublisherPair(operationalPosPubR,operationalPosPubRMsg);
    robot->addPublisherPair(operationalPosPubL,operationalPosPubLMsg);
    std::vector<std_msgs::Float32MultiArray*> msgs;msgs.push_back(operationalPosPubRMsg);msgs.push_back(operationalPosPubLMsg);
    auto updateJointsCallback = robot->getSubscriberCallBackPublishersRobot(updateJoints,msgs,robot);
    ros::Subscriber jointStateSubscriber = n.subscribe("joint_states",1,updateJointsCallback);
    ros::Publisher jointVelPubL = n.advertise<std_msgs::Float32MultiArray>("joint_velocity_command_L",1);
    ros::Publisher jointVelPubR = n.advertise<std_msgs::Float32MultiArray>("joint_velocity_command_R",1);
    auto jointVelPubRMsg = new std_msgs::Float32MultiArray();
    auto jointVelPubLMsg = new std_msgs::Float32MultiArray();
    robot->addPublisherPair(jointVelPubR,jointVelPubRMsg);
    robot->addPublisherPair(jointVelPubL,jointVelPubLMsg);
    std::vector<std_msgs::Float32MultiArray*> msgs2;msgs2.push_back(jointVelPubRMsg);msgs2.push_back(jointVelPubLMsg);
    auto sendJointVelCallback = robot->getSubscriberCallBackPublishersRobot(sendOpJointVelocities,msgs2,robot);
    ros::Subscriber operationalVelocityCommandSubscriber = n.subscribe("operational_velocity_command",1,sendJointVelCallback);
    ros::Rate loop_rate(250);
    while (ros::ok()) {
        robot->publishAll();
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
