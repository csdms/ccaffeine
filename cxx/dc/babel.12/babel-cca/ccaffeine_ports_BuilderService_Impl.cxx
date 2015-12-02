// 
// File:          ccaffeine_ports_BuilderService_Impl.cc
// Symbol:        ccaffeine.ports.BuilderService-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ports.BuilderService
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_ports_BuilderService_Impl.hxx"

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService._includes)
// Put additional includes or other arbitrary code here...
int ccaffeine::ports::BuilderService_impl::genSerial = 0;

#define RETHROW(s)  \
catch ( ccafeopq::TypeMismatchException &e) \
{ \
  /* convert */ \
  ccaffeine::TypeMismatchException ex = ccaffeine::TypeMismatchException::_create();  \
	  gov::cca::CCAException gex = ex; \
  ex.initializeTypes( \
  	BabelHelper::babelType(e.getRequestedType()), \
  	BabelHelper::babelType(e.getActualType()) ); \
  ex.SIDL_EXCEPTION_setMessage(e.getMessage()); \
  std::string egm = e.getMessage(); \
  IO_dn2("Exception: %s", egm.c_str()); \
  ex.SIDL_EXCEPTION_addToTrace( __FILE__, __LINE__, s); \
  throw gex; \
} \
catch ( ::ccafeopq::Exception& e2) \
{ \
  ccaffeine::CCAException ex = ccaffeine::CCAException::_create(); \
	  gov::cca::CCAException gex2 = ex; \
  ex.setCCAExceptionType( \
    BabelHelper::babelExceptionType(e2.getType())); \
  ex.SIDL_EXCEPTION_setMessage( e2.getMessage()); \
  std::string e2gm = e2.getMessage(); \
 IO_dn2("Exception: %s", e2gm.c_str()); \
  ex.SIDL_EXCEPTION_addToTrace(  __FILE__, __LINE__, s); \
  throw gex2; \
} do {} while(0)

#include "ccaffeine_ComponentID_Impl.hxx"
#include "ccaffeine_ConnectionID_Impl.hxx"
#include "ccaffeine_TypeMap_Impl.hxx"

// This needs to go away when we clean up the mushy separation of bindings
// from opq model around class and metadata loading.
#include "dc/framework/OpqBuilderService.h"
//#include "dc/user_iface/DefaultBuilderModel.h"
#define FETCHOBS \
OpqBuilderService *obs = ( cbs!=0 ?  dynamic_cast< OpqBuilderService * >(cbs) : 0)


// DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService._includes)

// user defined constructor
void ccaffeine::ports::BuilderService_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService._ctor)
  cbs = 0;
#ifdef CCAFE_AUDIT
  serial = nextNum();
  IO_dn2("ccaffeine::ports::BuilderService_impl _ctor %d", serial);
#endif
  // add construction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService._ctor)
}

// user defined destructor
void ccaffeine::ports::BuilderService_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService._dtor)
#ifdef CCAFE_AUDIT
  serial = -serial;
  IO_dn2("ccaffeine::ports::BuilderService_impl _dtor %d", serial);
#endif
  cbs = 0;
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * @param ccafeopq_BuilderService_port a
 * ::ccafeopq::BuilderService * cast to void *.
 * The pointer will be deleted when the babel wrapper
 * is destroyed.
 */
void
ccaffeine::ports::BuilderService_impl::initialize (
  /*in*/ void* ccafeopq_BuilderService_port ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.initialize)
#ifdef CCAFE_AUDIT
  IO_dn2("ccaffeine::ports::BuilderService_impl init %d", serial);
#endif
  cbs = 
    static_cast< ::ccafeopq::BuilderService *>(ccafeopq_BuilderService_port);
 
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.initialize)
}

/**
 * 	Creates an instance of a CCA component of the type defined by the 
 * 	string className.  The string classname uniquely defines the
 * 	"type" of the component, e.g.
 * 	    doe.cca.Library.GaussianElmination. 
 * 	It has an instance name given by the string instanceName.
 * 	The instanceName may be empty (zero length) in which case
 * 	the instanceName will be assigned to the component automatically.
 * 	@throws CCAException If the Component className is unknown, or if the
 * 		instanceName has already been used, a CCAException is thrown.
 * 	@return A ComponentID corresponding to the created component. Destroying
 * 		the returned ID does not destroy the component; 
 * 		see destroyInstance instead.
 */
