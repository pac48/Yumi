//
// Created by paul on 7/30/19.
//

#ifndef ROBOT_H
#define ROBOT_H


#include "rl/math/Transform.h"
#include "rl/math/Vector.h"
#include "rl/math/Matrix.h"
#include "rl/math/Unit.h"
#include "rl/mdl/Dynamic.h"
#include "rl/mdl/Model.h"
#include "rl/mdl/Body.h"
#include <fstream>
#include <cstdio>
#include <iostream>
#include <string>
#include "rl/mdl/UrdfFactory.h"
#include <ros/ros.h>
#include "std_msgs/Float32.h"
#include "rl/mdl/Joint.h"
#include <boost/function.hpp>





class Robot {

public:
    Robot(std::string name);
    Robot();
    void init(std::string name);

    ~Robot();


    rl::mdl::Dynamic* dynamics;
    std::string name;
    std::vector<std::string> jointNames;
    std::map<std::string,int> jointNames2Ind;

    rl::math::Vector floatVec2MathVec(std::vector<float> fv);

    std::vector<float> mathVec2FloatVec(rl::math::Vector mv);

    std::vector<float> getPosition();

    std::vector<float> getVelocity();

    std::vector<float> getKE();

    std::vector<float> getPE();

    std::vector<float> xd2jd(int EE, std::vector<float> xdf);

    rl::math::Vector xd2jd(int EE, rl::math::Vector xd);

    std::vector<float> getOperationalPosition(int EE);

    void step(float dt, int numsteps);

    void generateURDF(std::string myRobotstr);

    void loadModel(std::string urdf_file_name);


private:
    std::vector<ros::ServiceServer> services;
    rl::mdl::Model* model;
    rl::math::Matrix J;
    rl::math::Matrix M;
    std::vector<rl::math::Matrix> Ji;
    std::vector<rl::math::Matrix> invJi;
    std::vector<rl::math::Vector> xdi;
    rl::math::Vector tau0;
};




#endif
