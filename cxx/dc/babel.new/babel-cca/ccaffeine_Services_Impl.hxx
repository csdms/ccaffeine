// 
// File:          ccaffeine_Services_Impl.hxx
// Symbol:        ccaffeine.Services-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.Services
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_Services_Impl_hxx
#define included_ccaffeine_Services_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl.hxx"
#endif
#ifndef included_ccaffeine_Services_IOR_h
#include "ccaffeine_Services_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_sidl_BaseInterface_hxx
#include "sidl_BaseInterface.hxx"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "sidl_ClassInfo.hxx"
#endif
#ifndef included_ccaffeine_Services_hxx
#include "ccaffeine_Services.hxx"
#endif
#ifndef included_gov_cca_CCAException_hxx
#include "gov_cca_CCAException.hxx"
#endif
#ifndef included_gov_cca_ComponentID_hxx
#include "gov_cca_ComponentID.hxx"
#endif
#ifndef included_gov_cca_ComponentRelease_hxx
#include "gov_cca_ComponentRelease.hxx"
#endif
#ifndef included_gov_cca_Port_hxx
#include "gov_cca_Port.hxx"
#endif
#ifndef included_gov_cca_TypeMap_hxx
#include "gov_cca_TypeMap.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.Services._includes)
#include <map>
#include <string>
#include <vector>
#include "gov_cca_ports_BasicParameterPort.hxx"
#include "ccaffeine_TypeMap.hxx"
#include "ccaffeine_ComponentID.hxx"
#include "ccaffeine_ports_ConnectionEvent.hxx"
#include "dc/export/AllExport.hh"
#include "dc/babel.new/ccafe-bind/AllCcafeBind.hh"
#include "dc/babel.new/babel-cca/PortConverter.hxx"
#include "dc/babel.new/babel-cca/BuilderServicePC.hxx"
#include "dc/babel.new/babel-cca/ParameterPortFactoryPC.hxx"
#include "dc/babel.new/babel-cca/ParameterPortPC.hxx"
#include "dc/babel.new/babel-cca/ServiceRegistryPC.hxx"
#include "dc/babel.new/babel-cca/GUIServicePC.hxx"
#include "dc/babel.new/babel-cca/GoPortPC.hxx"
//#include <ports/AllEvents.h> // hacked cca-spec-bbel ports


// DO-NOT-DELETE splicer.end(ccaffeine.Services._includes)

namespace ccaffeine { 

  /**
   * Symbol "ccaffeine.Services" (version 0.3)
   * 
   * This is a wrapper class. It cannot be successfully
   * constructed directly from component or client code.
   * Only the ccaffeine framework
   * internals know how to initialize this object.
   */
  class Services_impl
  // DO-NOT-DELETE splicer.begin(ccaffeine.Services._inherits)
  // DO-NOT-DELETE splicer.end(ccaffeine.Services._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    Services self;

    // DO-NOT-DELETE splicer.begin(ccaffeine.Services._implementation)

    /* gize will NOT be deleted when this wrapper is destroyed. */
    ccafeopq::Services * giz;
    int serial;

    static int nextNum() { genSerial++; return genSerial; }
    static int genSerial;

    std::map< std::string, PortConverter_ptr > portConversions;

    gov::cca::Port getBabelPort(ccafeopq::Port* p);

    bool
    isPortTranslator(gov::cca::Port p);

    std::vector< ::gov::cca::ComponentRelease > releaseCallBacks;

    // DO-NOT-DELETE splicer.end(ccaffeine.Services._implementation)

  private:
    // private default constructor (required)
    Services_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    Services_impl( struct ccaffeine_Services__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~Services_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:

    /**
     * user defined non-static method.
     */
    void
    initialize (
      /*in*/ void* g
    )
    throw () 
    ;

    /**
     * user defined non-static method.
     */
    void
    doReleaseCallbacks() throw () 
    ;

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
    getPort (
      /*in*/ const ::std::string& portName
    )
    throw ( 
      ::gov::cca::CCAException
    );


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
    getPortNonblocking (
      /*in*/ const ::std::string& portName
    )
    throw ( 
      ::gov::cca::CCAException
    );


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
    releasePort (
      /*in*/ const ::std::string& portName
    )
    throw ( 
      ::gov::cca::CCAException
    );


    /**
     * Creates a TypeMap, potentially to be used in subsequent
     * calls to describe a Port.  Initially, this map is empty.
     */
    ::gov::cca::TypeMap
    createTypeMap() throw ( 
      ::gov::cca::CCAException
    );

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
    registerUsesPort (
      /*in*/ const ::std::string& portName,
      /*in*/ const ::std::string& type,
      /*in*/ ::gov::cca::TypeMap properties
    )
    throw ( 
      ::gov::cca::CCAException
    );


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
    unregisterUsesPort (
      /*in*/ const ::std::string& portName
    )
    throw ( 
      ::gov::cca::CCAException
    );


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
    addProvidesPort (
      /*in*/ ::gov::cca::Port inPort,
      /*in*/ const ::std::string& portName,
      /*in*/ const ::std::string& type,
      /*in*/ ::gov::cca::TypeMap properties
    )
    throw ( 
      ::gov::cca::CCAException
    );


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
    getPortProperties (
      /*in*/ const ::std::string& name
    )
    throw () 
    ;


    /**
     * Notifies the framework that a previously exposed Port is no longer 
     * available for use. The Port being removed must exist
     * until this call returns, or a CCAException may occur.
     * @param name The name of a provided Port.
     * @exception PortNotDefined. In general, the framework will not dictate 
     * when the component chooses to stop offering services.
     */
    void
    removeProvidesPort (
      /*in*/ const ::std::string& portName
    )
    throw ( 
      ::gov::cca::CCAException
    );


    /**
     * Get a reference to the component to which this 
     * Services object belongs. 
     */
    ::gov::cca::ComponentID
    getComponentID() throw () 
    ;

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
    registerForRelease (
      /*in*/ ::gov::cca::ComponentRelease callBack
    )
    throw ( 
      ::gov::cca::CCAException
    );

    /* fetch up a pointer for static casting. if the name
     * supplied is not exactly right, returns null.
     */
    void*
    getWrapped (
      /*in*/ const ::std::string& className
    )
    throw () 
    ;


    /**
     * get port name 
     */
    ::std::string
    genUniquePortName (
      /*in*/ const ::std::string& base
    )
    throw () 
    ;


};  // end class Services_impl

} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.Services._misc)
// DO-NOT-DELETE splicer.end(ccaffeine.Services._misc)

#endif