::gov::cca::ComponentID
ccaffeine::ports::BuilderService_impl::createInstance (
  /*in*/ const ::std::string& instanceName,
  /*in*/ const ::std::string& className,
  /*in*/ ::gov::cca::TypeMap properties ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.createInstance)
  checkthrow("createInstance");

  ::ccafeopq::TypeMap_shared ctm = 
    BabelOpaqueTypeMap_Interface::opaqueWrap(properties);

  try {
    ::ccafeopq::ComponentID_shared oid =
      cbs->createInstance(instanceName, className, ctm);

    ::gov::cca::ComponentID cid = 
      ccaffeine::ComponentID_impl::babelWrap(oid);
  
    return cid;
  }
  RETHROW("createInstance");

    ::gov::cca::ComponentID cid_bogon;
  return cid_bogon;
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.createInstance)
}


/**
 * add a new directory to the search path for components and babel classes
 */
void
ccaffeine::ports::BuilderService_impl::appendRepositoryPath (
  /* in */ const ::std::string& dirPathElement )
throw ()
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.appendRepositoryPath)
	FETCHOBS;
	obs->appendRepositoryPath(dirPathElement);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.appendRepositoryPath)
}

/**
 * cause ccaffeine to import metadata for the named class to palette.
 */
void
ccaffeine::ports::BuilderService_impl::loadComponentClass (
  /* in */ const ::std::string& className,
  /* in */ bool loadGlobal,
  /* in */ bool loadLazy )
throw ()
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.loadComponentClass)
	FETCHOBS;
	obs->loadRepositoryClass(className, loadGlobal,loadLazy);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.loadComponentClass)
}
/**
 *  Get component list.
 *  @return a ComponentID for each component currently created.
 */
::sidl::array< ::gov::cca::ComponentID>
ccaffeine::ports::BuilderService_impl::getComponentIDs () 
throw ( 
  ::gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.getComponentIDs)
  
  checkthrow("getComponentIDs");
  try {
    ::std::vector< ::ccafeopq::ComponentID_shared > cids = cbs->getComponentIDs();
    sidl::array<gov::cca::ComponentID> res;
    res = ccaffeine::ComponentID_impl::convertToSidlArray(cids);
    return res;
  }
  RETHROW("getComponentIDs");

  // notreached
  ::sidl::array< ::gov::cca::ComponentID> cids_bogon;
  return cids_bogon;
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.getComponentIDs)
}

/**
 *  Get property map for component.
 *  @return the public properties associated with the component referred to by
 *  ComponentID. 
 *  @throws a CCAException if the ComponentID is invalid.
 */
::gov::cca::TypeMap
ccaffeine::ports::BuilderService_impl::getComponentProperties (
  /*in*/ ::gov::cca::ComponentID cid ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.getComponentProperties)
  checkthrow("getComponentProperties");
  try {
    ::ccafeopq::ComponentID_shared oid = findOID(cid);
    ::ccafeopq::TypeMap_shared otm;
    otm = cbs->getComponentProperties(oid);
    gov::cca::TypeMap btm;
    btm = ccaffeine::TypeMap_impl::babelWrap(otm);
    return btm;
  }
  RETHROW("getComponentProperties");

  // notreached
    gov::cca::TypeMap btm_bogon;
   return btm_bogon;
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.getComponentProperties)
}

/**
 * 	Causes the framework implementation to associate the given properties 
 * 	with the component designated by cid. 
 * 	@throws CCAException if cid is invalid or if there is an attempted
 * 	change to a property locked by the framework implementation.
 */
