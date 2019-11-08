; Auto-generated. Do not edit!


(cl:in-package dynamics-srv)


;//! \htmlinclude getG-request.msg.html

(cl:defclass <getG-request> (roslisp-msg-protocol:ros-message)
  ((q
    :reader q
    :initarg :q
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass getG-request (<getG-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <getG-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'getG-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dynamics-srv:<getG-request> is deprecated: use dynamics-srv:getG-request instead.")))

(cl:ensure-generic-function 'q-val :lambda-list '(m))
(cl:defmethod q-val ((m <getG-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dynamics-srv:q-val is deprecated.  Use dynamics-srv:q instead.")
  (q m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <getG-request>) ostream)
  "Serializes a message object of type '<getG-request>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <getG-request>) istream)
  "Deserializes a message object of type '<getG-request>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<getG-request>)))
  "Returns string type for a service object of type '<getG-request>"
  "dynamics/getGRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getG-request)))
  "Returns string type for a service object of type 'getG-request"
  "dynamics/getGRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<getG-request>)))
  "Returns md5sum for a message object of type '<getG-request>"
  "74b149151fe783dcf4c3c5768c37537f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'getG-request)))
  "Returns md5sum for a message object of type 'getG-request"
  "74b149151fe783dcf4c3c5768c37537f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<getG-request>)))
  "Returns full string definition for message of type '<getG-request>"
  (cl:format cl:nil "float64[] q~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'getG-request)))
  "Returns full string definition for message of type 'getG-request"
  (cl:format cl:nil "float64[] q~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <getG-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'q) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <getG-request>))
  "Converts a ROS message object to a list"
  (cl:list 'getG-request
    (cl:cons ':q (q msg))
))
;//! \htmlinclude getG-response.msg.html

(cl:defclass <getG-response> (roslisp-msg-protocol:ros-message)
  ((g
    :reader g
    :initarg :g
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass getG-response (<getG-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <getG-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'getG-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dynamics-srv:<getG-response> is deprecated: use dynamics-srv:getG-response instead.")))

(cl:ensure-generic-function 'g-val :lambda-list '(m))
(cl:defmethod g-val ((m <getG-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dynamics-srv:g-val is deprecated.  Use dynamics-srv:g instead.")
  (g m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <getG-response>) ostream)
  "Serializes a message object of type '<getG-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'g))))
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
   (cl:slot-value msg 'g))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <getG-response>) istream)
  "Deserializes a message object of type '<getG-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'g) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'g)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<getG-response>)))
  "Returns string type for a service object of type '<getG-response>"
  "dynamics/getGResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getG-response)))
  "Returns string type for a service object of type 'getG-response"
  "dynamics/getGResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<getG-response>)))
  "Returns md5sum for a message object of type '<getG-response>"
  "74b149151fe783dcf4c3c5768c37537f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'getG-response)))
  "Returns md5sum for a message object of type 'getG-response"
  "74b149151fe783dcf4c3c5768c37537f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<getG-response>)))
  "Returns full string definition for message of type '<getG-response>"
  (cl:format cl:nil "float64[] g~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'getG-response)))
  "Returns full string definition for message of type 'getG-response"
  (cl:format cl:nil "float64[] g~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <getG-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'g) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <getG-response>))
  "Converts a ROS message object to a list"
  (cl:list 'getG-response
    (cl:cons ':g (g msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'getG)))
  'getG-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'getG)))
  'getG-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getG)))
  "Returns string type for a service object of type '<getG>"
  "dynamics/getG")