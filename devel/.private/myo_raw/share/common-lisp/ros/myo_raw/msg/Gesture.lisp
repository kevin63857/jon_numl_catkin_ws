; Auto-generated. Do not edit!


(cl:in-package myo_raw-msg)


;//! \htmlinclude Gesture.msg.html

(cl:defclass <Gesture> (roslisp-msg-protocol:ros-message)
  ((is_builtin
    :reader is_builtin
    :initarg :is_builtin
    :type cl:boolean
    :initform cl:nil)
   (pose_number
    :reader pose_number
    :initarg :pose_number
    :type cl:integer
    :initform 0)
   (confidence
    :reader confidence
    :initarg :confidence
    :type cl:float
    :initform 0.0))
)

(cl:defclass Gesture (<Gesture>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Gesture>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Gesture)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name myo_raw-msg:<Gesture> is deprecated: use myo_raw-msg:Gesture instead.")))

(cl:ensure-generic-function 'is_builtin-val :lambda-list '(m))
(cl:defmethod is_builtin-val ((m <Gesture>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader myo_raw-msg:is_builtin-val is deprecated.  Use myo_raw-msg:is_builtin instead.")
  (is_builtin m))

(cl:ensure-generic-function 'pose_number-val :lambda-list '(m))
(cl:defmethod pose_number-val ((m <Gesture>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader myo_raw-msg:pose_number-val is deprecated.  Use myo_raw-msg:pose_number instead.")
  (pose_number m))

(cl:ensure-generic-function 'confidence-val :lambda-list '(m))
(cl:defmethod confidence-val ((m <Gesture>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader myo_raw-msg:confidence-val is deprecated.  Use myo_raw-msg:confidence instead.")
  (confidence m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<Gesture>)))
    "Constants for message type '<Gesture>"
  '((:POSE_REST . 0)
    (:POSE_FIST . 1)
    (:POSE_WAVE_IN . 2)
    (:POSE_WAVE_OUT . 3)
    (:POSE_FINGERS_SPREAD . 4)
    (:POSE_THUMB_TO_PINKY . 5)
    (:POSE_UNKNOWN . 255))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'Gesture)))
    "Constants for message type 'Gesture"
  '((:POSE_REST . 0)
    (:POSE_FIST . 1)
    (:POSE_WAVE_IN . 2)
    (:POSE_WAVE_OUT . 3)
    (:POSE_FINGERS_SPREAD . 4)
    (:POSE_THUMB_TO_PINKY . 5)
    (:POSE_UNKNOWN . 255))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Gesture>) ostream)
  "Serializes a message object of type '<Gesture>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_builtin) 1 0)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'pose_number)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'confidence))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Gesture>) istream)
  "Deserializes a message object of type '<Gesture>"
    (cl:setf (cl:slot-value msg 'is_builtin) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'pose_number) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'confidence) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Gesture>)))
  "Returns string type for a message object of type '<Gesture>"
  "myo_raw/Gesture")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Gesture)))
  "Returns string type for a message object of type 'Gesture"
  "myo_raw/Gesture")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Gesture>)))
  "Returns md5sum for a message object of type '<Gesture>"
  "61762cbfd8d8bfa53ae334cb6f8d76a3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Gesture)))
  "Returns md5sum for a message object of type 'Gesture"
  "61762cbfd8d8bfa53ae334cb6f8d76a3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Gesture>)))
  "Returns full string definition for message of type '<Gesture>"
  (cl:format cl:nil "## A Gesture message can be used in place of the built in EMGData message~%## The gestures can either be trained using the myo_raw myo_classifier~%## of builtins (for api version 1+)~%~%# What a pose means if it's a builtin~%int32 POSE_REST = 0~%int32 POSE_FIST = 1~%int32 POSE_WAVE_IN = 2~%int32 POSE_WAVE_OUT = 3~%int32 POSE_FINGERS_SPREAD = 4~%int32 POSE_THUMB_TO_PINKY = 5~%int32 POSE_UNKNOWN = 255~%~%# Was the pose a builtin from the myo api and not a manually trained one~%bool 	is_builtin~%~%# Either the trained pose number or one of the built-ins~%# note the default classifier only can have a pose number from 0 to 9~%int32   pose_number~%~%# How confident was the built in classifier that this pose was accurate~%# will be 0 if the pose was a builtin~%float64 confidence~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Gesture)))
  "Returns full string definition for message of type 'Gesture"
  (cl:format cl:nil "## A Gesture message can be used in place of the built in EMGData message~%## The gestures can either be trained using the myo_raw myo_classifier~%## of builtins (for api version 1+)~%~%# What a pose means if it's a builtin~%int32 POSE_REST = 0~%int32 POSE_FIST = 1~%int32 POSE_WAVE_IN = 2~%int32 POSE_WAVE_OUT = 3~%int32 POSE_FINGERS_SPREAD = 4~%int32 POSE_THUMB_TO_PINKY = 5~%int32 POSE_UNKNOWN = 255~%~%# Was the pose a builtin from the myo api and not a manually trained one~%bool 	is_builtin~%~%# Either the trained pose number or one of the built-ins~%# note the default classifier only can have a pose number from 0 to 9~%int32   pose_number~%~%# How confident was the built in classifier that this pose was accurate~%# will be 0 if the pose was a builtin~%float64 confidence~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Gesture>))
  (cl:+ 0
     1
     4
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Gesture>))
  "Converts a ROS message object to a list"
  (cl:list 'Gesture
    (cl:cons ':is_builtin (is_builtin msg))
    (cl:cons ':pose_number (pose_number msg))
    (cl:cons ':confidence (confidence msg))
))
