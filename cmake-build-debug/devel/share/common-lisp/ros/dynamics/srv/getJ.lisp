; Auto-generated. Do not edit!


(cl:in-package dynamics-srv)


;//! \htmlinclude getJ-request.msg.html

(cl:defclass <getJ-request> (roslisp-msg-protocol:ros-message)
  ((q
    :reader q
    :initarg :q
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass getJ-request (<getJ-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <getJ-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'getJ-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dynamics-srv:<getJ-request> is deprecated: use dynamics-srv:getJ-request instead.")))

(cl:ensure-generic-function 'q-val :lambda-list '(m))
(cl:defmethod q-val ((m <getJ-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dynamics-srv:q-val is deprecated.  Use dynamics-srv:q instead.")
  (q m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <getJ-request>) ostream)
  "Serializes a message object of type '<getJ-request>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <getJ-request>) istream)
  "Deserializes a message object of type '<getJ-request>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<getJ-request>)))
  "Returns string type for a service object of type '<getJ-request>"
  "dynamics/getJRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getJ-request)))
  "Returns string type for a service object of type 'getJ-request"
  "dynamics/getJRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<getJ-request>)))
  "Returns md5sum for a message object of type '<getJ-request>"
  "06a3de3817aa53a10640e08369b1085e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'getJ-request)))
  "Returns md5sum for a message object of type 'getJ-request"
  "06a3de3817aa53a10640e08369b1085e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<getJ-request>)))
  "Returns full string definition for message of type '<getJ-request>"
  (cl:format cl:nil "float64[] q~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'getJ-request)))
  "Returns full string definition for message of type 'getJ-request"
  (cl:format cl:nil "float64[] q~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <getJ-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'q) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <getJ-request>))
  "Converts a ROS message object to a list"
  (cl:list 'getJ-request
    (cl:cons ':q (q msg))
))
;//! \htmlinclude getJ-response.msg.html

(cl:defclass <getJ-response> (roslisp-msg-protocol:ros-message)
  ((J
    :reader J
    :initarg :J
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass getJ-response (<getJ-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <getJ-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'getJ-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dynamics-srv:<getJ-response> is deprecated: use dynamics-srv:getJ-response instead.")))

(cl:ensure-generic-function 'J-val :lambda-list '(m))
(cl:defmethod J-val ((m <getJ-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dynamics-srv:J-val is deprecated.  Use dynamics-srv:J instead.")
  (J m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <getJ-response>) ostream)
  "Serializes a message object of type '<getJ-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'J))))
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
   (cl:slot-value msg 'J))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <getJ-response>) istream)
  "Deserializes a message object of type '<getJ-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'J) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'J)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<getJ-response>)))
  "Returns string type for a service object of type '<getJ-response>"
  "dynamics/getJResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getJ-response)))
  "Returns string type for a service object of type 'getJ-response"
  "dynamics/getJResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<getJ-response>)))
  "Returns md5sum for a message object of type '<getJ-response>"
  "06a3de3817aa53a10640e08369b1085e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'getJ-response)))
  "Returns md5sum for a message object of type 'getJ-response"
  "06a3de3817aa53a10640e08369b1085e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<getJ-response>)))
  "Returns full string definition for message of type '<getJ-response>"
  (cl:format cl:nil "float64[] J~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'getJ-response)))
  "Returns full string definition for message of type 'getJ-response"
  (cl:format cl:nil "float64[] J~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <getJ-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'J) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <getJ-response>))
  "Converts a ROS message object to a list"
  (cl:list 'getJ-response
    (cl:cons ':J (J msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'getJ)))
  'getJ-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'getJ)))
  'getJ-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getJ)))
  "Returns string type for a service object of type '<getJ>"
  "dynamics/getJ")