void
ccaffeine::ports::BuilderService_impl::setComponentProperties (
  /*in*/ ::gov::cca::ComponentID cid,
  /*in*/ ::gov::cca::TypeMap map ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.setComponentProperties)
  checkthrow("setComponentProperties");
  try {
    ::ccafeopq::ComponentID_shared oid = findOID(cid);
    ::ccafeopq::TypeMap_shared otm = BabelOpaqueTypeMap_Interface::opaqueWrap(map);
    cbs->setComponentProperties(oid, otm);
  }
  RETHROW("setComponentProperties");
	  
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.setComponentProperties)
}

/**
 * Get component id from stringified reference.
 *    @return a ComponentID from the string produced by 
 * 	ComponentID.getSerialization(). 
 *    @throws CCAException if the string does not represent the appropriate 
 * 	 serialization of a ComponentID for the underlying framework.
 */
::gov::cca::ComponentID
ccaffeine::ports::BuilderService_impl::getDeserialization (
  /*in*/ const ::std::string& s ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.getDeserialization)
  // insert implementation here
  checkthrow("getDeserialization");

  try {
    ::ccafeopq::ComponentID_shared oid = cbs->getDeserialization(s);
    ::gov::cca::ComponentID cid = ccaffeine::ComponentID_impl::babelWrap(oid);
    return cid;
  }
  RETHROW("getDeserialization");

  // notreached
  ::gov::cca::ComponentID cid_bogon;
  return cid_bogon;
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.getDeserialization)
}

/**
 * Get id from name by which it was created.
 *  @return a ComponentID from the instance name of the component
 *  produced by ComponentID.getInstanceName().
 *  @throws CCAException if there is no component matching the 
 *  given componentInstanceName.
 */
::gov::cca::ComponentID
ccaffeine::ports::BuilderService_impl::getComponentID (
  /*in*/ const ::std::string& componentInstanceName ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.getComponentID)
  checkthrow("getComponentID");

  try {
    ::ccafeopq::ComponentID_shared oid =
      cbs->getComponentID(componentInstanceName);

    ::gov::cca::ComponentID cid = 
      ccaffeine::ComponentID_impl::babelWrap(oid);

    return cid;
  }
  RETHROW("getComponentID");
  // notreached
  ::gov::cca::ComponentID cid_bogon;
  return cid_bogon;

  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.getComponentID)
}

/**
 *  Eliminate the Component instance, from the scope of the framework.
 *  @param toDie the component to be removed.
 *  @param timeout the allowable wait; 0 means up to the framework.
 *  @throws CCAException if toDie refers to an invalid component, or
 *  if the operation takes longer than timeout seconds.
 */
void
ccaffeine::ports::BuilderService_impl::destroyInstance (
  /*in*/ ::gov::cca::ComponentID toDie,
  /*in*/ float timeout ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.destroyInstance)
  // insert implementation here
  checkthrow("destroyInstance");
  try {
    ::ccafeopq::ComponentID_shared oid = findOID(toDie);
    cbs->destroyInstance(oid, timeout);
  }
  RETHROW("destroyInstance");
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.destroyInstance)
}

/**
 *  Get the names of Port instances provided by the identified component.
 *  @param cid the component.
 *  @throws CCAException if cid refers to an invalid component.
 */
::sidl::array< ::std::string>
ccaffeine::ports::BuilderService_impl::getProvidedPortNames (
  /*in*/ ::gov::cca::ComponentID cid ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.getProvidedPortNames)
  // insert implementation here
  checkthrow("getProvidedPortNames");
  try {
    ::ccafeopq::ComponentID_shared oid = findOID(cid);
    ::std::vector< ::std::string > names =
      cbs->getProvidedPortNames(oid);
    return BabelHelper::stringVectorToSidlArray(names);
  }
  RETHROW("getProvidedPortNames");
  // notreached
  ::sidl::array< ::std::string> names_bogon;
  return names_bogon;
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.getProvidedPortNames)
}

/**
 *  Get the names of Port instances used by the identified component.
 *  @param cid the component.
 *  @throws CCAException if cid refers to an invalid component. 
 */
