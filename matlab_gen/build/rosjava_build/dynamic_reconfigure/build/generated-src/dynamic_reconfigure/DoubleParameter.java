package dynamic_reconfigure;

public interface DoubleParameter extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "dynamic_reconfigure/DoubleParameter";
  static final java.lang.String _DEFINITION = "string name\nfloat64 value\n";
  static final boolean _IS_SERVICE = false;
  static final boolean _IS_ACTION = false;
  java.lang.String getName();
  void setName(java.lang.String value);
  double getValue();
  void setValue(double value);
}
