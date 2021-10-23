//
// Created by paul on 1/7/20.
//
#ifndef YUMI_WS_YUMI_H
#define YUMI_WS_YUMI_H

#include <sensor_msgs/JointState.h>
#include <std_msgs/Float32MultiArray.h>
#include "Robot.cpp"
#include "ROSProvider.h"

class Yumi : public Robot
{

public:
    Yumi():Robot("Yumi")  {
        auto q = this->dynamics->getPosition();
        q[0] = (46.0 / 180.0) * 3.14;
        q[1] = (-121.0 / 180.0) * 3.14;
        q[2] = (-87.0 / 180.0) * 3.14;
        q[3] = (4.0 / 180.0) * 3.14;
        q[4] = (44.0 / 180.0) * 3.14;
        q[5] = (54.0 / 180.0) * 3.14;
        q[6] = (-3.0 / 180.0) * 3.14;
        this->dynamics->setPosition(q);
    }
//    std::vector<std::string> jointNames = {"yumi_joint_1_r", "yumi_joint_2_r",
  //                                         "yumi_joint_7_r", "yumi_joint_3_r",
    //                                       "yumi_joint_4_r", "yumi_joint_5_r",
      //                                     "yumi_joint_6_r", "yumi_joint_1_l",
        //                                   "yumi_joint_2_l", "yumi_joint_7_l",
          //                                 "yumi_joint_3_l","yumi_joint_4_l",
            //                               "yumi_joint_5_l", "yumi_joint_6_l"};
    static void updateJoints(const sensor_msgs::JointState::ConstPtr &msg)
    { // set joints to new config from message
        Yumi* robot = RobotFactory::getRobot<Yumi>();
        auto q = robot->dynamics->getPosition();
        for (int i = 0; i < msg->position.size(); i++)
        {
            if (robot->jointNames2Ind.find(msg->name[i]) == robot->jointNames2Ind.end()) continue;
            int ind = robot->jointNames2Ind[msg->name[i]];
            q[ind] = msg->position[i];
        }
        robot->dynamics->setPosition(q);
        robot->dynamics->forwardPosition();
    }

    static void updateOperationalPos_L(const sensor_msgs::JointState::ConstPtr &msg)
    { // set joints to new config from message
        auto [operationalPosPub_L, operationalPosPubMsg_L] = ROSProvider::getPublisher<std_msgs::Float32MultiArray>("/operational_position_L");
        Yumi* robot = RobotFactory::getRobot<Yumi>();
        auto q = robot->dynamics->getPosition();
        for (int i = 0; i < msg->position.size(); i++)
        {
            if (robot->jointNames2Ind.find(msg->name[i]) == robot->jointNames2Ind.end()) continue;
            int ind = robot->jointNames2Ind[msg->name[i]];
            q[ind] = msg->position[i];
        }
        robot->dynamics->setPosition(q);
        robot->dynamics->forwardPosition();
        operationalPosPubMsg_L.data = robot->getOperationalPosition(1);
        operationalPosPub_L.publish(operationalPosPubMsg_L);
    }

    static void updateOperationalPos_R(const sensor_msgs::JointState::ConstPtr &msg)
    { // set joints to new config from message
        auto [operationalPosPub_R, operationalPosPubMsg_R] = ROSProvider::getPublisher<std_msgs::Float32MultiArray>("/operational_position_R");
        Yumi* robot = RobotFactory::getRobot<Yumi>();
        auto q = robot->dynamics->getPosition();
        for (int i = 0; i < msg->position.size(); i++)
        {
            if (robot->jointNames2Ind.find(msg->name[i]) == robot->jointNames2Ind.end()) continue;
            int ind = robot->jointNames2Ind[msg->name[i]];
            q[ind] = msg->position[i];
        }
        robot->dynamics->setPosition(q);
        robot->dynamics->forwardPosition();
        operationalPosPubMsg_R.data = robot->getOperationalPosition(0);
        operationalPosPub_R.publish(operationalPosPubMsg_R);
    }

    static void rvizUpdateJoints(const sensor_msgs::JointState::ConstPtr &msg)
    { //maybe broken
        auto [jointRvizPub, jointRvizMsg] = ROSProvider::getPublisher<sensor_msgs::JointState>("rviz/joint_states");
        jointRvizMsg.position = msg->position;
        jointRvizMsg.name = msg->name;
        ROSProvider::setTimeStampNow(jointRvizMsg);
        jointRvizPub.publish(jointRvizMsg);
    }

    static void sendOpJointVelocities_L(const std_msgs::Float32MultiArray::ConstPtr &opVelMsg)    {
        // send velocity commands given operational velocity command
        auto [jointVelPub_L, jointVelMsg_L] = ROSProvider::getPublisher<std_msgs::Float32MultiArray>("/joint_velocity_command_L");
        Yumi* robot = RobotFactory::getRobot<Yumi>();
        std::vector<float> opvel = opVelMsg->data;
        auto qd = robot->xd2jd(1, robot->floatVec2MathVec(opvel));
        for (int i = 0; i < qd.size(); i++)
        {
            string name = robot->jointNames[i];
          //  if (name== "head_pan" || name == "right_gripper_l_finger_joint" || name == "right_gripper_r_finger_joint")
           //     continue;
           int ind = robot->jointNames2Ind[name];
            jointVelMsg_L.data.push_back(qd[ind]);
        }
        jointVelPub_L.publish(jointVelMsg_L);
    }

    static void sendOpJointVelocities_R(const std_msgs::Float32MultiArray::ConstPtr &opVelMsg)
    { // send velocity commands given operational velocity command
        auto [jointVelPub_R, jointVelMsg_R] = ROSProvider::getPublisher<std_msgs::Float32MultiArray>("/joint_velocity_command_R");
        Yumi* robot = RobotFactory::getRobot<Yumi>();
        std::vector<float> opvel = opVelMsg->data;
        auto qd = robot->xd2jd(0, robot->floatVec2MathVec(opvel));
        for (int i = 0; i < qd.size(); i++)
        {
            string name = robot->jointNames[i];
            //  if (name== "head_pan" || name == "right_gripper_l_finger_joint" || name == "right_gripper_r_finger_joint")
            //     continue;
            int ind = robot->jointNames2Ind[name];
            jointVelMsg_R.data.push_back(qd[ind]);
        }
        jointVelPub_R.publish(jointVelMsg_R);
    }

};


#endif //YUMI_WS_YUMI_H

//#include "callbacks.h"
