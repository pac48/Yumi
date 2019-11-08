; Auto-generated. Do not edit!


(cl:in-package dynamics-srv)


;//! \htmlinclude setTorques-request.msg.html

(cl:defclass <setTorques-request> (roslisp-msg-protocol:ros-message)
  ((tau
    :reader tau
    :initarg :tau
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass setTorques-request (<setTorques-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <setTorques-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'setTorques-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dynamics-srv:<setTorques-request> is deprecated: use dynamics-srv:setTorques-request instead.")))

(cl:ensure-generic-function 'tau-val :lambda-list '(m))
(cl:defmethod tau-val ((m <setTorques-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dynamics-srv:tau-val is deprecated.  Use dynamics-srv:tau instead.")
  (tau m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <setTorques-request>) ostream)
  "Serializes a message object of type '<setTorques-request>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'tau))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'tau))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <setTorques-request>) istream)
  "Deserializes a message object of type '<setTorques-request>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'tau) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'tau)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<setTorques-request>)))
  "Returns string type for a service object of type '<setTorques-request>"
  "dynamics/setTorquesRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'setTorques-request)))
  "Returns string type for a service object of type 'setTorques-request"
  "dynamics/setTorquesRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<setTorques-request>)))
  "Returns md5sum for a message object of type '<setTorques-request>"
  "e58e0e3410894d2e4992e2dd98c576ea")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'setTorques-request)))
  "Returns md5sum for a message object of type 'setTorques-request"
  "e58e0e3410894d2e4992e2dd98c576ea")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<setTorques-request>)))
  "Returns full string definition for message of type '<setTorques-request>"
  (cl:format cl:nil "float64[] tau~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'setTorques-request)))
  "Returns full string definition for message of type 'setTorques-request"
  (cl:format cl:nil "float64[] tau~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <setTorques-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'tau) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <setTorques-request>))
  "Converts a ROS message object to a list"
  (cl:list 'setTorques-request
    (cl:cons ':tau (tau msg))
))
;//! \htmlinclude setTorques-response.msg.html

(cl:defclass <setTorques-response> (roslisp-msg-protocol:ros-message)
  ((qdd
    :reader qdd
    :initarg :qdd
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass setTorques-response (<setTorques-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <setTorques-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'setTorques-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dynamics-srv:<setTorques-response> is deprecated: use dynamics-srv:setTorques-response instead.")))

(cl:ensure-generic-function 'qdd-val :lambda-list '(m))
(cl:defmethod qdd-val ((m <setTorques-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dynamics-srv:qdd-val is deprecated.  Use dynamics-srv:qdd instead.")
  (qdd m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <setTorques-response>) ostream)
  "Serializes a message object of type '<setTorques-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'qdd))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'qdd))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <setTorques-response>) istream)
  "Deserializes a message object of type '<setTorques-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'qdd) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'qdd)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<setTorques-response>)))
  "Returns string type for a service object of type '<setTorques-response>"
  "dynamics/setTorquesResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'setTorques-response)))
  "Returns string type for a service object of type 'setTorques-response"
  "dynamics/setTorquesResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<setTorques-response>)))
  "Returns md5sum for a message object of type '<setTorques-response>"
  "e58e0e3410894d2e4992e2dd98c576ea")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'setTorques-response)))
  "Returns md5sum for a message object of type 'setTorques-response"
  "e58e0e3410894d2e4992e2dd98c576ea")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<setTorques-response>)))
  "Returns full string definition for message of type '<setTorques-response>"
  (cl:format cl:nil "float64[] qdd~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'setTorques-response)))
  "Returns full string definition for message of type 'setTorques-response"
  (cl:format cl:nil "float64[] qdd~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <setTorques-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'qdd) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <setTorques-response>))
  "Converts a ROS message object to a list"
  (cl:list 'setTorques-response
    (cl:cons ':qdd (qdd msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'setTorques)))
  'setTorques-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'setTorques)))
  'setTorques-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'setTorques)))
  "Returns string type for a service object of type '<setTorques>"
  "dynamics/setTorques")