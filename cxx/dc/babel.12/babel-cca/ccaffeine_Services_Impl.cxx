// 
// File:          ccaffeine_Services_Impl.cc
// Symbol:        ccaffeine.Services-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.Services
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_Services_Impl.hxx"

// DO-NOT-DELETE splicer.begin(ccaffeine.Services._includes)

int ccaffeine::Services_impl::genSerial =0;

#include "dc/babel.12/babel-cca/server/ccaffeine_ports_PortTranslator.hxx"
#include "ccaffeine_TypeMap_Impl.hxx"
#include "gov_cca_CCAExceptionType.hxx"
#include "ccaffeine_ComponentID_Impl.hxx"
#include "dc/babel.12/ccafe-bind/BabelOpaqueComponentFactory.hh"
#include "dc/babel.12/babel-cca/BabelCCAHelpers.hxx"
#include "util/IO.h"
#include <ctype.h>
#include <cstring>

// return true iff type is a valid SIDL type name
// use a simple finite state machine to check if type matches 
// the regular expression: 
//    [a-zA-Z][a-zA-Z0-9_]*(\\.[a-zA-Z][a-zA-Z0-9_]*)+
static bool
isCorrectSIDLType(const ::std::string& type)
{
  bool period = false;
  int state = 0;
  ::std::string::const_iterator i = type.begin();
  const ::std::string::const_iterator end = type.end();
  while (i != end) {
    if (isalpha(*i)) {
      if ((0 == state) || (1 == state)) { state = 2; }
    }
    else if (isdigit(*i) || ('_' == *i)) {
      if (2 != state) return false;
    }
    else if ('.' == *i) {
      if (2 == state) { state = 1; period = true; }
      else return false;
    }
    else {
      return false;
    }
    ++i;
  }
  return (2 == state) && period;
}

// DO-NOT-DELETE splicer.end(ccaffeine.Services._includes)

// user defined constructor
void ccaffeine::Services_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services._ctor)
  // add construction details here
  giz = 0;
#ifdef CCAFE_AUDIT
  serial = nextNum();
  IO_dn2("ccaffeine::Services_impl _ctor %d", serial);
#endif
  // DO-NOT-DELETE splicer.end(ccaffeine.Services._ctor)
}

// user defined destructor
void ccaffeine::Services_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services._dtor)
  // add destruction details here
  giz = 0;
#ifdef CCAFE_AUDIT
  IO_dn2("ccaffeine::Services_impl _dtor %d", serial);
  serial = -serial;
#endif
  // DO-NOT-DELETE splicer.end(ccaffeine.Services._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  initialize[]
 */
void
ccaffeine::Services_impl::initialize (
  /*in*/ void* g ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services.initialize)

#ifdef CCAFE_AUDIT
  IO_dn2("ccaffeine::Services_impl init %d", serial);
#endif
  giz = static_cast< ::ccafeopq::Services*>(g);

  // DO-NOT-DELETE splicer.end(ccaffeine.Services.initialize)
}

/**
 * Method:  hasMPIComm[]
 */
bool
ccaffeine::Services_impl::hasMPIComm (
  /* inout */ int64_t& fortranBorrowComm ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services.hasMPIComm)
  // Insert-Code-Here {ccaffeine.Services.hasMPIComm} (hasMPIComm method)
	return giz->hasMPIComm(fortranBorrowComm);
  // DO-NOT-DELETE splicer.end(ccaffeine.Services.hasMPIComm)
}

/**
 * Method:  doReleaseCallbacks[]
 */
void
ccaffeine::Services_impl::doReleaseCallbacks () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services.doReleaseCallbacks)
	for (size_t i = 0; i < releaseCallBacks.size(); i++)
	{
		gov::cca::ComponentRelease cr = releaseCallBacks[i];
		cr.releaseServices(*this);
	}
	releaseCallBacks.clear();
  // DO-NOT-DELETE splicer.end(ccaffeine.Services.doReleaseCallbacks)
}

/**
 * fetch up a pointer for static casting. if the name
 * supplied is not exactly right, returns null.
 */
