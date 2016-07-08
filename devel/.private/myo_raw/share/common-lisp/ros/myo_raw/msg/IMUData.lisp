; Auto-generated. Do not edit!


(cl:in-package myo_raw-msg)


;//! \htmlinclude IMUData.msg.html

(cl:defclass <IMUData> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (orientation
    :reader orientation
    :initarg :orientation
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (angular_velocity
    :reader angular_velocity
    :initarg :angular_velocity
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (linear_acceleration
    :reader linear_acceleration
    :initarg :linear_acceleration
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass IMUData (<IMUData>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <IMUData>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'IMUData)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name myo_raw-msg:<IMUData> is deprecated: use myo_raw-msg:IMUData instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <IMUData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader myo_raw-msg:header-val is deprecated.  Use myo_raw-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'orientation-val :lambda-list '(m))
(cl:defmethod orientation-val ((m <IMUData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader myo_raw-msg:orientation-val is deprecated.  Use myo_raw-msg:orientation instead.")
  (orientation m))

(cl:ensure-generic-function 'angular_velocity-val :lambda-list '(m))
(cl:defmethod angular_velocity-val ((m <IMUData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader myo_raw-msg:angular_velocity-val is deprecated.  Use myo_raw-msg:angular_velocity instead.")
  (angular_velocity m))

(cl:ensure-generic-function 'linear_acceleration-val :lambda-list '(m))
(cl:defmethod linear_acceleration-val ((m <IMUData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader myo_raw-msg:linear_acceleration-val is deprecated.  Use myo_raw-msg:linear_acceleration instead.")
  (linear_acceleration m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <IMUData>) ostream)
  "Serializes a message object of type '<IMUData>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'orientation) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'angular_velocity) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'linear_acceleration) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <IMUData>) istream)
  "Deserializes a message object of type '<IMUData>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'orientation) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'angular_velocity) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'linear_acceleration) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<IMUData>)))
  "Returns string type for a message object of type '<IMUData>"
  "myo_raw/IMUData")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'IMUData)))
  "Returns string type for a message object of type 'IMUData"
  "myo_raw/IMUData")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<IMUData>)))
  "Returns md5sum for a message object of type '<IMUData>"
  "fab8ee977726a5efe69ff134b60a4a0c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'IMUData)))
  "Returns md5sum for a message object of type 'IMUData"
  "fab8ee977726a5efe69ff134b60a4a0c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<IMUData>)))
  "Returns full string definition for message of type '<IMUData>"
  (cl:format cl:nil "# This is a message to hold data from an IMU (Inertial Measurement Unit)~%#~%# Accelerations should be in m/s^2 (not in g's), and angular velocity should be in rad/sec~%~%Header header~%~%#geometry_msgs/Quaternion orientation # user quaternion coordinates~%#float64[9] orientation_covariance # Row major about x, y, z axes~%geometry_msgs/Vector3 orientation # use euler angles~%~%geometry_msgs/Vector3 angular_velocity~%#float64[9] angular_velocity_covariance # Row major about x, y, z axes~%~%geometry_msgs/Vector3 linear_acceleration~%#float64[9] linear_acceleration_covariance # Row major x, y z ~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'IMUData)))
  "Returns full string definition for message of type 'IMUData"
  (cl:format cl:nil "# This is a message to hold data from an IMU (Inertial Measurement Unit)~%#~%# Accelerations should be in m/s^2 (not in g's), and angular velocity should be in rad/sec~%~%Header header~%~%#geometry_msgs/Quaternion orientation # user quaternion coordinates~%#float64[9] orientation_covariance # Row major about x, y, z axes~%geometry_msgs/Vector3 orientation # use euler angles~%~%geometry_msgs/Vector3 angular_velocity~%#float64[9] angular_velocity_covariance # Row major about x, y, z axes~%~%geometry_msgs/Vector3 linear_acceleration~%#float64[9] linear_acceleration_covariance # Row major x, y z ~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <IMUData>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'orientation))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'angular_velocity))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'linear_acceleration))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <IMUData>))
  "Converts a ROS message object to a list"
  (cl:list 'IMUData
    (cl:cons ':header (header msg))
    (cl:cons ':orientation (orientation msg))
    (cl:cons ':angular_velocity (angular_velocity msg))
    (cl:cons ':linear_acceleration (linear_acceleration msg))
))
