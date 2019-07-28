package simulator;

public interface getStaticTorquesResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "simulator/getStaticTorquesResponse";
  static final java.lang.String _DEFINITION = "float64[] tau";
  static final boolean _IS_SERVICE = true;
  static final boolean _IS_ACTION = false;
  double[] getTau();
  void setTau(double[] value);
}