void*
ccaffeine::Services_impl::getWrapped (
  /*in*/ const ::std::string& className )
throw ()
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services.getWrapped)
  return giz;
  // DO-NOT-DELETE splicer.end(ccaffeine.Services.getWrapped)
}
                                                                               

/**
 * Fetch a previously registered Port (defined by either 
 * addProvidePort or (more typically) registerUsesPort).  
 * @return Will return the Port (possibly waiting forever while
 * attempting to acquire it) or throw an exception. Does not return
 * NULL, even in the case where no connection has been made. 
 * If a Port is returned,
 * there is then a contract that the port will remain valid for use
 * by the caller until the port is released via releasePort(), or a 
 * Disconnect Event is successfully dispatched to the caller,
 * or a runtime exception (such as network failure) occurs during 
 * invocation of some function in the Port. 
 * <p>
 * Subtle interpretation: If the Component is not listening for
 * Disconnect events, then the framework has no clean way to
 * break the connection until after the component calls releasePort.
 * </p>
 * <p>The framework may go through some machinations to obtain
 *    the port, possibly involving an interactive user or network 
 *    queries, before giving up and throwing an exception.
 * </p>
 * 
 * @param portName The previously registered or provide port which
 * 	   the component now wants to use.
 * @exception CCAException with the following types: NotConnected, PortNotDefined, 
 *                NetworkError, OutOfMemory.
 */
::gov::cca::Port
ccaffeine::Services_impl::getPort (
  /*in*/ const ::std::string& portName ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services.getPort)

  // do we have it at all?
  ccafeopq::ExceptionType status = ccafeopq::Correct;
  ::ccafeopq::Port* op = giz->getPort(portName, status);
  if (op == NULL) {
    ccaffeine::CCAException ex = ccaffeine::CCAException::_create();
    switch(status) {
    case ccafeopq::PortNotConnected: {
      std::string msg = "Port not connected: " + portName;
      ex.setNote(msg);
      ex.add(__FILE__, __LINE__, "ccaffeine.Services.getPort");
      ex.setCCAExceptionType(gov::cca::CCAExceptionType_PortNotConnected);
    }
    case ccafeopq::PortNotDefined: {
      std::string msg = "Port not defined: " + portName;
      ex.setNote(msg);
      ex.add(__FILE__, __LINE__, "ccaffeine.Services.getPort");
      ex.setCCAExceptionType(gov::cca::CCAExceptionType_PortNotDefined);
    }
    default: {
      std::string msg = "Unanticipated error fetching: " + portName;
      ex.setNote(msg);
      ex.add(__FILE__, __LINE__, "ccaffeine.Services.getPort");
      ex.setCCAExceptionType(static_cast<gov::cca::CCAExceptionType>(status));
    }
    } // end switch
    throw ex;
    return gov::cca::Port(); // NULL. NotReached; not with cca specification behavior.
  }
  // is it a special case for this binding set up during registerUses?
  if (portConversions.find(portName) != portConversions.end()) {
    // if so, generate the wrapper around the opaque port
    ::gov::cca::Port p = portConversions[portName]->convert(op);
    // when the caller lets go of it, this wrapper will destroy
    // itself
    return p;
  }
  // Is it a special case of us getting a provides port specific to
  // our component (or its gizzard) that happens to be opaque and
  // not a port that went through registerUses/connect setup and needs a wrapper?
  if ( op->supportsKind(ccafeopq::OPAQUE_PORT) ) {
    gov::cca::Port wrap = ccafe::BabelCCAHelpers::convert(op);
    if ( wrap._not_nil() ) {
      return wrap;
    }
  }
  // normal case: just return it.
  return getBabelPort(op);

  // DO-NOT-DELETE splicer.end(ccaffeine.Services.getPort)
}

/**
 * Get a previously registered Port (defined by
 * either addProvide or registerUses) and return that
 * Port if it is available immediately (already connected
 * without further connection machinations).
 * There is an contract that the
 * port will remain valid per the description of getPort.
 * @return The named port, if it exists and is connected or self-provided,
 * 	      or NULL if it is registered and is not yet connected. Does not
 * 	      return if the Port is neither registered nor provided, but rather
 * 	      throws an exception.
 * @param portName registered or provided port that
 * 	     the component now wants to use.
 * @exception CCAException with the following types: PortNotDefined, OutOfMemory.
 */
