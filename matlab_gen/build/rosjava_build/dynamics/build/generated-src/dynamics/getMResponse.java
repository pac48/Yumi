package dynamics;

public interface getMResponse extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "dynamics/getMResponse";
  static final java.lang.String _DEFINITION = "float64[] M";
  static final boolean _IS_SERVICE = true;
  static final boolean _IS_ACTION = false;
  double[] getM();
  void setM(double[] value);
}
