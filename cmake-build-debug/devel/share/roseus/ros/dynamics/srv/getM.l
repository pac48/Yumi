;; Auto-generated. Do not edit!


(when (boundp 'dynamics::getM)
  (if (not (find-package "DYNAMICS"))
    (make-package "DYNAMICS"))
  (shadow 'getM (find-package "DYNAMICS")))
(unless (find-package "DYNAMICS::GETM")
  (make-package "DYNAMICS::GETM"))
(unless (find-package "DYNAMICS::GETMREQUEST")
  (make-package "DYNAMICS::GETMREQUEST"))
(unless (find-package "DYNAMICS::GETMRESPONSE")
  (make-package "DYNAMICS::GETMRESPONSE"))

(in-package "ROS")





(defclass dynamics::getMRequest
  :super ros::object
  :slots (_q ))

(defmethod dynamics::getMRequest
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

(defclass dynamics::getMResponse
  :super ros::object
  :slots (_M ))

(defmethod dynamics::getMResponse
  (:init
   (&key
    ((:M __M) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _M __M)
   self)
  (:M
   (&optional __M)
   (if __M (setq _M __M)) _M)
  (:serialization-length
   ()
   (+
    ;; float64[] _M
    (* 8    (length _M)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[] _M
     (write-long (length _M) s)
     (dotimes (i (length _M))
       (sys::poke (elt _M i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[] _M
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _M (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _M i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(defclass dynamics::getM
  :super ros::object
  :slots ())

(setf (get dynamics::getM :md5sum-) "a55fe0135909abaa5d880290a0f368d7")
(setf (get dynamics::getM :datatype-) "dynamics/getM")
(setf (get dynamics::getM :request) dynamics::getMRequest)
(setf (get dynamics::getM :response) dynamics::getMResponse)

(defmethod dynamics::getMRequest
  (:response () (instance dynamics::getMResponse :init)))

(setf (get dynamics::getMRequest :md5sum-) "a55fe0135909abaa5d880290a0f368d7")
(setf (get dynamics::getMRequest :datatype-) "dynamics/getMRequest")
(setf (get dynamics::getMRequest :definition-)
      "float64[] q
---
float64[] M
")

(setf (get dynamics::getMResponse :md5sum-) "a55fe0135909abaa5d880290a0f368d7")
(setf (get dynamics::getMResponse :datatype-) "dynamics/getMResponse")
(setf (get dynamics::getMResponse :definition-)
      "float64[] q
---
float64[] M
")



(provide :dynamics/getM "a55fe0135909abaa5d880290a0f368d7")


