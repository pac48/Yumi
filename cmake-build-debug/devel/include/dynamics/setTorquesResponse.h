// Generated by gencpp from file dynamics/setTorquesResponse.msg
// DO NOT EDIT!


#ifndef DYNAMICS_MESSAGE_SETTORQUESRESPONSE_H
#define DYNAMICS_MESSAGE_SETTORQUESRESPONSE_H


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
struct setTorquesResponse_
{
  typedef setTorquesResponse_<ContainerAllocator> Type;

  setTorquesResponse_()
    : qdd()  {
    }
  setTorquesResponse_(const ContainerAllocator& _alloc)
    : qdd(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _qdd_type;
  _qdd_type qdd;





  typedef boost::shared_ptr< ::dynamics::setTorquesResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::dynamics::setTorquesResponse_<ContainerAllocator> const> ConstPtr;

}; // struct setTorquesResponse_

typedef ::dynamics::setTorquesResponse_<std::allocator<void> > setTorquesResponse;

typedef boost::shared_ptr< ::dynamics::setTorquesResponse > setTorquesResponsePtr;
typedef boost::shared_ptr< ::dynamics::setTorquesResponse const> setTorquesResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::dynamics::setTorquesResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::dynamics::setTorquesResponse_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::dynamics::setTorquesResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::dynamics::setTorquesResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dynamics::setTorquesResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dynamics::setTorquesResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dynamics::setTorquesResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dynamics::setTorquesResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::dynamics::setTorquesResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "f9f5346aad9a21a7c1a3fdc3006a6c17";
  }

  static const char* value(const ::dynamics::setTorquesResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xf9f5346aad9a21a7ULL;
  static const uint64_t static_value2 = 0xc1a3fdc3006a6c17ULL;
};

template<class ContainerAllocator>
struct DataType< ::dynamics::setTorquesResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dynamics/setTorquesResponse";
  }

  static const char* value(const ::dynamics::setTorquesResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::dynamics::setTorquesResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64[] qdd\n\
";
  }

  static const char* value(const ::dynamics::setTorquesResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::dynamics::setTorquesResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.qdd);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct setTorquesResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::dynamics::setTorquesResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::dynamics::setTorquesResponse_<ContainerAllocator>& v)
  {
    s << indent << "qdd[]" << std::endl;
    for (size_t i = 0; i < v.qdd.size(); ++i)
    {
      s << indent << "  qdd[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.qdd[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // DYNAMICS_MESSAGE_SETTORQUESRESPONSE_H