::gov::cca::Port
ccaffeine::Services_impl::getPortNonblocking (
  /*in*/ const ::std::string& portName ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services.getPortNonblocking)

  return getPort(portName);

  // DO-NOT-DELETE splicer.end(ccaffeine.Services.getPortNonblocking)
}

/**
 * Notifies the framework that this component is finished 
 * using the previously fetched Port that is named.     
 * The releasePort() method calls should be paired with 
 * getPort() method calls; however, an extra call to releasePort()
 * for the same name may (is not required to) generate an exception.
 * Calls to release ports which are not defined or have never be fetched
 * with one of the getPort functions generate exceptions.
 * @param portName The name of a port.
 * @exception CCAException with the following types: PortNotDefined, PortNotInUse.
 */
void
ccaffeine::Services_impl::releasePort (
  /*in*/ const ::std::string& portName ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services.releasePort)

  giz->releasePort(portName);

  // DO-NOT-DELETE splicer.end(ccaffeine.Services.releasePort)
}

/**
 * Creates a TypeMap, potentially to be used in subsequent
 * calls to describe a Port.  Initially, this map is empty.
 */
::gov::cca::TypeMap
ccaffeine::Services_impl::createTypeMap () 
throw ( 
  ::gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services.createTypeMap)

  ::ccafeopq::TypeMap_shared tm = giz->createTypeMap();
  if (! tm) {
#ifdef CCAFE_AUDIT
    IO_dn2("Services_impl createTypeMap received null from opq Services. %d",
		    serial);
#endif
    ::gov::cca::TypeMap btm; // nil map
    return btm;
  }
  ccaffeine::TypeMap btm = ccaffeine::TypeMap_impl::babelWrap(tm);

  return btm;

  // DO-NOT-DELETE splicer.end(ccaffeine.Services.createTypeMap)
}

/**
 * Register a request for a Port that will be retrieved subsequently 
 * with a call to getPort().
 * @param portName A string uniquely describing this port.  This string
 * must be unique for this component, over both uses and provides ports.
 * @param type A string desribing the type of this port.
 * @param properties A TypeMap describing optional properties
 * associated with this port. This can be a null pointer, which
 * indicates an empty list of properties.  Properties may be
 * obtained from createTypeMap or any other source.  The properties
 * be copied into the framework, and subsequent changes to the
 * properties object will have no effect on the properties
 * associated with this port.
 * In these properties, all frameworks recognize at least the
 * following keys and values in implementing registerUsesPort:
 * <pre>
 * key:              standard values (in string form)     default
 * "MAX_CONNECTIONS" any nonnegative integer, "unlimited".   1
 * "MIN_CONNECTIONS" any integer > 0.                        0
 * "ABLE_TO_PROXY"   "true", "false"                      "false"
 * </pre>
 * The component is not expected to work if the framework
 * has not satisfied the connection requirements.
 * The framework is allowed to return an error if it
 * is incapable of meeting the connection requirements,
 * e.g. it does not implement multiple uses ports.
 * The caller of registerUsesPort is not obligated to define
 * these properties. If left undefined, the default listed above is
 *       assumed.
 * @exception CCAException with the following types: PortAlreadyDefined, OutOfMemory.
 */
