package dynamics;

public interface setTorquesResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "dynamics/setTorquesResponse";
  static final java.lang.String _DEFINITION = "float64[] qdd";
  static final boolean _IS_SERVICE = true;
  static final boolean _IS_ACTION = false;
  double[] getQdd();
  void setQdd(double[] value);
}
