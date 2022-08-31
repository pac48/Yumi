#include <sensor_msgs/msg/joint_state.hpp>
#include "rclcpp/rclcpp.hpp"
#include "Messenger.h"

class MessageHandler{
public:
    sensor_msgs::JointState joint_L;
    sensor_msgs::JointState joint_R;
    ros::Subscriber sub_joint_state_L;
    ros::Subscriber sub_joint_state_R;

    MessageHandler(ros::NodeHandle& n){
        sub_joint_state_R = n.subscribe("joint_state_R", 1, &MessageHandler::callback_R, this);
        sub_joint_state_L = n.subscribe("joint_state_L", 1, &MessageHandler::callback_L, this);
    };

    void callback_L(const sensor_msgs::JointState::ConstPtr &msg){
        joint_L.effort = msg->effort;
        joint_L.name = msg->name;
        joint_L.position = msg->position;
        joint_L.velocity = msg->velocity;
        joint_L.header = msg->header;
    }

    void callback_R(const sensor_msgs::JointState::ConstPtr &msg){
        joint_R.effort = msg->effort;
        joint_R.name = msg->name;
        joint_R.position = msg->position;
        joint_R.velocity = msg->velocity;
        joint_R.header = msg->header;
    }

};


int main(int argc, char **argv) {
    /*std::vector<std::string> jointNames = {
            "yumi_joint_1_r",
            "yumi_joint_2_r",
            "yumi_joint_3_r",
            "yumi_joint_4_r",
            "yumi_joint_5_r",
            "yumi_joint_6_r",
            "yumi_joint_7_r",
            "gripper_r_joint",
            "yumi_joint_1_l",
            "yumi_joint_2_l",
            "yumi_joint_3_l",
            "yumi_joint_4_l",
            "yumi_joint_5_l",
            "yumi_joint_6_l",
            "yumi_joint_7_l",
            "gripper_l_joint"};
            */
    ros::init(argc, argv, "state_server");
    ros::NodeHandle n;
    MessageHandler messageHandler = MessageHandler(n);
    ros::Publisher pub_joints = n.advertise<sensor_msgs::JointState>("joint_states", 1);
    while (ros::ok()) {
        sensor_msgs::JointState msg_joints;
        if (!messageHandler.joint_L.name.empty() && !messageHandler.joint_R.name.empty() ){
            msg_joints.header = messageHandler.joint_R.header;
            msg_joints.velocity = messageHandler.joint_R.velocity;
            msg_joints.position = messageHandler.joint_R.position;
            msg_joints.effort = messageHandler.joint_R.effort;
            msg_joints.name = messageHandler.joint_R.name;

            msg_joints.name.insert(msg_joints.name.end(), messageHandler.joint_L.name.begin(), messageHandler.joint_L.name.end());
            msg_joints.velocity.insert(msg_joints.velocity.end(), messageHandler.joint_L.velocity.begin(), messageHandler.joint_L.velocity.end());
            msg_joints.position.insert(msg_joints.position.end(), messageHandler.joint_L.position.begin(), messageHandler.joint_L.position.end());
            msg_joints.effort.insert(msg_joints.effort.end(), messageHandler.joint_L.effort.begin(), messageHandler.joint_L.effort.end());

            pub_joints.publish(msg_joints);
            messageHandler.joint_R = sensor_msgs::JointState();
            messageHandler.joint_L = sensor_msgs::JointState();
        }

        ros::spinOnce();

    }

    return 0;
}
