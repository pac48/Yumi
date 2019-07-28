; Auto-generated. Do not edit!


(cl:in-package simulator-srv)


;//! \htmlinclude getTorques-request.msg.html

(cl:defclass <getTorques-request> (roslisp-msg-protocol:ros-message)
  ((q
    :reader q
    :initarg :q
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass getTorques-request (<getTorques-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <getTorques-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'getTorques-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name simulator-srv:<getTorques-request> is deprecated: use simulator-srv:getTorques-request instead.")))

(cl:ensure-generic-function 'q-val :lambda-list '(m))
(cl:defmethod q-val ((m <getTorques-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader simulator-srv:q-val is deprecated.  Use simulator-srv:q instead.")
  (q m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <getTorques-request>) ostream)
  "Serializes a message object of type '<getTorques-request>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'q))))
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
   (cl:slot-value msg 'q))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <getTorques-request>) istream)
  "Deserializes a message object of type '<getTorques-request>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'q) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'q)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<getTorques-request>)))
  "Returns string type for a service object of type '<getTorques-request>"
  "simulator/getTorquesRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getTorques-request)))
  "Returns string type for a service object of type 'getTorques-request"
  "simulator/getTorquesRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<getTorques-request>)))
  "Returns md5sum for a message object of type '<getTorques-request>"
  "6b0ca527fdff0f3b38a61dfc2b4a926a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'getTorques-request)))
  "Returns md5sum for a message object of type 'getTorques-request"
  "6b0ca527fdff0f3b38a61dfc2b4a926a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<getTorques-request>)))
  "Returns full string definition for message of type '<getTorques-request>"
  (cl:format cl:nil "float64[] q~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'getTorques-request)))
  "Returns full string definition for message of type 'getTorques-request"
  (cl:format cl:nil "float64[] q~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <getTorques-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'q) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <getTorques-request>))
  "Converts a ROS message object to a list"
  (cl:list 'getTorques-request
    (cl:cons ':q (q msg))
))
;//! \htmlinclude getTorques-response.msg.html

(cl:defclass <getTorques-response> (roslisp-msg-protocol:ros-message)
  ((tau
    :reader tau
    :initarg :tau
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass getTorques-response (<getTorques-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <getTorques-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'getTorques-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name simulator-srv:<getTorques-response> is deprecated: use simulator-srv:getTorques-response instead.")))

(cl:ensure-generic-function 'tau-val :lambda-list '(m))
(cl:defmethod tau-val ((m <getTorques-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader simulator-srv:tau-val is deprecated.  Use simulator-srv:tau instead.")
  (tau m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <getTorques-response>) ostream)
  "Serializes a message object of type '<getTorques-response>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <getTorques-response>) istream)
  "Deserializes a message object of type '<getTorques-response>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<getTorques-response>)))
  "Returns string type for a service object of type '<getTorques-response>"
  "simulator/getTorquesResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getTorques-response)))
  "Returns string type for a service object of type 'getTorques-response"
  "simulator/getTorquesResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<getTorques-response>)))
  "Returns md5sum for a message object of type '<getTorques-response>"
  "6b0ca527fdff0f3b38a61dfc2b4a926a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'getTorques-response)))
  "Returns md5sum for a message object of type 'getTorques-response"
  "6b0ca527fdff0f3b38a61dfc2b4a926a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<getTorques-response>)))
  "Returns full string definition for message of type '<getTorques-response>"
  (cl:format cl:nil "float64[] tau~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'getTorques-response)))
  "Returns full string definition for message of type 'getTorques-response"
  (cl:format cl:nil "float64[] tau~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <getTorques-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'tau) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <getTorques-response>))
  "Converts a ROS message object to a list"
  (cl:list 'getTorques-response
    (cl:cons ':tau (tau msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'getTorques)))
  'getTorques-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'getTorques)))
  'getTorques-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getTorques)))
  "Returns string type for a service object of type '<getTorques>"
  "simulator/getTorques")