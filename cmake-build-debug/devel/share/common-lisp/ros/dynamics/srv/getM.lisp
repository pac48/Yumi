; Auto-generated. Do not edit!


(cl:in-package dynamics-srv)


;//! \htmlinclude getM-request.msg.html

(cl:defclass <getM-request> (roslisp-msg-protocol:ros-message)
  ((q
    :reader q
    :initarg :q
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass getM-request (<getM-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <getM-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'getM-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dynamics-srv:<getM-request> is deprecated: use dynamics-srv:getM-request instead.")))

(cl:ensure-generic-function 'q-val :lambda-list '(m))
(cl:defmethod q-val ((m <getM-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dynamics-srv:q-val is deprecated.  Use dynamics-srv:q instead.")
  (q m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <getM-request>) ostream)
  "Serializes a message object of type '<getM-request>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <getM-request>) istream)
  "Deserializes a message object of type '<getM-request>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<getM-request>)))
  "Returns string type for a service object of type '<getM-request>"
  "dynamics/getMRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getM-request)))
  "Returns string type for a service object of type 'getM-request"
  "dynamics/getMRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<getM-request>)))
  "Returns md5sum for a message object of type '<getM-request>"
  "a55fe0135909abaa5d880290a0f368d7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'getM-request)))
  "Returns md5sum for a message object of type 'getM-request"
  "a55fe0135909abaa5d880290a0f368d7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<getM-request>)))
  "Returns full string definition for message of type '<getM-request>"
  (cl:format cl:nil "float64[] q~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'getM-request)))
  "Returns full string definition for message of type 'getM-request"
  (cl:format cl:nil "float64[] q~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <getM-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'q) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <getM-request>))
  "Converts a ROS message object to a list"
  (cl:list 'getM-request
    (cl:cons ':q (q msg))
))
;//! \htmlinclude getM-response.msg.html

(cl:defclass <getM-response> (roslisp-msg-protocol:ros-message)
  ((M
    :reader M
    :initarg :M
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass getM-response (<getM-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <getM-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'getM-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dynamics-srv:<getM-response> is deprecated: use dynamics-srv:getM-response instead.")))

(cl:ensure-generic-function 'M-val :lambda-list '(m))
(cl:defmethod M-val ((m <getM-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dynamics-srv:M-val is deprecated.  Use dynamics-srv:M instead.")
  (M m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <getM-response>) ostream)
  "Serializes a message object of type '<getM-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'M))))
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
   (cl:slot-value msg 'M))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <getM-response>) istream)
  "Deserializes a message object of type '<getM-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'M) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'M)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<getM-response>)))
  "Returns string type for a service object of type '<getM-response>"
  "dynamics/getMResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getM-response)))
  "Returns string type for a service object of type 'getM-response"
  "dynamics/getMResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<getM-response>)))
  "Returns md5sum for a message object of type '<getM-response>"
  "a55fe0135909abaa5d880290a0f368d7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'getM-response)))
  "Returns md5sum for a message object of type 'getM-response"
  "a55fe0135909abaa5d880290a0f368d7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<getM-response>)))
  "Returns full string definition for message of type '<getM-response>"
  (cl:format cl:nil "float64[] M~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'getM-response)))
  "Returns full string definition for message of type 'getM-response"
  (cl:format cl:nil "float64[] M~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <getM-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'M) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <getM-response>))
  "Converts a ROS message object to a list"
  (cl:list 'getM-response
    (cl:cons ':M (M msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'getM)))
  'getM-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'getM)))
  'getM-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'getM)))
  "Returns string type for a service object of type '<getM>"
  "dynamics/getM")