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

class getTrajTorquesRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.q = null;
      this.qd = null;
      this.qdd = null;
      this.Fext = null;
    }
    else {
      if (initObj.hasOwnProperty('q')) {
        this.q = initObj.q
      }
      else {
        this.q = [];
      }
      if (initObj.hasOwnProperty('qd')) {
        this.qd = initObj.qd
      }
      else {
        this.qd = [];
      }
      if (initObj.hasOwnProperty('qdd')) {
        this.qdd = initObj.qdd
      }
      else {
        this.qdd = [];
      }
      if (initObj.hasOwnProperty('Fext')) {
        this.Fext = initObj.Fext
      }
      else {
        this.Fext = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type getTrajTorquesRequest
    // Serialize message field [q]
    bufferOffset = _arraySerializer.float64(obj.q, buffer, bufferOffset, null);
    // Serialize message field [qd]
    bufferOffset = _arraySerializer.float64(obj.qd, buffer, bufferOffset, null);
    // Serialize message field [qdd]
    bufferOffset = _arraySerializer.float64(obj.qdd, buffer, bufferOffset, null);
    // Serialize message field [Fext]
    bufferOffset = _arraySerializer.float64(obj.Fext, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type getTrajTorquesRequest
    let len;
    let data = new getTrajTorquesRequest(null);
    // Deserialize message field [q]
    data.q = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [qd]
    data.qd = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [qdd]
    data.qdd = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [Fext]
    data.Fext = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.q.length;
    length += 8 * object.qd.length;
    length += 8 * object.qdd.length;
    length += 8 * object.Fext.length;
    return length + 16;
  }

  static datatype() {
    // Returns string type for a service object
    return 'dynamics/getTrajTorquesRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3f47c7f52170cf888db2e2e44df8f0fb';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[] q
    float64[] qd
    float64[] qdd
    float64[] Fext
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new getTrajTorquesRequest(null);
    if (msg.q !== undefined) {
      resolved.q = msg.q;
    }
    else {
      resolved.q = []
    }

    if (msg.qd !== undefined) {
      resolved.qd = msg.qd;
    }
    else {
      resolved.qd = []
    }

    if (msg.qdd !== undefined) {
      resolved.qdd = msg.qdd;
    }
    else {
      resolved.qdd = []
    }

    if (msg.Fext !== undefined) {
      resolved.Fext = msg.Fext;
    }
    else {
      resolved.Fext = []
    }

    return resolved;
    }
};

class getTrajTorquesResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Tau = null;
      this.KE = null;
    }
    else {
      if (initObj.hasOwnProperty('Tau')) {
        this.Tau = initObj.Tau
      }
      else {
        this.Tau = [];
      }
      if (initObj.hasOwnProperty('KE')) {
        this.KE = initObj.KE
      }
      else {
        this.KE = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type getTrajTorquesResponse
    // Serialize message field [Tau]
    bufferOffset = _arraySerializer.float64(obj.Tau, buffer, bufferOffset, null);
    // Serialize message field [KE]
    bufferOffset = _serializer.float64(obj.KE, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type getTrajTorquesResponse
    let len;
    let data = new getTrajTorquesResponse(null);
    // Deserialize message field [Tau]
    data.Tau = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [KE]
    data.KE = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.Tau.length;
    return length + 12;
  }

  static datatype() {
    // Returns string type for a service object
    return 'dynamics/getTrajTorquesResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ab47d2c112ba01b9ab54b5ca03947601';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[] Tau
    float64 KE
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new getTrajTorquesResponse(null);
    if (msg.Tau !== undefined) {
      resolved.Tau = msg.Tau;
    }
    else {
      resolved.Tau = []
    }

    if (msg.KE !== undefined) {
      resolved.KE = msg.KE;
    }
    else {
      resolved.KE = 0.0
    }

    return resolved;
    }
};

module.exports = {
  Request: getTrajTorquesRequest,
  Response: getTrajTorquesResponse,
  md5sum() { return 'a503289886a65ff9ff9284d2897da3bc'; },
  datatype() { return 'dynamics/getTrajTorques'; }
};
