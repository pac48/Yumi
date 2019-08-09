//
// Created by paul on 7/26/19.
//

#include <iostream>

#include <rl/math/Transform.h>
#include <rl/math/Vector.h>
#include <rl/math/Matrix.h>
#include <rl/math/Unit.h>
#include <rl/mdl/Kinematic.h>
#include <rl/mdl/Dynamic.h>
#include <rl/mdl/Model.h>
#include <fstream>
#include <string>
#include "rl/mdl/UrdfFactory.h"
#include "ros/ros.h"
#include "rl/mdl/Joint.h"
#include "simulator/getStaticTorques.h"
#include "std_msgs/Float32MultiArray.h"
#include <Eigen/QR>






void generateURDF(std::string myRobotstr){
    std::ofstream myfile;
    myfile.open ("/home/paul/Yumi_WS/src/dynamics/src/yumi.urdf");
    myfile<<myRobotstr;
    myfile.close();

}

rl::mdl::Model* loadModel(std::shared_ptr<rl::mdl::Model>& model,std::string urdf_file_name){
    std::ifstream f(urdf_file_name.c_str());
    if(!f.good()){
        std::string myRobotstr;
        ros::param::get("robot_description",myRobotstr);
        generateURDF(myRobotstr);
    }
    rl::mdl::UrdfFactory urdf;
    urdf.load(urdf_file_name, model.get());
}

struct jointConfig {
    rl::math::Vector q;
    rl::math::Vector qd;
    rl::math::Vector qdd;
    rl::math::Vector tau;
};
struct operationalConfig {
    rl::math::Transform x;
    rl::math::MotionVector xd;
    rl::math::MotionVector xdd;
    rl::math::ForceVector f;

};


static rl::mdl::Dynamic* dynamicsReal;
static rl::mdl::Dynamic* dynamicsSRV;
static jointConfig JCReal;
static jointConfig JCSRV;
static operationalConfig OCRealL;
static operationalConfig OCSRVL;
static operationalConfig OCRealR;
static operationalConfig OCSRVR;

bool getStaticTorques(simulator::getStaticTorques::Request  &req, simulator::getStaticTorques::Response &res){

    for (int i=0;i<req.q.size();i++){
        JCSRV.q[i]=req.q[i];
        JCSRV.qd[i]=0;
        JCSRV.qdd[i]=0;
    }
    dynamicsSRV->setPosition(JCSRV.q);
    dynamicsSRV->setVelocity(JCSRV.qd);
    dynamicsSRV->setAcceleration(JCSRV.qdd);
    dynamicsSRV->inverseDynamics();
    JCSRV.tau = dynamicsSRV->getTorque();
    res.tau=req.q;
    for (int i=0;i<req.q.size();i++) {
        res.tau[i] = JCSRV.tau[i];
    }

    return true;
}


//void updateJoints(const std_msgs::Float32MultiArray::ConstPtr& msg){
template<typename T>
void updateJoints(const std_msgs::Float32MultiArray::ConstPtr& msg,T pubs){
    std::vector<float> data = msg->data;
    for (int i=0;i<data.size();i++) {
        JCReal.q[i] = data[i];
    }
    dynamicsReal->setPosition(JCReal.q);
    dynamicsReal->forwardPosition();
    std_msgs::Float32MultiArray msgL;
    std_msgs::Float32MultiArray msgR;
    OCRealR.x = dynamicsReal->getOperationalPosition(0);
    OCRealL.x = dynamicsReal->getOperationalPosition(1);
    for (int i=0;i<3;i++) {
        msgR.data.push_back(OCRealR.x(i, 3));
        msgL.data.push_back(OCRealL.x(i, 3));
    }
    pubs[0].publish(msgR);
    pubs[1].publish(msgL);
}
rl::math::Matrix J(6*2, 14);
rl::math::Matrix JL(6, 7);
rl::math::Matrix JR(6, 7);
rl::math::Matrix invJL(7, 6);
rl::math::Matrix invJR(7, 6);
template<typename T>
void sendJointVelocities(const std_msgs::Float32MultiArray::ConstPtr& msg,T JointVelPubs){
    std::vector<float> data = msg->data;
    rl::math::Vector xdR(6);
    rl::math::Vector xdL(6);
    for (int i=0;i<data.size();i++) {
        if (i<data.size()/2){
            xdR[i]=data[i];
        } else{
            xdL[i-data.size()/2]=data[i];
        }

    }
    dynamicsReal->calculateJacobian(J);
    for (int i =0;i<6;i++){
        for (int j=0;j<7;j++){
            JR(i,j) = J(i,j);
            JL(i,j) = J(i+6,j+7);
        }
    }
    dynamicsReal->calculateJacobianInverse(JR,invJR,0.1f,true);
    dynamicsReal->calculateJacobianInverse(JL,invJL,0.1f,true);
    rl::math::Vector jdR = invJR*xdR;
    rl::math::Vector jdL = invJL*xdL;
    std_msgs::Float32MultiArray msgL;
    std_msgs::Float32MultiArray msgR;
    for (int i=0;i<7;i++)
        msgR.data.push_back(jdR[i]);
    for (int i=0;i<7;i++)
        msgL.data.push_back(jdL[i]);
    JointVelPubs[0].publish(msgR);
    JointVelPubs[1].publish(msgL);

}