void
ccaffeine::Services_impl::registerUsesPort (
  /*in*/ const ::std::string& portName,
  /*in*/ const ::std::string& type,
  /*in*/ ::gov::cca::TypeMap properties ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services.registerUsesPort)
  if (properties._is_nil()) {
	  properties = (*this).createTypeMap();
  }
  if (! isCorrectSIDLType(type)) {
    gov::cca::CCAException ex = ::ccaffeine::CCAException::_create();
    ex.SIDL_EXCEPTION_setMessage(::std::string("ccaffeine::Services_impl::registerUsesPort: ") + 
				 type + ::std::string(" \
is not a valid SIDL type name. A SIDL type name is a period separated list of identifiers. Each identifier must begin with a letter and then may contain any number of letters, digits and underscores. A SIDL type name should match [a-zA-Z][a-zA-Z0-9_]*(\\.[a-zA-Z][a-zA-Z0-9_]*)+"));
    throw ex;
  }

  ::ccafeopq::TypeMap_shared tm = 
    BabelOpaqueTypeMap_Interface::opaqueWrap(properties);

  properties.putString("cca.portType", type);
  properties.putString("cca.portName", portName);
  properties.putString("ccafe.babel.portType", type );
  // FIXME ccaffeine.Services.registerUsesPort
  // this block needs to move out into a helper and
  // be abstracted ala neo.
  std::string ntype = type;
  if(type == "gov.cca.BuilderService" ||
     type == "gov.cca.ports.BuilderService") {
    ntype = "::ccafeopq::BuilderService";
    BuilderServicePC *bspc = new BuilderServicePC();
    boost::shared_ptr< PortConverter > bspc_ptr(bspc);
    portConversions[portName] = bspc_ptr;
  }

  if(type == "gov.cca.ports.GoPort") {
    ntype = "::ccafeopq::GoPort";
    GoPortPC *gppc = new GoPortPC();
    boost::shared_ptr< PortConverter > gppc_ptr(gppc);
    portConversions[portName] = gppc_ptr;
  }

  if(type == "gov.cca.ports.ServiceRegistry") {
    ntype = "::ccafeopq::ServiceRegistry";
    ServiceRegistryPC *srpc = new ServiceRegistryPC();
    ccafeopq::ComponentID_shared mcid = giz->getComponentID();
    srpc->initialize(mcid);
    boost::shared_ptr< PortConverter > srpc_ptr(srpc);
    portConversions[portName] = srpc_ptr;
  }

  if(type == "gov.cca.ports.ParameterPortFactory") {
    ntype = "::ccafeopq::ports::ParameterPortFactory";
    ParameterPortFactoryPC *ppfpc = new ParameterPortFactoryPC();
    boost::shared_ptr< PortConverter > ppfpc_ptr(ppfpc);
    portConversions[portName] = ppfpc_ptr;
  }
  if(type == "gov.cca.ports.ConnectionEventService") {
    ntype = "::ccafeopq::ports::ConnectionEventService";
    ConnectionEventServicePC *cespc = new ConnectionEventServicePC();
    boost::shared_ptr< PortConverter > cespc_ptr(cespc);
    portConversions[portName] = cespc_ptr;
  }

  if(type == "gov.cca.ports.ParameterPort") {
    ntype = "::ccafeopq::ports::ParameterPort";
    ParameterPortPC *pppc = new ParameterPortPC();
    boost::shared_ptr< PortConverter > pppc_ptr(pppc);
    portConversions[portName] = pppc_ptr;
  }

  if(type == "gov.cca.ports.BasicParameterPort") {
    ntype = "::ccafeopq::ports::BasicParameterPort";
    BasicParameterPortPC *bpppc = new BasicParameterPortPC();
    boost::shared_ptr< PortConverter > bpppc_ptr(bpppc);
    portConversions[portName] = bpppc_ptr;
  }

  if (type == "ccaffeine.ports.GUIService") {
	ntype = "::ccafeopq::GUIService";
	GUIServicePC *gspc = new GUIServicePC();
	boost::shared_ptr< PortConverter > gspc_ptr(gspc);
	portConversions[portName] = gspc_ptr;
  }

  giz->registerUsesPort(portName, ntype, tm);

  // DO-NOT-DELETE splicer.end(ccaffeine.Services.registerUsesPort)
}

/**
 * Notify the framework that a Port, previously registered by this
 * component but currently not in use, is no longer desired. 
 * Unregistering a port that is currently 
 * in use (i.e. an unreleased getPort() being outstanding) 
 * is an error.
 * @param name The name of a registered Port.
 * @exception CCAException with the following types: UsesPortNotReleased, PortNotDefined.
 */
