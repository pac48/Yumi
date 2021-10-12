//
// Created by paulg on 1/22/2021.
//

#ifndef SRC_ROBOTFACTORY_H
#define SRC_ROBOTFACTORY_H

#include <typeinfo>
#include <typeindex>
#include <map>
#include <cstdlib>

using namespace std;

class RobotFactory
{
public:
    static inline map<string, Robot *> *mapping;

    template <typename T>
    static T *getRobot(const string &id)
    {
        if (!mapping)
            mapping = new map<string, Robot *>();
        static_assert(is_base_of<Robot, T>::value, "type parameter of this class must derive from Robot");
        string className = typeid(T).name();
        className += id;
        if (!mapping->operator[](className))
        {
            mapping->operator[](className) = (Robot *) new T();
            atexit(RobotFactory::deleteRobot<T>);
            cout << "ititialized " << className << endl;
        }
        return (T *)mapping->operator[](className);
    }

    template <typename T>
    static T *getRobot()
    {
        return RobotFactory::getRobot<T>("");
    }


    template <typename T>
    static void deleteRobot()
    {
        if (mapping)
        {
            for (auto it = mapping->begin(); it != mapping->end(); it++)
                delete it->second;
            delete mapping;
            mapping = nullptr;
            cout << "deleted all robots" << endl;
        }
    }
};

#endif
