; Auto-generated. Do not edit!


(cl:in-package myo_raw-msg)


;//! \htmlinclude MyoArm.msg.html

(cl:defclass <MyoArm> (roslisp-msg-protocol:ros-message)
  ((arm
    :reader arm
    :initarg :arm
    :type cl:integer
    :initform 0)
   (xdir
    :reader xdir
    :initarg :xdir
    :type cl:integer
    :initform 0))
)

(cl:defclass MyoArm (<MyoArm>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MyoArm>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MyoArm)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name myo_raw-msg:<MyoArm> is deprecated: use myo_raw-msg:MyoArm instead.")))

(cl:ensure-generic-function 'arm-val :lambda-list '(m))
(cl:defmethod arm-val ((m <MyoArm>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader myo_raw-msg:arm-val is deprecated.  Use myo_raw-msg:arm instead.")
  (arm m))

(cl:ensure-generic-function 'xdir-val :lambda-list '(m))
(cl:defmethod xdir-val ((m <MyoArm>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader myo_raw-msg:xdir-val is deprecated.  Use myo_raw-msg:xdir instead.")
  (xdir m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<MyoArm>)))
    "Constants for message type '<MyoArm>"
  '((:ARM_UNKNOWN . 0)
    (:ARM_RIGHT . 1)
    (:ARM_LEFT . 2)
    (:XDIR_UNKNOWN . 0)
    (:XDIR_TOWARD_WRIST . 1)
    (:XDIR_TOWARD_ELBOW . 2))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'MyoArm)))
    "Constants for message type 'MyoArm"
  '((:ARM_UNKNOWN . 0)
    (:ARM_RIGHT . 1)
    (:ARM_LEFT . 2)
    (:XDIR_UNKNOWN . 0)
    (:XDIR_TOWARD_WRIST . 1)
    (:XDIR_TOWARD_ELBOW . 2))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MyoArm>) ostream)
  "Serializes a message object of type '<MyoArm>"
  (cl:let* ((signed (cl:slot-value msg 'arm)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'xdir)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MyoArm>) istream)
  "Deserializes a message object of type '<MyoArm>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'arm) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'xdir) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MyoArm>)))
  "Returns string type for a message object of type '<MyoArm>"
  "myo_raw/MyoArm")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MyoArm)))
  "Returns string type for a message object of type 'MyoArm"
  "myo_raw/MyoArm")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MyoArm>)))
  "Returns md5sum for a message object of type '<MyoArm>"
  "ef98f3b0198c2ce3840df4d4d22e916b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MyoArm)))
  "Returns md5sum for a message object of type 'MyoArm"
  "ef98f3b0198c2ce3840df4d4d22e916b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MyoArm>)))
  "Returns full string definition for message of type '<MyoArm>"
  (cl:format cl:nil "## A MyoArm message can be used to determine the last known~%## arm the myo was determined to be on (only sent for API version 1+)~%~%int32 ARM_UNKNOWN = 0~%int32 ARM_RIGHT = 1~%int32 ARM_LEFT = 2~%~%int32 XDIR_UNKNOWN = 0~%int32 XDIR_TOWARD_WRIST = 1~%int32 XDIR_TOWARD_ELBOW = 2~%~%~%# Which arm is the myo currently on~%int32 arm~%~%# What is the determined x direction (is is the light up or down)~%# In other words is the light pointing up or down?~%int32 xdir~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MyoArm)))
  "Returns full string definition for message of type 'MyoArm"
  (cl:format cl:nil "## A MyoArm message can be used to determine the last known~%## arm the myo was determined to be on (only sent for API version 1+)~%~%int32 ARM_UNKNOWN = 0~%int32 ARM_RIGHT = 1~%int32 ARM_LEFT = 2~%~%int32 XDIR_UNKNOWN = 0~%int32 XDIR_TOWARD_WRIST = 1~%int32 XDIR_TOWARD_ELBOW = 2~%~%~%# Which arm is the myo currently on~%int32 arm~%~%# What is the determined x direction (is is the light up or down)~%# In other words is the light pointing up or down?~%int32 xdir~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MyoArm>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MyoArm>))
  "Converts a ROS message object to a list"
  (cl:list 'MyoArm
    (cl:cons ':arm (arm msg))
    (cl:cons ':xdir (xdir msg))
))
