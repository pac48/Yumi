;; Auto-generated. Do not edit!


(when (boundp 'simulator::getStaticTorques)
  (if (not (find-package "SIMULATOR"))
    (make-package "SIMULATOR"))
  (shadow 'getStaticTorques (find-package "SIMULATOR")))
(unless (find-package "SIMULATOR::GETSTATICTORQUES")
  (make-package "SIMULATOR::GETSTATICTORQUES"))
(unless (find-package "SIMULATOR::GETSTATICTORQUESREQUEST")
  (make-package "SIMULATOR::GETSTATICTORQUESREQUEST"))
(unless (find-package "SIMULATOR::GETSTATICTORQUESRESPONSE")
  (make-package "SIMULATOR::GETSTATICTORQUESRESPONSE"))

(in-package "ROS")





(defclass simulator::getStaticTorquesRequest
  :super ros::object
  :slots (_q ))

(defmethod simulator::getStaticTorquesRequest
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

(defclass simulator::getStaticTorquesResponse
  :super ros::object
  :slots (_tau ))

(defmethod simulator::getStaticTorquesResponse
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

(defclass simulator::getStaticTorques
  :super ros::object
  :slots ())

(setf (get simulator::getStaticTorques :md5sum-) "6b0ca527fdff0f3b38a61dfc2b4a926a")
(setf (get simulator::getStaticTorques :datatype-) "simulator/getStaticTorques")
(setf (get simulator::getStaticTorques :request) simulator::getStaticTorquesRequest)
(setf (get simulator::getStaticTorques :response) simulator::getStaticTorquesResponse)

(defmethod simulator::getStaticTorquesRequest
  (:response () (instance simulator::getStaticTorquesResponse :init)))

(setf (get simulator::getStaticTorquesRequest :md5sum-) "6b0ca527fdff0f3b38a61dfc2b4a926a")
(setf (get simulator::getStaticTorquesRequest :datatype-) "simulator/getStaticTorquesRequest")
(setf (get simulator::getStaticTorquesRequest :definition-)
      "float64[] q
---
float64[] tau
")

(setf (get simulator::getStaticTorquesResponse :md5sum-) "6b0ca527fdff0f3b38a61dfc2b4a926a")
(setf (get simulator::getStaticTorquesResponse :datatype-) "simulator/getStaticTorquesResponse")
(setf (get simulator::getStaticTorquesResponse :definition-)
      "float64[] q
---
float64[] tau
")



(provide :simulator/getStaticTorques "6b0ca527fdff0f3b38a61dfc2b4a926a")


