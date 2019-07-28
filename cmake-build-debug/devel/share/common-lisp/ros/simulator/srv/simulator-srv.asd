
(cl:in-package :asdf)

(defsystem "simulator-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "getStaticTorques" :depends-on ("_package_getStaticTorques"))
    (:file "_package_getStaticTorques" :depends-on ("_package"))
  ))