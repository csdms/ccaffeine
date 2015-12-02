// 
// File:          test_script_babel_ComponentClassDescription_Impl.hh
// Symbol:        test_script_babel.ComponentClassDescription-v0.0
// Symbol Type:   class
// Babel Version: 0.10.0
// Description:   Server-side implementation for test_script_babel.ComponentClassDescription
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// babel-version = 0.10.0
// 

#ifndef included_test_script_babel_ComponentClassDescription_Impl_hh
#define included_test_script_babel_ComponentClassDescription_Impl_hh

#ifndef included_sidl_cxx_hh
#include "sidl_cxx.hh"
#endif
#ifndef included_test_script_babel_ComponentClassDescription_IOR_h
#include "test_script_babel_ComponentClassDescription_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_gov_cca_CCAException_hh
#include "gov_cca_CCAException.hh"
#endif
#ifndef included_sidl_BaseInterface_hh
#include "sidl_BaseInterface.hh"
#endif
#ifndef included_sidl_ClassInfo_hh
#include "sidl_ClassInfo.hh"
#endif
#ifndef included_test_script_babel_ComponentClassDescription_hh
#include "test_script_babel_ComponentClassDescription.hh"
#endif


// DO-NOT-DELETE splicer.begin(test_script_babel.ComponentClassDescription._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(test_script_babel.ComponentClassDescription._includes)

namespace test_script_babel { 

  /**
   * Symbol "test_script_babel.ComponentClassDescription" (version 0.0)
   */
  class ComponentClassDescription_impl
  // DO-NOT-DELETE splicer.begin(test_script_babel.ComponentClassDescription._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(test_script_babel.ComponentClassDescription._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    ComponentClassDescription self;

    // DO-NOT-DELETE splicer.begin(test_script_babel.ComponentClassDescription._implementation)
    std::string cName;
    std::string cAlias;
    // DO-NOT-DELETE splicer.end(test_script_babel.ComponentClassDescription._implementation)

  private:
    // private default constructor (required)
    ComponentClassDescription_impl() {} 

  public:
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    ComponentClassDescription_impl( struct 
      test_script_babel_ComponentClassDescription__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~ComponentClassDescription_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

    // static class initializer
    static void _load();

  public:

    /**
     * user defined non-static method.
     */
    void
    initialize (
      /*in*/ const ::std::string& className,
      /*in*/ const ::std::string& classAlias
    )
    throw () 
    ;


    /**
     *  Returns the class name provided in 
     *   <code>BuilderService.createInstance()</code>
     *   or in
     *   <code>AbstractFramework.getServices()</code>.
     *  <p>
     *  Throws <code>CCAException</code> if <code>ComponentClassDescription</code> is invalid.
     */
    ::std::string
    getComponentClassName() throw ( 
      ::gov::cca::CCAException
    );
  };  // end class ComponentClassDescription_impl

} // end namespace test_script_babel

// DO-NOT-DELETE splicer.begin(test_script_babel.ComponentClassDescription._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(test_script_babel.ComponentClassDescription._misc)

#endif
