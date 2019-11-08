;; Auto-generated. Do not edit!


(when (boundp 'dynamics::getTrajTorques)
  (if (not (find-package "DYNAMICS"))
    (make-package "DYNAMICS"))
  (shadow 'getTrajTorques (find-package "DYNAMICS")))
(unless (find-package "DYNAMICS::GETTRAJTORQUES")
  (make-package "DYNAMICS::GETTRAJTORQUES"))
(unless (find-package "DYNAMICS::GETTRAJTORQUESREQUEST")
  (make-package "DYNAMICS::GETTRAJTORQUESREQUEST"))
(unless (find-package "DYNAMICS::GETTRAJTORQUESRESPONSE")
  (make-package "DYNAMICS::GETTRAJTORQUESRESPONSE"))

(in-package "ROS")





(defclass dynamics::getTrajTorquesRequest
  :super ros::object
  :slots (_q _qd _qdd _Fext ))

(defmethod dynamics::getTrajTorquesRequest
  (:init
   (&key
    ((:q __q) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:qd __qd) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:qdd __qdd) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:Fext __Fext) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _q __q)
   (setq _qd __qd)
   (setq _qdd __qdd)
   (setq _Fext __Fext)
   self)
  (:q
   (&optional __q)
   (if __q (setq _q __q)) _q)
  (:qd
   (&optional __qd)
   (if __qd (setq _qd __qd)) _qd)
  (:qdd
   (&optional __qdd)
   (if __qdd (setq _qdd __qdd)) _qdd)
  (:Fext
   (&optional __Fext)
   (if __Fext (setq _Fext __Fext)) _Fext)
  (:serialization-length
   ()
   (+
    ;; float64[] _q
    (* 8    (length _q)) 4
    ;; float64[] _qd
    (* 8    (length _qd)) 4
    ;; float64[] _qdd
    (* 8    (length _qdd)) 4
    ;; float64[] _Fext
    (* 8    (length _Fext)) 4
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
     ;; float64[] _qdd
     (write-long (length _qdd) s)
     (dotimes (i (length _qdd))
       (sys::poke (elt _qdd i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _Fext
     (write-long (length _Fext) s)
     (dotimes (i (length _Fext))
       (sys::poke (elt _Fext i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
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
   ;; float64[] _qdd
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _qdd (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _qdd i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _Fext
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _Fext (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _Fext i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(defclass dynamics::getTrajTorquesResponse
  :super ros::object
  :slots (_Tau _KE ))

(defmethod dynamics::getTrajTorquesResponse
  (:init
   (&key
    ((:Tau __Tau) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:KE __KE) 0.0)
    )
   (send-super :init)
   (setq _Tau __Tau)
   (setq _KE (float __KE))
   self)
  (:Tau
   (&optional __Tau)
   (if __Tau (setq _Tau __Tau)) _Tau)
  (:KE
   (&optional __KE)
   (if __KE (setq _KE __KE)) _KE)
  (:serialization-length
   ()
   (+
    ;; float64[] _Tau
    (* 8    (length _Tau)) 4
    ;; float64 _KE
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[] _Tau
     (write-long (length _Tau) s)
     (dotimes (i (length _Tau))
       (sys::poke (elt _Tau i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64 _KE
       (sys::poke _KE (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[] _Tau
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _Tau (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _Tau i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64 _KE
     (setq _KE (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass dynamics::getTrajTorques
  :super ros::object
  :slots ())

(setf (get dynamics::getTrajTorques :md5sum-) "a503289886a65ff9ff9284d2897da3bc")
(setf (get dynamics::getTrajTorques :datatype-) "dynamics/getTrajTorques")
(setf (get dynamics::getTrajTorques :request) dynamics::getTrajTorquesRequest)
(setf (get dynamics::getTrajTorques :response) dynamics::getTrajTorquesResponse)

(defmethod dynamics::getTrajTorquesRequest
  (:response () (instance dynamics::getTrajTorquesResponse :init)))

(setf (get dynamics::getTrajTorquesRequest :md5sum-) "a503289886a65ff9ff9284d2897da3bc")
(setf (get dynamics::getTrajTorquesRequest :datatype-) "dynamics/getTrajTorquesRequest")
(setf (get dynamics::getTrajTorquesRequest :definition-)
      "float64[] q
float64[] qd
float64[] qdd
float64[] Fext
---
float64[] Tau
float64 KE
")

(setf (get dynamics::getTrajTorquesResponse :md5sum-) "a503289886a65ff9ff9284d2897da3bc")
(setf (get dynamics::getTrajTorquesResponse :datatype-) "dynamics/getTrajTorquesResponse")
(setf (get dynamics::getTrajTorquesResponse :definition-)
      "float64[] q
float64[] qd
float64[] qdd
float64[] Fext
---
float64[] Tau
float64 KE
")



(provide :dynamics/getTrajTorques "a503289886a65ff9ff9284d2897da3bc")


