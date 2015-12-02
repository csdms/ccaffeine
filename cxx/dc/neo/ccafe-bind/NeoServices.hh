#ifndef __NEOSERVICES_HH__
#define __NEOSERVICES_HH__

/** The handle through which the component communicates with its
    containing framework.
    Member function documentation covers implementation details,
    rather than repeating the doc to be found in class
    neo::cca::Services.
 */
class NeoServices : public virtual neo::cca::Services {
private:
      
  static int nextNum;
  int nsNum;

  ccafeopq::Services* svc;
  std::vector< neo::cca::ComponentRelease * > releaseListeners;

  /** The fewer of these we must manage, the better.
   These are mapping functors.
   */
  std::map< std::string, NeoPortConverter_shared > portConversions;
  
  /** Uses port wrapper data that come and go with get/release, some
   of which are generated by the portConversions.
   */
  std::map< std::string, neo::cca::Port * > portAdapters;

  /** provides port wrapper data that come and go with add/remove */
  std::map< std::string, ccafeopq::Port * > opaquePorts;

  void checkthrow(const char *funcName);

public:

  /** the real constructor */
  NeoServices(ccafeopq::Services* svcs);

  /** test constructor only for qc */
  NeoServices(int bogon);

  /** obligatory virtual destructor */
  virtual ~NeoServices();

  /**  
   * we have special cases to support the binding.
   * - If the port supports neo natively, just get it.
   * - If the port does not support neo, is it one of the
   *   opq supported types for which we registered specially and got connected?
   * - If it is not one we registered for it must be
   *   a port this component 'provides' (possibly by being decorated
   *   by the framework). The spec allows getport of ports on self, after all.
   *   To return these sorts of ports, we may need a wrapper. this is ugly.
   */
  virtual neo::cca::Port *getPort (const std::string & name) throw(neo::cca::Exception);

  /**  
  */
  virtual neo::cca::Port *getPortNonBlocking(const std::string & name) throw(neo::cca::Exception );

  /** 
   */
  virtual void releasePort (const std::string & name)  throw(neo::cca::Exception );

  /** 
  */
  virtual void registerUsesPort(const std::string & name, const std::string & type) throw(neo::cca::Exception);
  /**
   */
  virtual void registerUsesPort(const std::string & name, const std::string & type,
		                neo::cca::TypeMap_shared properties) throw(neo::cca::Exception);

  /** 
  */
  virtual void unregisterUsesPort(const std::string & name) throw(neo::cca::Exception) ;

  /**
   */
  virtual void addProvidesPort(neo::cca::Port *inPort, 
                              const std::string & name, const std::string & type) throw (neo::cca::Exception );
  /**
   */
  virtual void addProvidesPort(neo::cca::Port *inPort, 
                              const std::string & name, const std::string & type,
                              neo::cca::TypeMap_shared properties) throw (neo::cca::Exception );

  /** 
    */
  virtual void removeProvidesPort(const std::string & name) throw (neo::cca::Exception );

  /**
    */
  virtual neo::cca::ComponentID_shared getComponentID();

  /** */
  virtual neo::cca::TypeMap_shared createTypeMap() throw (neo::cca::Exception );

  /** 
   */
  virtual neo::cca::TypeMap_shared getPortProperties(const ::std::string & portName) throw (neo::cca::Exception);

  /**
   **/
  virtual ::std::string genUniquePortName(const ::std::string & base);

  /**
   **/
  virtual void registerForRelease(neo::cca::ComponentRelease *callBack) throw (neo::cca::Exception );

  ///////////////////////////////////////////
  
  /** Real components *never* use this function. (because they can't see it).
   * It's for framework testing purposes only.
   * The pointer returned must not be stored anywhere.
   */
  ::ccafeopq::Services *unwrapServices();

  /**
   * implements release (shutdown) notification, and
   * empties the listener list.
   */
  void notifyReleaseListeners();

};

extern NeoServices NeoServices_test;
#endif // __NEOSERVICES_HH__
