package dynamics;

public interface getCResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "dynamics/getCResponse";
  static final java.lang.String _DEFINITION = "float64[] c";
  static final boolean _IS_SERVICE = true;
  static final boolean _IS_ACTION = false;
  double[] getC();
  void setC(double[] value);
}