::sidl::array< ::std::string>
ccaffeine::ports::BuilderService_impl::getUsedPortNames (
  /*in*/ ::gov::cca::ComponentID cid ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.getUsedPortNames)
  // insert implementation here
  checkthrow("getUsedPortNames");
  try {
    ::ccafeopq::ComponentID_shared oid = findOID(cid);
    ::std::vector< ::std::string > names =
      cbs->getUsedPortNames(oid);
    return BabelHelper::stringVectorToSidlArray(names);
  }
  RETHROW("getUsedPortNames");
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.getUsedPortNames)
}

/**
 *  Fetch map of Port properties exposed by the framework.
 *  @return the public properties pertaining to the Port instance 
 *    portname on the component referred to by cid. 
 *  @throws CCAException when any one of the following conditions occur:<ul>
 *    <li>portname is not a registered Port on the component indicated by cid,
 *    <li>cid refers to an invalid component. </ul>
 */
::gov::cca::TypeMap
ccaffeine::ports::BuilderService_impl::getPortProperties (
  /*in*/ ::gov::cca::ComponentID cid,
  /*in*/ const ::std::string& portName ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.getPortProperties)
  checkthrow("getPortProperties");
  try {
    ::ccafeopq::ComponentID_shared oid = findOID(cid);
    ::ccafeopq::TypeMap_shared otm = cbs->getPortProperties(oid,portName);
    // if it's a special type, we have to re-type the type string on this
    // copy before exposing it to babel.
    std::string ccaPortType = otm->getString("cca.portType","BUG_PORTTYPE_ccaffeine::ports::BuilderService_impl");
    std::string ccafeBabelPortType = otm->getString("ccafe.babel.portType", ccaPortType);
    //std::string ccafeBabelPortType = otm->getString("ccafe.babel.portType", "BUGneverSet");
    otm->putString("cca.portType", ccafeBabelPortType);
    // wrap it up
    gov::cca::TypeMap btm; 
    btm = ccaffeine::TypeMap_impl::babelWrap(otm);
    return btm;
  }
  RETHROW("getPortProperties");
  // notreached
    gov::cca::TypeMap btm_bogon;
   return btm_bogon;
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.getPortProperties)
}

/**
 *  Associates the properties given in map with the Port indicated by 
 *  portname. The component must have a Port known by portname.
 *  @throws CCAException if either cid or portname are
 * 	invalid, or if this a changed property is locked by 
 * 	 the underlying framework or component.
 */
void
ccaffeine::ports::BuilderService_impl::setPortProperties (
  /*in*/ ::gov::cca::ComponentID cid,
  /*in*/ const ::std::string& portName,
  /*in*/ ::gov::cca::TypeMap map ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.setPortProperties)
  // insert implementation here
  checkthrow("setPortProperties");
  try {
    ::ccafeopq::ComponentID_shared oid = findOID(cid);
    ::ccafeopq::TypeMap_shared otm;
    otm = BabelOpaqueTypeMap_Interface::opaqueWrap(map);
    cbs->setPortProperties(oid, portName, otm);
  }
  RETHROW("setPortProperties");
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.setPortProperties)
}

/**
 *   Creates a connection between ports on component user and 
 *   component provider. Destroying the ConnectionID does not
 *   cause a disconnection; for that, see disconnect().
 *   @throws CCAException when any one of the following conditions occur:<ul>
 *   <li>If either user or provider refer to an invalid component,
 *   <li>If either usingPortName or providingPortName refer to a 
 * 	 nonexistent Port on their respective component,
 *   <li>If other-- In reality there are a lot of things that can go wrong 
 * 	 with this operation, especially if the underlying connections 
 * 	 involve networking.</ul>
 */
