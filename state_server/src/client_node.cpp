#include <iostream>
#include <boost/asio.hpp>
#include <sensor_msgs/JointState.h>
#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
#include "vector"
#include "string"

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
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(IP), 11002));
    ros::init(argc, argv, "state_server");
    ros::NodeHandle n;
    ros::Publisher SS_pub_L = n.advertise<std_msgs::Float32MultiArray>("joint_state_L", 1);
    ros::Publisher SS_pub_R = n.advertise<std_msgs::Float32MultiArray>("joint_state_R", 1);
    ros::Publisher SS_pub_LR = n.advertise<std_msgs::Float32MultiArray>("joint_states", 1);
    ros::Rate loop_rate(100);
    boost::asio::streambuf receive_buffer;
    boost::system::error_code error;
    while (ros::ok()){
        std_msgs::Float32MultiArray msg_L;
        std_msgs::Float32MultiArray msg_R;
        std_msgs::Float32MultiArray msg_LR;
        std::vector<float> tmpData_L;
        std::vector<float> tmpData_R;
        boost::asio::read(socket, receive_buffer,boost::asio::transfer_exactly(84), error);
        if( error && error != boost::asio::error::eof ) {
            cout << "receive failed: " << error.message() << endl;
        }else {
            float const* data = boost::asio::buffer_cast<float const*>(receive_buffer.data());
        for (int i=1;i<60/4;i++){
            if (i<=30/4){
               tmpData_L.push_back(data[i]);
            } else{
               tmpData_R.push_back(data[i]);
            }
            }

        float temp1 = tmpData_L[6];
        float temp2 = tmpData_R[6];
        for (int i =6;i>2;i--){
            tmpData_L[i]=tmpData_L[i-1];
            tmpData_R[i]=tmpData_R[i-1];
        }
        receive_buffer.consume(84);
        tmpData_L[2] = temp1;
        tmpData_R[2] = temp2;
        std::vector<float> tmpData_LR;
        std::copy(tmpData_R.begin(),tmpData_R.end(),std::back_inserter(tmpData_LR));
        tmpData_LR.insert( tmpData_LR.end(), tmpData_L.begin(), tmpData_L.end());
        msg_L.data = tmpData_L;
        msg_R.data = tmpData_R;
        msg_LR.data = tmpData_LR;

        }
        SS_pub_L.publish(msg_L);
        SS_pub_R.publish(msg_R);
        SS_pub_LR.publish(msg_LR);
        ros::spinOnce();
        loop_rate.sleep();
    }
    socket.close();
    return 0;
}
