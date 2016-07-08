
(cl:in-package :asdf)

(defsystem "myo_raw-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "IMUData" :depends-on ("_package_IMUData"))
    (:file "_package_IMUData" :depends-on ("_package"))
    (:file "EMGData" :depends-on ("_package_EMGData"))
    (:file "_package_EMGData" :depends-on ("_package"))
    (:file "MyoArm" :depends-on ("_package_MyoArm"))
    (:file "_package_MyoArm" :depends-on ("_package"))
    (:file "Gesture" :depends-on ("_package_Gesture"))
    (:file "_package_Gesture" :depends-on ("_package"))
  ))