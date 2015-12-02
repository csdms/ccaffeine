#ifndef ConfigurableParameterFactory_h_seen
#define ConfigurableParameterFactory_h_seen

/**
  This is a simple factory to hide the details of the
  framework from the component. Any component that
  wishes to provide a ParameterPort can use a
  ConfigurableParameterFactory Port to obtain it from
  the framework and provide it by delegation.
*/
class ConfigurableParameterFactory 
#ifdef HAVE_CLASSIC
:  public virtual classic::gov::cca::Port
#endif // HAVE_CLASSIC
{

public:

  virtual ~ConfigurableParameterFactory() {}

  /** Create and return an empty ConfigurableParameterPort
   */
  /*CDELETE*/ virtual ConfigurableParameterPort *createConfigurableParameterPort() =0;

};


#endif //ConfigurableParameterFactory_h_seen
