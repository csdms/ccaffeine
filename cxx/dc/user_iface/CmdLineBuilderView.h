#ifndef CmdLineBuilderView_h_seen
#define CmdLineBuilderView_h_seen

/** Interface definition for Views of commandline builders. 
These can be and are multiplexed.
@see CmdLineBuilderViewMux
*/
class CmdLineBuilderView : public virtual ComponentChangedListener {

private:

public:

  virtual ~CmdLineBuilderView() {}

  /**@ Setup the CmdLineBuilderView before it can answer other calls. */
  //@{
  /** Configure the output stream */
  virtual void setOutputStream(FILE *out_) = 0;
  /** Configure the buildermodel, from which we steal input. */
  virtual void setBuilderModel(BuilderModel *bm_) = 0;
  //@}

  /**@ Stream output functions. */
  //@{
  /** Write an error string to someplace that may eventually reach a user. */
  virtual void error(const char *msg) = 0;
  virtual void error(const std::string msg) = 0;

  /** Write an error Exception to someplace that may eventually reach a user,
      and then die. */
  virtual void errorFatal(const char *msg) = 0;


  /** Write a char and newline to someplace that may eventually reach a user. */
  virtual void pn(const char c) = 0;
  /** Write a char and to someplace that may eventually reach a user. */
  virtual void p(const char c) = 0;

  /** Write a string and newline to someplace that may eventually reach a user. */
  virtual void pn(const char *s)  = 0;
  /** Write a string and to someplace that may eventually reach a user. */
  virtual void p(const char *s)  = 0;
  //@}


  /**@ Changing what's in the container. */
  //@{
  /** Create an instance of a component class using the given name. */
  virtual void pullDownComponent(const char *className, const char *instanceName) = 0;

  /** Make a connection, given arguments in an odd order. */
  virtual void connect(const char *fromInstance, const char *providesInstance,
                      const char *toInstance, const char *usesInstance) = 0;

  /** Break a connection, given arguments in an odd order. */
  virtual void disconnect(const char *fromInstance,
		      const char *providesInstance,
                      const char *toInstance,
		      const char *usesInstance) = 0;

  /** Whine about apparently failing to make a connection. */
  virtual void displayConnectionFailed(const char *message) = 0;

  /** Whine about apparently failing to make a connection. */
  virtual void displayDisconnectionFailed(const char *message) = 0;
  //@}


  /**@ Describing what's in the container. */
  //@{
  /** List classes in the pallet. */
  virtual void displayPallet() = 0;

  /** List instances in the arena. */
  virtual void displayInstantiatedComponents() = 0;
  
  /** List component info for an instance. */
  virtual void displayComponentInfo(const char *instanceName) = 0;

  /** List all the existing connections in the arena. */
  virtual void displayChain() = 0;

  /** List The parameters from a given instance and port, using data
      in output formatting. */
  virtual void displayConfiguration(const char * instanceName, const char * portName, const char * data)=0;

  /** Set a parameter value. */
  virtual void setConfiguration(const char * instanceName, const char * portName, const char * fieldName, const char * data)=0;

  /** List the table of properties on this component. */
  virtual void displayComponentProperties(const char * instanceName, std::vector< std::string > & props) =0;

  /** List named property of component. */
  virtual void displayComponentProperty(const char * instanceName, const char * key, const char * value) =0;

  /** Reflect setting named property of component, possibly including an error result from the buildermodel. */
  virtual void setComponentProperty(const char * instanceName, const char * key, const char * value, int err) =0;

  /** List named property of port, or all if key is the empty string. */
  virtual void displayPortProperties(const std::string & iname, const std::string & pname, ::ccafeopq::TypeMap_shared t, const std::string & key) = 0;

  /** Reflect setting named property of port, possibly including an error result from the buildermodel. */
  virtual void setPortProperty(const std::string & instanceName, const std::string & portName, const std::string & key, const std::string & valType, const std::string & value, int err) = 0;

  //@}


};

typedef ::boost::shared_ptr< CmdLineBuilderView > CmdLineBuilderView_shared;
#endif // CmdLineBuilderView_h_seen
