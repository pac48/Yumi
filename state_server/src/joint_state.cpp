#include <iostream>
#include <boost/asio.hpp>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float32.h>
#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
#include "vector"
#include "string"
#include "Messenger.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "state_server");
    ros::NodeHandle n;
    Messenger<std::vector<float> , const std_msgs::Float32MultiArray::ConstPtr> messenger_R;
    ros::Subscriber sub_joint_state_R = n.subscribe("joint_state_R",5,&Messenger<std::vector<float> , const std_msgs::Float32MultiArray::ConstPtr>::callback, &messenger_R);
    Messenger<std::vector<float> , const std_msgs::Float32MultiArray::ConstPtr> messenger_L;
    ros::Subscriber sub_joint_state_L= n.subscribe("joint_state_L",5,&Messenger<std::vector<float> , const std_msgs::Float32MultiArray::ConstPtr>::callback, &messenger_L);
    ros::Publisher pub_joints = n.advertise<std_msgs::Float32MultiArray>("joint_states", 1);
    ros::Rate loop_rate(100);
    while (ros::ok()) {
        std_msgs::Float32MultiArray msg_joints;
        ros::spinOnce();
        if (messenger_R.data.size()==0 || messenger_L.data.size()==0)
            continue;
        for (int i=0;i<7;i++){
            msg_joints.data.push_back(messenger_R.data[i]);
        }
        for (int i=0;i<7;i++){
            msg_joints.data.push_back(messenger_L.data[i]);
        }
        //std::copy(messenger_R.data, messenger_R.data + 7, std::back_inserter(msg_joints.data));
        //std::copy(messenger_L.data, messenger_L.data + 7, std::back_inserter(msg_joints.data));
        pub_joints.publish(msg_joints);
        loop_rate.sleep();
    }
}
