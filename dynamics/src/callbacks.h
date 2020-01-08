//
// Created by paul on 1/8/20.
//
#ifndef YUMI_WS_CALLBACKS_H
#define YUMI_WS_CALLBACKS_H

// Service callbacks
bool getStaticTorques(dynamics::getStaticTorques::Request  &req, dynamics::getStaticTorques::Response &res,void*& Struct){ // serviceRobot
    Robot* robot = (Robot*) Struct;
    auto q = robot->dynamics->getPosition();
    auto qd = robot->dynamics->getVelocity();
    auto qdd = robot->dynamics->getAcceleration();
    auto qtmp = robot->dynamics->getPosition();
    auto qdtmp = robot->dynamics->getVelocity();
    auto qddtmp = robot->dynamics->getAcceleration();
    for (int i=0;i<req.q.size();i++){
        q[i]=req.q[i];
        qd[i]=0;
        qdd[i]=0;
    }
    robot->dynamics->setPosition(q);
    robot->dynamics->setVelocity(qd);
    robot->dynamics->setAcceleration(qdd);
    robot->dynamics->inverseDynamics();
    auto tau = robot->dynamics->getTorque();
    res.tau=req.q;
    for (int i=0;i<req.q.size();i++) {
        res.tau[i] = tau[i];
    }
    robot->dynamics->setPosition(qtmp);
    robot->dynamics->setVelocity(qdtmp);
    robot->dynamics->setAcceleration(qddtmp);
    robot->dynamics->forwardDynamics();
    return true;
}
bool getTrajTorques(dynamics::getTrajTorques::Request  &req, dynamics::getTrajTorques::Response &res,void*& Struct){ // serviceRobot
    Robot* robot = (Robot*) Struct;
    auto q = robot->dynamics->getPosition();
    auto qd = robot->dynamics->getVelocity();
    auto qdd = robot->dynamics->getAcceleration();
    auto qtmp = robot->dynamics->getPosition();
    auto qdtmp = robot->dynamics->getVelocity();
    auto qddtmp = robot->dynamics->getAcceleration();
    for (int i=0;i<req.q.size();i++){
        q[i]=req.q[i];
        qd[i]=req.qd[i];
        qdd[i]=req.qdd[i];
    }
    robot->dynamics->setPosition(q);
    robot->dynamics->setVelocity(qd);
    robot->dynamics->setAcceleration(qdd);
    robot->dynamics->inverseDynamics();
    auto tau = robot->dynamics->getTorque();
    res.Tau = req.q;
    for (int i=0;i<req.q.size();i++) {
        res.Tau[i] = tau[i];
    }
    auto M = robot->getMassMatrix();
    double KE = robot->getKE();
    res.KE=KE;
    robot->dynamics->setPosition(qtmp);
    robot->dynamics->setVelocity(qdtmp);
    robot->dynamics->setAcceleration(qddtmp);
    robot->dynamics->forwardDynamics();
    return true;
}
bool setTorques(dynamics::setTorques::Request  &req, dynamics::setTorques::Response &res,void*& Struct){ // serviceRobot
    Robot* robot = (Robot*) Struct;
    auto tau = robot->dynamics->getTorque();
    for (int i=0;i<req.tau.size();i++){
        tau[i]=req.tau[i];
    }
    robot->dynamics->setTorque(tau);
    robot->dynamics->forwardDynamics();
    auto qdd = robot->dynamics->getAcceleration();
    for (int i=0;i<req.tau.size();i++) {
        res.qdd.push_back(qdd[i]);
    }
    return true;
}
bool setAccelerations(dynamics::setTorques::Request  &req, dynamics::setTorques::Response &res,void*& Struct){ // serviceRobot
    Robot* robot = (Robot*) Struct;
    auto qdd = robot->dynamics->getTorque();
    for (int i=0;i<req.tau.size();i++){
        qdd[i]=req.tau[i];
    }
    robot->dynamics->setAcceleration(qdd);
    robot->dynamics->inverseDynamics();
    auto tau = robot->dynamics->getTorque();
    for (int i=0;i<req.tau.size();i++) {
        res.qdd.push_back(tau[i]);
    }
    return true;
}
rl::math::Vector3 cross(rl::math::Vector3 a,rl::math::Vector3 b){
    rl::math::Vector3 r =rl::math::Vector3::Zero();
    r[0] = a[1]*b[2]-a[2]*b[1];
    r[1] = a[2]*b[0]-a[0]*b[2];
    r[2] = a[0]*b[1]-a[1]*b[0];
    return r;
}

