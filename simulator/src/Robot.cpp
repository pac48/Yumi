//
// Created by paul on 7/30/19.
//

#include "Robot.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Float64.h"
#include <iostream>
#include <fstream>
#include <cstdio>

Robot::Robot(std::string name){
    using namespace rl;
    this->name = name;
    std::string urdf_file_name = name+".urdf";
    this->model = new mdl::Model();
    this->loadModel(urdf_file_name);
    this->dynamics = (mdl::Dynamic*) this->model;
    int numEE = this->dynamics->getOperationalDof();
    int numDof = this->dynamics->getDof();
    this->J =rl::math::Matrix(6*numEE, numDof);
    for (int n=0;n<numEE;n++){
        this->Ji.push_back(rl::math::Matrix(6, numDof/numEE));
        this->invJi.push_back(rl::math::Matrix(6, numDof/numEE));
        this->xdi.push_back(rl::math::Vector(6));
    }
}
Robot::~Robot(){
    delete this->model;
}
rl::math::Vector Robot::floatVec2MathVec(std::vector<float> fv){
    rl::math::Vector mv =rl::math::Vector(fv.size());
    for (int i =0;i<fv.size();i++){
        mv[i]=fv[i];
    }
    return mv;
}
std::vector<float> Robot::mathVec2FloatVec(rl::math::Vector mv){
    std::vector<float> fv;
    for (int i =0;i<mv.size();i++){
        fv.push_back(mv[i]);
    }
    return fv;
}
std::vector<float> Robot::xd2jd(int EE, std::vector<float> xdf){
    rl::math::Vector xd =this->floatVec2MathVec(xdf);
    rl::math::Vector jd = this->xd2jd(EE,xd);
    return this->mathVec2FloatVec(jd);

}

rl::math::Vector Robot::xd2jd(int EE, rl::math::Vector xd){
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
    this->dynamics->calculateJacobianInverse(Ji,invJi,0.1f,true);
    //std::cout<<xd<<std::endl;
    //std::cout<<Ji<<std::endl;
    //std::cout<<invJi<<std::endl;
    rl::math::Vector jd = invJi*xd;
    //std::cout<<jd<<std::endl;
    return jd;
}
std::vector<float> Robot::getOperationalPosition(int EE){
    this->dynamics->forwardPosition();
    rl::math::Transform T = this->dynamics->getOperationalPosition(EE);
    std::vector<float> p;
    for (int i =0;i<3;i++){
        p.push_back(T(i,3));
    }
    rl::math::Vector z0 = rl::math::Vector::Zero(3);
    z0[2]=1;
    rl::math::Vector z = T.inverse().rotation()*z0;
    for (int i =0;i<3;i++){
        p.push_back(z[i]);
    };
    return p;
}
void Robot::generateURDF(std::string myRobotstr){
    std::ofstream myfile;
    myfile.open (this->name+".urdf");
    myfile<<myRobotstr;
    myfile.close();
}

