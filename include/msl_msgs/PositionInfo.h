// Generated by gencpp from file msl_msgs/PositionInfo.msg
// DO NOT EDIT!


#ifndef MSL_MSGS_MESSAGE_POSITIONINFO_H
#define MSL_MSGS_MESSAGE_POSITIONINFO_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace msl_msgs
{
template <class ContainerAllocator>
struct PositionInfo_
{
  typedef PositionInfo_<ContainerAllocator> Type;

  PositionInfo_()
    : x(0.0)
    , y(0.0)
    , angle(0.0)
    , certainty(0.0)  {
    }
  PositionInfo_(const ContainerAllocator& _alloc)
    : x(0.0)
    , y(0.0)
    , angle(0.0)
    , certainty(0.0)  {
  (void)_alloc;
    }



   typedef double _x_type;
  _x_type x;

   typedef double _y_type;
  _y_type y;

   typedef double _angle_type;
  _angle_type angle;

   typedef double _certainty_type;
  _certainty_type certainty;




  typedef boost::shared_ptr< ::msl_msgs::PositionInfo_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::msl_msgs::PositionInfo_<ContainerAllocator> const> ConstPtr;

}; // struct PositionInfo_

typedef ::msl_msgs::PositionInfo_<std::allocator<void> > PositionInfo;

typedef boost::shared_ptr< ::msl_msgs::PositionInfo > PositionInfoPtr;
typedef boost::shared_ptr< ::msl_msgs::PositionInfo const> PositionInfoConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::msl_msgs::PositionInfo_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::msl_msgs::PositionInfo_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace msl_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'msl_msgs': ['/home/paspartout/cnws/src/cnc-msl/msl_msgs/msg'], 'std_msgs': ['/home/paspartout/dev/pro/ros-void/ros_catkin_ws/install_isolated/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/home/paspartout/cnws/src/common_msgs/geometry_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::msl_msgs::PositionInfo_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::msl_msgs::PositionInfo_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::msl_msgs::PositionInfo_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::msl_msgs::PositionInfo_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::msl_msgs::PositionInfo_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::msl_msgs::PositionInfo_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::msl_msgs::PositionInfo_<ContainerAllocator> >
{
  static const char* value()
  {
    return "4c45eacfd4118121cfbaa8603ecc1c8c";
  }

  static const char* value(const ::msl_msgs::PositionInfo_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x4c45eacfd4118121ULL;
  static const uint64_t static_value2 = 0xcfbaa8603ecc1c8cULL;
};

template<class ContainerAllocator>
struct DataType< ::msl_msgs::PositionInfo_<ContainerAllocator> >
{
  static const char* value()
  {
    return "msl_msgs/PositionInfo";
  }

  static const char* value(const ::msl_msgs::PositionInfo_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::msl_msgs::PositionInfo_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 x\n\
float64 y\n\
float64 angle\n\
float64 certainty\n\
";
  }

  static const char* value(const ::msl_msgs::PositionInfo_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::msl_msgs::PositionInfo_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.x);
      stream.next(m.y);
      stream.next(m.angle);
      stream.next(m.certainty);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PositionInfo_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::msl_msgs::PositionInfo_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::msl_msgs::PositionInfo_<ContainerAllocator>& v)
  {
    s << indent << "x: ";
    Printer<double>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    Printer<double>::stream(s, indent + "  ", v.y);
    s << indent << "angle: ";
    Printer<double>::stream(s, indent + "  ", v.angle);
    s << indent << "certainty: ";
    Printer<double>::stream(s, indent + "  ", v.certainty);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MSL_MSGS_MESSAGE_POSITIONINFO_H