::gov::cca::ConnectionID
ccaffeine::ports::BuilderService_impl::connect (
  /*in*/ ::gov::cca::ComponentID user,
  /*in*/ const ::std::string& usingPortName,
  /*in*/ ::gov::cca::ComponentID provider,
  /*in*/ const ::std::string& providingPortName ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.connect)
  checkthrow("connect");
  try {
    IO_dn1("entry");
    ::ccafeopq::ComponentID_shared uoid = findOID(user);
    ::ccafeopq::ComponentID_shared poid = findOID(provider);
    IO_dn1("done with component id");
    // ::ccafeopq::TypeMap_shared otm = BabelOpaqueTypeMap_Interface::opaqueWrap(map);
    ::ccafeopq::ConnectionID_shared oconn =
      cbs->connect(uoid, usingPortName, poid, providingPortName);
    IO_dn1("Done with connect");
    gov::cca::ConnectionID bconn;
    // Fix me (?)
        bconn = ccaffeine::ConnectionID_impl::babelWrap(oconn);
    IO_dn1("Done with wrap");
    return bconn; // nil connection returned witout wrap statement above
  } 
    RETHROW("connect");
  // notreached
  ::gov::cca::ConnectionID connid_bogon;
  return connid_bogon;
  
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.connect)
}

/**
 * Returns a list of connections as an array of 
 * 	handles. This will return all connections involving components 
 * 	in the given componentList of ComponentIDs. This
 * 	means that ConnectionID's will be returned even if only one 
 * 	of the participants in the connection appears in componentList.
 * 
 * 	@throws CCAException if any component in componentList is invalid.
 */
::sidl::array< ::gov::cca::ConnectionID>
ccaffeine::ports::BuilderService_impl::getConnectionIDs (
  /*in*/ ::sidl::array< ::gov::cca::ComponentID> componentList ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.getConnectionIDs)
  // insert implementation here
  checkthrow("getConnectionIDs");
  try {
    // repackage input
    int len = (componentList.upper(0) - componentList.lower(0)) + 1;
    ::std::vector< ::ccafeopq::ComponentID_shared > clist;
    int bottom = componentList.lower(0);
    for (int i = 0; i < len; i++)
    {
      gov::cca::ComponentID bid = componentList.get(bottom+i);
      ::ccafeopq::ComponentID_shared oid = findOID( bid );
      clist.push_back(oid);
    }

    // repackage output
    ::std::vector< ::ccafeopq::ConnectionID_shared > conns;
    conns = cbs->getConnectionIDs(clist);
    sidl::array< ::gov::cca::ConnectionID > bconns;
    bconns = ccaffeine::ConnectionID_impl::convertToSidlArray(conns);
    return bconns;
  }
  RETHROW("getConnectionIDs");
  // notreached
  ::sidl::array< ::gov::cca::ConnectionID> list_bogon;
  return list_bogon;
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.getConnectionIDs)
}

/**
 *   Fetch property map of a connection.
 *   @returns the properties for the given connection.
 *   @throws CCAException if connID is invalid.
 */
::gov::cca::TypeMap
ccaffeine::ports::BuilderService_impl::getConnectionProperties (
  /*in*/ ::gov::cca::ConnectionID connID ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.getConnectionProperties)
  checkthrow("getConnectionProperties");
  try {
    ::ccafeopq::ConnectionID_shared ocid = findOConnID(connID);
    ::ccafeopq::TypeMap_shared otm = cbs->getConnectionProperties(ocid);
    gov::cca::TypeMap btm;
    btm = ccaffeine::TypeMap_impl::babelWrap(otm);
    return btm;
  }
  RETHROW("getConnectionProperties");
  // notreached
    gov::cca::TypeMap btm_bogon;
   return btm_bogon;
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.getConnectionProperties)
}

/**
 * Associates the properties with the connection.
 *   @param map the source of the properties.
 *   @param connID connection to receive property values.
 *   @throws CCAException if connID is invalid, or if this changes 
 * 	 a property locked by the underlying framework.
 */
void
ccaffeine::ports::BuilderService_impl::setConnectionProperties (
  /*in*/ ::gov::cca::ConnectionID connID,
  /*in*/ ::gov::cca::TypeMap map ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.setConnectionProperties)
  checkthrow("setConnectionProperties");
  try {
    ::ccafeopq::ConnectionID_shared ocid = findOConnID(connID);
    ::ccafeopq::TypeMap_shared ctm = 
      BabelOpaqueTypeMap_Interface::opaqueWrap( map );
    cbs->setConnectionProperties(ocid,ctm);
  }
  RETHROW("setConnectionProperties");
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.setConnectionProperties)
}

