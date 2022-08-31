/***********************************************************************************************************************
 *
 * Copyright (c) 2018, ABB Schweiz AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with
 * or without modification, are permitted provided that
 * the following conditions are met:
 *
 *    * Redistributions of source code must retain the
 *      above copyright notice, this list of conditions
 *      and the following disclaimer.
 *    * Redistributions in binary form must reproduce the
 *      above copyright notice, this list of conditions
 *      and the following disclaimer in the documentation
 *      and/or other materials provided with the
 *      distribution.
 *    * Neither the name of ABB nor the names of its
 *      contributors may be used to endorse or promote
 *      products derived from this software without
 *      specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ***********************************************************************************************************************
 */

#include <ros/ros.h>
#include "std_msgs/Float32MultiArray.h"
#include <abb_libegm/egm_controller_interface.h>
#include "Messenger.h"
#include "stdlib.h"
#include <string>
#include <std_msgs/Float64.h>

#define _USE_MATH_DEFINES



int main(int argc, char** argv)
{
  //----------------------------------------------------------
  // Preparations
  //----------------------------------------------------------
  // Initialize the node.
  std::string LR = argv[1];

  std::string velocityTopicNames[] = {

            "/yumi/joint_1_r_velocity_controller/command",
            "/yumi/joint_2_r_velocity_controller/command",
            "/yumi/joint_7_r_velocity_controller/command",
            "/yumi/joint_3_r_velocity_controller/command",
            "/yumi/joint_4_r_velocity_controller/command",
            "/yumi/joint_5_r_velocity_controller/command",
            "/yumi/joint_6_r_velocity_controller/command"};

  if (LR=="_L"){
      velocityTopicNames[0]="/yumi/joint_1_l_velocity_controller/command";
      velocityTopicNames[1]="/yumi/joint_2_l_velocity_controller/command";
      velocityTopicNames[2]="/yumi/joint_7_l_velocity_controller/command";
      velocityTopicNames[3]="/yumi/joint_3_l_velocity_controller/command";
      velocityTopicNames[4]="/yumi/joint_4_l_velocity_controller/command";
      velocityTopicNames[5]= "/yumi/joint_5_l_velocity_controller/command";
      velocityTopicNames[6]= "/yumi/joint_6_l_velocity_controller/command";

  }
  ros::init(argc, argv, "joint_velocity_controller_node"+LR);
  ros::NodeHandle n;
  Messenger<std::vector<float> ,const std_msgs::Float32MultiArray::ConstPtr> messenger;
  ros::Subscriber sub = n.subscribe("joint_velocity_command"+LR,10,&Messenger<std::vector<float> ,const std_msgs::Float32MultiArray::ConstPtr>::callback, &messenger);
    std::vector <ros::Subscriber> velocitySubscribers;
    ros::Subscriber velocitySubscriber;
    const int JOINT_NUMBER=7;
    Messenger<double ,const std_msgs::Float64::ConstPtr> *messengers [JOINT_NUMBER];
    for(int i = 0;i < JOINT_NUMBER;i++){
        Messenger<double ,const std_msgs::Float64::ConstPtr>* mi = new Messenger<double ,const std_msgs::Float64::ConstPtr>;
        messengers[i] = mi;
        velocitySubscriber = n.subscribe(velocityTopicNames[i], 10,&Messenger<double ,const std_msgs::Float64::ConstPtr>::callback,mi);
        velocitySubscribers.push_back(velocitySubscriber);
    }
  // Boost components for managing asynchronous UDP socket(s).
  boost::asio::io_service io_service;
  boost::thread_group thread_group;
  // Create EGM configurations.
  abb::egm::BaseConfiguration configuration;
  configuration.use_velocity_outputs = true;
  int port = atoi(argv[2]);
  abb::egm::EGMControllerInterface egm_interface(io_service, port, configuration);
  if(!egm_interface.isInitialized())
  {
    ROS_ERROR("EGM interface failed to initialize (e.g. due to port already bound)");
    return 0;
  }
  // Spin up a thread to run the io_service.
  thread_group.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));
  ROS_INFO("========== Joint velocity py_controllers (open-loop) sample ==========");
  bool wait = true;
  abb::egm::wrapper::Input input;
  abb::egm::wrapper::Joints initial_velocity;
  abb::egm::wrapper::Joints initial_velocity2;
  int sequence_number = 0;    // [-] (sequence number of a received EGM message).
  abb::egm::wrapper::Output output;
  std::vector<float> reference(7);

  ROS_INFO("1: Wait for an EGM communication session to start...");
  while(ros::ok() && wait)
  {
    if(egm_interface.isConnected())
    {
      if(egm_interface.getStatus().rapid_execution_state() == abb::egm::wrapper::Status_RAPIDExecutionState_RAPID_UNDEFINED)
      {
        ROS_WARN("RAPID execution state is UNDEFINED (might happen first time after py_controllers start/restart). Try to restart the RAPID program.");
      }
      else
      {
        wait = egm_interface.getStatus().rapid_execution_state() != abb::egm::wrapper::Status_RAPIDExecutionState_RAPID_RUNNING;
      }
    }
    ros::Duration(0.5).sleep();
    ROS_WARN("waiting");
  }

  while(ros::ok())
  {
    // Wait for a new EGM message from the EGM client (with a timeout of 500 ms).
    if(egm_interface.waitForMessage(50))
    {
      // Read the message received from the EGM client.
      egm_interface.read(&input);
      sequence_number = input.header().sequence_number();

      if(sequence_number == 0)
      {
        // Reset all references, if it is the first message.
        output.Clear();
        initial_velocity.CopyFrom(input.feedback().robot().joints().velocity());
        output.mutable_robot()->mutable_joints()->mutable_velocity()->CopyFrom(initial_velocity);
        initial_velocity2.CopyFrom(input.feedback().external().joints().velocity());
        output.mutable_external()->mutable_joints()->mutable_velocity()->CopyFrom(initial_velocity2);
      }
      else
      {
        reference = messenger.data;
//        ROS_INFO_STREAM("References: Joint 1 = " << reference[0] << " [rad/s]");
//        ROS_INFO_STREAM(output.mutable_external()->mutable_joints()->mutable_velocity()->values_size());
//        ROS_INFO_STREAM(output.mutable_robot()->mutable_joints()->mutable_velocity()->values_size());
        if(output.mutable_robot()->mutable_joints()->mutable_velocity()->values_size() > 5 &&
            output.mutable_external()->mutable_joints()->mutable_velocity()->values_size() > 0) {
            for (int i = 0; i < 7; i++) {
                double r = reference[i]*180/M_PI;
                if (i < 2) {
                    output.mutable_robot()->mutable_joints()->mutable_velocity()->set_values(i, r);
                } else if (i > 2) {
                    output.mutable_robot()->mutable_joints()->mutable_velocity()->set_values(i - 1, r); \

                } else {
                    output.mutable_external()->mutable_joints()->mutable_velocity()->set_values(0, r);
                }
            }
        }
      }
      // Write references back to the EGM client.
      egm_interface.write(output);
    }
    ros::spinOnce();
  }
  // Perform a clean shutdown.
  io_service.stop();
  thread_group.join_all();
  return 0;
}
