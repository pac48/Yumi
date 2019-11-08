package dynamics;

public interface getCRequest extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "dynamics/getCRequest";
  static final java.lang.String _DEFINITION = "float64[] q\nfloat64[] qd\n";
  static final boolean _IS_SERVICE = true;
  static final boolean _IS_ACTION = false;
  double[] getQ();
  void setQ(double[] value);
  double[] getQd();
  void setQd(double[] value);
}