/**
 * Disconnect the connection indicated by connID before the indicated
 *     timeout in secs. Upon successful completion, connID and the connection
 *     it represents become invalid. 
 *     @param timeout the time in seconds to wait for a connection to close; 0
 *     means to use the framework implementation default.
 *     @throws CCAException when any one of the following conditions occur: <ul>
 *     <li>id refers to an invalid ConnectionID,
 *     <li>timeout is exceeded, after which, if id was valid before 
 * disconnect() was invoked, it remains valid
 * </ul>
 * 
 */
void
ccaffeine::ports::BuilderService_impl::disconnect (
  /*in*/ ::gov::cca::ConnectionID connID,
  /*in*/ float timeout ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.disconnect)
  checkthrow("disconnect");
  try {
    ::ccafeopq::ConnectionID_shared ocid = findOConnID(connID);
    cbs->disconnect(ocid, timeout);
  }
  RETHROW("disconnect");
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.disconnect)
}

/**
 * Remove all connections between components id1 and id2 within 
 *   the period of timeout secs. If id2 is null, then all connections 
 *   to id1 are removed (within the period of timeout secs).
 *   @throws CCAException when any one of the following conditions occur:<ul>
 * 	  <li>id1 or id2 refer to an invalid ComponentID (other than id2 == null),
 * 	  <li>The timeout period is exceeded before the disconnections can be made. 
 * 	  </ul>
 */
void
ccaffeine::ports::BuilderService_impl::disconnectAll (
  /*in*/ ::gov::cca::ComponentID id1,
  /*in*/ ::gov::cca::ComponentID id2,
  /*in*/ float timeout ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService.disconnectAll)
  checkthrow("disconnectAll");
  try {
    ::ccafeopq::ComponentID_shared uoid = findOID(id1);
    ::ccafeopq::ComponentID_shared poid = findOID(id2);
    cbs->disconnectAll(uoid, poid, timeout);
  }
  RETHROW("disconnectAll");
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService.disconnectAll)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService._misc)
// Put miscellaneous code here
void ccaffeine::ports::BuilderService_impl::checkthrow(const char *funcName)
{
  if (! cbs) {
    ::ccaffeine::CCAException ex = ::ccaffeine::CCAException::_create();
    std::string mess = "ccaffeine::ports::BuilderService_impl cbs uninit in ";
    mess += funcName;
    ex.setCCAExceptionType( ::gov::cca::CCAExceptionType_Nonstandard);
    ex.SIDL_EXCEPTION_setMessage(mess);
    throw ex;
  }
}

::ccafeopq::ConnectionID_shared  ccaffeine::ports::BuilderService_impl::findOConnID( gov::cca::ConnectionID bconn)
{
	std::vector< ::ccafeopq::ConnectionID_shared > matches = findOConnIDs(bconn);
	if ( matches.size() != 1 )
	{
		::ccafeopq::ConnectionID_shared nilconn;
		return nilconn;
	} else {
		return matches[0];
	}
}

std::vector< ::ccafeopq::ConnectionID_shared > ccaffeine::ports::BuilderService_impl::findOConnIDs( gov::cca::ConnectionID bconn)
{
	std::vector< ::ccafeopq::ConnectionID_shared > matches;
	if (bconn._is_nil()) {
		return matches;
	}

	::gov::cca::ComponentID uid = bconn.getUser();
	::gov::cca::ComponentID pid = bconn.getProvider();

	::std::string uname = uid.getInstanceName();
	::std::string pname = pid.getInstanceName();
	::std::string uport = bconn.getUserPortName();
	::std::string pport = bconn.getProviderPortName();

	matches = cbs->getConnectionIDs(uname, uport, pname, pport);
	return matches;
}

::ccafeopq::ComponentID_shared ccaffeine::ports::BuilderService_impl::findOID( gov::cca::ComponentID bid)
{
	::std::string cname = bid.getInstanceName();
	::ccafeopq::ComponentID_shared oid;
	oid = cbs->getComponentID(cname);
	return oid;
}
		      
// DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService._misc)