void
ccaffeine::Services_impl::unregisterUsesPort (
  /*in*/ const ::std::string& portName ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services.unregisterUsesPort)

  giz->unregisterUsesPort(portName);
  // The erase is ok according to c++ even if there is no converter.
  // The fact that the converter is a shared pointer means the PC
  // allocated in getport will be deleted finally.
  portConversions.erase(portName);

  // DO-NOT-DELETE splicer.end(ccaffeine.Services.unregisterUsesPort)
}

/**
 * Exposes a Port from this component to the framework.  
 * This Port is now available for the framework to connect 
 * to other components. 
 * @param inPort An abstract interface (tagged with CCA-ness
 * 	by inheriting from gov.cca.Port) the framework will
 * 	make available to other components.
 * 
 * @param portName string uniquely describing this port.  This string
 * must be unique for this component, over both uses and provides ports.
 * 
 * @param type string describing the type (class) of this port.
 * 
 * @param properties A TypeMap describing optional properties
 * associated with this port. This can be a null pointer, which
 * indicates an empty list of properties.  Properties may be
 * obtained from createTypeMap or any other source.  The properties
 * be copied into the framework, and subsequent changes to the
 * properties object will have no effect on the properties
 * associated with this port.
 * In these properties, all frameworks recognize at least the
 * following keys and values in implementing registerUsesPort:
 * <pre>
 * key:              standard values (in string form)     default
 * "MAX_CONNECTIONS" any nonnegative integer, "unlimited".   1
 * "MIN_CONNECTIONS" any integer > 0.                        0
 * "ABLE_TO_PROXY"   "true", "false"                      "false"
 * </pre>
 * The component is not expected to work if the framework
 * has not satisfied the connection requirements.
 * The framework is allowed to return an error if it
 * is incapable of meeting the connection requirements,
 * e.g. it does not implement multiple uses ports.
 * The caller of addProvidesPort is not obligated to define
 * these properties. If left undefined, the default listed above is
 * assumed.
 * @exception CCAException with the following types: PortAlreadyDefined, OutOfMemory.
 */
void
ccaffeine::Services_impl::addProvidesPort (
  /*in*/ ::gov::cca::Port inPort,
  /*in*/ const ::std::string& portName,
  /*in*/ const ::std::string& type,
  /*in*/ ::gov::cca::TypeMap properties ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services.addProvidesPort)
#ifdef CCAFE_AUDIT
  IO_dn1("addProvidesPort entry");
#endif

  if(inPort._is_nil()) {
    gov::cca::CCAException ex = ::ccaffeine::CCAException::_create();
    ex.SIDL_EXCEPTION_setMessage("ccaffeine::Services_impl::addProvidesPort: Port is nil");
#ifdef CCAFE_AUDIT
    IO_dn2("Services_impl addProvidesPort got nil port named %s", portName.c_str());
#endif
    throw ex;
  }
  if (! isCorrectSIDLType(type)) {
    gov::cca::CCAException ex = ::ccaffeine::CCAException::_create();
    ex.SIDL_EXCEPTION_setMessage(::std::string("ccaffeine::Services_impl::addProvidesPort: ") + 
				 type + ::std::string(" \
is not a valid SIDL type name. A SIDL type name is a period separated list of identifiers. Each identifier must begin with a letter and then may contain any number of letters, digits and underscores. A SIDL type name should match [a-zA-Z][a-zA-Z0-9_]*(\\.[a-zA-Z][a-zA-Z0-9_]*)+"));
#ifdef CCAFE_AUDIT
    IO_dn3("Services_impl addProvidesPort got mis-spelled port type  %s (%s)", type.c_str(), portName.c_str());
#endif
    throw ex;
  }
  if (! inPort.isType(type)) {
    gov::cca::CCAException ex = ::ccaffeine::CCAException::_create();
    ex.SIDL_EXCEPTION_setMessage(::std::string("ccaffeine::Services_impl::addProvidesPort: Port is not of type ") + type);
#ifdef CCAFE_AUDIT
    IO_dn3("Services_impl addProvidesPort got mismatched port type %s (%s)", type.c_str(), portName.c_str());
#endif
    throw ex;
  }
  if (properties._is_nil()) {
	  properties = (*this).createTypeMap();
  }
  properties.putString("cca.portType", type);
  properties.putString("cca.portName", portName);
  properties.putString("ccafe.babel.portType", type );
  ::ccafeopq::TypeMap_shared tm = 
      BabelOpaqueTypeMap_Interface::opaqueWrap(properties);

  ccaffeine::ports::PortTranslator px = 
       ::babel_cast<ccaffeine::ports::PortTranslator> (inPort); // CAST
  if(px._not_nil()) {
    ::ccafeopq::Port * op = 
	static_cast< ::ccafeopq::Port * >(px.getRawPort());
    giz->addProvidesPort(op, portName, type, tm);
    return;
  }

  std::string canonicalType = type;
  ::ccafeopq::Port* op = 0;
  op = ccafe::BabelCCAHelpers::createSpecialProvider(inPort,portName,type,tm,canonicalType);
  if ( op == 0) {
    op = new BabelOpaquePort(inPort);
  }
  giz->addProvidesPort(op, portName, canonicalType, tm);


  // DO-NOT-DELETE splicer.end(ccaffeine.Services.addProvidesPort)
}