void Robot::loadModel(std::string urdf_file_name){
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
void Robot::publishOne(T msgIn){
    PublisherPair pp = this->msgMap[msgIn];
    void* msg = pp.msg;
    ros::Publisher pub = pp.publisher;
    pp.publish(pub,msg);
}

void Robot::publishOne(int i){
    void* msg = this->publisherPairs[i].msg;
    ros::Publisher pub = this->publisherPairs[i].publisher;
    this->publisherPairs[i].publish(pub,msg);
}

void Robot::publishAll(){
    for (int i =0;i<this->publisherPairs.size();i++){
        publishOne(i);
    }
}

template<typename T>
void Robot::publisher(ros::Publisher pub,void* msg){
    T* msg2 =(T*) msg;
    pub.publish(*msg2);
}

template<typename T>
void Robot::addPublisherPair(ros::Publisher pub,T* msg) {
    PublisherPair pp;
    pp.publisher=pub;
    pp.msg = (void*) msg;
    //boost::function<void (ros::Publisher pub,void* msg)> func = [=](ros::Publisher pub,void* msg) {this->publisher<T>(pub,msg);};
    boost::function<void (ros::Publisher pub,void* msg)> publish = [=](ros::Publisher pub,void* msg) {publisher<T>(pub,msg);};
    pp.publish= publish;
    this->publisherPairs.push_back(pp);
    this->msgMap[pp.msg] = pp;
}
template<typename T>
boost::function<void (T msg)> Robot::getSubscriberCallBack(void (*userFunc)(T)){
    boost::function<void (T msg)> callBack = [=](T msg) {userFunc(msg);};
    return callBack;
}
template<typename T,typename T2>
boost::function<void (T msg)> Robot::getSubscriberCallBackPublisher(void (*userFunc)(T,T2*),T2* pubMsg){
    boost::function<void (T msg)> callBack = [=](T msg) {userFunc(msg,pubMsg);};
    return callBack;
}
template<typename T,typename T2>
boost::function<void (T msg)> Robot::getSubscriberCallBackPublisherRobot(void (*userFunc)(T,T2*,Robot*),T2* pubMsg,Robot* robot){
    boost::function<void (T msg)> callBack = [=](T msg) {userFunc(msg,pubMsg,robot);};
    return callBack;
}
template<typename T,typename T2>
boost::function<void (T msg)> Robot::getSubscriberCallBackPublishersRobot(void (*userFunc)(T,std::vector<T2*>,Robot*),std::vector<T2*> pubMsgs,Robot* robot){
    boost::function<void (T msg)> callBack = [=](T msg) {userFunc(msg,pubMsgs,robot);};
    return callBack;
}


template<typename T1, typename T2, typename T3>
boost::function<bool (T1,T2)> Robot::getServiceCallBack(bool(*userFunc)(T1,T2)){
    boost::function<bool (T1 req,T2 res)> callBack = [=](T1 req,T2 res) {userFunc(req,res);};
    return callBack;
}
template<typename T1, typename T2, typename T3>
boost::function<bool (T1,T2)> Robot::getServiceCallBackPublisher(bool (*userFunc)(T1,T2,T3*),T3* msg){
    boost::function<bool (T1 req,T2 res)> callBack = [=](T1 req,T2 res) {userFunc(req,res,msg);};
    return callBack;
}
template<typename T1, typename T2, typename T3>
boost::function<bool (T1,T2)> Robot::getServiceCallBackPublisherRobot(bool (*userFunc)(T1,T2,T3*,Robot*),T3* msg, Robot* robot){
    boost::function<bool (T1 req,T2 res)> callBack = [=](T1 req,T2 res) {userFunc(req,res,msg,robot);};
    return callBack;
}
template<typename T1, typename T2>
boost::function<bool (T1,T2)> Robot::getServiceCallBackRobot(bool (*userFunc)(T1,T2,Robot*), Robot* robot){
    boost::function<bool (T1 req,T2 res)> callBack = [=](T1 req,T2 res) {userFunc(req,res,robot);};
    return callBack;
}


/*

void mycallback(const std_msgs::Float32::ConstPtr& msg, std_msgs::Float32* publisherMsg){
    std_msgs::Float32 msg2;
     publisherMsg->data=msg->data+3;
    //pub.publish(msg2);
}
void mycallback2(const std_msgs::Float32::ConstPtr& msg, std_msgs::Float32* publisherMsg,Robot* robot){
    std_msgs::Float32 msg2;
    publisherMsg->data=msg->data+3;
    robot->publishOne(publisherMsg);
}


int main(int argc, char *argv[]) {
    ros::init(argc, argv, "robot_node");
    ros::NodeHandle n;
    Robot* robot = new Robot("yumi");
    std_msgs::Float32* msg = new std_msgs::Float32();
    msg->data=12.0f;
    ros::Publisher pub = n.advertise<std_msgs::Float32>("test1",10);
    robot->addPublisherPair(pub,msg);
    std_msgs::Float32* msg2 = new std_msgs::Float32();
    msg2->data=2.0;
    ros::Publisher pub2 = n.advertise<std_msgs::Float32>("test2",10);
    robot->addPublisherPair(pub2,msg2);
    auto callback2 = robot->getSubscriberCallBackPublisherRobot(mycallback2,msg2,robot);
    ros::Subscriber sub = n.subscribe("test1",5,callback2);
    ros::Rate loopRate = ros::Rate(10);
    int i=0;
    while (ros::ok()) {
        loopRate.sleep();
        //robot->publishAll();
        robot->publishAll();
        ros::spinOnce();
        i++;
        msg2->data=i;
        std::vector<float> xd =std::vector<float>(6);
        xd[2]=-1;
        //std::cout<<xd<<std::endl;
        std::vector<float> qd = robot->xd2jd(1,xd);
        std::vector<float> p = robot->getOperationalPosition(0);
        std::cout<<qd[0]<<std::endl;

    }
    return 0;
}
*/

