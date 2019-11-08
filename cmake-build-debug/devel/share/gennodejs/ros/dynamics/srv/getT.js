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

class getTRequest {
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
    // Serializes a message object of type getTRequest
    // Serialize message field [q]
    bufferOffset = _arraySerializer.float64(obj.q, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type getTRequest
    let len;
    let data = new getTRequest(null);
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
    return 'dynamics/getTRequest';
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
    const resolved = new getTRequest(null);
    if (msg.q !== undefined) {
      resolved.q = msg.q;
    }
    else {
      resolved.q = []
    }

    return resolved;
    }
};

class getTResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.T = null;
    }
    else {
      if (initObj.hasOwnProperty('T')) {
        this.T = initObj.T
      }
      else {
        this.T = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type getTResponse
    // Serialize message field [T]
    bufferOffset = _arraySerializer.float64(obj.T, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type getTResponse
    let len;
    let data = new getTResponse(null);
    // Deserialize message field [T]
    data.T = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.T.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'dynamics/getTResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2dbc3d227c6d31b0408289b7e29c22ce';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[] T
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new getTResponse(null);
    if (msg.T !== undefined) {
      resolved.T = msg.T;
    }
    else {
      resolved.T = []
    }

    return resolved;
    }
};

module.exports = {
  Request: getTRequest,
  Response: getTResponse,
  md5sum() { return 'bdb52c1037f5355c7f4e4f94e7d00a52'; },
  datatype() { return 'dynamics/getT'; }
};
