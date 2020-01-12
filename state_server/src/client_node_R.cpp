#include <iostream>
#include <boost/asio.hpp>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float32.h>
#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
#include "vector"
#include "string"
#include <math.h>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

struct ROS_msg_header{
    int msg_type;
};

struct ROS_msg{
    ROS_msg_header header;
    unsigned char data[];
};

struct ROS_msg_joint_data{
    int msg_type;
    float joints[7];
};

struct ROS_msg_gripper_position{
    int msg_type;
    float position;
};

struct ROS_msg_gripper_force{
    int msg_type;
    float force;
};

struct ROS_msgs{
    int msgType;
    ROS_msg_joint_data joint_position_msg;
    ROS_msg_gripper_position gripper_position_msg;
    ROS_msg_gripper_force gripper_force_msg;
    ROS_msg_joint_data joint_torque_msg;
};

int main(int argc, char **argv) {
    boost::asio::io_service io_service;
//socket creation
    tcp::socket socket(io_service);
//connection
    std::string IP = argv[1];
    //std::string IP = "192.168.1.13";
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(IP), 11002));
    ros::init(argc, argv, "state_server_R");
    ros::NodeHandle n;
    ros::Publisher pub_joints = n.advertise<std_msgs::Float32MultiArray>("joint_state_R", 1);
    ros::Publisher pub_torques = n.advertise<std_msgs::Float32MultiArray>("joint_torque_R", 1);
    ros::Publisher pub_gripper_pos = n.advertise<std_msgs::Float32>("gripper_state_R", 1);
    //ros::Publisher pub_gripper_force = n.advertise<std_msgs::Float32>("gripper_froce_L", 1);
    ros::Rate loop_rate(100);
    boost::asio::streambuf receive_buffer;
    boost::system::error_code error;
    while (ros::ok()){
        std_msgs::Float32MultiArray msg_joints;
        std_msgs::Float32MultiArray msg_torque;
        std_msgs::Float32 msg_gripper_pos;
        std_msgs::Float32 msg_gripper_force;
        int msg_size = 21*4;
        boost::asio::read(socket, receive_buffer,boost::asio::transfer_exactly(msg_size), error);
        if( error && error != boost::asio::error::eof ) {
            cout << "receive failed: " << error.message() << endl;
        }else {
            ROS_msgs const* data = boost::asio::buffer_cast<ROS_msgs const*>(receive_buffer.data());
            std::copy(data->joint_position_msg.joints, data->joint_position_msg.joints + 7, std::back_inserter(msg_joints.data));
            for (int i =0;i<7;i++){
                msg_joints.data[i]*=(M_PI/180.0);
            }
            std::copy(data->joint_torque_msg.joints, data->joint_torque_msg.joints + 7, std::back_inserter(msg_torque.data));
            msg_gripper_pos.data = data->gripper_position_msg.position;
            msg_gripper_force.data = data->gripper_force_msg.force;

        }
        pub_joints.publish(msg_joints);
        //pub_torques.publish(msg_torque);
        //pub_gripper_pos.publish(msg_gripper_pos);
        //pub_gripper_force.publish(msg_gripper_force);
        receive_buffer.consume(msg_size*10);
        //ros::spinOnce();
        //loop_rate.sleep();
    }
    socket.close();
    return 0;
}