/**
 * Returns the complete list of the properties for a Port.  This
 * includes the properties defined when the port was registered
 * (these properties can be modified by the framework), two special
 * properties "cca.portName" and "cca.portType", and any other
 * properties that the framework wishes to disclose to the component.
 * The framework may also choose to provide only the subset of input
 * properties (i.e. from addProvidesPort/registerUsesPort) that it
 * will honor.      
 */
::gov::cca::TypeMap
ccaffeine::Services_impl::getPortProperties (
  /*in*/ const ::std::string& name ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services.getPortProperties)
	
  ::ccafeopq::TypeMap_shared tm = giz->getPortProperties(name);
  if (! tm) {
#ifdef CCAFE_AUDIT
    IO_dn2("Services_impl getPortProperties received null from opq Services. %d", serial);
#endif
    ::gov::cca::TypeMap btm; // nil map
    return btm;
  }
  // if it's a special type, we have to re-type the type string on this
  // copy before exposing it to babel clients.
  std::string ccaPortType = tm->getString("cca.portType","BUG_PORTTYPE_ccaffeine::ports::BuilderService_impl");
  std::string ccafeBabelPortType = tm->getString("ccafe.babel.portType", ccaPortType);
  tm->putString("cca.portType", ccafeBabelPortType);
  ccaffeine::TypeMap btm = ccaffeine::TypeMap_impl::babelWrap(tm);

  return btm;
  
  // DO-NOT-DELETE splicer.end(ccaffeine.Services.getPortProperties)
}

/**
 * Notifies the framework that a previously exposed Port is no longer 
 * available for use. The Port being removed must exist
 * until this call returns, or a CCAException may occur.
 * @param name The name of a provided Port.
 * @exception PortNotDefined. In general, the framework will not dictate 
 * when the component chooses to stop offering services.
 */
void
ccaffeine::Services_impl::removeProvidesPort (
  /*in*/ const ::std::string& portName ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services.removeProvidesPort)

  ::ccafeopq::Port *port = 0;
  char* str = strdup(portName.c_str());
  port = giz->removeProvidesPort(str);
  if (port != 0) { delete port; }
  free(str);

  // DO-NOT-DELETE splicer.end(ccaffeine.Services.removeProvidesPort)
}

/**
 * Get a reference to the component to which this 
 * Services object belongs. 
 */
::gov::cca::ComponentID
ccaffeine::Services_impl::getComponentID () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services.getComponentID)

#ifdef CCAFE_AUDIT
  IO_dn2("Services_impl getComponentID %d", serial);
#endif

  ::ccafeopq::ComponentID_shared oid;
  oid = giz->getComponentID();
  ::gov::cca::ComponentID cid = 
    ccaffeine::ComponentID_impl::babelWrap(oid);
  return cid;

  // DO-NOT-DELETE splicer.end(ccaffeine.Services.getComponentID)
}

