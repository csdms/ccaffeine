#ifndef CmdLineBuilderViewForHuman_h_seen
#define CmdLineBuilderViewForHuman_h_seen

/** View that puts out ASCII info on stdout or equivalent. */
class CmdLineBuilderViewForHuman : public virtual CmdLineBuilderView {

private:

  BuilderModel *bm;
  FILE *out;

public:

  CDELETE CmdLineBuilderViewForHuman() ;
  virtual ~CmdLineBuilderViewForHuman() ;

  /** Implements ComponentChangedListener.  Signal a change in the
      Component's status. */
  virtual void componentChanged(ComponentChangedEvent* evt);

  virtual void setOutputStream(FILE *out_) ;

  virtual void setBuilderModel(BuilderModel *bm_) ;

  virtual void displayPallet() ;

  virtual void displayInstantiatedComponents() ;
  
  virtual void displayComponentInfo(const char *instanceName);

  virtual void pullDownComponent(const char *className, const char *instanceName) ;

  virtual void connect(const char *fromInstance, const char *providesInstance,
                      const char *toInstance, const char *usesInstance) ;

  virtual void disconnect(const char *fromInstance,
			  const char *providesInstance,
                      const char *toInstance, const char *usesInstance) ;

  virtual void displayConnectionFailed(const char *);
  virtual void displayDisconnectionFailed(const char *);

  virtual void displayChain() ;

  virtual void displayChain(ComponentInfo_shared l);

  virtual void error(const char *msg) ;
  virtual void error(const std::string msg);

  virtual void errorFatal(const char *msg) ;

  virtual void pn(const char *s) ;

  virtual void p(const char *s) ;

  virtual void pn(const std::string & s);

  virtual void p(const std::string & s);

  virtual void pn(const char c) ;

  virtual void p(const char c) ;

  virtual void displayConfiguration(const char * instanceName, const char * portName, const char * data);

  virtual void setConfiguration(const char * instanceName, const char * portName, const char *fieldName, const char * data);

  /** List the table of properties on this component. */
  virtual void displayComponentProperties(const char * instanceName, std::vector< std::string > & props);

  /** List named property of component. */
  virtual void displayComponentProperty(const char * instanceName, const char * key, const char * value);

  /** Reflect setting named property of component, possibly including an error result from the buildermodel. */
  virtual void setComponentProperty(const char * instanceName, const char * key, const char * value, int err);

   /** List named property of port, or all if key is the empty string. */
  virtual void displayPortProperties(const std::string & iname, const std::string & pname, ::ccafeopq::TypeMap_shared t, const std::string & key) ;

      /** Reflect setting named property of port, possibly including an error result from the buildermodel. */
  virtual void setPortProperty(const std::string & instanceName, const std::string & portName, const std::string & key, const std::string & vType, const std::string & value, int err);


};
#endif // CmdLineBuilderViewForHuman_h_seen
