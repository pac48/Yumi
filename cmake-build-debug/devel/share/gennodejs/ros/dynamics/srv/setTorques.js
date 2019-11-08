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

class setTorquesRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.tau = null;
    }
    else {
      if (initObj.hasOwnProperty('tau')) {
        this.tau = initObj.tau
      }
      else {
        this.tau = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type setTorquesRequest
    // Serialize message field [tau]
    bufferOffset = _arraySerializer.float64(obj.tau, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type setTorquesRequest
    let len;
    let data = new setTorquesRequest(null);
    // Deserialize message field [tau]
    data.tau = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.tau.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'dynamics/setTorquesRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6488f72361a7c3710faf21208a8c781c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[] tau
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new setTorquesRequest(null);
    if (msg.tau !== undefined) {
      resolved.tau = msg.tau;
    }
    else {
      resolved.tau = []
    }

    return resolved;
    }
};

class setTorquesResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.qdd = null;
    }
    else {
      if (initObj.hasOwnProperty('qdd')) {
        this.qdd = initObj.qdd
      }
      else {
        this.qdd = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type setTorquesResponse
    // Serialize message field [qdd]
    bufferOffset = _arraySerializer.float64(obj.qdd, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type setTorquesResponse
    let len;
    let data = new setTorquesResponse(null);
    // Deserialize message field [qdd]
    data.qdd = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.qdd.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'dynamics/setTorquesResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f9f5346aad9a21a7c1a3fdc3006a6c17';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[] qdd
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new setTorquesResponse(null);
    if (msg.qdd !== undefined) {
      resolved.qdd = msg.qdd;
    }
    else {
      resolved.qdd = []
    }

    return resolved;
    }
};

module.exports = {
  Request: setTorquesRequest,
  Response: setTorquesResponse,
  md5sum() { return 'e58e0e3410894d2e4992e2dd98c576ea'; },
  datatype() { return 'dynamics/setTorques'; }
};
