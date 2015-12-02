// 
// File:          ccaffeine_ConnectionEventService_Impl.hxx
// Symbol:        ccaffeine.ConnectionEventService-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ConnectionEventService
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_ConnectionEventService_Impl_hxx
#define included_ccaffeine_ConnectionEventService_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_ConnectionEventService_IOR_h
#include "ccaffeine_ConnectionEventService_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_sidl_BaseInterface_hxx
#include "SIDL_BaseInterface.hh"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "SIDL_ClassInfo.hh"
#endif
#ifndef included_ccaffeine_ConnectionEventService_hxx
#include "ccaffeine_ConnectionEventService.hxx"
#endif
#ifndef included_gov_cca_ports_ConnectionEventListener_hxx
#include "gov_cca_ports_ConnectionEventListener.hxx"
#endif
#ifndef included_gov_cca_ports_EventType_hxx
#include "gov_cca_ports_EventType.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionEventService._includes)

#include <map>
#include <boost/shared_ptr.hpp>
#ifdef HAVE_CLASSIC
#include <cca.h>
#include <ports/AllEvents.h>
#endif // HAVE_CLASSIC
#include "ccaffeine_TypeMap.hxx"
#include "ccaffeine_ComponentID.hxx"
#include "ccaffeine_ports_ConnectionEvent.hxx"
#include "dc/framework/dc_fwkStar.h"
//#include "dc/framework/bbl_fwkStar.h"
#include "dc/export/AllExport.hh"
#include "AllCCA.hh"

// DO-NOT-DELETE splicer.end(ccaffeine.ConnectionEventService._includes)

namespace ccaffeine { 

  /**
   * Symbol "ccaffeine.ConnectionEventService" (version 0.3)
   * 
   * This is a wrapper only the ccaffeine framework
   * can successfully create. 
   */
  class ConnectionEventService_impl
  // DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionEventService._inherits)
  // DO-NOT-DELETE splicer.end(ccaffeine.ConnectionEventService._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    ConnectionEventService self;

    // DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionEventService._implementation)

    Gizzard* giz;
    std::map< gov::cca::ports::EventType, ccafeopq::connectionevents::ConnectionEventListener_shared >   listeners;

    // Put additional implementation details here...
    // DO-NOT-DELETE splicer.end(ccaffeine.ConnectionEventService._implementation)

  private:
    // private default constructor (required)
    ConnectionEventService_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    ConnectionEventService_impl( struct 
      ccaffeine_ConnectionEventService__object * s ) : self(s,true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~ConnectionEventService_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:

    /**
     * user defined non-static method.
     */
    void
    initialize (
      /*in*/ void* gizzard
    )
    throw () 
    ;


    /**
     * Sign up to be told about connection activity.
     * connectionEventType must be one of the integer 
     * values defined iN ConnectionEvent. 
     */
    void
    addConnectionEventListener (
      /*in*/ ::gov::cca::ports::EventType et,
      /*in*/ ::gov::cca::ports::ConnectionEventListener cel
    )
    throw () 
    ;


    /**
     * Ignore future ConnectionEvents of the given type.
     * connectionEventType must be one of the integer values 
     * defined in ConnectionEvent. 
     */
    void
    removeConnectionEventListener (
      /*in*/ ::gov::cca::ports::EventType et,
      /*in*/ ::gov::cca::ports::ConnectionEventListener cel
    )
    throw () 
    ;

  };  // end class ConnectionEventService_impl

} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionEventService._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.ConnectionEventService._misc)

#endif
