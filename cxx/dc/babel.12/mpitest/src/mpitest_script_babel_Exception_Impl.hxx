// 
// File:          mpitest_script_babel_Exception_Impl.hxx
// Symbol:        mpitest.script.babel.Exception-v0.0
// Symbol Type:   class
// Babel Version: 0.99.1
// Description:   Server-side implementation for mpitest.script.babel.Exception
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_mpitest_script_babel_Exception_Impl_hxx
#define included_mpitest_script_babel_Exception_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl_cxx.hxx"
#endif
#ifndef included_mpitest_script_babel_Exception_IOR_h
#include "mpitest_script_babel_Exception_IOR.h"
#endif
#ifndef included_gov_cca_CCAException_hxx
#include "gov_cca_CCAException.hxx"
#endif
#ifndef included_gov_cca_CCAExceptionType_hxx
#include "gov_cca_CCAExceptionType.hxx"
#endif
#ifndef included_mpitest_script_babel_Exception_hxx
#include "mpitest_script_babel_Exception.hxx"
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


#line 46 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_Exception_Impl.hxx"
// DO-NOT-DELETE splicer.begin(mpitest.script.babel.Exception._hincludes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(mpitest.script.babel.Exception._hincludes)
#line 51 "src/mpitest_script_babel_Exception_Impl.hxx"

namespace mpitest { 
  namespace script { 
    namespace babel { 

      /**
       * Symbol "mpitest.script.babel.Exception" (version 0.0)
       */
      class Exception_impl : public virtual ::mpitest::script::babel::Exception 
#line 58 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_Exception_Impl.hxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.Exception._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.Exception._inherits)
#line 65 "src/mpitest_script_babel_Exception_Impl.hxx"
      {

      // All data marked protected will be accessable by 
      // descendant Impl classes
      protected:

#line 67 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_Exception_Impl.hxx"
    // DO-NOT-DELETE splicer.begin(mpitest.script.babel.Exception._implementation)
    // Put additional implementation details here...
    ::gov::cca::CCAExceptionType myType;
    // DO-NOT-DELETE splicer.end(mpitest.script.babel.Exception._implementation)
#line 77 "src/mpitest_script_babel_Exception_Impl.hxx"

        bool _wrapped;
      public:
        // default constructor, used for data wrapping(required)
        Exception_impl();
        // sidl constructor (required)
        // Note: alternate Skel constructor doesn't call addref()
        // (fixes bug #275)
        Exception_impl( struct mpitest_script_babel_Exception__object * s ) : 
          StubBase(s,true) { _ctor(); }

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

    } // end namespace babel
  } // end namespace script
} // end namespace mpitest

#line 119 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_Exception_Impl.hxx"
// DO-NOT-DELETE splicer.begin(mpitest.script.babel.Exception._hmisc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(mpitest.script.babel.Exception._hmisc)
#line 130 "src/mpitest_script_babel_Exception_Impl.hxx"

#endif
