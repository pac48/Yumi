; Auto-generated. Do not edit!


(cl:in-package dynamics-srv)


;//! \htmlinclude getT-request.msg.html

(cl:defclass <getT-request> (roslisp-msg-protocol:ros-message)
  ((q
    :reader q
    :initarg :q
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass getT-request (<getT-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <getT-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'getT-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dynamics-srv:<getT-request> is deprecated: use dynamics-srv:getT-request instead.")))

(cl:ensure-generic-function 'q-val :lambda-list '(m))
(cl:defmethod q-val ((m <getT-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dynamics-srv:q-val is deprecated.  Use dynamics-srv:q instead.")
  (q m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <getT-request>) ostream)
  "Serializes a message object of type '<getT-request>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <getT-request>) istream)
  "Deserializes a message object of type '<getT-request>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<getT-request>)))
  "Returns string type for a service object of type '<getT-request>"
  "dynamics/getTRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getT-request)))
  "Returns string type for a service object of type 'getT-request"
  "dynamics/getTRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<getT-request>)))
  "Returns md5sum for a message object of type '<getT-request>"
  "bdb52c1037f5355c7f4e4f94e7d00a52")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'getT-request)))
  "Returns md5sum for a message object of type 'getT-request"
  "bdb52c1037f5355c7f4e4f94e7d00a52")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<getT-request>)))
  "Returns full string definition for message of type '<getT-request>"
  (cl:format cl:nil "float64[] q~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'getT-request)))
  "Returns full string definition for message of type 'getT-request"
  (cl:format cl:nil "float64[] q~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <getT-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'q) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <getT-request>))
  "Converts a ROS message object to a list"
  (cl:list 'getT-request
    (cl:cons ':q (q msg))
))
;//! \htmlinclude getT-response.msg.html

(cl:defclass <getT-response> (roslisp-msg-protocol:ros-message)
  ((T
    :reader T
    :initarg :T
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass getT-response (<getT-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <getT-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'getT-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dynamics-srv:<getT-response> is deprecated: use dynamics-srv:getT-response instead.")))

(cl:ensure-generic-function 'T-val :lambda-list '(m))
(cl:defmethod T-val ((m <getT-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dynamics-srv:T-val is deprecated.  Use dynamics-srv:T instead.")
  (T m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <getT-response>) ostream)
  "Serializes a message object of type '<getT-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'T))))
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
   (cl:slot-value msg 'T))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <getT-response>) istream)
  "Deserializes a message object of type '<getT-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'T) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'T)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<getT-response>)))
  "Returns string type for a service object of type '<getT-response>"
  "dynamics/getTResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getT-response)))
  "Returns string type for a service object of type 'getT-response"
  "dynamics/getTResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<getT-response>)))
  "Returns md5sum for a message object of type '<getT-response>"
  "bdb52c1037f5355c7f4e4f94e7d00a52")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'getT-response)))
  "Returns md5sum for a message object of type 'getT-response"
  "bdb52c1037f5355c7f4e4f94e7d00a52")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<getT-response>)))
  "Returns full string definition for message of type '<getT-response>"
  (cl:format cl:nil "float64[] T~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'getT-response)))
  "Returns full string definition for message of type 'getT-response"
  (cl:format cl:nil "float64[] T~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <getT-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'T) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <getT-response>))
  "Converts a ROS message object to a list"
  (cl:list 'getT-response
    (cl:cons ':T (T msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'getT)))
  'getT-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'getT)))
  'getT-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getT)))
  "Returns string type for a service object of type '<getT>"
  "dynamics/getT")