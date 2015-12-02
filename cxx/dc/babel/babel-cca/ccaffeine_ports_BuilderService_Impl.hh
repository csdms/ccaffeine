// 
// File:          ccaffeine_ports_BuilderService_Impl.hh
// Symbol:        ccaffeine.ports.BuilderService-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ports.BuilderService
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_ports_BuilderService_Impl_hh
#define included_ccaffeine_ports_BuilderService_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_ports_BuilderService_IOR_h
#include "ccaffeine_ports_BuilderService_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_SIDL_BaseInterface_hh
#include "SIDL_BaseInterface.hh"
#endif
#ifndef included_SIDL_ClassInfo_hh
#include "SIDL_ClassInfo.hh"
#endif
#ifndef included_ccaffeine_ports_BuilderService_hh
#include "ccaffeine_ports_BuilderService.hh"
#endif
#ifndef included_gov_cca_CCAException_hh
#include "gov_cca_CCAException.hh"
#endif
#ifndef included_gov_cca_ComponentID_hh
#include "gov_cca_ComponentID.hh"
#endif
#ifndef included_gov_cca_ConnectionID_hh
#include "gov_cca_ConnectionID.hh"
#endif
#ifndef included_gov_cca_TypeMap_hh
#include "gov_cca_TypeMap.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService._includes)
// Put additional includes or other arbitrary code here...
#include <map>
#include "dc/export/AllExport.hh"
#include "AllCCA.hh"
#include "dc/babel/babel-cca/AllBabelCCA.hh"
#include "dc/babel/ccafe-bind/AllCcafeBind.hh"
#include "util/IO.h"
// DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService._includes)

namespace ccaffeine { 
  namespace ports { 

