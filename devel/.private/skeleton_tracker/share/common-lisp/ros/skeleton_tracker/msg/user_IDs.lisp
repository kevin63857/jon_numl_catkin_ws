; Auto-generated. Do not edit!


(cl:in-package skeleton_tracker-msg)


;//! \htmlinclude user_IDs.msg.html

(cl:defclass <user_IDs> (roslisp-msg-protocol:ros-message)
  ((users
    :reader users
    :initarg :users
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 0 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass user_IDs (<user_IDs>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <user_IDs>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'user_IDs)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name skeleton_tracker-msg:<user_IDs> is deprecated: use skeleton_tracker-msg:user_IDs instead.")))

(cl:ensure-generic-function 'users-val :lambda-list '(m))
(cl:defmethod users-val ((m <user_IDs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader skeleton_tracker-msg:users-val is deprecated.  Use skeleton_tracker-msg:users instead.")
  (users m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <user_IDs>) ostream)
  "Serializes a message object of type '<user_IDs>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'users))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'users))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <user_IDs>) istream)
  "Deserializes a message object of type '<user_IDs>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'users) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'users)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<user_IDs>)))
  "Returns string type for a message object of type '<user_IDs>"
  "skeleton_tracker/user_IDs")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'user_IDs)))
  "Returns string type for a message object of type 'user_IDs"
  "skeleton_tracker/user_IDs")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<user_IDs>)))
  "Returns md5sum for a message object of type '<user_IDs>"
  "0370fea64fb82134b7a78a66cb25797c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'user_IDs)))
  "Returns md5sum for a message object of type 'user_IDs"
  "0370fea64fb82134b7a78a66cb25797c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<user_IDs>)))
  "Returns full string definition for message of type '<user_IDs>"
  (cl:format cl:nil "uint8[] users~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'user_IDs)))
  "Returns full string definition for message of type 'user_IDs"
  (cl:format cl:nil "uint8[] users~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <user_IDs>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'users) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <user_IDs>))
  "Converts a ROS message object to a list"
  (cl:list 'user_IDs
    (cl:cons ':users (users msg))
))
