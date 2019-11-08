; Auto-generated. Do not edit!


(cl:in-package dynamics-srv)


;//! \htmlinclude getC-request.msg.html

(cl:defclass <getC-request> (roslisp-msg-protocol:ros-message)
  ((q
    :reader q
    :initarg :q
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (qd
    :reader qd
    :initarg :qd
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass getC-request (<getC-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <getC-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'getC-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dynamics-srv:<getC-request> is deprecated: use dynamics-srv:getC-request instead.")))

(cl:ensure-generic-function 'q-val :lambda-list '(m))
(cl:defmethod q-val ((m <getC-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dynamics-srv:q-val is deprecated.  Use dynamics-srv:q instead.")
  (q m))

(cl:ensure-generic-function 'qd-val :lambda-list '(m))
(cl:defmethod qd-val ((m <getC-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dynamics-srv:qd-val is deprecated.  Use dynamics-srv:qd instead.")
  (qd m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <getC-request>) ostream)
  "Serializes a message object of type '<getC-request>"
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
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'qd))))
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
   (cl:slot-value msg 'qd))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <getC-request>) istream)
  "Deserializes a message object of type '<getC-request>"
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
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'qd) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'qd)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<getC-request>)))
  "Returns string type for a service object of type '<getC-request>"
  "dynamics/getCRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getC-request)))
  "Returns string type for a service object of type 'getC-request"
  "dynamics/getCRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<getC-request>)))
  "Returns md5sum for a message object of type '<getC-request>"
  "bf7b2a43e3810114058d53b94861aa7b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'getC-request)))
  "Returns md5sum for a message object of type 'getC-request"
  "bf7b2a43e3810114058d53b94861aa7b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<getC-request>)))
  "Returns full string definition for message of type '<getC-request>"
  (cl:format cl:nil "float64[] q~%float64[] qd~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'getC-request)))
  "Returns full string definition for message of type 'getC-request"
  (cl:format cl:nil "float64[] q~%float64[] qd~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <getC-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'q) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'qd) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <getC-request>))
  "Converts a ROS message object to a list"
  (cl:list 'getC-request
    (cl:cons ':q (q msg))
    (cl:cons ':qd (qd msg))
))
;//! \htmlinclude getC-response.msg.html

(cl:defclass <getC-response> (roslisp-msg-protocol:ros-message)
  ((c
    :reader c
    :initarg :c
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass getC-response (<getC-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <getC-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'getC-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dynamics-srv:<getC-response> is deprecated: use dynamics-srv:getC-response instead.")))

(cl:ensure-generic-function 'c-val :lambda-list '(m))
(cl:defmethod c-val ((m <getC-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dynamics-srv:c-val is deprecated.  Use dynamics-srv:c instead.")
  (c m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <getC-response>) ostream)
  "Serializes a message object of type '<getC-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'c))))
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
   (cl:slot-value msg 'c))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <getC-response>) istream)
  "Deserializes a message object of type '<getC-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'c) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'c)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<getC-response>)))
  "Returns string type for a service object of type '<getC-response>"
  "dynamics/getCResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getC-response)))
  "Returns string type for a service object of type 'getC-response"
  "dynamics/getCResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<getC-response>)))
  "Returns md5sum for a message object of type '<getC-response>"
  "bf7b2a43e3810114058d53b94861aa7b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'getC-response)))
  "Returns md5sum for a message object of type 'getC-response"
  "bf7b2a43e3810114058d53b94861aa7b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<getC-response>)))
  "Returns full string definition for message of type '<getC-response>"
  (cl:format cl:nil "float64[] c~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'getC-response)))
  "Returns full string definition for message of type 'getC-response"
  (cl:format cl:nil "float64[] c~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <getC-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'c) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <getC-response>))
  "Converts a ROS message object to a list"
  (cl:list 'getC-response
    (cl:cons ':c (c msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'getC)))
  'getC-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'getC)))
  'getC-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getC)))
  "Returns string type for a service object of type '<getC>"
  "dynamics/getC")