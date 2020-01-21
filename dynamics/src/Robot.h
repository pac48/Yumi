//
// Created by paul on 7/30/19.
//

#ifndef YUMI_WS_ROBOT_H
#define YUMI_WS_ROBOT_H

#include "ros/ros.h"
#include "dynamics/getStaticTorques.h"
#include "dynamics/setTorques.h"
#include "dynamics/getTrajTorques.h"
#include "dynamics/getT.h"
#include "dynamics/getM.h"
#include "dynamics/getG.h"
#include "dynamics/getC.h"
#include "dynamics/getJ.h"
#include "std_msgs/Float32MultiArray.h"
#include "sensor_msgs/JointState.h"
#include <rl/math/Transform.h>
#include <rl/math/Vector.h>
#include <rl/math/Matrix.h>
#include <rl/math/Quaternion.h>
#include <rl/math/Unit.h>
#include <rl/mdl/Dynamic.h>
#include <rl/mdl/Kinematic.h>
#include <rl/mdl/Model.h>
#include <rl/mdl/Body.h>
#include "rl/mdl/Joint.h"
#include "rl/mdl/UrdfFactory.h"
#include <fstream>
#include <cstdio>
#include <iostream>
#include <string>
#include <ros/ros.h>
#include "std_msgs/Float32.h"
#include <boost/function.hpp>
#include <chrono>


struct PublisherPair{
    ros::Publisher publisher;
    void* msg;
    boost::function<void (ros::Publisher pub,void* msg)> publish;
};

