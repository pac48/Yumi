;; Auto-generated. Do not edit!


(when (boundp 'dynamics::setTorques)
  (if (not (find-package "DYNAMICS"))
    (make-package "DYNAMICS"))
  (shadow 'setTorques (find-package "DYNAMICS")))
(unless (find-package "DYNAMICS::SETTORQUES")
  (make-package "DYNAMICS::SETTORQUES"))
(unless (find-package "DYNAMICS::SETTORQUESREQUEST")
  (make-package "DYNAMICS::SETTORQUESREQUEST"))
(unless (find-package "DYNAMICS::SETTORQUESRESPONSE")
  (make-package "DYNAMICS::SETTORQUESRESPONSE"))

(in-package "ROS")





(defclass dynamics::setTorquesRequest
  :super ros::object
  :slots (_tau ))

(defmethod dynamics::setTorquesRequest
  (:init
   (&key
    ((:tau __tau) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _tau __tau)
   self)
  (:tau
   (&optional __tau)
   (if __tau (setq _tau __tau)) _tau)
  (:serialization-length
   ()
   (+
    ;; float64[] _tau
    (* 8    (length _tau)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[] _tau
     (write-long (length _tau) s)
     (dotimes (i (length _tau))
       (sys::poke (elt _tau i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[] _tau
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _tau (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _tau i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(defclass dynamics::setTorquesResponse
  :super ros::object
  :slots (_qdd ))

(defmethod dynamics::setTorquesResponse
  (:init
   (&key
    ((:qdd __qdd) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _qdd __qdd)
   self)
  (:qdd
   (&optional __qdd)
   (if __qdd (setq _qdd __qdd)) _qdd)
  (:serialization-length
   ()
   (+
    ;; float64[] _qdd
    (* 8    (length _qdd)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[] _qdd
     (write-long (length _qdd) s)
     (dotimes (i (length _qdd))
       (sys::poke (elt _qdd i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[] _qdd
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _qdd (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _qdd i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(defclass dynamics::setTorques
  :super ros::object
  :slots ())

(setf (get dynamics::setTorques :md5sum-) "e58e0e3410894d2e4992e2dd98c576ea")
(setf (get dynamics::setTorques :datatype-) "dynamics/setTorques")
(setf (get dynamics::setTorques :request) dynamics::setTorquesRequest)
(setf (get dynamics::setTorques :response) dynamics::setTorquesResponse)

(defmethod dynamics::setTorquesRequest
  (:response () (instance dynamics::setTorquesResponse :init)))

(setf (get dynamics::setTorquesRequest :md5sum-) "e58e0e3410894d2e4992e2dd98c576ea")
(setf (get dynamics::setTorquesRequest :datatype-) "dynamics/setTorquesRequest")
(setf (get dynamics::setTorquesRequest :definition-)
      "float64[] tau
---
float64[] qdd
")

(setf (get dynamics::setTorquesResponse :md5sum-) "e58e0e3410894d2e4992e2dd98c576ea")
(setf (get dynamics::setTorquesResponse :datatype-) "dynamics/setTorquesResponse")
(setf (get dynamics::setTorquesResponse :definition-)
      "float64[] tau
---
float64[] qdd
")



(provide :dynamics/setTorques "e58e0e3410894d2e4992e2dd98c576ea")


