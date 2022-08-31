#include <iostream>
#include <boost/asio.hpp>
#include <std_msgs/msg/float32.hpp>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "vector"
#include "string"
#include "Messenger.h"
#include "ABBMessages.h"

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;


int main(int argc, char **argv) {
    boost::asio::io_service io_service;
//socket creation
    tcp::socket socket(io_service);
//connection
    std::string IP = argv[1];
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(IP), 11000));
    ros::init(argc, argv, "motion_server_R");
    ros::NodeHandle n;
    Messenger<float , const std_msgs::Float32::ConstPtr> messenger{};
    ros::Subscriber sub_grippe = n.subscribe("gripper_command_R",1,&Messenger<float , const std_msgs::Float32::ConstPtr>::callback, &messenger);
    ros::Rate loop_rate(10);
    boost::asio::streambuf receive_buffer;
    boost::system::error_code error;
    boost::array<ROS_msg_gripper_force , 1> buf = boost::array<ROS_msg_gripper_force , 1>();
    float old_data = messenger.data;
    while (ros::ok()) {
        ros::spinOnce();
        if (old_data != messenger.data){
            ROS_msg_gripper_force msgs;
            msgs.force = messenger.data;
            buf.assign(msgs);
            socket.write_some(boost::asio::buffer(&buf, 8), error);
            old_data = messenger.data;
    }
        loop_rate.sleep();
    }
    socket.close();
    return 0;
}