    /**
     * Symbol "ccaffeine.ports.BuilderService" (version 0.3)
     * 
     * This is a wrapper class. It cannot be successfully
     * constructed directly from component or client code.
     * Only the ccaffeine framework internals know how to initialize 
     * this object. If you want to use one, you should get
     * it as a port only in the form 'gov.cca.ports.BuilderService'.
     */
    class BuilderService_impl
    // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService._inherits)
    // Put additional inheritance here...
    // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService._inherits)
    {

    private:
      // Pointer back to IOR.
      // Use this to dispatch back through IOR vtable.
      BuilderService self;

      // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService._implementation)
      /** cbs will not be deleted when the babel object is destroyed.
       * borrowed from framework. */
      ::ccafeopq::BuilderService *cbs;
      int serial;
      static int nextNum() { genSerial++; return genSerial; }
      static int genSerial;
      void checkthrow(const char *funcName);
      ::ccafeopq::ComponentID_shared findOID( gov::cca::ComponentID bid);

      ::ccafeopq::ConnectionID_shared findOConnID( gov::cca::ConnectionID bconn);

      std::vector< ::ccafeopq::ConnectionID_shared >findOConnIDs( gov::cca::ConnectionID bconn);


      // Put additional implementation details here...
      // DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService._implementation)

    private:
      // private default constructor (required)
      BuilderService_impl() {} 

    public:
      // SIDL constructor (required)
      // Note: alternate Skel constructor doesn't call addref()
      // (fixes bug #275)
      BuilderService_impl( struct ccaffeine_ports_BuilderService__object * s ) 
        : self(s,true) { _ctor(); }

      // user defined construction
      void _ctor();

      // virtual destructor (required)
      virtual ~BuilderService_impl() { _dtor(); }

      // user defined destruction
      void _dtor();

    public:


      /**
       * @param ccafeopq_BuilderService_port a
       * ::ccafeopq::BuilderService * cast to void *.
       * The pointer will be deleted when the babel wrapper
       * is destroyed.
       */
      void
      initialize (
        /*in*/ void* ccafeopq_BuilderService_port
      )
      throw () 
      ;


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
      createInstance (
        /*in*/ const ::std::string& instanceName,
        /*in*/ const ::std::string& className,
        /*in*/ ::gov::cca::TypeMap properties
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       *  Get component list.
       *  @return a ComponentID for each component currently created.
       */
      ::sidl::array< ::gov::cca::ComponentID>
      getComponentIDs() throw ( 
        ::gov::cca::CCAException
      );

      /**
       *  Get property map for component.
       *  @return the public properties associated with the component referred to by
       *  ComponentID. 
       *  @throws a CCAException if the ComponentID is invalid.
       */
      ::gov::cca::TypeMap
      getComponentProperties (
        /*in*/ ::gov::cca::ComponentID cid
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * 	Causes the framework implementation to associate the given properties 
       * 	with the component designated by cid. 
       * 	@throws CCAException if cid is invalid or if there is an attempted
       * 	change to a property locked by the framework implementation.
       */
      void
      setComponentProperties (
        /*in*/ ::gov::cca::ComponentID cid,
        /*in*/ ::gov::cca::TypeMap map
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Get component id from stringified reference.
       *    @return a ComponentID from the string produced by 
       * 	ComponentID.getSerialization(). 
       *    @throws CCAException if the string does not represent the appropriate 
       * 	 serialization of a ComponentID for the underlying framework.
       */
      ::gov::cca::ComponentID
      getDeserialization (
        /*in*/ const ::std::string& s
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Get id from name by which it was created.
       *  @return a ComponentID from the instance name of the component
       *  produced by ComponentID.getInstanceName().
       *  @throws CCAException if there is no component matching the 
       *  given componentInstanceName.
       */
      ::gov::cca::ComponentID
      getComponentID (
        /*in*/ const ::std::string& componentInstanceName
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       *  Eliminate the Component instance, from the scope of the framework.
       *  @param toDie the component to be removed.
       *  @param timeout the allowable wait; 0 means up to the framework.
       *  @throws CCAException if toDie refers to an invalid component, or
       *  if the operation takes longer than timeout seconds.
       */
      void
      destroyInstance (
        /*in*/ ::gov::cca::ComponentID toDie,
        /*in*/ float timeout
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       *  Get the names of Port instances provided by the identified component.
       *  @param cid the component.
       *  @throws CCAException if cid refers to an invalid component.
       */
      ::sidl::array< ::std::string>
      getProvidedPortNames (
        /*in*/ ::gov::cca::ComponentID cid
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       *  Get the names of Port instances used by the identified component.
       *  @param cid the component.
       *  @throws CCAException if cid refers to an invalid component. 
       */
      ::sidl::array< ::std::string>
      getUsedPortNames (
        /*in*/ ::gov::cca::ComponentID cid
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       *  Fetch map of Port properties exposed by the framework.
       *  @return the public properties pertaining to the Port instance 
       *    portname on the component referred to by cid. 
       *  @throws CCAException when any one of the following conditions occur:<ul>
       *    <li>portname is not a registered Port on the component indicated by cid,
       *    <li>cid refers to an invalid component. </ul>
       */
      ::gov::cca::TypeMap
      getPortProperties (
        /*in*/ ::gov::cca::ComponentID cid,
        /*in*/ const ::std::string& portName
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       *  Associates the properties given in map with the Port indicated by 
       *  portname. The component must have a Port known by portname.
       *  @throws CCAException if either cid or portname are
       * 	invalid, or if this a changed property is locked by 
       * 	 the underlying framework or component.
       */
      void
      setPortProperties (
        /*in*/ ::gov::cca::ComponentID cid,
        /*in*/ const ::std::string& portName,
        /*in*/ ::gov::cca::TypeMap map
      )
      throw ( 
        ::gov::cca::CCAException
      );


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
      connect (
        /*in*/ ::gov::cca::ComponentID user,
        /*in*/ const ::std::string& usingPortName,
        /*in*/ ::gov::cca::ComponentID provider,
        /*in*/ const ::std::string& providingPortName
      )
      throw ( 
        ::gov::cca::CCAException
      );


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
      getConnectionIDs (
        /*in*/ ::sidl::array< ::gov::cca::ComponentID> componentList
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       *   Fetch property map of a connection.
       *   @returns the properties for the given connection.
       *   @throws CCAException if connID is invalid.
       */
      ::gov::cca::TypeMap
      getConnectionProperties (
        /*in*/ ::gov::cca::ConnectionID connID
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Associates the properties with the connection.
       *   @param map the source of the properties.
       *   @param connID connection to receive property values.
       *   @throws CCAException if connID is invalid, or if this changes 
       * 	 a property locked by the underlying framework.
       */
      void
      setConnectionProperties (
        /*in*/ ::gov::cca::ConnectionID connID,
        /*in*/ ::gov::cca::TypeMap map
      )
      throw ( 
        ::gov::cca::CCAException
      );


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
      disconnect (
        /*in*/ ::gov::cca::ConnectionID connID,
        /*in*/ float timeout
      )
      throw ( 
        ::gov::cca::CCAException
      );


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
      disconnectAll (
        /*in*/ ::gov::cca::ComponentID id1,
        /*in*/ ::gov::cca::ComponentID id2,
        /*in*/ float timeout
      )
      throw ( 
        ::gov::cca::CCAException
      );

    };  // end class BuilderService_impl

  } // end namespace ports
} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.BuilderService._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.ports.BuilderService._misc)

#endif
