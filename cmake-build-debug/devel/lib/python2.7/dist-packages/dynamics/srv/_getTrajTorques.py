# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from dynamics/getTrajTorquesRequest.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class getTrajTorquesRequest(genpy.Message):
  _md5sum = "3f47c7f52170cf888db2e2e44df8f0fb"
  _type = "dynamics/getTrajTorquesRequest"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """float64[] q
float64[] qd
float64[] qdd
float64[] Fext
"""
  __slots__ = ['q','qd','qdd','Fext']
  _slot_types = ['float64[]','float64[]','float64[]','float64[]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       q,qd,qdd,Fext

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(getTrajTorquesRequest, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.q is None:
        self.q = []
      if self.qd is None:
        self.qd = []
      if self.qdd is None:
        self.qdd = []
      if self.Fext is None:
        self.Fext = []
    else:
      self.q = []
      self.qd = []
      self.qdd = []
      self.Fext = []

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      length = len(self.q)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.pack(pattern, *self.q))
      length = len(self.qd)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.pack(pattern, *self.qd))
      length = len(self.qdd)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.pack(pattern, *self.qdd))
      length = len(self.Fext)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.pack(pattern, *self.Fext))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.q = struct.unpack(pattern, str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.qd = struct.unpack(pattern, str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.qdd = struct.unpack(pattern, str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.Fext = struct.unpack(pattern, str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      length = len(self.q)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.q.tostring())
      length = len(self.qd)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.qd.tostring())
      length = len(self.qdd)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.qdd.tostring())
      length = len(self.Fext)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.Fext.tostring())
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.q = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.qd = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.qdd = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.Fext = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from dynamics/getTrajTorquesResponse.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class getTrajTorquesResponse(genpy.Message):
  _md5sum = "ab47d2c112ba01b9ab54b5ca03947601"
  _type = "dynamics/getTrajTorquesResponse"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """float64[] Tau
float64 KE
"""
  __slots__ = ['Tau','KE']
  _slot_types = ['float64[]','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       Tau,KE

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(getTrajTorquesResponse, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.Tau is None:
        self.Tau = []
      if self.KE is None:
        self.KE = 0.
    else:
      self.Tau = []
      self.KE = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      length = len(self.Tau)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.pack(pattern, *self.Tau))
      buff.write(_get_struct_d().pack(self.KE))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.Tau = struct.unpack(pattern, str[start:end])
      start = end
      end += 8
      (self.KE,) = _get_struct_d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      length = len(self.Tau)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.Tau.tostring())
      buff.write(_get_struct_d().pack(self.KE))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.Tau = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      start = end
      end += 8
      (self.KE,) = _get_struct_d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_d = None
def _get_struct_d():
    global _struct_d
    if _struct_d is None:
        _struct_d = struct.Struct("<d")
    return _struct_d
class getTrajTorques(object):
  _type          = 'dynamics/getTrajTorques'
  _md5sum = 'a503289886a65ff9ff9284d2897da3bc'
  _request_class  = getTrajTorquesRequest
  _response_class = getTrajTorquesResponse
