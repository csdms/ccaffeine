// 
// File:          TestScriptBabel_PrivateRepository_Impl.hxx
// Symbol:        TestScriptBabel.PrivateRepository-v0.0
// Symbol Type:   class
// Babel Version: 1.0.0
// Description:   Server-side implementation for TestScriptBabel.PrivateRepository
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_TestScriptBabel_PrivateRepository_Impl_hxx
#define included_TestScriptBabel_PrivateRepository_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl_cxx.hxx"
#endif
#ifndef included_TestScriptBabel_PrivateRepository_IOR_h
#include "TestScriptBabel_PrivateRepository_IOR.h"
#endif
#ifndef included_TestScriptBabel_PrivateRepository_hxx
#include "TestScriptBabel_PrivateRepository.hxx"
#endif
#ifndef included_ccaffeine_ports_ComponentFactory_hxx
#include "ccaffeine_ports_ComponentFactory.hxx"
#endif
#ifndef included_gov_cca_CCAException_hxx
#include "gov_cca_CCAException.hxx"
#endif
#ifndef included_gov_cca_Component_hxx
#include "gov_cca_Component.hxx"
#endif
#ifndef included_gov_cca_ComponentClassDescription_hxx
#include "gov_cca_ComponentClassDescription.hxx"
#endif
#ifndef included_gov_cca_ports_ComponentRepository_hxx
#include "gov_cca_ports_ComponentRepository.hxx"
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
#ifndef included_sidl_RuntimeException_hxx
#include "sidl_RuntimeException.hxx"
#endif


// DO-NOT-DELETE splicer.begin(TestScriptBabel.PrivateRepository._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(TestScriptBabel.PrivateRepository._includes)

namespace TestScriptBabel { 

  /**
   * Symbol "TestScriptBabel.PrivateRepository" (version 0.0)
   */
  class PrivateRepository_impl : public virtual 
    ::TestScriptBabel::PrivateRepository 
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.PrivateRepository._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(TestScriptBabel.PrivateRepository._inherits)
  {

  // All data marked protected will be accessable by 
  // descendant Impl classes
  protected:

    bool _wrapped;

    // DO-NOT-DELETE splicer.begin(TestScriptBabel.PrivateRepository._implementation)
    
	std::vector< gov::cca::ComponentClassDescription > descriptions;

    // DO-NOT-DELETE splicer.end(TestScriptBabel.PrivateRepository._implementation)

  public:
    // default constructor, used for data wrapping(required)
    PrivateRepository_impl();
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    PrivateRepository_impl( struct TestScriptBabel_PrivateRepository__object * 
      s ) : StubBase(s,true), _wrapped(false) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~PrivateRepository_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

    // true if this object was created by a user newing the impl
    inline bool _isWrapped() {return _wrapped;}

    // static class initializer
    static void _load();

  public:

    /**
     * user defined non-static method.
     */
    void
    addDescription_impl (
      /* in */const ::std::string& className,
      /* in */const ::std::string& classAlias
    )
    ;


    /**
     *  
     * Collect the currently obtainable class name strings from
     * factories known to the builder and the from the
     * already instantiated components.
     * @return The list of class description, which may be empty, that are
     * known a priori to contain valid values for the className
     * argument of createInstance. 
     * @throws CCAException in the event of error.
     */
    ::sidl::array< ::gov::cca::ComponentClassDescription>
    getAvailableComponentClasses_impl() // throws:
    //     ::gov::cca::CCAException
    //     ::sidl::RuntimeException
    ;

    /**
     *  the component instance returned is nil if the name is unknown
     * to the factory. The component is raw: it has been constructed
     * but not initialized via setServices.
     */
    ::gov::cca::Component
    createComponentInstance_impl (
      /* in */const ::std::string& className
    )
    ;


    /**
     *  reclaim any resources the factory may have associated with
     * the port it is using. This will occur after the
     * normal component shutdown  (ala componentrelease) is finished. 
     */
    void
    destroyComponentInstance_impl (
      /* in */const ::std::string& className,
      /* in */::gov::cca::Component c
    )
    ;

  };  // end class PrivateRepository_impl

} // end namespace TestScriptBabel

// DO-NOT-DELETE splicer.begin(TestScriptBabel.PrivateRepository._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(TestScriptBabel.PrivateRepository._misc)

#endif
