//
// Created by paul on 10/20/21.
//
#pragma once
namespace yumi_packets {

    struct ROS_msg_header {
        int msg_type;
    };

    struct ROS_msg {
        ROS_msg_header header;
        unsigned char data[];
    };

    struct ROS_msg_joint_data {
        int msg_type = 1;
        float joints[7];
    };

    struct ROS_msg_gripper_position {
        int msg_type = 2;
        float position;
//    int endType;
    };

    struct ROS_msg_gripper_force {
        int msg_type = 3;
        float force;
    };

    struct ROS_msgs {
        int msgType;
        ROS_msg_joint_data joint_position_msg;
        ROS_msg_gripper_position gripper_position_msg;
        ROS_msg_gripper_force gripper_force_msg;
        ROS_msg_joint_data joint_torque_msg;
    };


}