/**
 * Obtain a callback for component destruction.
 * @param Callback an object that implements the ComponentRelease
 * interface that will be called when the component is to be destroyed.
 * 
 * Register a callback to be executed when the component is going
 * to be destroyed.  During this callback, the Services object passed
 * through setServices will still be valid, but after all such
 * callbacks are made for a specific component, subsequent usage
 * of the Services object is not allowed/is undefined.
 */
void
ccaffeine::Services_impl::registerForRelease (
  /*in*/ ::gov::cca::ComponentRelease callBack ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services.registerForRelease)
  // insert implementation here
  releaseCallBacks.push_back(callBack);
  // DO-NOT-DELETE splicer.end(ccaffeine.Services.registerForRelease)
}

::std::string
ccaffeine::Services_impl::genUniquePortName (
  /*in*/ const ::std::string& base ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services.genUniquePortName)
  return giz->genUniquePortName(base);
  // DO-NOT-DELETE splicer.end(ccaffeine.Services.genUniquePortName)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.Services._misc)


  //------------------------------------------------------------------
gov::cca::Port
ccaffeine::Services_impl::getBabelPort(::ccafeopq::Port* p) {
#ifdef CCAFE_AUDIT
  IO_dn2("Services_impl getBabelPort %d", serial);
#endif
  if (p == 0) {
	  // dynamic_cast of null is an exception.
#ifdef CCAFE_AUDIT
    IO_dn2("Services_impl getBabelPort called on null %d", serial);
#endif
    return gov::cca::Port(); // this is a nil Port
  }
  BabelOpaquePort* bp = dynamic_cast< BabelOpaquePort * >(p);
  if(bp) {
    return bp->getBabelPort();
  } else {
    if(p != NULL) {
      IO_dn2("ccaffeine::ports::PortTranslator pt = 0x%x", p);
      ccaffeine::ports::PortTranslator pt = 
	ccaffeine::ports::PortTranslator::_create();
      void * vp = static_cast< void * >(p);
      pt.initialize(vp);
      return pt;
    } else {
      return gov::cca::Port(); // this is a nil Port
    }
  }
    
}

  //------------------------------------------------------------------
bool
ccaffeine::Services_impl::isPortTranslator(gov::cca::Port pq) {
  // Must be a better way but I can't find it.
  ccaffeine::ports::PortTranslator p = 
	::babel_cast<ccaffeine::ports::PortTranslator> (pq); // CAST
  if(p._not_nil()) {
    return true;
  } else {
    return false;
  }
}

  //------------------------------------------------------------------

void 
ccafe::BabelCCAHelpers::checkthrow(const char * className, const char * memberName, void * member, const char *funcName)
{
  if (! member ) {
    ::ccaffeine::CCAException ex = ::ccaffeine::CCAException::_create();
    std::string mess = className;
    mess += " ";
    mess += memberName;
    mess += " uninit in ";
    mess += funcName;
    ex.setCCAExceptionType( ::gov::cca::CCAExceptionType_Nonstandard );
    ex.SIDL_EXCEPTION_setMessage(mess);
    ::gov::cca::CCAException gex = 
           ::babel_cast<gov::cca::CCAException> (ex); // CAST
    throw gex;
  }
}

::gov::cca::Port 
ccafe::BabelCCAHelpers::convert( ::ccafeopq::Port * op)
{
#ifdef CCAFE_AUDIT
  IO_dn1("BabelCCAHelpers:: convert");
#endif
  if (op == 0) {
	  // dynamic_cast of null is an exception.
#ifdef CCAFE_AUDIT
    IO_dn1("BabelCCAHelpers:: convert called on null");
#endif
    return gov::cca::Port(); // this is a nil Port
  }

  // case 1
  ccafeopq::ports::ParameterPort * opp = 
    dynamic_cast< ccafeopq::ports::ParameterPort * >(op);
  if (opp != 0) {
    ccaffeine::ports::ParameterPortWrap ppw = 
      ccaffeine::ports::ParameterPortWrap::_create();
    ppw.initialize(opp);
    gov::cca::Port p = ppw;
    return p;
  }

  // case 2
  ccafeopq::ports::BasicParameterPort * obpp = 
    dynamic_cast< ccafeopq::ports::BasicParameterPort * >(op);
  if (obpp != 0) {
    ccaffeine::ports::BasicParameterPortWrap ppw2 = 
      ccaffeine::ports::BasicParameterPortWrap::_create();
    ppw2.initialize(obpp);
    gov::cca::Port p2 = ppw2;
    return p2;
  }

  // case ...


  return gov::cca::Port(); // this is a nil Port
}