bool setArmVelocity(dynamics::setTorques::Request  &req, dynamics::setTorques::Response &res, void*& Struct) { // serviceRobot
    Robot* robot = (Robot*) Struct;
    rl::math::Vector3 gax = rl::math::Vector3::Zero();
    rl::math::Vector3 gaxS = rl::math::Vector3::Zero();
    for (int i = 0; i < 3; i++) {
        gaxS[i] = req.tau[i]; // this is goal axis
    }
    for (int i = 0; i < 3; i++) {
        gax[i] = req.tau[i+3]; // this is goal axis
    }
    double theta = req.tau[6];
    rl::math::Vector3 z0 = rl::math::Vector3::Zero();
    z0[2]=1;
    rl::math::Vector3 e1 =  rl::math::Vector3::Zero();
    rl::math::Vector3 e2 = rl::math::Vector3::Zero();
    do {
        auto f3 = robot->dynamics->getBody(5);
        auto R3 = f3->t.rotation();
        rl::math::Vector3 z3 = R3 * z0;
        rl::math::Vector3 p3 = f3->t.translation();
        auto f2 = robot->dynamics->getBody(4);
        auto R2 = f2->t.rotation();
        rl::math::Vector3 z2 = R2 * z0;
        rl::math::Vector3 p2 = f2->t.translation();
        auto f1 = robot->dynamics->getBody(3);
        auto R1 = f1->t.rotation();
        rl::math::Vector3 z1 = R1 * z0;
        rl::math::Vector3 p1 = f1->t.translation();
        auto d1 = cross(z1, p3 - p1);
        d1.normalize();
        auto d2 = cross(z2, p3 - p2);
        d2.normalize();
        rl::math::Matrix D = rl::math::Matrix(3, 2);
        D << d1, d2;
        rl::math::Vector3 g = gax - z3;
        rl::math::Matrix22 lambdaM = rl::math::Matrix22::Identity() * 0.0001;
        rl::math::Matrix22 DD = rl::math::Matrix22::Zero();
        DD = D.transpose() * D + lambdaM;
        rl::math::Vector2 x = DD.inverse() * D.transpose() * g;
        x.normalize();
        auto f3S = robot->dynamics->getBody(3);
        auto R3S = f3S->t.rotation();
        rl::math::Vector3 z3S = R3S * z0;
        rl::math::Vector3 p3S = f3S->t.translation();
        auto f2S = robot->dynamics->getBody(2);
        auto R2S = f2S->t.rotation();
        rl::math::Vector3 z2S = R2S * z0;
        rl::math::Vector3 p2S = f2S->t.translation();
        auto f1S = robot->dynamics->getBody(1);
        auto R1S = f1S->t.rotation();
        rl::math::Vector3 z1S = R1S * z0;
        rl::math::Vector3 p1S = f1S->t.translation();
        d1 = cross(z1S, p3S - p1S);
        d1.normalize();
        d2 = cross(z2S, p3S - p2S);
        d2.normalize();
        D = rl::math::Matrix(3, 2);
        D << d1, d2;
        g = gaxS - z3S;
        DD = D.transpose() * D + lambdaM;
        rl::math::Vector2 xS = DD.inverse() * D.transpose() * g;
        xS.normalize();
        auto q = robot->dynamics->getPosition();
        q[0]+=xS[0]*theta;
        q[1]+=xS[1]*theta;
        q[2]+=x[0]*theta;
        q[3]+=x[1]*theta;
        robot->dynamics->setPosition(q);
        robot->dynamics->forwardPosition();
        e1 =  gax - z3;
        e2 =  gaxS - z3S;
        ///std::cout<<e1.norm()+e2.norm()<<std::endl;
    }
    while(e1.norm()+e2.norm()>0.005);

    auto tau = robot->dynamics->getPosition();
    for (int i = 0; i < tau.size(); i++) {
        res.qdd.push_back(tau[i]);
    }
    return true;
}
// Structs
struct VectorFloat32MultiArrayRobot{
    std::vector<std_msgs::Float32MultiArray*>* msgs;
    Yumi* robot;
};
struct Float32MultiArrayRobot{
    std_msgs::Float32MultiArray* msg;
    Yumi* robot;
};
struct JointStateRobot{
    sensor_msgs::JointState* msg;
    Yumi* robot;
};
// Subscriber callbacks
void updateOpPosition(const std_msgs::Float32MultiArray::ConstPtr& msg, void*& Struct){ //subpub
    VectorFloat32MultiArrayRobot* tmp = (VectorFloat32MultiArrayRobot*) Struct;
    Yumi* robot = tmp->robot;
    std::vector<std_msgs::Float32MultiArray*>* opPostionMsgs = tmp->msgs;
    std::vector<float> data = msg->data;
    auto q = robot->floatVec2MathVec(data);
    for (int i=0;i<data.size();i++) {
        q[i] = data[i];
    }
    opPostionMsgs->at(0)->data = robot->getOperationalPosition(0);
    opPostionMsgs->at(1)->data = robot->getOperationalPosition(1);
}
void rvizUpdateJoints(const std_msgs::Float32MultiArray::ConstPtr& msg, void*& Struct){ //subpub
    JointStateRobot* tmp1 = (JointStateRobot*) Struct;
    sensor_msgs::JointState* rvizMsgs = tmp1->msg;
    Yumi* robot = tmp1->robot;
    std::vector<double> tmp;
    for (int i=0;i<msg->data.size();i++) {
        double val = msg->data[i];
        tmp.push_back(val);
    }
    rvizMsgs->position=tmp;
    rvizMsgs->name = robot->jointNames;
    rvizMsgs->header.stamp = ros::Time::now();
}
// Link update functions
void updateJoints(void*& Struct){
    Float32MultiArrayRobot* tmp = (Float32MultiArrayRobot*) Struct;
    Yumi* robot = tmp->robot;
    std_msgs::Float32MultiArray* jointStateMsg = tmp->msg;
    jointStateMsg->data = robot->getPosition();
}
void updateJointsVel(void*& Struct){
    Float32MultiArrayRobot* tmp = (Float32MultiArrayRobot*) Struct;
    Yumi* robot = tmp->robot;
    std_msgs::Float32MultiArray* jointStateVelMsg = tmp->msg;
    jointStateVelMsg->data = robot->getVelocity();
}

#endif //YUMI_WS_CALLBACKS_H
