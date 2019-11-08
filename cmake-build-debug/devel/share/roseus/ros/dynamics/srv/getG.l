;; Auto-generated. Do not edit!


(when (boundp 'dynamics::getG)
  (if (not (find-package "DYNAMICS"))
    (make-package "DYNAMICS"))
  (shadow 'getG (find-package "DYNAMICS")))
(unless (find-package "DYNAMICS::GETG")
  (make-package "DYNAMICS::GETG"))
(unless (find-package "DYNAMICS::GETGREQUEST")
  (make-package "DYNAMICS::GETGREQUEST"))
(unless (find-package "DYNAMICS::GETGRESPONSE")
  (make-package "DYNAMICS::GETGRESPONSE"))

(in-package "ROS")





(defclass dynamics::getGRequest
  :super ros::object
  :slots (_q ))

(defmethod dynamics::getGRequest
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

(defclass dynamics::getGResponse
  :super ros::object
  :slots (_g ))

(defmethod dynamics::getGResponse
  (:init
   (&key
    ((:g __g) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _g __g)
   self)
  (:g
   (&optional __g)
   (if __g (setq _g __g)) _g)
  (:serialization-length
   ()
   (+
    ;; float64[] _g
    (* 8    (length _g)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[] _g
     (write-long (length _g) s)
     (dotimes (i (length _g))
       (sys::poke (elt _g i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[] _g
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _g (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _g i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(defclass dynamics::getG
  :super ros::object
  :slots ())

(setf (get dynamics::getG :md5sum-) "74b149151fe783dcf4c3c5768c37537f")
(setf (get dynamics::getG :datatype-) "dynamics/getG")
(setf (get dynamics::getG :request) dynamics::getGRequest)
(setf (get dynamics::getG :response) dynamics::getGResponse)

(defmethod dynamics::getGRequest
  (:response () (instance dynamics::getGResponse :init)))

(setf (get dynamics::getGRequest :md5sum-) "74b149151fe783dcf4c3c5768c37537f")
(setf (get dynamics::getGRequest :datatype-) "dynamics/getGRequest")
(setf (get dynamics::getGRequest :definition-)
      "float64[] q
---
float64[] g
")

(setf (get dynamics::getGResponse :md5sum-) "74b149151fe783dcf4c3c5768c37537f")
(setf (get dynamics::getGResponse :datatype-) "dynamics/getGResponse")
(setf (get dynamics::getGResponse :definition-)
      "float64[] q
---
float64[] g
")



(provide :dynamics/getG "74b149151fe783dcf4c3c5768c37537f")


