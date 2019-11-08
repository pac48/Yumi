package dynamics;

public interface getTrajTorques$Service extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "dynamics/getTrajTorques$Service";
  static final java.lang.String _DEFINITION = "float64[] q\nfloat64[] qd\nfloat64[] qdd\nfloat64[] Fext\n---\nfloat64[] Tau\nfloat64 KE";
  static final boolean _IS_SERVICE = true;
  static final boolean _IS_ACTION = false;
}
