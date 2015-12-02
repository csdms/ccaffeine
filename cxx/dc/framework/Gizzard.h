#ifndef __GIZZARD_H__
#define __GIZZARD_H__

#include <map>
#include <string>
#include <vector>




class OpqParameterPortFactory;
class OpqConnectionEventService;

/** CCAFFEINE implementation of the CCA specification. */
class Gizzard : public virtual ::ccafeopq::Services,
		public virtual KernelPort
{

private:
  static bool countInitDone;
  static int pnameCount;

  
  /** True if you want debugging info. */
  bool debug;

  /** Name of this instance. unique. Redundant with CmpBox,
   * ComponentInfo, possibly other things. The thing is, we
   * ned to put it someplace accessible via gizzard and
   * none of those other things are.
   */
  ::ccafeopq::ComponentID_shared cid;


  // provides ports
  ::std::vector< ProviderPortData > pData;
  // uses ports, connected or not
  ::std::vector< UserPortData > uData;
  // provided-port connections.
  ::std::vector< ConnectionID_ptr > cData;
  int serial;
  int nextSerial();


  /** Search a vector of ProviderPortData  for one with name. */
  int findIndex( ::std::vector< ProviderPortData > & info, const std::string & name);

  /** Search a vector of UserPortData  for one with name. */
  int findIndex( ::std::vector< UserPortData > & info, const std::string & name);

  int getNextCount();

  ::ccafeopq::TypeMap_shared compPropertyMap;

  int64_t fortranMPIComm;
  bool hasComm;

public:
  /** Build a Services core object, with name given for component
   * and fortran form mpi communicator (or ignore fcomm and mpi if useComm is false).
   */
  Gizzard(const std::string & instanceName, int64_t fComm, bool useComm);

  virtual ~Gizzard();

  /** Turn on/off debugging information. */
  void dbug(bool tf) {
    debug = tf;
  }


  /** The PortInfo which presumably came from createPortInfo is the
   * Services responsibility (i.e. it takes over the memory management
   * from here on).
   */
  virtual void registerUsesPort(ccafeopq::PortInfo * pInfo) throw 
   (ccafeopq::Exception);

  virtual void registerUsesPort(const ::std::string & pName, const ::std::string & pType, ::ccafeopq::TypeMap_shared props) throw ( ::ccafeopq::Exception );

  /** Returns -1 if error. 0 otherwise. duplicate add is an error. */
  virtual void addProvidesPort(ccafeopq::Port * inPort, 
			      ccafeopq::PortInfo * name) throw (ccafeopq::Exception);


  /** Just like getPort() except it returns a non-type-specific
     ::ccafeopq::Port. does not throw on missing ports. */
  ::ccafeopq::Port * getOpaquePort(const char* name, enum ccafeopq::ExceptionType &status);
  ::ccafeopq::Port * getOpaquePort(const ::std::string & name, enum ccafeopq::ExceptionType &status);

  /** Just like getPort() except it returns a non-type-specific
      ccafeopq::Port. */
  ::ccafeopq::Port * getPort(const std::string & name, enum ccafeopq::ExceptionType &status) throw (ccafeopq::Exception);


  /** Undo the getPort. */
  virtual void releasePort(char *name);
  /** Undo the getPort. */
  virtual void releasePort(const std::string & name) throw (ccafeopq::Exception);
  /** For ccafeopq::Services */
  virtual void releasePort(const char *name);


  /** For the ::ccafeopq:: binding. basically useless otherwise. */
  virtual ccafeopq::PortInfo * 
  createPortInfo(const std::string & name, const std::string & type, 
		 const std::map<std::string, std::string> & properties)  
    throw (ccafeopq::Exception); 

  /** destroy a previously created PortInfo. kill it; not stored
      anywhere. */
  virtual void destroyPortInfo(ccafeopq::PortInfo * pi);

  /** Component instance name for this component. */
  virtual const char* getComponentInstanceName();

  /** return the shared_ptr opaque id. */
  ::ccafeopq::ComponentID_shared getComponentID();
  
  /** get rid of a ComponentID */
  virtual void destroyComponentID( ::ccafeopq::ComponentID_shared cid_);

  virtual void addProvidesPort(ccafeopq::Port*, const std::string& pname, const std::string& ptype, ::ccafeopq::TypeMap_shared t) throw ( ::ccafeopq::Exception );

  virtual void addProvidesPort(ccafeopq::Port*, const std::string& pname, const std::string& ptype) throw ( ::ccafeopq::Exception );

  static ::ccafeopq::TypeMap_shared createTypeMapStatic() throw ( ::ccafeopq::Exception );

  virtual ::ccafeopq::TypeMap_shared createTypeMap() throw ( ::ccafeopq::Exception );

  virtual ::ccafeopq::TypeMap_shared getPortProperties(const ::std::string& Name) throw ( ::ccafeopq::Exception );

  virtual void setPortProperties(const ::std::string& Name, ::ccafeopq::TypeMap_shared tm) throw ( ::ccafeopq::Exception );

  virtual ::std::string genUniquePortName(const ::std::string& baseName) throw ( ::ccafeopq::Exception );

  /** fetch a *copy* of the property data. */
  ::ccafeopq::TypeMap_shared getPropertyMap();

  /** copy data from tm to internal map. */
  void setPropertyMapData( ::ccafeopq::TypeMap_shared tm );


  // Below here these methods are unavailable to the a component
  // contained by our framework.

  /** This was how the framework adds a UsesPort.  Note that this is
      completely inaccessible from the component. DEPRECATED */
  int connectUsesPort(::ccafeopq::PortInfo *info, 
		     ::ccafeopq::Port *up,  
		      ::ccafeopq::PortInfo *fromPI, 
		      Gizzard *fromG);
  /** the connection call, less events. */
  int connectUsesPort(const ::std::string & userPortName,
		      ::ccafeopq::Port *up,  
		      const ::std::string &providerPortName,
		      Gizzard *fromG);

  // for internal (fwk) connections only.
  int connectUsesPort(const ::std::string & pName, ::ccafeopq::Port *up);


  /** Inform Gizzard that its provided Port is nolonger in use in this
      Connection. */
  int disconnectProvidesPort(ConnectionID_ptr c);
  //int disconnectProvidesPort(Connection* c);

  /** Inform Gizzard that its provided Port is used in this Connection.*/
  int connectProvidesPort(ConnectionID_ptr c);
  //int connectProvidesPort(Connection * c);

  /** Get all the connections that are attached to this Gizzard. */
  ::std::vector< ConnectionID_ptr > getConnections();

  /** Get the connections that are used by this Gizzard. */
  ::std::vector< ConnectionID_ptr > getUsesConnections();

  /** Remove all connections to this Gizzard.  */
  int disconnectAllUsesPorts();

  /** In cases that are exceptional, this returns a number < 0, otherwise 0.
      if not uses port exist and connected return silently.
      if isActive, return -1.
      still need to be checked:
      if !fromPI==ups.providedPortInfo hurl rte;
      if !fromG==ups.providerGizzard hurl rte;
  */
  int disconnectUsesPort(int pindex);

  /** Answer with the UsesPort's that have been registered by the
      component holding this Services object. Same as
      getUsesPorts.
  */
  const ::std::vector< UserPortData > & getUsesPortRegister();

  /** Inform Ccaffeine that you no longer intend to use this
      Port. Returns -1 if error. 0 otherwise.  */
    virtual int unregisterUsesPort(const char * name);
  /** Inform Ccaffeine that you no longer intend to use this
      Port. Returns -1 if error. 0 otherwise.  */
    virtual void unregisterUsesPort(const std::string & name) throw (ccafeopq::Exception);
  /** Notify the framework that a Port, previously
      registered by this component, is no longer desired. */
  virtual int unregisterUsesPort(char *name);

  /** Notifies the framework that a previously exported Port is no longer 
      available for use. */
  virtual ::ccafeopq::Port * removeProvidesPort(const char * name);

  
  /** Notifies the framework that a previously exported Port is no longer 
      available for use. */
  virtual ::ccafeopq::Port * removeProvidesPort(const std::string & name) throw (ccafeopq::Exception);

  bool usesThisPortType(const std::string& typeToTest);
  bool providesThisPortType(const std::string& typeToTest);

  ::std::vector< ::std::string > getUsesPortTypes();
  ::std::vector< ::std::string > getUsesPortNames();
  ::std::vector< ::std::string > getProvidesPortTypes();
  ::std::vector< ::std::string > getProvidesPortNames();
  
  /** Mental health methods not on the Services class... */
  /** return a vector list of Uses PortInfos */
  virtual const ::std::vector< UserPortData > & getUsesPorts();

  /** return a vector list of Provides PortInfos */
  virtual const ::std::vector< ProviderPortData > & getProvidesPorts();
  
  /** Return strings describing current connections. Vector
      returned may be empty but not null.
      Each string is
      using-instance uses-port providing-instance provided-port [ACTIVE]
      ACTIVE is present if an outstanding getPort (!isReleased).
      providing-instance may be FRAMEWORK if framework/gizzard
      provides the port.
  */
  ::std::vector< ::std::string> getConnectionStrings();

  OpqConnectionEventService * getOCES();

private: 
  OpqParameterPortFactory *oppf; // very lightweight
  OpqConnectionEventService *oces; // very lightweight
 

  // most of the guts of checkInternalServices are now part of the binding.
  // the kernel is getting smaller and less tangled with legacy code.
  // addServicesHelper and the bindings now take care of binding-
  // specific special ports.
  void checkInternalServices(const ::std::string & name, const ::std::string & type);

  ::ccafeopq::SvcPortMap opaqueDelegates;
  ::std::vector< ::ccafeopq::ServicesHelper * > helpers;

public:
  void initDelegates();

  /** add binding specific helper for port 'service' connections. */
  void addServicesHelper( ::ccafeopq::ServicesHelper *sh);


public:
  virtual void addComponentChangedListener(ComponentChangedListener* l) ;
  void fireComponentChangedEvent(ComponentChangedEvent* evt) ;

  void setFrameData(std::map<std::string, void *> *fd);

  /* basically this is only here for ServicesHelper implementations. */
  ::ccafeopq::TypeMap_shared getComponentInternalPropertyMap();

  bool hasMPIComm(int64_t & fortranBorrowComm) ;
private:
  /** Contains the ComponentChangedListeners */
  ::std::vector< ComponentChangedListener * > cmptChgLsnrs;

private:

  /** A registry for global string to void*. It is global to
   * the instance of ConnectionFramework in which the Gizzard lives.
   * it is forgotten when the gizzard is destroyed.
   */
  ::std::map<std::string, void *> *frame;


};

#endif //__GIZZARD_H__