ccafeopq::Port *
ccafe::BabelCCAHelpers::createSpecialProvider(::gov::cca::Port inPort,
	const std::string & name, const ::std::string& type,
	ccafeopq::TypeMap_shared portProperties, ::std::string & supportedType)
{
        // assume input is good, as it comes from ccaffeine Services.
        supportedType = type; 
        ccafeopq::Port * wrapper = 0;

#define WHINE_TYPE_MISMATCH(t, ct) else IO_en3("You seem to have classified a non-%s as a %s by mistake.", ct.c_str(), type.c_str())

        // The rules are: check for string matches, then check for cast.
        // Switching based on cast will give wrong result for
        // components that implement multiple ports.

//// GO PORT section //////////////////////////////////////
        if (
                type == "::gov::cca::ports::GoPort" ||
                type == "gov::cca::ports::GoPort"||
                type == "gov.cca.ports.GoPort" ||
                type == "GoPort" ||
                type == "gov.cca.GoPort"
        )
        {
                supportedType = "::ccafeopq::GoPort";
                IO_dn3("Adding an apparent GoPort of type: %s and named: %s",                         type.c_str(), name.c_str());

                gov::cca::ports::GoPort gp = 
                    ::babel_cast<gov::cca::ports::GoPort> (inPort); // CAST
                if (gp._not_nil()) {
                        BabelOpaqueGoPort * cop = new BabelOpaqueGoPort(gp);
                        wrapper = cop;
                        return wrapper;
                }
                WHINE_TYPE_MISMATCH(type, supportedType);
        }

        if (
                type == "::gov::cca::ports::BasicParameterPort" ||
                type == "gov::cca::ports::BasicParameterPort" ||
                type == "gov.cca.ports.BasicParameterPort" ||
                type == "BasicParameterPort"
        )
        {
                supportedType = "::ccafeopq::ports::BasicParameterPort";
                IO_dn3("Adding an apparent BasicParameterPort of type: %s and named: %s",                         type.c_str(), name.c_str());

                gov::cca::ports::BasicParameterPort bpp = 
                    ::babel_cast<gov::cca::ports::BasicParameterPort> (inPort); // CAST
                if (bpp._not_nil()) {
                        BabelOpaqueBasicParameterPort * cop = new BabelOpaqueBasicParameterPort(bpp);
                        wrapper = cop;
                        return wrapper;
                }
                WHINE_TYPE_MISMATCH(type, supportedType);
        }

        if (
                type == "::ccaffeine::ports::ComponentFactory" ||
                type == "ccaffeine::ports::ComponentFactory" ||
                type == "ccaffeine.ports.ComponentFactory" ||
                type == "ComponentFactory"
        )
        {
                supportedType = "::ccafeopq::ComponentFactory";
                IO_dn3("Adding an apparent Factory of type: %s and named: %s",
                         type.c_str(), name.c_str());

                ccaffeine::ports::ComponentFactory cf = 
                    ::babel_cast<ccaffeine::ports::ComponentFactory> (inPort); //CAST
                if (cf._not_nil()) {
                        BabelOpaqueComponentFactory * cop = new BabelOpaqueComponentFactory(cf);
                        wrapper = cop;
                        return wrapper;
                }
                WHINE_TYPE_MISMATCH(type, supportedType);
        }

        return 0;

#undef WHINE_TYPE_MISMATCH

}




// DO-NOT-DELETE splicer.end(ccaffeine.Services._misc)

