//
// Created by paul on 7/26/19.
//
#include "Yumi.h"
#include <iostream>
#include <arpa/nameser.h>
//#include <chrono>
//typedef std::chrono::high_resolution_clock Clock;

int main(int argc, char *argv[]) {
    float realTimeFactor = 1;
    float rate = 500;
    bool gravity = true;
    ros::init(argc, argv, "sim_robot_node");
    ros::NodeHandle n;
    ros::param::set("/realTimeFactor", realTimeFactor);
    ros::param::set("/rosRate", rate);
    ros::param::set("/gravity", gravity);
    ros::Rate loop_rate(rate);
    Yumi* robot = new Yumi();
    auto q0 = robot->dynamics->getPosition();
    auto qd0 = robot->dynamics->getVelocity();
    // Messages
    sensor_msgs::JointState* jointRvizMsg;
    std_msgs::Float32MultiArray* jointStateMsg;
    std_msgs::Float32MultiArray* jointState_RMsg;
    std_msgs::Float32MultiArray* jointStateVelMsg;
    std_msgs::Float32MultiArray* operationalPosPubLMsg;
    std_msgs::Float32MultiArray* operationalPosPubRMsg;
    std::vector<std_msgs::Float32MultiArray*> opPostionMsgs;
    // Publishers
    jointRvizMsg = robot->addPublisher(n,"rviz/joint_states",1, new sensor_msgs::JointState());
    jointStateMsg = robot->addPublisher(n,"joint_states",1,new std_msgs::Float32MultiArray());
    jointState_RMsg = robot->addPublisher(n,"joint_state_R",1,new std_msgs::Float32MultiArray());
    jointStateVelMsg = robot->addPublisher(n,"joint_states_vel",1,new std_msgs::Float32MultiArray());
    operationalPosPubLMsg = robot->addPublisher(n,"operational_position_L",1, new std_msgs::Float32MultiArray());
    operationalPosPubRMsg = robot->addPublisher(n,"operational_position_R",1, new std_msgs::Float32MultiArray());
    // Services
    robot->addService(n, "getStaticJointTorques", getStaticTorques, (void*&) robot);
    robot->addService(n,"getTrajTorques",getTrajTorques,(void*&) robot);
    robot->addService(n,"setTrajTorques",setTorques,(void*&) robot);
    robot->addService(n,"setArmVelocities",setArmVelocity,(void*&) robot);
    robot->addService(n,"setJointAccelerations",setAccelerations,(void*&) robot);
    robot->addService(n,"getTransformations",getTransformations,(void*&) robot);
    robot->addService(n,"getRigidBodyVelocities",getRigidBodyVelocities,(void*&) robot);
    robot->addService(n,"getLastTransformation",getLastTransformation,(void*&) robot);
    robot->addService(n,"getBlender",getBlender,(void*&) robot);
    robot->addService(n,"getM",getM,(void*&) robot);
    robot->addService(n,"getJ",getJ,(void*&) robot);
    robot->addService(n,"getG",getG,(void*&) robot);
    robot->addService(n,"getC",getC,(void*&) robot);
    robot->addService(n,"getT",getT,(void*&) robot);
    // Subscribers
    JointStateRobot* s2 = new JointStateRobot{jointRvizMsg,robot};
    //robot->addSubscriber(n,"joint_states",1,updateOpPosition,(void*&) s1);
    robot->addSubscriber(n,"joint_states",1,rvizUpdateJoints,(void*&) s2);
    robot->addSubscriber(n,"operational_velocity_command",1,setOpJointVelocities,(void*&) robot);
    // Links
    auto s3 = new Float32MultiArrayRobot{jointStateMsg,robot};
    robot->addStepCallback(updateJoints, (void*&) s3);
    auto s5 = new Float32MultiArrayRobot{jointState_RMsg,robot};
    robot->addStepCallback(updateJoints_R, (void*&) s5);
    auto s4 = new Float32MultiArrayRobot{jointStateVelMsg,robot};
    robot->addStepCallback(updateJointsVel, (void*&) s4);
    opPostionMsgs.push_back(operationalPosPubRMsg);
    opPostionMsgs.push_back(operationalPosPubLMsg);
    VectorFloat32MultiArrayRobot* s1 = new VectorFloat32MultiArrayRobot{&opPostionMsgs,robot};
    robot->addStepCallback(updateOpPos, (void*&) s1);
    // main loop
    while (ros::ok()) {
       // auto qi = robot->getPosition();
      //  for (int i=0;i<qi.size();i++) {
       //     if (std::isnan(qi[i])) {
       //         robot->dynamics->setPosition(q0);
       //         robot->dynamics->setVelocity(qd0);
       //         robot->dynamics->forwardDynamics();
       //         robot->dynamics->update();
       //         robot->dynamics->forwardPosition();
        //        robot->dynamics->forwardVelocity();
       //     }
        //}
       // qi = robot->getPosition();
        robot->step(1/rate*realTimeFactor,1); // simulate robot forward and updates messages linked to robot
       // qi = robot->getPosition();
       // for (int i=0;i<qi.size();i++) {
       //     if (std::isnan(qi[i])) {
        //        robot->dynamics->setPosition(q0);
         //       robot->dynamics->setVelocity(qd0);
         //       robot->dynamics->forwardDynamics();
         //       robot->dynamics->update();
         //       robot->dynamics->forwardPosition();
         //       robot->dynamics->forwardVelocity();
         //   }
       // }
       // qi = robot->getPosition();
        robot->publishAll(); //publishers all messages
       // qi = robot->getPosition();
        ros::spinOnce(); // checks for incoming messages and executes callbacks

        if (ros::param::get("/realTimeFactor", realTimeFactor)){} // set parameters
        if (ros::param::get("/gravity", gravity)){
            if (gravity) {
                //rl::math::Vector v = rl::math::Vector(3);
               // robot->dynamics->getWorldGravity(v);
                //std::cout << v << std::endl;
                robot->dynamics->setWorldGravity(0, 0, 9.80665);

            } else
                robot->dynamics->setWorldGravity(0,0,0);
        }
        if (ros::param::get("/rosRate", rate)){
            if (rate<10.0)
                rate=10.0;
            loop_rate = rate;}
        loop_rate.sleep(); //wait

    }
    return 0;
}
// DEBUG code
//auto t1 = Clock::now();
//auto J =robot->getJacobian();
//std::cout<< J<<std::endl;
//auto t2 = Clock::now();
// std::cout << "Delta t2-t1: "
//         << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()
//        << " microseconds" << std::endl;
