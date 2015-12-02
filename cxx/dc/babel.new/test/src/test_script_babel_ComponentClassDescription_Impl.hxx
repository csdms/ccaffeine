// 
// File:          test_script_babel_ComponentClassDescription_Impl.hxx
// Symbol:        test.script.babel.ComponentClassDescription-v0.0
// Symbol Type:   class
// Babel Version: 0.99.1
// Description:   Server-side implementation for test.script.babel.ComponentClassDescription
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_test_script_babel_ComponentClassDescription_Impl_hxx
#define included_test_script_babel_ComponentClassDescription_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl_cxx.hxx"
#endif
#ifndef included_test_script_babel_ComponentClassDescription_IOR_h
#include "test_script_babel_ComponentClassDescription_IOR.h"
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
#ifndef included_test_script_babel_ComponentClassDescription_hxx
#include "test_script_babel_ComponentClassDescription.hxx"
#endif


#line 43 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.new/test/src/test_script_babel_ComponentClassDescription_Impl.hxx"
// DO-NOT-DELETE splicer.begin(test.script.babel.ComponentClassDescription._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(test.script.babel.ComponentClassDescription._includes)
#line 48 "src/test_script_babel_ComponentClassDescription_Impl.hxx"

namespace test { 
  namespace script { 
    namespace babel { 

      /**
       * Symbol "test.script.babel.ComponentClassDescription" (version 0.0)
       */
      class ComponentClassDescription_impl : public virtual 
        ::test::script::babel::ComponentClassDescription 
#line 56 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.new/test/src/test_script_babel_ComponentClassDescription_Impl.hxx"
  // DO-NOT-DELETE splicer.begin(test.script.babel.ComponentClassDescription._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(test.script.babel.ComponentClassDescription._inherits)
#line 63 "src/test_script_babel_ComponentClassDescription_Impl.hxx"
      {

      // All data marked protected will be accessable by 
      // descendant Impl classes
      protected:

#line 65 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.new/test/src/test_script_babel_ComponentClassDescription_Impl.hxx"
    // DO-NOT-DELETE splicer.begin(test.script.babel.ComponentClassDescription._implementation)
    std::string cName;
    std::string cAlias;
    // DO-NOT-DELETE splicer.end(test.script.babel.ComponentClassDescription._implementation)
#line 75 "src/test_script_babel_ComponentClassDescription_Impl.hxx"

        bool _wrapped;
      public:
        // default constructor, used for data wrapping(required)
        ComponentClassDescription_impl();
        // sidl constructor (required)
        // Note: alternate Skel constructor doesn't call addref()
        // (fixes bug #275)
        ComponentClassDescription_impl( struct 
          test_script_babel_ComponentClassDescription__object * s ) : 
          StubBase(s,true) { _ctor(); }

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

    } // end namespace babel
  } // end namespace script
} // end namespace test

#line 129 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.new/test/src/test_script_babel_ComponentClassDescription_Impl.hxx"
// DO-NOT-DELETE splicer.begin(test.script.babel.ComponentClassDescription._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(test.script.babel.ComponentClassDescription._misc)
#line 140 "src/test_script_babel_ComponentClassDescription_Impl.hxx"

#endif
