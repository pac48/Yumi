//
// Created by paul on 7/30/19.
//

#ifndef ROS_PROVIDER_H
#define ROS_PROVIDER_H

#include "ros/ros.h"
#include <boost/function.hpp>
#include <tuple>
#include <map>

using namespace std;

class ROSProvider
{
public:
    static inline uint32_t queue_size_pub;
    static inline uint32_t queue_size_sub;

    static void init(ros::NodeHandle* nIn){
        n = nIn;
        queue_size_pub = 1;
        queue_size_sub = 1;
    }

    template<typename T>
    static void setTimeStampNow(T &msg){
        auto t = ros::Time::now();
        msg.header.stamp.sec = t.sec;
        msg.header.stamp.nsec = t.nsec;
    }

    template <typename T>
    static auto getSubscriberCallBack(void (*userCallback)(T))
    {
        boost::function<void(T)> callBack = [=](T msg) { userCallback(msg); };
        return callBack;
    }

    template <typename T>
    static tuple<ros::Publisher, T> getPublisher(const string &topic, const string& channel="")
    {
        if (!publisherPairs)
        {
            publisherPairs = new vector<PublisherPair *>();
        }
        if (!topic2Pub<T>)
        {
            topic2Pub<T> = new map<string, tuple<ros::Publisher, boost::function<T()> > >();
            atexit(ROSProvider::cleanPub<T>);
        }
        string key = channel+topic;
        if (topic2Pub<T>->find(key) == topic2Pub<T>->end())
        {
            ros::Publisher pub = n->advertise<T>(topic, queue_size_pub);
            auto msg = T();
            publisherPairs->push_back(new PublisherPair{pub, (void *) &msg, ROSProvider::publishOne<T>});
            boost::function<T()> msgGen = [=]() { return T();};
            auto tmp = tuple<ros::Publisher , boost::function<T()> >{pub, msgGen};
            topic2Pub<T>->operator[](key) = tmp;
        }
        auto [pub, msgGen] = topic2Pub<T>->operator[](key);
        tuple<ros::Publisher, T> tmp = make_tuple(pub, msgGen());
        return tmp; //tuple<ros::Publisher, T *>{pub, msg_ptr}; //*topic2Pub<T>->operator[](topic);
    }

    template <typename T>
    static ros::Subscriber getSubscriber(const string &topic,
                                         void (*userCallback)(T), const string& channel="")
    {
        if (!topic2Sub)
        {
            topic2Sub = new map<string, ros::Subscriber >();
            atexit(ROSProvider::cleanSub);
        }
        string key = channel+topic; // userCallback is required to be static, so the function pointer can be used as an identifier
        if (!topic2Sub->operator[](key))
        {
            auto callback = getSubscriberCallBack(userCallback);
            topic2Sub->operator[](key) = n->subscribe(topic, queue_size_sub, callback);
        }
        return (topic2Sub->operator[](key));
    }

    template <typename T1, typename T2>
    static auto getServiceCallBack(bool (*userCallback)(T1, T2))
    {
        boost::function<bool(T1 req, T2 res)> callBack = [=](T1 req, T2 res) { return userCallback(req, res); };
        return callBack;
    }

    template <typename T1, typename T2>
    static ros::ServiceServer getService(const string &topic, bool (*userCallback)(T1, T2))
    {
        if (!topic2Serv)
        {
            topic2Serv = new map<string, ros::ServiceServer>();
            atexit(ROSProvider::cleanServ);
        }
        if (!topic2Serv->operator[](topic))
        {
            auto callback = getServiceCallBack(userCallback);
            topic2Serv->operator[](topic) = n->advertiseService(topic, callback);
        }
        return (topic2Serv->operator[](topic));
    }

    static void publishAll()
    {
        for (auto pp : *publisherPairs)
            pp->publish(pp->msg, pp->publisher);
    }

    template <typename T>
    static void publishOne(void *msg, ros::Publisher pub)
    {
        T *msg2 = (T *)msg;
        pub.publish(*msg2);
    }

    static void cleanSub()
    {
        if (topic2Sub)
        {
            delete topic2Sub;
            topic2Sub = nullptr;
            cout << "cleaned subscribers" << endl;
        }
    }

    static void cleanServ()
    {
        if (topic2Serv)
        {
            delete topic2Serv;
            topic2Serv = nullptr;
            cout << "cleaned subscribers" << endl;
        }
    }

    template <typename T>
    static void cleanPub()
    {
        if (publisherPairs)
        {
            for (auto pp : *publisherPairs)
                delete pp;
            delete publisherPairs;
            publisherPairs = nullptr;
            cout << "cleaned "
                 << "publisherPairs" << endl;
        }
        if (topic2Pub<T>)
        {
            delete topic2Pub<T>;
            topic2Pub<T> = nullptr;
            cout << "cleaned publishers " << typeid(T).name() << endl;
        }
    }

    struct PublisherPair
    {
        ros::Publisher publisher;
        void *msg;
        void (*publish)(void *, ros::Publisher);
    };
    static inline ros::NodeHandle* n;
    static inline vector<PublisherPair *> *publisherPairs;
    static inline map<string, ros::ServiceServer > *topic2Serv;
    static inline map<string, ros::Subscriber > *topic2Sub;
    template <typename T>
    static inline map<string, tuple<ros::Publisher, boost::function<T()>> > *topic2Pub;

};
#endif
