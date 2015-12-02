// 
// File:          test_script_babel_PrivateRepository_Impl.hh
// Symbol:        test_script_babel.PrivateRepository-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for test_script_babel.PrivateRepository
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_test_script_babel_PrivateRepository_Impl_hh
#define included_test_script_babel_PrivateRepository_Impl_hh

#ifndef included_sidl_cxx_hh
#include "sidl_cxx.hh"
#endif
#ifndef included_test_script_babel_PrivateRepository_IOR_h
#include "test_script_babel_PrivateRepository_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_gov_cca_CCAException_hh
#include "gov_cca_CCAException.hh"
#endif
#ifndef included_gov_cca_Component_hh
#include "gov_cca_Component.hh"
#endif
#ifndef included_gov_cca_ComponentClassDescription_hh
#include "gov_cca_ComponentClassDescription.hh"
#endif
#ifndef included_sidl_BaseInterface_hh
#include "sidl_BaseInterface.hh"
#endif
#ifndef included_sidl_ClassInfo_hh
#include "sidl_ClassInfo.hh"
#endif
#ifndef included_sidl_RuntimeException_hh
#include "sidl_RuntimeException.hh"
#endif
#ifndef included_test_script_babel_PrivateRepository_hh
#include "test_script_babel_PrivateRepository.hh"
#endif


// DO-NOT-DELETE splicer.begin(test_script_babel.PrivateRepository._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(test_script_babel.PrivateRepository._includes)

namespace test_script_babel { 

  /**
   * Symbol "test_script_babel.PrivateRepository" (version 0.0)
   */
  class PrivateRepository_impl
  // DO-NOT-DELETE splicer.begin(test_script_babel.PrivateRepository._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(test_script_babel.PrivateRepository._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    PrivateRepository self;

    // DO-NOT-DELETE splicer.begin(test_script_babel.PrivateRepository._implementation)
    
	std::vector< gov::cca::ComponentClassDescription > descriptions;

    // DO-NOT-DELETE splicer.end(test_script_babel.PrivateRepository._implementation)

  private:
    // private default constructor (required)
    PrivateRepository_impl() 
    {} 

  public:
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    PrivateRepository_impl( struct test_script_babel_PrivateRepository__object 
      * s ) : self(s,true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~PrivateRepository_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

    // static class initializer
    static void _load();

  public:

    /**
     * user defined non-static method.
     */
    void
    addDescription (
      /* in */ const ::std::string& className,
      /* in */ const ::std::string& classAlias
    )
    ;


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
      ::gov::cca::CCAException, 
      ::sidl::RuntimeException
    );

    /**
     * the component instance returned is nil if the name is unknown
     * to the factory. The component is raw: it has been constructed
     * but not initialized via setServices.
     */
    ::gov::cca::Component
    createComponentInstance (
      /* in */ const ::std::string& className
    )
    ;


    /**
     * reclaim any resources the factory may have associated with
     * the port it is using. This will occur after the
     * normal component shutdown  (ala componentrelease) is finished. 
     */
    void
    destroyComponentInstance (
      /* in */ const ::std::string& className,
      /* in */ ::gov::cca::Component c
    )
    ;

  };  // end class PrivateRepository_impl

} // end namespace test_script_babel

// DO-NOT-DELETE splicer.begin(test_script_babel.PrivateRepository._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(test_script_babel.PrivateRepository._misc)

#endif
