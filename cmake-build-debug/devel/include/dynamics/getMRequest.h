// Generated by gencpp from file dynamics/getMRequest.msg
// DO NOT EDIT!


#ifndef DYNAMICS_MESSAGE_GETMREQUEST_H
#define DYNAMICS_MESSAGE_GETMREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace dynamics
{
template <class ContainerAllocator>
struct getMRequest_
{
  typedef getMRequest_<ContainerAllocator> Type;

  getMRequest_()
    : q()  {
    }
  getMRequest_(const ContainerAllocator& _alloc)
    : q(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _q_type;
  _q_type q;





  typedef boost::shared_ptr< ::dynamics::getMRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::dynamics::getMRequest_<ContainerAllocator> const> ConstPtr;

}; // struct getMRequest_

typedef ::dynamics::getMRequest_<std::allocator<void> > getMRequest;

typedef boost::shared_ptr< ::dynamics::getMRequest > getMRequestPtr;
typedef boost::shared_ptr< ::dynamics::getMRequest const> getMRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::dynamics::getMRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::dynamics::getMRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace dynamics

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::dynamics::getMRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::dynamics::getMRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dynamics::getMRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dynamics::getMRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dynamics::getMRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dynamics::getMRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::dynamics::getMRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ab94b9bcaaa12f74def43e4b33992df1";
  }

  static const char* value(const ::dynamics::getMRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xab94b9bcaaa12f74ULL;
  static const uint64_t static_value2 = 0xdef43e4b33992df1ULL;
};

template<class ContainerAllocator>
struct DataType< ::dynamics::getMRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dynamics/getMRequest";
  }

  static const char* value(const ::dynamics::getMRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::dynamics::getMRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64[] q\n\
";
  }

  static const char* value(const ::dynamics::getMRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::dynamics::getMRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.q);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct getMRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::dynamics::getMRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::dynamics::getMRequest_<ContainerAllocator>& v)
  {
    s << indent << "q[]" << std::endl;
    for (size_t i = 0; i < v.q.size(); ++i)
    {
      s << indent << "  q[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.q[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // DYNAMICS_MESSAGE_GETMREQUEST_H
