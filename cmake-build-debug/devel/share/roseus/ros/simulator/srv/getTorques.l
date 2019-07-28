;; Auto-generated. Do not edit!


(when (boundp 'simulator::getTorques)
  (if (not (find-package "SIMULATOR"))
    (make-package "SIMULATOR"))
  (shadow 'getTorques (find-package "SIMULATOR")))
(unless (find-package "SIMULATOR::GETTORQUES")
  (make-package "SIMULATOR::GETTORQUES"))
(unless (find-package "SIMULATOR::GETTORQUESREQUEST")
  (make-package "SIMULATOR::GETTORQUESREQUEST"))
(unless (find-package "SIMULATOR::GETTORQUESRESPONSE")
  (make-package "SIMULATOR::GETTORQUESRESPONSE"))

(in-package "ROS")





(defclass simulator::getTorquesRequest
  :super ros::object
  :slots (_q ))

(defmethod simulator::getTorquesRequest
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

(defclass simulator::getTorquesResponse
  :super ros::object
  :slots (_tau ))

(defmethod simulator::getTorquesResponse
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

(defclass simulator::getTorques
  :super ros::object
  :slots ())

(setf (get simulator::getTorques :md5sum-) "6b0ca527fdff0f3b38a61dfc2b4a926a")
(setf (get simulator::getTorques :datatype-) "simulator/getTorques")
(setf (get simulator::getTorques :request) simulator::getTorquesRequest)
(setf (get simulator::getTorques :response) simulator::getTorquesResponse)

(defmethod simulator::getTorquesRequest
  (:response () (instance simulator::getTorquesResponse :init)))

(setf (get simulator::getTorquesRequest :md5sum-) "6b0ca527fdff0f3b38a61dfc2b4a926a")
(setf (get simulator::getTorquesRequest :datatype-) "simulator/getTorquesRequest")
(setf (get simulator::getTorquesRequest :definition-)
      "float64[] q
---
float64[] tau
")

(setf (get simulator::getTorquesResponse :md5sum-) "6b0ca527fdff0f3b38a61dfc2b4a926a")
(setf (get simulator::getTorquesResponse :datatype-) "simulator/getTorquesResponse")
(setf (get simulator::getTorquesResponse :definition-)
      "float64[] q
---
float64[] tau
")



(provide :simulator/getTorques "6b0ca527fdff0f3b38a61dfc2b4a926a")


