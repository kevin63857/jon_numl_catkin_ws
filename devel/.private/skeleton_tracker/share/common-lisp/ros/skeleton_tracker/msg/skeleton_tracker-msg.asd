
(cl:in-package :asdf)

(defsystem "skeleton_tracker-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "user_IDs" :depends-on ("_package_user_IDs"))
    (:file "_package_user_IDs" :depends-on ("_package"))
  ))