int main(int argc, char *argv[]) {
    ros::init(argc, argv, "dynamics_node");
    ros::NodeHandle n;
    using namespace rl;
    std::string urdf_file_name = "/home/paul/Yumi_WS/src/dynamics/src/yumi.urdf";
    std::shared_ptr<mdl::Model> modelReal =(std::shared_ptr<mdl::Model>) new mdl::Model();
    loadModel(modelReal,urdf_file_name);
    dynamicsReal =  static_cast<mdl::Dynamic*>(modelReal.get());
    std::shared_ptr<mdl::Model> modelSRV =(std::shared_ptr<mdl::Model>) new mdl::Model();
    loadModel(modelSRV,urdf_file_name);
    dynamicsSRV =  static_cast<mdl::Dynamic*>(modelSRV.get());
    JCSRV.q=dynamicsReal->getPosition();
    JCSRV.qd=dynamicsReal->getVelocity();
    JCSRV.qdd=dynamicsReal->getAcceleration();
    JCSRV.tau=dynamicsReal->getTorque();
    JCReal.q=dynamicsReal->getPosition();
    JCReal.qd=dynamicsReal->getVelocity();
    JCReal.qdd=dynamicsReal->getAcceleration();
    JCReal.tau=dynamicsReal->getTorque();
    OCSRVR.x =dynamicsReal->getOperationalPosition(0);
    OCSRVR.xd = dynamicsReal->getOperationalVelocity(0);
    OCSRVR.xdd = dynamicsReal->getOperationalAcceleration(0);
    OCSRVL.x = dynamicsReal->getOperationalPosition(0);
    OCSRVL.xd = dynamicsReal->getOperationalVelocity(0);
    OCSRVL.xdd = dynamicsReal->getOperationalAcceleration(0);
    OCSRVL.f = dynamicsReal->getOperationalForce(0);
    OCSRVR.f = dynamicsReal->getOperationalForce(0);
    OCRealR.x = dynamicsReal->getOperationalPosition(0);
    OCRealR.xd = dynamicsReal->getOperationalVelocity(0);
    OCRealR.xdd = dynamicsReal->getOperationalAcceleration(0);
    OCRealR.f = dynamicsReal->getOperationalForce(0);
    OCRealL.x = dynamicsReal->getOperationalPosition(0);
    OCRealL.xd = dynamicsReal->getOperationalVelocity(0);
    OCRealL.xdd = dynamicsReal->getOperationalAcceleration(0);
    OCRealL.f = dynamicsReal->getOperationalForce(0);
    ros::ServiceServer getStaticJointTorqueService = n.advertiseService("getStaticJointTorques", getStaticTorques);
    ros::Publisher operationalPosPubL = n.advertise<std_msgs::Float32MultiArray>("operational_position_L",1);
    ros::Publisher operationalPosPubR = n.advertise<std_msgs::Float32MultiArray>("operational_position_R",1);
    std::vector <ros::Publisher> operationalPosPubs;
    operationalPosPubs.push_back(operationalPosPubR);operationalPosPubs.push_back(operationalPosPubL);
    boost::function<void (const std_msgs::Float32MultiArray::ConstPtr&)> updateJointsLambda = [=](const std_msgs::Float32MultiArray::ConstPtr& msg) {updateJoints(msg,operationalPosPubs);};
    ros::Subscriber jointStateSubscriber = n.subscribe("joint_states",1,updateJointsLambda);
    ros::Publisher jointVelPubL = n.advertise<std_msgs::Float32MultiArray>("joint_velocity_command_L",1);
    ros::Publisher jointVelPubR = n.advertise<std_msgs::Float32MultiArray>("joint_velocity_command_R",1);

    std::vector <ros::Publisher> jointVelPubs;
    jointVelPubs.push_back(jointVelPubR);jointVelPubs.push_back(jointVelPubL);
    boost::function<void (const std_msgs::Float32MultiArray::ConstPtr&)> sendJointVelocitiesLambda = [=](const std_msgs::Float32MultiArray::ConstPtr& msg) {sendJointVelocities(msg,jointVelPubs);};
    ros::Subscriber operationalVelocityCommandSubscriber = n.subscribe("operational_velocity_command",1,sendJointVelocitiesLambda);
    ros::Rate loop_rate(250);
    while (ros::ok()) {
        ros::spin();
        loop_rate.sleep();
    }
    return 0;
}




/*
 *
 *     dynamics->forwardPosition();
    dynamics->forwardVelocity();
    dynamics->forwardAcceleration();
    dynamics->forwardDynamics(); //overwrite acceleration
    dynamics->inverseDynamics(); //overwrite torque
 *
 *     rl::math::Vector q = kinematics->getPosition();
    for (int i=0;i<kinematics->getDof();i++){
        std::cout<<q[i]<<std::endl;
    }
    int s = q.size();


    for (int i=0;i<kinematics->getDof();i++) {
        Joint *J = kinematics->getJoint(i);
        const ::rl::math::Vector V = J->getMaximum();
        for (int j=0;j<V.size();j++) {
            std::cout << V[j] << " ";
        }
        std::cout << std::endl;
    }

        const rl::math::ForceVector vec = dynamics->getOperationalForce(0).force();
    std::cout <<vec2[0]<<std::endl;
    std::cout <<vec2[1]<<std::endl;
    std::cout <<vec2[2]<<std::endl;
    const rl::math::ForceVector::ConstMomentType vec3 = vec.moment();
    std::cout <<vec3[0]<<std::endl;
    std::cout <<vec3[1]<<std::endl;
    std::cout <<vec3[2]<<std::endl;

    const rl::math::MotionVector vecA = dynamics->getOperationalAcceleration(0);
    const rl::math::MotionVector::ConstLinearType vecA2 = vecA.linear();
    std::cout <<vecA2[0]<<std::endl;
    std::cout <<vecA2[1]<<std::endl;
    std::cout <<vecA2[2]<<std::endl;
    const rl::math::MotionVector::ConstAngularType vecA3 = vecA.angular();
    std::cout <<vecA3[0]<<std::endl;
    std::cout <<vecA3[1]<<std::endl;
    std::cout <<vecA3[2]<<std::endl;

    */