class Robot {
public:
    Robot(std::string name){
        using namespace rl;
        this->name = name;
        std::string urdf_file_name = name+".urdf";
        this->model = new mdl::Model();
        this->loadModel(urdf_file_name);
        this->dynamics = (mdl::Dynamic*) this->model;
        int numEE = this->dynamics->getOperationalDof();
        int numDof = this->dynamics->getDof();
        this->J =rl::math::Matrix(6*numEE, numDof);
        this->M =rl::math::Matrix(numDof,numDof);
        this->C =rl::math::Vector(numDof);
        this->G =rl::math::Vector(numDof);
        for (int n=0;n<numEE;n++){
            this->Ji.push_back(rl::math::Matrix(6, numDof/numEE));
            this->invJi.push_back(rl::math::Matrix(6, numDof/numEE));
            this->xdi.push_back(rl::math::Vector(6));
        }
        this->time =  std::chrono::high_resolution_clock::now();
    }
    ~Robot(){
        delete this->model;
    }
    static rl::math::Vector floatVec2MathVec(std::vector<float> fv){
        rl::math::Vector mv =rl::math::Vector(fv.size());
        for (int i =0;i<fv.size();i++){
            mv[i]=fv[i];
        }
        return mv;
    }
    static std::vector<float> mathVec2FloatVec(rl::math::Vector mv){
        std::vector<float> fv;
        for (int i =0;i<mv.size();i++){
            fv.push_back(mv[i]);
        }
        return fv;
    }
    std::vector<float> getPosition(){
        rl::math::Vector j = this->dynamics->getPosition();
        return this->mathVec2FloatVec(j);
    }
    std::vector<float> getVelocity(){
        rl::math::Vector j = this->dynamics->getVelocity();
        return this->mathVec2FloatVec(j);
    }
    double getKE(){
        auto qd=this->dynamics->getVelocity();
        auto tau=this->dynamics->getTorque();
        this->dynamics->calculateMassMatrix(this->M);
        this->dynamics->setVelocity(qd);
        this->dynamics->setTorque(tau);
        double KE = .5*qd.transpose()*(this->M)*qd;
        return KE;
    }
    std::vector<float> getPE(){
        auto qd=this->dynamics->getVelocity();
        for (int i=0;i<this->dynamics->getBodies();i++){
            auto b0 = this->dynamics->getBody(i); // 3 is 2
            auto b1 = this->dynamics->getBody(i+1);
            float mass = b0->m;
            auto T0 = b0->t;
            float h0 = T0(2,3);
            auto T1 = b1->t;
            float h1 = T1(2,3);
        }
        return this->mathVec2FloatVec(qd);
    }
    std::vector<float> xd2jd(int EE, std::vector<float> xdf){
        rl::math::Vector xd =this->floatVec2MathVec(xdf);
        rl::math::Vector jd = this->xd2jd(EE,xd);
        return this->mathVec2FloatVec(jd);
    }
    rl::math::Matrix& getInvJacobian(int EE){
        this->dynamics->calculateJacobian(this->J);
        rl::math::Matrix Ji = this->Ji[EE];
        rl::math::Matrix invJi = this->invJi[EE];
        int numEE = this->dynamics->getOperationalDof();
        int numDof = this->dynamics->getDof();
        int offseti = EE*6;
        int offsetj=EE*numDof/numEE;
        for (int i =0;i<6;i++){
            for (int j=0;j<7;j++){
                Ji(i,j) = this->J(i+offseti,j+offsetj);
            }
        }
        this->dynamics->calculateJacobianInverse(Ji,invJi, 0.01f,true);
        this->invJi[EE] = invJi;
        return this->invJi[EE];
    }
    rl::math::Matrix& getJacobian(){
        this->dynamics->calculateJacobian(this->J);
        return this->J;
    }
    rl::math::Matrix getMassMatrix(){
        this->dynamics->calculateMassMatrix(this->M);
        return this->M;
    }
    rl::math::Vector& getCentrifugalCoriolis(){
        this->dynamics->calculateCentrifugalCoriolis(this->C);
        return this->C;
    }
    rl::math::Vector& getGravity(){
        this->dynamics->calculateGravity(this->G);
        return this->G;
    }
    rl::math::Vector xd2jd(int EE, rl::math::Vector xd){
        this->dynamics->calculateJacobian(this->J);
        rl::math::Matrix Ji = this->Ji[EE];
        rl::math::Matrix invJi = this->invJi[EE];
        int numEE = this->dynamics->getOperationalDof();
        int numDof = this->dynamics->getDof();
        int offseti = EE*6;
        int offsetj=EE*numDof/numEE;
        for (int i =0;i<6;i++){
            for (int j=0;j<7;j++){
                Ji(i,j) = J(i+offseti,j+offsetj);
            }
        }
        this->dynamics->calculateJacobianInverse(Ji,invJi,0.0f,true);
        rl::math::Vector jd = invJi*xd;
        return jd;
    }
    std::vector<float> getOperationalPosition(int EE){
        //this->dynamics->forwardPosition();
        //this->dynamics->update();
        //this->dynamics->forwardPosition();
        //rl::math::Transform T = this->dynamics->getOperationalPosition(EE);
        rl::math::Transform T;
        if (EE==0)
           T = this->dynamics->getFrame(7); // 3 is 2
        else
            T = this->dynamics->getFrame(9+7); //probably not
        std::vector<float> p;
        for (int i =0;i<3;i++){
            p.push_back(T(i,3));
        }
        //rl::math::Vector z0 = rl::math::Vector::Zero(3);
        //z0[2]=1;
        //rl::math::Vector z = T*z0;
        for (int i =0;i<3;i++){
            p.push_back(T(i,2));
        }
        return p;
    }
    void step(float dt, int numsteps){
        auto appliedTau = this->dynamics->getTorque();
        auto q = this->dynamics->getPosition();
        auto qd = this->dynamics->getVelocity();
        auto tau = this->dynamics->getTorque();
        for (int i=0;i<numsteps;i++){
            for (int i=0;i<tau.size();i++){
                tau[i]=appliedTau[i]-qd[i]*1.1*0;
            }
            this->dynamics->setTorque(tau);
            this->dynamics->forwardDynamics();
            this->dynamics->rungeKuttaNystrom(dt/numsteps);
            qd = this->dynamics->getVelocity();
        }
        this->dynamics->setTorque(appliedTau);
        this->updateStepCallbacks();
    }
    void generateURDF(std::string myRobotstr){
        std::ofstream myfile;
        myfile.open (this->name+".urdf");
        myfile<<myRobotstr;
        myfile.close();
    }
    void loadModel(std::string urdf_file_name){
        std::ifstream f(urdf_file_name.c_str());
        if(f.good()){
            std::remove(urdf_file_name.c_str()) ;
        }
        std::string myRobotstr;
        ros::param::get("robot_description",myRobotstr);
        this->generateURDF(myRobotstr);
        rl::mdl::UrdfFactory urdf;
        urdf.load(urdf_file_name, this->model);
    }
    template<typename T>
    void publishOne(T msgIn){
        PublisherPair pp = this->msgMap[msgIn];
        void* msg = pp.msg;
        ros::Publisher pub = pp.publisher;
        pp.publish(pub,msg);
    }
    void publishOne(int i){
        void* msg = this->publisherPairs[i].msg;
        ros::Publisher pub = this->publisherPairs[i].publisher;
        this->publisherPairs[i].publish(pub,msg);
    }
    void publishAll(){
        for (int i =0;i<this->publisherPairs.size();i++){
            publishOne(i);
        }
    }
    void updateStepCallbacks(){
        for (int i =0;i<this->funcs.size();i++){
            this->funcs[i]();
        }
    }
    template<typename T>
    void publisher(ros::Publisher pub,void* msg) {
        T *msg2 = (T *) msg;
        pub.publish(*msg2);
    }
    void addStepCallback(void (*func)(void*&),void*& Struct) {
        boost::function<void ()> update = [=,&Struct]() {func(Struct);};
        this->funcs.push_back(update);
    }
    template<typename T>
    void addPublisherPair(ros::Publisher pub,T* msg) {
        PublisherPair pp;
        pp.publisher=pub;
        pp.msg = (void*) msg;
        boost::function<void (ros::Publisher pub,void* msg)> publish = [=](ros::Publisher pub,void* msg) {publisher<T>(pub,msg);};
        pp.publish= publish;
        this->publisherPairs.push_back(pp);
        this->msgMap[pp.msg] = pp;
    }
    template<typename T>
    T* addPublisher(ros::NodeHandle n, const std::string& topic, uint32_t queue_size,T* msg) {
        ros::Publisher Pub = n.advertise<T>(topic,queue_size);
        this->addPublisherPair(Pub,msg);
        return msg;
    }
    template<typename T1,typename T2>
    void addService(ros::NodeHandle& n, const std::string& topic, bool(*userFunc)(T1,T2,void*& Struct), void*& Struct){
        boost::function<bool(T1,T2)> callback = this->getServiceCallBack(userFunc,Struct);
        services.push_back(n.advertiseService(topic,callback));
    }
    template<typename T>
    void addSubscriber(ros::NodeHandle& n, const std::string& topic,uint32_t queue_size, void(*userFunc)(T,void*& Struct), void*& Struct){
        boost::function<void (T msg)> callback = this->getSubscriberCallBack(userFunc,Struct);
        subscribers.push_back(n.subscribe(topic,queue_size,callback));
    }
    template<typename T>
    boost::function<void (T msg)> getSubscriberCallBack(void (*userFunc)(T,void*&), void*& Struct){
        boost::function<void (T msg)> callBack = [=,&Struct](T msg) {userFunc(msg,Struct);};
        return callBack;
    }
    template<typename T1, typename T2>
    boost::function<bool(T1,T2)> getServiceCallBack(bool (*userFunc)(T1,T2,void*& Struct), void*& Struct){
        boost::function<bool(T1 req,T2 res)> callBack = [=,&Struct](T1 req,T2 res) {return  userFunc(req,res,Struct);};
        return callBack;
    }
    rl::mdl::Dynamic* dynamics;
    std::string name;
    rl::math::Matrix M;
    rl::mdl::Model* model;
    std::chrono::high_resolution_clock::time_point time;
private:
    std::vector<ros::Subscriber> subscribers;
    std::vector<ros::ServiceServer> services;
    std::vector<PublisherPair> publisherPairs;

