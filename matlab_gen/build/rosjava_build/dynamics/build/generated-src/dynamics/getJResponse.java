package dynamics;

public interface getJResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "dynamics/getJResponse";
  static final java.lang.String _DEFINITION = "float64[] J";
  static final boolean _IS_SERVICE = true;
  static final boolean _IS_ACTION = false;
  double[] getJ();
  void setJ(double[] value);
}
