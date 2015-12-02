// 
// File:          ccaffeine_ports_ConnectionEventServiceWrap_Impl.hxx
// Symbol:        ccaffeine.ports.ConnectionEventServiceWrap-v0.3
// Symbol Type:   class
// Babel Version: 1.4.0 (Revision: 6607 release-1-4-0-branch)
// Description:   Server-side implementation for ccaffeine.ports.ConnectionEventServiceWrap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_ports_ConnectionEventServiceWrap_Impl_hxx
#define included_ccaffeine_ports_ConnectionEventServiceWrap_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl_cxx.hxx"
#endif
#ifndef included_ccaffeine_ports_ConnectionEventServiceWrap_IOR_h
#include "ccaffeine_ports_ConnectionEventServiceWrap_IOR.h"
#endif
#ifndef included_ccaffeine_ports_ConnectionEventServiceWrap_hxx
#include "ccaffeine_ports_ConnectionEventServiceWrap.hxx"
#endif
#ifndef included_gov_cca_ports_ConnectionEventListener_hxx
#include "gov_cca_ports_ConnectionEventListener.hxx"
#endif
#ifndef included_gov_cca_ports_ConnectionEventService_hxx
#include "gov_cca_ports_ConnectionEventService.hxx"
#endif
#ifndef included_gov_cca_ports_EventType_hxx
#include "gov_cca_ports_EventType.hxx"
#endif
#ifndef included_sidl_BaseClass_hxx
#include "sidl_BaseClass.hxx"
#endif
#ifndef included_sidl_BaseInterface_hxx
#include "sidl_BaseInterface.hxx"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "sidl_ClassInfo.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEventServiceWrap._hincludes)

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
#include "dc/export/AllExport.hh"
#include "AllCCA.hh"

// DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEventServiceWrap._hincludes)

namespace ccaffeine { 
  namespace ports { 

    /**
     * Symbol "ccaffeine.ports.ConnectionEventServiceWrap" (version 0.3)
     * 
     *  ccaffeine implementation of cca standard. 
     */
    class ConnectionEventServiceWrap_impl : public virtual 
      ::ccaffeine::ports::ConnectionEventServiceWrap 
    // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEventServiceWrap._inherits)
    // insert code here (optional inheritance here)
    // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEventServiceWrap._inherits)

    {

    // All data marked protected will be accessable by 
    // descendant Impl classes
    protected:

      bool _wrapped;

      // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEventServiceWrap._implementation)
      ::ccafeopq::ports::ConnectionEventService *oces;
      std::map< gov::cca::ports::EventType, ccafeopq::connectionevents::ConnectionEventListener_shared >   listeners;
      int serial;
      static int nextNum() { genSerial++; return genSerial; }
      static int genSerial;
      void checkthrow(const char *funcName);


      // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEventServiceWrap._implementation)

    public:
      // default constructor, used for data wrapping(required)
      ConnectionEventServiceWrap_impl();
      // sidl constructor (required)
      // Note: alternate Skel constructor doesn't call addref()
      // (fixes bug #275)
        ConnectionEventServiceWrap_impl( struct 
          ccaffeine_ports_ConnectionEventServiceWrap__object * ior ) : StubBase(
          ior,true), 
        ::gov::cca::Port((ior==NULL) ? NULL : &((*ior).d_gov_cca_port)),
      ::gov::cca::ports::ConnectionEventService((ior==NULL) ? NULL : &((
        *ior).d_gov_cca_ports_connectioneventservice)) , _wrapped(false) {_ctor(
        );}


      // user defined construction
      void _ctor();

      // virtual destructor (required)
      virtual ~ConnectionEventServiceWrap_impl() { _dtor(); }

      // user defined destruction
      void _dtor();

      // true if this object was created by a user newing the impl
      inline bool _isWrapped() {return _wrapped;}

      // static class initializer
      static void _load();

    public:


      /**
       *  passed in is a void  cast pointer of
       * ccafeopq::ports::ConnectionEventService .
       */
      void
      initialize_impl (
        /* in */void* co_p_ConnEvtSvc_star
      )
      ;


      /**
       *  fetch up a pointer for static casting. if the name
       * supplied is not exactly right, returns null.
       */
      void*
      getWrapped_impl (
        /* in */const ::std::string& className
      )
      ;


      /**
       *  
       * Sign up to be told about connection activity.
       * connectionEventType must be one of the integer 
       * values defined iN ConnectionEvent. 
       */
      void
      addConnectionEventListener_impl (
        /* in */::gov::cca::ports::EventType et,
        /* in */::gov::cca::ports::ConnectionEventListener& cel
      )
      ;


      /**
       *  
       * Ignore future ConnectionEvents of the given type.
       * connectionEventType must be one of the integer values 
       * defined in ConnectionEvent. 
       */
      void
      removeConnectionEventListener_impl (
        /* in */::gov::cca::ports::EventType et,
        /* in */::gov::cca::ports::ConnectionEventListener& cel
      )
      ;

    };  // end class ConnectionEventServiceWrap_impl

  } // end namespace ports
} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEventServiceWrap._hmisc)
// insert code here (miscellaneous things)
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEventServiceWrap._hmisc)

#endif
