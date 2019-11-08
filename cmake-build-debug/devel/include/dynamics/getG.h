// Generated by gencpp from file dynamics/getG.msg
// DO NOT EDIT!


#ifndef DYNAMICS_MESSAGE_GETG_H
#define DYNAMICS_MESSAGE_GETG_H

#include <ros/service_traits.h>


#include <dynamics/getGRequest.h>
#include <dynamics/getGResponse.h>


namespace dynamics
{

struct getG
{

typedef getGRequest Request;
typedef getGResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct getG
} // namespace dynamics


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::dynamics::getG > {
  static const char* value()
  {
    return "74b149151fe783dcf4c3c5768c37537f";
  }

  static const char* value(const ::dynamics::getG&) { return value(); }
};

template<>
struct DataType< ::dynamics::getG > {
  static const char* value()
  {
    return "dynamics/getG";
  }

  static const char* value(const ::dynamics::getG&) { return value(); }
};


// service_traits::MD5Sum< ::dynamics::getGRequest> should match 
// service_traits::MD5Sum< ::dynamics::getG > 
template<>
struct MD5Sum< ::dynamics::getGRequest>
{
  static const char* value()
  {
    return MD5Sum< ::dynamics::getG >::value();
  }
  static const char* value(const ::dynamics::getGRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::dynamics::getGRequest> should match 
// service_traits::DataType< ::dynamics::getG > 
template<>
struct DataType< ::dynamics::getGRequest>
{
  static const char* value()
  {
    return DataType< ::dynamics::getG >::value();
  }
  static const char* value(const ::dynamics::getGRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::dynamics::getGResponse> should match 
// service_traits::MD5Sum< ::dynamics::getG > 
template<>
struct MD5Sum< ::dynamics::getGResponse>
{
  static const char* value()
  {
    return MD5Sum< ::dynamics::getG >::value();
  }
  static const char* value(const ::dynamics::getGResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::dynamics::getGResponse> should match 
// service_traits::DataType< ::dynamics::getG > 
template<>
struct DataType< ::dynamics::getGResponse>
{
  static const char* value()
  {
    return DataType< ::dynamics::getG >::value();
  }
  static const char* value(const ::dynamics::getGResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // DYNAMICS_MESSAGE_GETG_H
