package dynamics;

public interface getTrajTorquesResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "dynamics/getTrajTorquesResponse";
  static final java.lang.String _DEFINITION = "float64[] Tau\nfloat64 KE";
  static final boolean _IS_SERVICE = true;
  static final boolean _IS_ACTION = false;
  double[] getTau();
  void setTau(double[] value);
  double getKE();
  void setKE(double value);
}
