//
// Created by paul on 7/26/19.
//
#include <iostream>
#include "ros/ros.h"
#include "Yumi.h"
#include <iostream>
#include "std_msgs/Float32MultiArray.h"
#include "sensor_msgs/JointState.h"
#include "RobotFactory.h"
#include "ROSProvider.h"

void simulateYumi(Yumi* yumi, ros::Publisher &jointStatePub, sensor_msgs::JointState &jointStateMsg, double dt){
    //  sawyer->step(dt,100);
    auto q = yumi->dynamics->getPosition();
    auto qd = yumi->dynamics->getVelocity();
    if (qd[6] == 1.0)
        qd[6] = 0;
    //cout << qd << endl << endl;
    //qd *= .99;
    q += qd*dt;
    jointStateMsg = sensor_msgs::JointState();
    for (int i =0 ; i < q.size(); i++){
        jointStateMsg.position.push_back(q[i]);
        jointStateMsg.name.push_back(yumi->jointNames[i]);
    }
    yumi->dynamics->setPosition(q);
    // sawyer->dynamics->setVelocity(qd*0);
    yumi->dynamics->forwardPosition();
    //sawyer->dynamics->forwardVelocity();
    jointStatePub.publish(jointStateMsg);

}


int main(int argc, char *argv[]) {
    ros::init(argc, argv, "yumi_node");
    ros::NodeHandle n;
    ROSProvider::init(&n);
    bool use_sim;
    n.param<bool>("/yumi_node/use_simulation", use_sim, false);
    auto yumi = RobotFactory::getRobot<Yumi>();
    // update joints
    auto [jointRvizPub, jointRvizMsg] = ROSProvider::getPublisher<sensor_msgs::JointState>("rviz/joint_states");
    auto jointStateSubscriberrviz = ROSProvider::getSubscriber("/joint_states", Yumi::rvizUpdateJoints, "1");
    // operational position
    auto [operationalPosPub_L, operationalPosPubMsg_L] = ROSProvider::getPublisher<std_msgs::Float32MultiArray>("/operational_position_L");
    auto [operationalPosPub_R, operationalPosPubMsg_R] = ROSProvider::getPublisher<std_msgs::Float32MultiArray>("/operational_position_R");
    auto operationalPosSubscriber_L = ROSProvider::getSubscriber("/joint_states_L", Yumi::updateOperationalPos_L, "0");
    auto operationalPosSubscriber_R = ROSProvider::getSubscriber("/joint_states_R", Yumi::updateOperationalPos_R, "0");
    // operational velocity
    auto [jointVelPub_L, jointVelPubMsg_L] = ROSProvider::getPublisher<std_msgs::Float32MultiArray>("/joint_velocity_command_L");
    auto [jointVelPub_R, jointVelPubMsg_R] = ROSProvider::getPublisher<std_msgs::Float32MultiArray>("/joint_velocity_command_R");
    auto operationalVelSubscriber_L = ROSProvider::getSubscriber("/operational_vel_L", Yumi::sendOpJointVelocities_L);
    auto operationalVelSubscriber_R = ROSProvider::getSubscriber("/operational_vel_R", Yumi::sendOpJointVelocities_R);
    //auto  jointVelSub = ROSProvider::getSubscriber("/joint_velocity_command_L", Yumi::updateVelJoints_L, "0");
    //auto  jointVelSub = ROSProvider::getSubscriber("/joint_velocity_command_R", Yumi::updateVelJoints_R, "0");
    int rate = 100.0;
    double dt = 1.0/rate;
    ros::Rate loop_rate(rate);

    // simulated
    if (use_sim){
        auto [jointStatePub_L, jointStateMsg_L] = ROSProvider::getPublisher<sensor_msgs::JointState>("/joint_states_L");
        auto [jointStatePub_R, jointStateMsg_R] = ROSProvider::getPublisher<sensor_msgs::JointState>("/joint_states_R");
        yumi->dynamics->setWorldGravity(0,0,0);
        while (ros::ok())
        {
            simulateYumi(yumi, jointStatePub_L, jointStateMsg_L, dt);
            ros::spinOnce();
            loop_rate.sleep();
        }

    } else{
        auto jointStateSubscriber_L = ROSProvider::getSubscriber("/joint_states", Yumi::updateJoints, "0");
      //  auto jointStateSubscriber_R = ROSProvider::getSubscriber("/robot/joint_states_R", Yumi::updateJoints_R, "0");
        while (ros::ok())
        {
            ros::spinOnce();
            loop_rate.sleep();
        }

    }

    return 0;
}
