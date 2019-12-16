package dynamics;

public interface getTrajTorquesRequest extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "dynamics/getTrajTorquesRequest";
  static final java.lang.String _DEFINITION = "float64[] q\nfloat64[] qd\nfloat64[] qdd\nfloat64[] Fext\n";
  static final boolean _IS_SERVICE = true;
  static final boolean _IS_ACTION = false;
  double[] getQ();
  void setQ(double[] value);
  double[] getQd();
  void setQd(double[] value);
  double[] getQdd();
  void setQdd(double[] value);
  double[] getFext();
  void setFext(double[] value);
}