    rl::math::Matrix J;
    rl::math::Vector C;
    rl::math::Vector G;
    std::vector<rl::math::Matrix> Ji;
    std::vector<rl::math::Matrix> invJi;
    std::vector<rl::math::Vector> xdi;
    std::map<void*,PublisherPair> msgMap;
    std::vector<boost::function<void ()> > funcs;
};

#endif //YUMI_WS_ROBOT_H

//template<typename T>
//boost::function<void (T msg)> getSubscriberCallBackRobot(void (*userFunc)(T,Robot*&), Robot*& robot){
//    boost::function<void (T msg)> callBack = [=,&robot](T msg) {userFunc(msg,robot);};
//    return callBack;
//}
// template<typename T,typename T2>
//boost::function<void (T msg)> getSubscriberCallBackPublisher(void (*userFunc)(T,T2*),T2* pubMsg){
//    boost::function<void (T msg)> callBack = [=](T msg) {userFunc(msg,pubMsg);};
//    return callBack;
//}
//template<typename T,typename T2>
//boost::function<void (T msg)> getSubscriberCallBackPublisherRobot(void (*userFunc)(T,T2*,Robot*&),T2* pubMsg,Robot*& robot){
//    boost::function<void (T msg)> callBack = [=,&robot](T msg) {userFunc(msg,pubMsg,robot);};
//    return callBack;
//}
//template<typename T,typename T2>
//boost::function<void (T msg)> getSubscriberCallBackPublishersRobot(void (*userFunc)(T,std::vector<T2*>,Robot*&),std::vector<T2*> pubMsgs,Robot*& robot){
//    boost::function<void (T msg)> callBack = [=,&robot](T msg) {userFunc(msg,pubMsgs,robot);};
//    return callBack;
//}

//template<typename T1, typename T2, typename T3>
//boost::function<bool (T1,T2)> getServiceCallBack(bool(*userFunc)(T1,T2)){
//    boost::function<bool (T1 req,T2 res)> callBack = [=](T1 req,T2 res) {return userFunc(req,res);};
//    return callBack;
//}
//template<typename T1, typename T2, typename T3>
//boost::function<bool (T1,T2)> getServiceCallBackPublisher(bool (*userFunc)(T1,T2,T3*),T3* msg){
//    boost::function<bool (T1 req,T2 res)> callBack = [=](T1 req,T2 res) {return userFunc(req,res,msg);};
//    return callBack;
//}
//template<typename T1, typename T2, typename T3>
//boost::function<bool (T1,T2)> getServiceCallBackPublisherRobot(bool (*userFunc)(T1,T2,T3*,Robot*&),T3* msg, Robot*& robot){
//    boost::function<bool (T1 req,T2 res)> callBack = [=,&robot](T1 req,T2 res) { return userFunc(req,res,msg,robot);};
//    return callBack;
//}
//template<typename T1, typename T2>
//boost::function<bool(T1,T2)> getServiceCallBackRobot(bool (*userFunc)(T1,T2,Robot*&), Robot*& robot){
//    boost::function<bool(T1 req,T2 res)> callBack = [=,&robot](T1 req,T2 res) {return  userFunc(req,res,robot);};
//    return callBack;
//}
