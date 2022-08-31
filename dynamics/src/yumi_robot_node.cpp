//
// Created by paul on 7/26/19.
//

#include "rclcpp/rclcpp.hpp"
#include "Yumi.h"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "sensor_msgs/msg/JointState.h"
#include "RobotFactory.h"
#include "ROSProvider.h"

void simulateYumi(Yumi* yumi, double dt){
    auto [jointStatePub_L, jointStateMsg_L] = ROSProvider::getPublisher<sensor_msgs::JointState>("/joint_state_L");
    auto [jointStatePub_R, jointStateMsg_R] = ROSProvider::getPublisher<sensor_msgs::JointState>("/joint_state_R");
    auto [jointStatesPub, jointStatesMsg] = ROSProvider::getPublisher<sensor_msgs::JointState>("/joint_states");

    auto q = yumi->dynamics->getPosition();
    auto qd = yumi->dynamics->getVelocity();
//    for (int i =0 ; i < q.size(); i++){
//        if (qd[i] == 1.0)
//            qd[i] = 0;
//    }
    q += qd*dt;
    ROSProvider::setTimeStampNow(jointStatesMsg);
    ROSProvider::setTimeStampNow(jointStateMsg_L);
    ROSProvider::setTimeStampNow(jointStateMsg_R);
    for (int i =0 ; i < q.size(); i++){
        jointStatesMsg.position.push_back(q[i]);
        jointStatesMsg.name.push_back(yumi->jointNames[i]);
        if (yumi->jointNames[i].find("_l") != string::npos){
            jointStateMsg_L.position.push_back(q[i]);
            jointStateMsg_L.name.push_back(yumi->jointNames[i]);
        }
        if (yumi->jointNames[i].find("_r") != string::npos){
            jointStateMsg_R.position.push_back(q[i]);
            jointStateMsg_R.name.push_back(yumi->jointNames[i]);
        }
    }
    yumi->dynamics->setPosition(q);
    yumi->dynamics->setVelocity(qd);
    yumi->dynamics->forwardPosition();
    yumi->dynamics->forwardVelocity();
    jointStatesPub.publish(jointStatesMsg);
    jointStatePub_L.publish(jointStateMsg_L);
    jointStatePub_R.publish(jointStateMsg_R);

}


int main(int argc, char *argv[]) {
    std::string useSim = argv[1];
    ros::init(argc, argv, "yumi_node");
    ros::NodeHandle n;
    ROSProvider::init(&n);
    auto yumi = RobotFactory::getRobot<Yumi>();
    // update joints
//    auto [jointRvizPub, jointRvizMsg] = ROSProvider::getPublisher<sensor_msgs::JointState>("rviz/joint_states");
//    auto jointStateSubscriberrviz = ROSProvider::getSubscriber("/joint_states", Yumi::rvizUpdateJoints, "1");
    // operational position
    auto [operationalPosPub_L, operationalPosPubMsg_L] = ROSProvider::getPublisher<std_msgs::Float32MultiArray>("/operational_position_L");
    auto [operationalPosPub_R, operationalPosPubMsg_R] = ROSProvider::getPublisher<std_msgs::Float32MultiArray>("/operational_position_R");
    // operational velocity
    auto [jointVelPub_L, jointVelPubMsg_L] = ROSProvider::getPublisher<std_msgs::Float32MultiArray>("/joint_velocity_command_L");
    auto [jointVelPub_R, jointVelPubMsg_R] = ROSProvider::getPublisher<std_msgs::Float32MultiArray>("/joint_velocity_command_R");
    auto operationalVelSubscriber_L = ROSProvider::getSubscriber("/operational_velocity_command_L", Yumi::sendOpJointVelocities_L);
    auto operationalVelSubscriber_R = ROSProvider::getSubscriber("/operational_velocity_command_R", Yumi::sendOpJointVelocities_R);
    auto operationalPosSubscriber_L = ROSProvider::getSubscriber("/joint_state_L", Yumi::updateOperationalPos_L, "0");
    auto operationalPosSubscriber_R = ROSProvider::getSubscriber("/joint_state_R", Yumi::updateOperationalPos_R, "0");
    int rate = 100.0;
    double dt = 1.0/rate;
    ros::Rate loop_rate(rate);
    bool use_sim = useSim != "false";
    // simulated
    if (use_sim){
//        yumi->dynamics->setWorldGravity(0,0,0);
        ROSProvider::getSubscriber("/joint_velocity_command_R", Yumi::updateJointVels_R, "0");
        ROSProvider::getSubscriber("/joint_velocity_command_L", Yumi::updateJointVels_L, "0");
        while (ros::ok())
        {
            simulateYumi(yumi, dt);
            ros::spinOnce();
            loop_rate.sleep();
        }

    } else{
        auto jointStateSubscriber = ROSProvider::getSubscriber("/joint_states", Yumi::updateJoints, "0");
        while (ros::ok())
        {
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

    return 0;
}
