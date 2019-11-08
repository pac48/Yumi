;; Auto-generated. Do not edit!


(when (boundp 'dynamics::getT)
  (if (not (find-package "DYNAMICS"))
    (make-package "DYNAMICS"))
  (shadow 'getT (find-package "DYNAMICS")))
(unless (find-package "DYNAMICS::GETT")
  (make-package "DYNAMICS::GETT"))
(unless (find-package "DYNAMICS::GETTREQUEST")
  (make-package "DYNAMICS::GETTREQUEST"))
(unless (find-package "DYNAMICS::GETTRESPONSE")
  (make-package "DYNAMICS::GETTRESPONSE"))

(in-package "ROS")





(defclass dynamics::getTRequest
  :super ros::object
  :slots (_q ))

(defmethod dynamics::getTRequest
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

(defclass dynamics::getTResponse
  :super ros::object
  :slots (_T ))

(defmethod dynamics::getTResponse
  (:init
   (&key
    ((:T __T) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _T __T)
   self)
  (:T
   (&optional __T)
   (if __T (setq _T __T)) _T)
  (:serialization-length
   ()
   (+
    ;; float64[] _T
    (* 8    (length _T)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[] _T
     (write-long (length _T) s)
     (dotimes (i (length _T))
       (sys::poke (elt _T i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[] _T
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _T (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _T i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(defclass dynamics::getT
  :super ros::object
  :slots ())

(setf (get dynamics::getT :md5sum-) "bdb52c1037f5355c7f4e4f94e7d00a52")
(setf (get dynamics::getT :datatype-) "dynamics/getT")
(setf (get dynamics::getT :request) dynamics::getTRequest)
(setf (get dynamics::getT :response) dynamics::getTResponse)

(defmethod dynamics::getTRequest
  (:response () (instance dynamics::getTResponse :init)))

(setf (get dynamics::getTRequest :md5sum-) "bdb52c1037f5355c7f4e4f94e7d00a52")
(setf (get dynamics::getTRequest :datatype-) "dynamics/getTRequest")
(setf (get dynamics::getTRequest :definition-)
      "float64[] q
---
float64[] T
")

(setf (get dynamics::getTResponse :md5sum-) "bdb52c1037f5355c7f4e4f94e7d00a52")
(setf (get dynamics::getTResponse :datatype-) "dynamics/getTResponse")
(setf (get dynamics::getTResponse :definition-)
      "float64[] q
---
float64[] T
")



(provide :dynamics/getT "bdb52c1037f5355c7f4e4f94e7d00a52")


