#ifndef CmdLineBuilderViewMux_h_seen
#define CmdLineBuilderViewMux_h_seen

// requires
// #include "dc/framework/ComponentInfo.h"
// #include "dc/user_iface/BuilderView.h"
// #include "dc/user_iface/BuilderModel.h"

// #include "dc/framework/dc_fwkPublic.h"
// #include "dc/user_iface/CmdLineBuilderView.h"
// #include "dc/user_iface/CmdLineBuilderViewMux.h"
// #include "dc/framework/ComponentChangedEvent.h"
// #include "dc/framework/ComponentChangedListener.h"


/** Multiplexer of Views for the CmdLineBuilder. */
class CmdLineBuilderViewMux : public virtual CmdLineBuilderView {

private:

  ::std::vector< CmdLineBuilderView_shared > clbv; 

public:

  CmdLineBuilderViewMux();

  virtual ~CmdLineBuilderViewMux();

  /** Implements ComponentChangedListener.  Signal a change in the
      Component's status. */
  virtual void componentChanged(ComponentChangedEvent* evt) {
    // do nothing the others have added themselves to the bm
    (void)evt;
  }
    /** mux specific */
  void addCLBV(CmdLineBuilderView_shared bv);

  virtual void setOutputStream(FILE *out_);

  virtual void setBuilderModel(BuilderModel *bm_);

  virtual void displayPallet();

  virtual void displayInstantiatedComponents();
  
  virtual void displayComponentInfo(const char *instanceName);

  virtual void pullDownComponent(const char *className, const char *instanceName);

  virtual void connect(const char *fromInstance, const char *providesInstance,
                      const char *toInstance,const  char *usesInstance);

  virtual void disconnect(const char *fromInstance,
		 	 const char *providesInstance,
                      const char *toInstance, const char *usesInstance);

  virtual void displayChain();

  virtual void displayConnectionFailed(const char *msg);
  virtual void displayDisconnectionFailed(const char *msg);

  virtual void error(const char *msg);
  virtual void error(const std::string msg);

  /** this is kind of a funny one to mux, eh? */
  virtual void errorFatal(const char *msg);

  virtual void pn(const char *s) ;

  virtual void p(const char *s) ;

  virtual void pn(const char c);

  virtual void p(const char c);

  virtual void displayConfiguration(const char * instanceName, const char * portName,const char * data) ;

  virtual void setConfiguration(const char * instanceName, const char * portName, const char * fieldName, const char * data) ;

  virtual void displayComponentProperties(const char * instanceName, std::vector< std::string > & props);

  virtual void displayComponentProperty(const char * instanceName, const char * key, const char * value);

  virtual void setComponentProperty(const char * instanceName, const char * key, const char * value, int err);

  /** List named property of port, or all if key is the empty string. */
  virtual void displayPortProperties(const std::string & iname, const std::string & pname, ::ccafeopq::TypeMap_shared t, const std::string & key) ;

  /** Reflect setting named property of port, possibly including an error result from the buildermodel. */
  virtual void setPortProperty(const std::string & instanceName, const std::string & portName, const std::string & key, const std::string & vType, const std::string & value, int err);


};
#endif // CmdLineBuilderViewMux_h_seen
