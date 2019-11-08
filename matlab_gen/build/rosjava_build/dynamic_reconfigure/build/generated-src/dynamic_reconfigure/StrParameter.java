package dynamic_reconfigure;

public interface StrParameter extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "dynamic_reconfigure/StrParameter";
  static final java.lang.String _DEFINITION = "string name\nstring value\n";
  static final boolean _IS_SERVICE = false;
  static final boolean _IS_ACTION = false;
  java.lang.String getName();
  void setName(java.lang.String value);
  java.lang.String getValue();
  void setValue(java.lang.String value);
}
