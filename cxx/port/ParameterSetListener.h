#ifndef ParameterSetListener_h_seen
#define ParameterSetListener_h_seen

class ConfigurableParameterPort;

  /** This interface is typically only implemented by the owner
      of a ConfigurableParameterPort instance. 

      The ParameterSet listeners on a ParameterPort 
      instance are called after the setConfigurationString function 
      is called.

      The argument pp allows a listener ParameterPort
      to manage more than one. In this case, the updatedParameterValue()
      implementation is responsible for discriminating.

      @see ParameterSetListener
  */
class ParameterSetListener {
public:
  virtual ~ParameterSetListener() {}
  /** The component wishing to listen implements this function. */
  virtual void updatedParameterValue(ParameterPort *pp, 
                                     const char *fieldName,
                                     const char *value )=0;
};

#endif //ParameterSetListener_h_seen
