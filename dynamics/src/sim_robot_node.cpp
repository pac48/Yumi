//
// Created by paul on 7/26/19.
//
#include "Yumi.h"
#include <iostream>
#include "ros/ros.h"
#include "dynamics/getStaticTorques.h"
#include "dynamics/setTorques.h"
#include "dynamics/getTrajTorques.h"
#include "std_msgs/Float32MultiArray.h"
#include "sensor_msgs/JointState.h"
#include <arpa/nameser.h>
//#include <chrono>
//typedef std::chrono::high_resolution_clock Clock;

int main(int argc, char *argv[]) {
    float realTimeFactor = .1;
    float rate = 200;
    ros::init(argc, argv, "sim_robot_node");
    ros::NodeHandle n;
    ros::Rate loop_rate(rate);
    Yumi* robot = new Yumi();
    // Messages
    sensor_msgs::JointState* jointRvizMsg;
    std_msgs::Float32MultiArray* jointStateMsg;
    std_msgs::Float32MultiArray* jointStateVelMsg;
    std_msgs::Float32MultiArray* operationalPosPubLMsg;
    std_msgs::Float32MultiArray* operationalPosPubRMsg;
    std::vector<std_msgs::Float32MultiArray*> opPostionMsgs;
    // Publishers
    jointRvizMsg = robot->addPublisher(n,"rviz/joint_states",1, new sensor_msgs::JointState());
    jointStateMsg = robot->addPublisher(n,"joint_states",1,new std_msgs::Float32MultiArray());
    jointStateVelMsg = robot->addPublisher(n,"joint_states_vel",1,new std_msgs::Float32MultiArray());
    operationalPosPubLMsg = robot->addPublisher(n,"operational_position_L",1, new std_msgs::Float32MultiArray());
    operationalPosPubRMsg = robot->addPublisher(n,"operational_position_R",1, new std_msgs::Float32MultiArray());
    // Services
    robot->addService(n, "getStaticJointTorques", getStaticTorques, (void*&) robot);
    robot->addService(n,"getTrajTorques",getTrajTorques,(void*&) robot);
    robot->addService(n,"setTrajTorques",setTorques,(void*&) robot);
    robot->addService(n,"setArmVelocities",setArmVelocity,(void*&) robot);
    robot->addService(n,"setJointAccelerations",setAccelerations,(void*&) robot);
    // Subscribers
    opPostionMsgs.push_back(operationalPosPubRMsg);
    opPostionMsgs.push_back(operationalPosPubLMsg);
    VectorFloat32MultiArrayRobot* s1 = new VectorFloat32MultiArrayRobot{&opPostionMsgs,robot};
    JointStateRobot* s2 = new JointStateRobot{jointRvizMsg,robot};
    robot->addSubscriber(n,"joint_states",1,updateOpPosition,(void*&) s1);
    robot->addSubscriber(n,"joint_states",1,rvizUpdateJoints,(void*&) s2);
    // Links
    auto s3 = new Float32MultiArrayRobot{jointStateMsg,robot};
    robot->addStepCallback(updateJoints, (void*&) s3);
    auto s4 = new Float32MultiArrayRobot{jointStateVelMsg,robot};
    robot->addStepCallback(updateJointsVel, (void*&) s4);
    // main loop
    while (ros::ok()) {
        robot->publishAll(); //publishers all messages
        ros::spinOnce(); // checks for incoming messages and executes callbacks
        robot->step(1/rate*realTimeFactor,5); // simulate robot forward and updates messages linked to robot
        loop_rate.sleep(); //wait
    }
    return 0;
}
// DEBUG code
//auto t1 = Clock::now();
//auto J =robot->getJacobian();
//std::cout<< J<<std::endl;
//auto t2 = Clock::now();
// std::cout << "Delta t2-t1: "
//         << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()
//        << " microseconds" << std::endl;
