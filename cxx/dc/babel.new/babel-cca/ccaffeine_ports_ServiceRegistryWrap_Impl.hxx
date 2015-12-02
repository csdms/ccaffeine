// 
// File:          ccaffeine_ports_ServiceRegistryWrap_Impl.hxx
// Symbol:        ccaffeine.ports.ServiceRegistryWrap-v0.3
// Symbol Type:   class
// Babel Version: 0.8.6
// Description:   Server-side implementation for ccaffeine.ports.ServiceRegistryWrap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// babel-version = 0.8.6
// 

#ifndef included_ccaffeine_ports_ServiceRegistryWrap_Impl_hxx
#define included_ccaffeine_ports_ServiceRegistryWrap_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_ports_ServiceRegistryWrap_IOR_h
#include "ccaffeine_ports_ServiceRegistryWrap_IOR.h"
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
#ifndef included_ccaffeine_ports_ServiceProvider_hxx
#include "ccaffeine_ports_ServiceProvider.hxx"
#endif
#ifndef included_ccaffeine_ports_ServiceRegistryWrap_hxx
#include "ccaffeine_ports_ServiceRegistryWrap.hxx"
#endif
#ifndef included_gov_cca_Port_hxx
#include "gov_cca_Port.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ServiceRegistryWrap._includes)
// Put additional includes or other arbitrary code here...
#include "dc/export/AllExport.hh"
#include "AllCCA.hh"
#include "dc/babel.new/babel-cca/AllBabelCCA.hxx"

// DO-NOT-DELETE splicer.end(ccaffeine.ports.ServiceRegistryWrap._includes)

namespace ccaffeine { 
  namespace ports { 

    /**
     * Symbol "ccaffeine.ports.ServiceRegistryWrap" (version 0.3)
     */
    class ServiceRegistryWrap_impl
    // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ServiceRegistryWrap._inherits)
    // Put additional inheritance here...
    // DO-NOT-DELETE splicer.end(ccaffeine.ports.ServiceRegistryWrap._inherits)
    {

    private:
      // Pointer back to IOR.
      // Use this to dispatch back through IOR vtable.
      ServiceRegistryWrap self;

      // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ServiceRegistryWrap._implementation)
	/** ports registered singleton, keyed by neo type. */
	std::map< std::string, ccafeopq::Port * > opqSingletons;

	/** names registered with opq layer, keyed by neo type. */
	std::map< std::string, std::string > opqSingletonCanonical;


	::ccafeopq::ServiceRegistry *sr;
	::ccafeopq::ComponentID_shared cid;
	int serial;
	static int nextNum() { genSerial++; return genSerial; }
	static int genSerial;
	void checkthrow(const char *funcName);
      
      // DO-NOT-DELETE splicer.end(ccaffeine.ports.ServiceRegistryWrap._implementation)

    private:
      // private default constructor (required)
      ServiceRegistryWrap_impl() {} 

    public:
      // SIDL constructor (required)
      // Note: alternate Skel constructor doesn't call addref()
      // (fixes bug #275)
      ServiceRegistryWrap_impl( struct 
        ccaffeine_ports_ServiceRegistryWrap__object * s ) : self(s,
        true) { _ctor(); }

      // user defined construction
      void _ctor();

      // virtual destructor (required)
      virtual ~ServiceRegistryWrap_impl() { _dtor(); }

      // user defined destruction
      void _dtor();

    public:

      /**
       * user defined non-static method.
       */
      void
      initialize (
        /*in*/ void* ccafeopq_ServiceRegistry_star,
        /*in*/ void* opaque_ComponentID_addr
      )
      throw () 
      ;


      /**
       * fetch up a pointer for static casting. if the name
       * supplied is not exactly right, returns null.
       */
      void*
      getWrapped (
        /*in*/ const ::std::string& className
      )
      throw () 
      ;


      /**
       * return opq cidshared. 
       */
      void
      getProviderID (
        /*in*/ void* opaque_ComponentID_addr
      )
      throw () 
      ;


      /**
       * Add a ServiceProvider that can be asked to produce service Port's
       * for other components to use subsequently.
       * True means success. False means that for some reason, the
       * provider isn't going to function. Possibly another server is doing
       * the job.
       */
      bool
      addService (
        /*in*/ const ::std::string& serviceType,
        /*in*/ ::ccaffeine::ports::ServiceProvider portProvider
      )
      throw () 
      ;


      /**
       * Add a "reusable" service gov.cca.Port for other components to use 
       * subsequently.
       */
      bool
      addSingletonService (
        /*in*/ const ::std::string& serviceType,
        /*in*/ ::gov::cca::Port server
      )
      throw () 
      ;


      /**
       * Inform the framework that this service Port is no longer to
       * be used, subsequent to this call. This is likely to
       * cause an exception unless all the ports obtained from the
       * previously added services have been released and disconnected.
       */
      void
      removeService (
        /*in*/ const ::std::string& serviceType
      )
      throw () 
      ;

    };  // end class ServiceRegistryWrap_impl

  } // end namespace ports
} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ServiceRegistryWrap._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ServiceRegistryWrap._misc)

#endif
