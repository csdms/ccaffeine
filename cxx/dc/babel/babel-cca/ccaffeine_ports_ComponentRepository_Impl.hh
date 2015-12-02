// 
// File:          ccaffeine_ports_ComponentRepository_Impl.hh
// Symbol:        ccaffeine.ports.ComponentRepository-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ports.ComponentRepository
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_ports_ComponentRepository_Impl_hh
#define included_ccaffeine_ports_ComponentRepository_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_ports_ComponentRepository_IOR_h
#include "ccaffeine_ports_ComponentRepository_IOR.h"
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
#ifndef included_ccaffeine_ports_ComponentRepository_hh
#include "ccaffeine_ports_ComponentRepository.hh"
#endif
#ifndef included_gov_cca_CCAException_hh
#include "gov_cca_CCAException.hh"
#endif
#ifndef included_gov_cca_ComponentClassDescription_hh
#include "gov_cca_ComponentClassDescription.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ComponentRepository._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ComponentRepository._includes)

namespace ccaffeine { 
  namespace ports { 

    /**
     * Symbol "ccaffeine.ports.ComponentRepository" (version 0.3)
     * 
     * This is a wrapper class. It should not be used directly from
     * component code. It should be access only in the form
     * 'gov.cca.ports.ComponentRepository', not 'ccaffeine.ComponentRepository'.
     */
    class ComponentRepository_impl
    // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ComponentRepository._inherits)
    // Put additional inheritance here...
    // DO-NOT-DELETE splicer.end(ccaffeine.ports.ComponentRepository._inherits)
    {

    private:
      // Pointer back to IOR.
      // Use this to dispatch back through IOR vtable.
      ComponentRepository self;

      // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ComponentRepository._implementation)
      // Put additional implementation details here...
      // DO-NOT-DELETE splicer.end(ccaffeine.ports.ComponentRepository._implementation)

    private:
      // private default constructor (required)
      ComponentRepository_impl() {} 

    public:
      // SIDL constructor (required)
      // Note: alternate Skel constructor doesn't call addref()
      // (fixes bug #275)
      ComponentRepository_impl( struct 
        ccaffeine_ports_ComponentRepository__object * s ) : self(s,
        true) { _ctor(); }

      // user defined construction
      void _ctor();

      // virtual destructor (required)
      virtual ~ComponentRepository_impl() { _dtor(); }

      // user defined destruction
      void _dtor();

    public:


      /**
       *  Collect the currently obtainable class name strings from
       *  factories known to the builder and the from the
       *  already instantiated components.
       *  @return The list of class description, which may be empty, that are
       *   known a priori to contain valid values for the className
       *  argument of createInstance. 
       *  @throws CCAException in the event of error.
       */
      ::sidl::array< ::gov::cca::ComponentClassDescription>
      getAvailableComponentClasses() throw ( 
        ::gov::cca::CCAException
      );
    };  // end class ComponentRepository_impl

  } // end namespace ports
} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ComponentRepository._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ComponentRepository._misc)

#endif
