//
// Created by paul on 1/7/20.
//
#ifndef YUMI_WS_YUMI_H
#define YUMI_WS_YUMI_H

#include "Robot.h"
#include "callbacks.h"

class Yumi: public Robot {
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
    std::vector<std::string> jointNames = {"yumi_joint_1_r", "yumi_joint_2_r",
                                           "yumi_joint_7_r", "yumi_joint_3_r",
                                           "yumi_joint_4_r", "yumi_joint_5_r",
                                           "yumi_joint_6_r", "yumi_joint_1_l",
                                           "yumi_joint_2_l", "yumi_joint_7_l",
                                           "yumi_joint_3_l","yumi_joint_4_l",
                                           "yumi_joint_5_l", "yumi_joint_6_l"};
};

#endif //YUMI_WS_YUMI_H
