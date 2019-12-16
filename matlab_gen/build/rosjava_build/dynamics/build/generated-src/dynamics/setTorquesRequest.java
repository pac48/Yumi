package dynamics;

public interface setTorquesRequest extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "dynamics/setTorquesRequest";
  static final java.lang.String _DEFINITION = "float64[] tau\n";
  static final boolean _IS_SERVICE = true;
  static final boolean _IS_ACTION = false;
  double[] getTau();
  void setTau(double[] value);
}
