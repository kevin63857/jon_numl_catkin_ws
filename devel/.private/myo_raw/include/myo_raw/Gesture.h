// Generated by gencpp from file myo_raw/Gesture.msg
// DO NOT EDIT!


#ifndef MYO_RAW_MESSAGE_GESTURE_H
#define MYO_RAW_MESSAGE_GESTURE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace myo_raw
{
template <class ContainerAllocator>
struct Gesture_
{
  typedef Gesture_<ContainerAllocator> Type;

  Gesture_()
    : is_builtin(false)
    , pose_number(0)
    , confidence(0.0)  {
    }
  Gesture_(const ContainerAllocator& _alloc)
    : is_builtin(false)
    , pose_number(0)
    , confidence(0.0)  {
  (void)_alloc;
    }



   typedef uint8_t _is_builtin_type;
  _is_builtin_type is_builtin;

   typedef int32_t _pose_number_type;
  _pose_number_type pose_number;

   typedef double _confidence_type;
  _confidence_type confidence;


    enum { POSE_REST = 0 };
     enum { POSE_FIST = 1 };
     enum { POSE_WAVE_IN = 2 };
     enum { POSE_WAVE_OUT = 3 };
     enum { POSE_FINGERS_SPREAD = 4 };
     enum { POSE_THUMB_TO_PINKY = 5 };
     enum { POSE_UNKNOWN = 255 };
 

  typedef boost::shared_ptr< ::myo_raw::Gesture_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::myo_raw::Gesture_<ContainerAllocator> const> ConstPtr;

}; // struct Gesture_

typedef ::myo_raw::Gesture_<std::allocator<void> > Gesture;

typedef boost::shared_ptr< ::myo_raw::Gesture > GesturePtr;
typedef boost::shared_ptr< ::myo_raw::Gesture const> GestureConstPtr;

// constants requiring out of line definition

   

   

   

   

   

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::myo_raw::Gesture_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::myo_raw::Gesture_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace myo_raw

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'myo_raw': ['/home/hoenir/numl_catkin_ws/src/myo_raw/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::myo_raw::Gesture_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::myo_raw::Gesture_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::myo_raw::Gesture_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::myo_raw::Gesture_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::myo_raw::Gesture_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::myo_raw::Gesture_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::myo_raw::Gesture_<ContainerAllocator> >
{
  static const char* value()
  {
    return "61762cbfd8d8bfa53ae334cb6f8d76a3";
  }

  static const char* value(const ::myo_raw::Gesture_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x61762cbfd8d8bfa5ULL;
  static const uint64_t static_value2 = 0x3ae334cb6f8d76a3ULL;
};

template<class ContainerAllocator>
struct DataType< ::myo_raw::Gesture_<ContainerAllocator> >
{
  static const char* value()
  {
    return "myo_raw/Gesture";
  }

  static const char* value(const ::myo_raw::Gesture_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::myo_raw::Gesture_<ContainerAllocator> >
{
  static const char* value()
  {
    return "## A Gesture message can be used in place of the built in EMGData message\n\
## The gestures can either be trained using the myo_raw myo_classifier\n\
## of builtins (for api version 1+)\n\
\n\
# What a pose means if it's a builtin\n\
int32 POSE_REST = 0\n\
int32 POSE_FIST = 1\n\
int32 POSE_WAVE_IN = 2\n\
int32 POSE_WAVE_OUT = 3\n\
int32 POSE_FINGERS_SPREAD = 4\n\
int32 POSE_THUMB_TO_PINKY = 5\n\
int32 POSE_UNKNOWN = 255\n\
\n\
# Was the pose a builtin from the myo api and not a manually trained one\n\
bool 	is_builtin\n\
\n\
# Either the trained pose number or one of the built-ins\n\
# note the default classifier only can have a pose number from 0 to 9\n\
int32   pose_number\n\
\n\
# How confident was the built in classifier that this pose was accurate\n\
# will be 0 if the pose was a builtin\n\
float64 confidence\n\
";
  }

  static const char* value(const ::myo_raw::Gesture_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::myo_raw::Gesture_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.is_builtin);
      stream.next(m.pose_number);
      stream.next(m.confidence);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Gesture_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::myo_raw::Gesture_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::myo_raw::Gesture_<ContainerAllocator>& v)
  {
    s << indent << "is_builtin: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.is_builtin);
    s << indent << "pose_number: ";
    Printer<int32_t>::stream(s, indent + "  ", v.pose_number);
    s << indent << "confidence: ";
    Printer<double>::stream(s, indent + "  ", v.confidence);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MYO_RAW_MESSAGE_GESTURE_H