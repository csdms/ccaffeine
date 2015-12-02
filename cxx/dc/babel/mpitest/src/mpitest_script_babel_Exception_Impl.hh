// 
// File:          mpitest_script_babel_Exception_Impl.hh
// Symbol:        mpitest_script_babel.Exception-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for mpitest_script_babel.Exception
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_mpitest_script_babel_Exception_Impl_hh
#define included_mpitest_script_babel_Exception_Impl_hh

#ifndef included_sidl_cxx_hh
#include "sidl_cxx.hh"
#endif
#ifndef included_mpitest_script_babel_Exception_IOR_h
#include "mpitest_script_babel_Exception_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_gov_cca_CCAExceptionType_hh
#include "gov_cca_CCAExceptionType.hh"
#endif
#ifndef included_mpitest_script_babel_Exception_hh
#include "mpitest_script_babel_Exception.hh"
#endif
#ifndef included_sidl_BaseInterface_hh
#include "sidl_BaseInterface.hh"
#endif
#ifndef included_sidl_ClassInfo_hh
#include "sidl_ClassInfo.hh"
#endif


// DO-NOT-DELETE splicer.begin(mpitest_script_babel.Exception._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(mpitest_script_babel.Exception._includes)

namespace mpitest_script_babel { 

  /**
   * Symbol "mpitest_script_babel.Exception" (version 0.0)
   */
  class Exception_impl
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.Exception._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.Exception._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    Exception self;

    // DO-NOT-DELETE splicer.begin(mpitest_script_babel.Exception._implementation)
    // Put additional implementation details here...
    ::gov::cca::CCAExceptionType myType;
    // DO-NOT-DELETE splicer.end(mpitest_script_babel.Exception._implementation)

  private:
    // private default constructor (required)
    Exception_impl() 
    {} 

  public:
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    Exception_impl( struct mpitest_script_babel_Exception__object * s ) : 
      self(s,true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~Exception_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

    // static class initializer
    static void _load();

  public:

    /**
     * user defined non-static method.
     */
    void
    setType (
      /* in */ ::gov::cca::CCAExceptionType t
    )
    throw () 
    ;

    /**
     * user defined non-static method.
     */
    ::gov::cca::CCAExceptionType
    getCCAExceptionType() throw () 
    ;
  };  // end class Exception_impl

} // end namespace mpitest_script_babel

// DO-NOT-DELETE splicer.begin(mpitest_script_babel.Exception._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(mpitest_script_babel.Exception._misc)

#endif
