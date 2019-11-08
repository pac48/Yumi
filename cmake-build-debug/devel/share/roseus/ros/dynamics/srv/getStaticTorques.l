;; Auto-generated. Do not edit!


(when (boundp 'dynamics::getStaticTorques)
  (if (not (find-package "DYNAMICS"))
    (make-package "DYNAMICS"))
  (shadow 'getStaticTorques (find-package "DYNAMICS")))
(unless (find-package "DYNAMICS::GETSTATICTORQUES")
  (make-package "DYNAMICS::GETSTATICTORQUES"))
(unless (find-package "DYNAMICS::GETSTATICTORQUESREQUEST")
  (make-package "DYNAMICS::GETSTATICTORQUESREQUEST"))
(unless (find-package "DYNAMICS::GETSTATICTORQUESRESPONSE")
  (make-package "DYNAMICS::GETSTATICTORQUESRESPONSE"))

(in-package "ROS")





(defclass dynamics::getStaticTorquesRequest
  :super ros::object
  :slots (_q ))

(defmethod dynamics::getStaticTorquesRequest
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

(defclass dynamics::getStaticTorquesResponse
  :super ros::object
  :slots (_tau ))

(defmethod dynamics::getStaticTorquesResponse
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

(defclass dynamics::getStaticTorques
  :super ros::object
  :slots ())

(setf (get dynamics::getStaticTorques :md5sum-) "6b0ca527fdff0f3b38a61dfc2b4a926a")
(setf (get dynamics::getStaticTorques :datatype-) "dynamics/getStaticTorques")
(setf (get dynamics::getStaticTorques :request) dynamics::getStaticTorquesRequest)
(setf (get dynamics::getStaticTorques :response) dynamics::getStaticTorquesResponse)

(defmethod dynamics::getStaticTorquesRequest
  (:response () (instance dynamics::getStaticTorquesResponse :init)))

(setf (get dynamics::getStaticTorquesRequest :md5sum-) "6b0ca527fdff0f3b38a61dfc2b4a926a")
(setf (get dynamics::getStaticTorquesRequest :datatype-) "dynamics/getStaticTorquesRequest")
(setf (get dynamics::getStaticTorquesRequest :definition-)
      "float64[] q
---
float64[] tau
")

(setf (get dynamics::getStaticTorquesResponse :md5sum-) "6b0ca527fdff0f3b38a61dfc2b4a926a")
(setf (get dynamics::getStaticTorquesResponse :datatype-) "dynamics/getStaticTorquesResponse")
(setf (get dynamics::getStaticTorquesResponse :definition-)
      "float64[] q
---
float64[] tau
")



(provide :dynamics/getStaticTorques "6b0ca527fdff0f3b38a61dfc2b4a926a")


