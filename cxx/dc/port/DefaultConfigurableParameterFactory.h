#ifndef DefaultConfigurableParameterFactory_h_seen
#define DefaultConfigurableParameterFactory_h_seen

/** Implementation for ccaffeine of the ConfigurableParameterFactory interface.*/
class DefaultConfigurableParameterFactory : public virtual ConfigurableParameterFactory {

public:

  DefaultConfigurableParameterFactory();
  virtual ~DefaultConfigurableParameterFactory() {}

  /** create and return an empty ConfigurableParameterPort */
  /*CDELETE*/ virtual ConfigurableParameterPort *createConfigurableParameterPort();

};
#endif // DefaultConfigurableParameterFactory_h_seen
