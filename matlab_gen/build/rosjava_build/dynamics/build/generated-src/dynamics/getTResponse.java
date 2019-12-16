package dynamics;

public interface getTResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "dynamics/getTResponse";
  static final java.lang.String _DEFINITION = "float64[] T";
  static final boolean _IS_SERVICE = true;
  static final boolean _IS_ACTION = false;
  double[] getT();
  void setT(double[] value);
}
