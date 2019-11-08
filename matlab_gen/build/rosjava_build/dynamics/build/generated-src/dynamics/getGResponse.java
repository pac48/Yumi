package dynamics;

public interface getGResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "dynamics/getGResponse";
  static final java.lang.String _DEFINITION = "float64[] g";
  static final boolean _IS_SERVICE = true;
  static final boolean _IS_ACTION = false;
  double[] getG();
  void setG(double[] value);
}
