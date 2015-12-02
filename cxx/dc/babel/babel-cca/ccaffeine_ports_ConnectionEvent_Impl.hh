// 
// File:          ccaffeine_ports_ConnectionEvent_Impl.hh
// Symbol:        ccaffeine.ports.ConnectionEvent-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ports.ConnectionEvent
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_ports_ConnectionEvent_Impl_hh
#define included_ccaffeine_ports_ConnectionEvent_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_ports_ConnectionEvent_IOR_h
#include "ccaffeine_ports_ConnectionEvent_IOR.h"
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
#ifndef included_ccaffeine_ports_ConnectionEvent_hh
#include "ccaffeine_ports_ConnectionEvent.hh"
#endif
#ifndef included_gov_cca_TypeMap_hh
#include "gov_cca_TypeMap.hh"
#endif
#ifndef included_gov_cca_ports_EventType_hh
#include "gov_cca_ports_EventType.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEvent._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEvent._includes)

namespace ccaffeine { 
  namespace ports { 

    /**
     * Symbol "ccaffeine.ports.ConnectionEvent" (version 0.3)
     * 
     * This is a wrapper class. It cannot be successfully
     * constructed directly from component or client code.
     * Only the ccaffeine framework
     * internals know how to initialize this object.
     */
    class ConnectionEvent_impl
    // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEvent._inherits)
    // Put additional inheritance here...
    // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEvent._inherits)
    {

    private:
      // Pointer back to IOR.
      // Use this to dispatch back through IOR vtable.
      ConnectionEvent self;

      // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEvent._implementation)
      gov::cca::ports::EventType e;
      gov::cca::TypeMap portInfo;
      int serial;
      static int nextNum() { genSerial++; return genSerial; }
      static int genSerial;

      // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEvent._implementation)

    private:
      // private default constructor (required)
      ConnectionEvent_impl() {} 

    public:
      // SIDL constructor (required)
      // Note: alternate Skel constructor doesn't call addref()
      // (fixes bug #275)
      ConnectionEvent_impl( struct ccaffeine_ports_ConnectionEvent__object * s 
        ) : self(s,true) { _ctor(); }

      // user defined construction
      void _ctor();

      // virtual destructor (required)
      virtual ~ConnectionEvent_impl() { _dtor(); }

      // user defined destruction
      void _dtor();

    public:

      /**
       * user defined non-static method.
       */
      void
      initialize (
        /*in*/ ::gov::cca::ports::EventType eventType,
        /*in*/ ::gov::cca::TypeMap portProperties
      )
      throw () 
      ;


      /**
       * <p>Returns the integer from those enumerated that describes the event.</p>
       * 
       * <p>
       * The semantics are noted before
       * each member of the enum/static constant. We can add in different
       * types of connect/disconnect as multiports and
       * explicit local/global/sync/async semantics are agreed to in the future.
       * At present we assume that:
       * <ul>
       * <li> All instances in a component cohort (often thought of as a single
       *   "parallel component") receive all the events
       *   and in the same order, but not necessarily globally synchronously.
       * 
       * <li> For disconnections, within a process the events are delivered first
       *   to the using component then (if necessary) to the providing
       *   component.
       * 
       * <li> For connections, within a process the events are delivered first
       *   to the providing component then (if necessary) to the using
       *   component.
       * </ul>
       * </p>
       * 
       * <p>
       * Clearly some of the assumptions above may not suit a component
       * instance in which multiple execution threads act on a
       * single instance of the <code>cca.Services</code> object (SMP). The Services
       * specification is ambiguous as to whether such a component is even
       * allowed.
       * </p>
       * <p>
       * When this is clarified, additional members of the enum may arise,
       * in which case the assumptions here apply only to
       * <code>ConnectPending</code>, <code>Connected</code>, <code>DisconnectPending</code>, 
       * <code>Disconnected</code> types.
       */
      ::gov::cca::ports::EventType
      getEventType() throw () 
      ;

      /**
       * Get Properties of the affected Port.
       * Among the standard properties are the name and type info.
       */
      ::gov::cca::TypeMap
      getPortInfo() throw () 
      ;
    };  // end class ConnectionEvent_impl

  } // end namespace ports
} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEvent._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEvent._misc)

#endif
