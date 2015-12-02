// 
// File:          TestScriptBabel_ComponentClassDescription_Impl.hxx
// Symbol:        TestScriptBabel.ComponentClassDescription-v0.0
// Symbol Type:   class
// Babel Version: 1.0.0
// Description:   Server-side implementation for TestScriptBabel.ComponentClassDescription
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_TestScriptBabel_ComponentClassDescription_Impl_hxx
#define included_TestScriptBabel_ComponentClassDescription_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl_cxx.hxx"
#endif
#ifndef included_TestScriptBabel_ComponentClassDescription_IOR_h
#include "TestScriptBabel_ComponentClassDescription_IOR.h"
#endif
#ifndef included_TestScriptBabel_ComponentClassDescription_hxx
#include "TestScriptBabel_ComponentClassDescription.hxx"
#endif
#ifndef included_gov_cca_CCAException_hxx
#include "gov_cca_CCAException.hxx"
#endif
#ifndef included_gov_cca_ComponentClassDescription_hxx
#include "gov_cca_ComponentClassDescription.hxx"
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


// DO-NOT-DELETE splicer.begin(TestScriptBabel.ComponentClassDescription._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(TestScriptBabel.ComponentClassDescription._includes)

namespace TestScriptBabel { 

  /**
   * Symbol "TestScriptBabel.ComponentClassDescription" (version 0.0)
   */
  class ComponentClassDescription_impl : public virtual 
    ::TestScriptBabel::ComponentClassDescription 
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.ComponentClassDescription._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(TestScriptBabel.ComponentClassDescription._inherits)
  {

  // All data marked protected will be accessable by 
  // descendant Impl classes
  protected:

    bool _wrapped;

    // DO-NOT-DELETE splicer.begin(TestScriptBabel.ComponentClassDescription._implementation)
    std::string cName;
    std::string cAlias;
    // DO-NOT-DELETE splicer.end(TestScriptBabel.ComponentClassDescription._implementation)

  public:
    // default constructor, used for data wrapping(required)
    ComponentClassDescription_impl();
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    ComponentClassDescription_impl( struct 
      TestScriptBabel_ComponentClassDescription__object * s ) : StubBase(s,
      true), _wrapped(false) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~ComponentClassDescription_impl() { _dtor(); }

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
    initialize_impl (
      /* in */const ::std::string& className,
      /* in */const ::std::string& classAlias
    )
    ;


    /**
     *  
     * Returns the class name provided in 
     * <code>BuilderService.createInstance()</code>
     * or in
     * <code>AbstractFramework.getServices()</code>.
     * <p>
     * Throws <code>CCAException</code> if <code>ComponentClassDescription</code> is invalid.
     */
    ::std::string
    getComponentClassName_impl() // throws:
    //     ::gov::cca::CCAException
    //     ::sidl::RuntimeException
    ;
  };  // end class ComponentClassDescription_impl

} // end namespace TestScriptBabel

// DO-NOT-DELETE splicer.begin(TestScriptBabel.ComponentClassDescription._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(TestScriptBabel.ComponentClassDescription._misc)

#endif
