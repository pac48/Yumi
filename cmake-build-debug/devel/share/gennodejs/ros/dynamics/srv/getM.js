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

class getMRequest {
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
    // Serializes a message object of type getMRequest
    // Serialize message field [q]
    bufferOffset = _arraySerializer.float64(obj.q, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type getMRequest
    let len;
    let data = new getMRequest(null);
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
    return 'dynamics/getMRequest';
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
    const resolved = new getMRequest(null);
    if (msg.q !== undefined) {
      resolved.q = msg.q;
    }
    else {
      resolved.q = []
    }

    return resolved;
    }
};

class getMResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.M = null;
    }
    else {
      if (initObj.hasOwnProperty('M')) {
        this.M = initObj.M
      }
      else {
        this.M = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type getMResponse
    // Serialize message field [M]
    bufferOffset = _arraySerializer.float64(obj.M, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type getMResponse
    let len;
    let data = new getMResponse(null);
    // Deserialize message field [M]
    data.M = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.M.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'dynamics/getMResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '73e152eab53681d6e00b6057975dbeff';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[] M
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new getMResponse(null);
    if (msg.M !== undefined) {
      resolved.M = msg.M;
    }
    else {
      resolved.M = []
    }

    return resolved;
    }
};

module.exports = {
  Request: getMRequest,
  Response: getMResponse,
  md5sum() { return 'a55fe0135909abaa5d880290a0f368d7'; },
  datatype() { return 'dynamics/getM'; }
};
