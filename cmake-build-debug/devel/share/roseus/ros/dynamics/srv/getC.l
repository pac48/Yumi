;; Auto-generated. Do not edit!


(when (boundp 'dynamics::getC)
  (if (not (find-package "DYNAMICS"))
    (make-package "DYNAMICS"))
  (shadow 'getC (find-package "DYNAMICS")))
(unless (find-package "DYNAMICS::GETC")
  (make-package "DYNAMICS::GETC"))
(unless (find-package "DYNAMICS::GETCREQUEST")
  (make-package "DYNAMICS::GETCREQUEST"))
(unless (find-package "DYNAMICS::GETCRESPONSE")
  (make-package "DYNAMICS::GETCRESPONSE"))

(in-package "ROS")





(defclass dynamics::getCRequest
  :super ros::object
  :slots (_q _qd ))

(defmethod dynamics::getCRequest
  (:init
   (&key
    ((:q __q) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:qd __qd) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _q __q)
   (setq _qd __qd)
   self)
  (:q
   (&optional __q)
   (if __q (setq _q __q)) _q)
  (:qd
   (&optional __qd)
   (if __qd (setq _qd __qd)) _qd)
  (:serialization-length
   ()
   (+
    ;; float64[] _q
    (* 8    (length _q)) 4
    ;; float64[] _qd
    (* 8    (length _qd)) 4
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
     ;; float64[] _qd
     (write-long (length _qd) s)
     (dotimes (i (length _qd))
       (sys::poke (elt _qd i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
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
   ;; float64[] _qd
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _qd (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _qd i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(defclass dynamics::getCResponse
  :super ros::object
  :slots (_c ))

(defmethod dynamics::getCResponse
  (:init
   (&key
    ((:c __c) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _c __c)
   self)
  (:c
   (&optional __c)
   (if __c (setq _c __c)) _c)
  (:serialization-length
   ()
   (+
    ;; float64[] _c
    (* 8    (length _c)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[] _c
     (write-long (length _c) s)
     (dotimes (i (length _c))
       (sys::poke (elt _c i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[] _c
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _c (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _c i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(defclass dynamics::getC
  :super ros::object
  :slots ())

(setf (get dynamics::getC :md5sum-) "bf7b2a43e3810114058d53b94861aa7b")
(setf (get dynamics::getC :datatype-) "dynamics/getC")
(setf (get dynamics::getC :request) dynamics::getCRequest)
(setf (get dynamics::getC :response) dynamics::getCResponse)

(defmethod dynamics::getCRequest
  (:response () (instance dynamics::getCResponse :init)))

(setf (get dynamics::getCRequest :md5sum-) "bf7b2a43e3810114058d53b94861aa7b")
(setf (get dynamics::getCRequest :datatype-) "dynamics/getCRequest")
(setf (get dynamics::getCRequest :definition-)
      "float64[] q
float64[] qd
---
float64[] c
")

(setf (get dynamics::getCResponse :md5sum-) "bf7b2a43e3810114058d53b94861aa7b")
(setf (get dynamics::getCResponse :datatype-) "dynamics/getCResponse")
(setf (get dynamics::getCResponse :definition-)
      "float64[] q
float64[] qd
---
float64[] c
")



(provide :dynamics/getC "bf7b2a43e3810114058d53b94861aa7b")


