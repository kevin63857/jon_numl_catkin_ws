; Auto-generated. Do not edit!


(cl:in-package myo_raw-msg)


;//! \htmlinclude EMGData.msg.html

(cl:defclass <EMGData> (roslisp-msg-protocol:ros-message)
  ((emg_data
    :reader emg_data
    :initarg :emg_data
    :type (cl:vector cl:integer)
   :initform (cl:make-array 8 :element-type 'cl:integer :initial-element 0))
   (moving
    :reader moving
    :initarg :moving
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass EMGData (<EMGData>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <EMGData>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'EMGData)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name myo_raw-msg:<EMGData> is deprecated: use myo_raw-msg:EMGData instead.")))

(cl:ensure-generic-function 'emg_data-val :lambda-list '(m))
(cl:defmethod emg_data-val ((m <EMGData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader myo_raw-msg:emg_data-val is deprecated.  Use myo_raw-msg:emg_data instead.")
  (emg_data m))

(cl:ensure-generic-function 'moving-val :lambda-list '(m))
(cl:defmethod moving-val ((m <EMGData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader myo_raw-msg:moving-val is deprecated.  Use myo_raw-msg:moving instead.")
  (moving m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <EMGData>) ostream)
  "Serializes a message object of type '<EMGData>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) ele) ostream))
   (cl:slot-value msg 'emg_data))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'moving) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <EMGData>) istream)
  "Deserializes a message object of type '<EMGData>"
  (cl:setf (cl:slot-value msg 'emg_data) (cl:make-array 8))
  (cl:let ((vals (cl:slot-value msg 'emg_data)))
    (cl:dotimes (i 8)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:aref vals i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:aref vals i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:aref vals i)) (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'moving) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<EMGData>)))
  "Returns string type for a message object of type '<EMGData>"
  "myo_raw/EMGData")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'EMGData)))
  "Returns string type for a message object of type 'EMGData"
  "myo_raw/EMGData")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<EMGData>)))
  "Returns md5sum for a message object of type '<EMGData>"
  "cacb00d78b8d8a4ba46dcd469cd1cda3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'EMGData)))
  "Returns md5sum for a message object of type 'EMGData"
  "cacb00d78b8d8a4ba46dcd469cd1cda3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<EMGData>)))
  "Returns full string definition for message of type '<EMGData>"
  (cl:format cl:nil "# Provides access to the raw emg data off the sensor~%# Useful to try and write your own classifier~%~%~%# The raw sensor reading off of each of the 8 emg sensors~%# note this reading is dependent on the rotation of the sensor~%# on the arm~%uint32[8] emg_data~%~%# Was the sensor moving during this reading~%bool     moving~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'EMGData)))
  "Returns full string definition for message of type 'EMGData"
  (cl:format cl:nil "# Provides access to the raw emg data off the sensor~%# Useful to try and write your own classifier~%~%~%# The raw sensor reading off of each of the 8 emg sensors~%# note this reading is dependent on the rotation of the sensor~%# on the arm~%uint32[8] emg_data~%~%# Was the sensor moving during this reading~%bool     moving~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <EMGData>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'emg_data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <EMGData>))
  "Converts a ROS message object to a list"
  (cl:list 'EMGData
    (cl:cons ':emg_data (emg_data msg))
    (cl:cons ':moving (moving msg))
))
