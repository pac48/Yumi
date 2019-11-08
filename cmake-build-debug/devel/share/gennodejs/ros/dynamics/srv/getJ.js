// Auto-generated. Do not edit!

// (in-package dynamics.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class getJRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.q = null;
    }
    else {
      if (initObj.hasOwnProperty('q')) {
        this.q = initObj.q
      }
      else {
        this.q = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type getJRequest
    // Serialize message field [q]
    bufferOffset = _arraySerializer.float64(obj.q, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type getJRequest
    let len;
    let data = new getJRequest(null);
    // Deserialize message field [q]
    data.q = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.q.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'dynamics/getJRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ab94b9bcaaa12f74def43e4b33992df1';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[] q
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new getJRequest(null);
    if (msg.q !== undefined) {
      resolved.q = msg.q;
    }
    else {
      resolved.q = []
    }

    return resolved;
    }
};

class getJResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.J = null;
    }
    else {
      if (initObj.hasOwnProperty('J')) {
        this.J = initObj.J
      }
      else {
        this.J = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type getJResponse
    // Serialize message field [J]
    bufferOffset = _arraySerializer.float64(obj.J, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type getJResponse
    let len;
    let data = new getJResponse(null);
    // Deserialize message field [J]
    data.J = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.J.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'dynamics/getJResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4753a207fbbe24f44a3db59ebb4be3e3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[] J
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new getJResponse(null);
    if (msg.J !== undefined) {
      resolved.J = msg.J;
    }
    else {
      resolved.J = []
    }

    return resolved;
    }
};

module.exports = {
  Request: getJRequest,
  Response: getJResponse,
  md5sum() { return '06a3de3817aa53a10640e08369b1085e'; },
  datatype() { return 'dynamics/getJ'; }
};
