#include <iostream>
#include <boost/asio.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <std_msgs/msg/float32.hpp>
#include "rclcpp/rclcpp.hpp"
#include "vector"
#include "string"
#include "ABBMessages.h"

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;


int main(int argc, char **argv) {
    std::vector<string> jointNames = {
            "yumi_joint_1_l",
            "yumi_joint_2_l",
            "yumi_joint_7_l",
            "yumi_joint_3_l",
            "yumi_joint_4_l",
            "yumi_joint_5_l",
            "yumi_joint_6_l",
            "gripper_l_joint" };

    boost::asio::io_service io_service;
//socket creation
    tcp::socket socket(io_service);
//connection
    std::string IP = argv[1];
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(IP), 12002));
    ros::init(argc, argv, "state_server_L");
    ros::NodeHandle n;
    ros::Publisher pub_joints_L = n.advertise<sensor_msgs::JointState>("joint_state_L", 1);
    ros::Rate loop_rate(100);
    boost::asio::streambuf receive_buffer;
    boost::system::error_code error;
    while (ros::ok()){
        std::vector<float> joints_pos;
        std::vector<float> joints_torque;
        float gripper_pos;
        float gripper_force;
        sensor_msgs::JointState msg_joints;
        int msg_size = 21*4;
        boost::asio::read(socket, receive_buffer,boost::asio::transfer_exactly(msg_size), error);
        if( error && error != boost::asio::error::eof ) {
            cout << "receive failed: " << error.message() << endl;
        }else {
            ROS_msgs const* data = boost::asio::buffer_cast<ROS_msgs const*>(receive_buffer.data());
            std::copy(data->joint_position_msg.joints, data->joint_position_msg.joints + 7, std::back_inserter(joints_pos));
            for (int i =0;i<7;i++){
                joints_pos[i]*=(M_PI/180.0);
            }
            std::copy(data->joint_torque_msg.joints, data->joint_torque_msg.joints + 7, std::back_inserter(joints_torque));
            gripper_pos = data->gripper_position_msg.position;
            gripper_force = data->gripper_force_msg.force;
            joints_pos.push_back(gripper_pos);
            joints_torque.push_back(gripper_force);
        }
        for (int i = 0; i < joints_pos.size(); i++){
            msg_joints.name.push_back(jointNames[i]);
            msg_joints.position.push_back(joints_pos[i]);
            msg_joints.effort.push_back(joints_torque[i]);
        }
        auto t = ros::Time::now();
        msg_joints.header.stamp.sec = t.sec;
        msg_joints.header.stamp.nsec = t.nsec;

        pub_joints_L.publish(msg_joints);;
        receive_buffer.consume(msg_size);
    }
    socket.close();
    return 0;
}
