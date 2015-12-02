// 
// File:          TestScriptBabel_Exception_Impl.hxx
// Symbol:        TestScriptBabel.Exception-v0.0
// Symbol Type:   class
// Babel Version: 1.0.0
// Description:   Server-side implementation for TestScriptBabel.Exception
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_TestScriptBabel_Exception_Impl_hxx
#define included_TestScriptBabel_Exception_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl_cxx.hxx"
#endif
#ifndef included_TestScriptBabel_Exception_IOR_h
#include "TestScriptBabel_Exception_IOR.h"
#endif
#ifndef included_TestScriptBabel_Exception_hxx
#include "TestScriptBabel_Exception.hxx"
#endif
#ifndef included_gov_cca_CCAException_hxx
#include "gov_cca_CCAException.hxx"
#endif
#ifndef included_gov_cca_CCAExceptionType_hxx
#include "gov_cca_CCAExceptionType.hxx"
#endif
#ifndef included_sidl_BaseInterface_hxx
#include "sidl_BaseInterface.hxx"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "sidl_ClassInfo.hxx"
#endif
#ifndef included_sidl_SIDLException_hxx
#include "sidl_SIDLException.hxx"
#endif
#ifndef included_sidl_io_Deserializer_hxx
#include "sidl_io_Deserializer.hxx"
#endif
#ifndef included_sidl_io_Serializer_hxx
#include "sidl_io_Serializer.hxx"
#endif


// DO-NOT-DELETE splicer.begin(TestScriptBabel.Exception._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(TestScriptBabel.Exception._includes)

namespace TestScriptBabel { 

  /**
   * Symbol "TestScriptBabel.Exception" (version 0.0)
   */
  class Exception_impl : public virtual ::TestScriptBabel::Exception 
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.Exception._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(TestScriptBabel.Exception._inherits)
  {

  // All data marked protected will be accessable by 
  // descendant Impl classes
  protected:

    bool _wrapped;

    // DO-NOT-DELETE splicer.begin(TestScriptBabel.Exception._implementation)
    // Put additional implementation details here...
    ::gov::cca::CCAExceptionType myType;
    // DO-NOT-DELETE splicer.end(TestScriptBabel.Exception._implementation)

  public:
    // default constructor, used for data wrapping(required)
    Exception_impl();
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    Exception_impl( struct TestScriptBabel_Exception__object * s ) : StubBase(s,
      true), _wrapped(false) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~Exception_impl() { _dtor(); }

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
    setType_impl (
      /* in */::gov::cca::CCAExceptionType t
    )
    ;

    /**
     * user defined non-static method.
     */
    ::gov::cca::CCAExceptionType
    getCCAExceptionType_impl() ;
  };  // end class Exception_impl

} // end namespace TestScriptBabel

// DO-NOT-DELETE splicer.begin(TestScriptBabel.Exception._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(TestScriptBabel.Exception._misc)

#endif
