;; Auto-generated. Do not edit!


(when (boundp 'dynamics::getJ)
  (if (not (find-package "DYNAMICS"))
    (make-package "DYNAMICS"))
  (shadow 'getJ (find-package "DYNAMICS")))
(unless (find-package "DYNAMICS::GETJ")
  (make-package "DYNAMICS::GETJ"))
(unless (find-package "DYNAMICS::GETJREQUEST")
  (make-package "DYNAMICS::GETJREQUEST"))
(unless (find-package "DYNAMICS::GETJRESPONSE")
  (make-package "DYNAMICS::GETJRESPONSE"))

(in-package "ROS")





(defclass dynamics::getJRequest
  :super ros::object
  :slots (_q ))

(defmethod dynamics::getJRequest
  (:init
   (&key
    ((:q __q) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _q __q)
   self)
  (:q
   (&optional __q)
   (if __q (setq _q __q)) _q)
  (:serialization-length
   ()
   (+
    ;; float64[] _q
    (* 8    (length _q)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[] _q
     (write-long (length _q) s)
     (dotimes (i (length _q))
       (sys::poke (elt _q i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[] _q
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _q (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _q i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(defclass dynamics::getJResponse
  :super ros::object
  :slots (_J ))

(defmethod dynamics::getJResponse
  (:init
   (&key
    ((:J __J) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _J __J)
   self)
  (:J
   (&optional __J)
   (if __J (setq _J __J)) _J)
  (:serialization-length
   ()
   (+
    ;; float64[] _J
    (* 8    (length _J)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[] _J
     (write-long (length _J) s)
     (dotimes (i (length _J))
       (sys::poke (elt _J i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[] _J
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _J (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _J i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(defclass dynamics::getJ
  :super ros::object
  :slots ())

(setf (get dynamics::getJ :md5sum-) "06a3de3817aa53a10640e08369b1085e")
(setf (get dynamics::getJ :datatype-) "dynamics/getJ")
(setf (get dynamics::getJ :request) dynamics::getJRequest)
(setf (get dynamics::getJ :response) dynamics::getJResponse)

(defmethod dynamics::getJRequest
  (:response () (instance dynamics::getJResponse :init)))

(setf (get dynamics::getJRequest :md5sum-) "06a3de3817aa53a10640e08369b1085e")
(setf (get dynamics::getJRequest :datatype-) "dynamics/getJRequest")
(setf (get dynamics::getJRequest :definition-)
      "float64[] q
---
float64[] J
")

(setf (get dynamics::getJResponse :md5sum-) "06a3de3817aa53a10640e08369b1085e")
(setf (get dynamics::getJResponse :datatype-) "dynamics/getJResponse")
(setf (get dynamics::getJResponse :definition-)
      "float64[] q
---
float64[] J
")



(provide :dynamics/getJ "06a3de3817aa53a10640e08369b1085e")


