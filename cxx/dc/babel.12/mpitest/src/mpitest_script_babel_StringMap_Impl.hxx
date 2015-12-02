// 
// File:          mpitest_script_babel_StringMap_Impl.hxx
// Symbol:        mpitest.script.babel.StringMap-v0.0
// Symbol Type:   class
// Babel Version: 0.99.1
// Description:   Server-side implementation for mpitest.script.babel.StringMap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_mpitest_script_babel_StringMap_Impl_hxx
#define included_mpitest_script_babel_StringMap_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl_cxx.hxx"
#endif
#ifndef included_mpitest_script_babel_StringMap_IOR_h
#include "mpitest_script_babel_StringMap_IOR.h"
#endif
#ifndef included_mpitest_script_babel_StringMap_hxx
#include "mpitest_script_babel_StringMap.hxx"
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


#line 34 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_StringMap_Impl.hxx"
// DO-NOT-DELETE splicer.begin(mpitest.script.babel.StringMap._hincludes)
#include <string>
#include <map>
// DO-NOT-DELETE splicer.end(mpitest.script.babel.StringMap._hincludes)
#line 40 "src/mpitest_script_babel_StringMap_Impl.hxx"

namespace mpitest { 
  namespace script { 
    namespace babel { 

      /**
       * Symbol "mpitest.script.babel.StringMap" (version 0.0)
       */
      class StringMap_impl : public virtual ::mpitest::script::babel::StringMap 
#line 47 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_StringMap_Impl.hxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.StringMap._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.StringMap._inherits)
#line 54 "src/mpitest_script_babel_StringMap_Impl.hxx"
      {

      // All data marked protected will be accessable by 
      // descendant Impl classes
      protected:

#line 56 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_StringMap_Impl.hxx"
    // DO-NOT-DELETE splicer.begin(mpitest.script.babel.StringMap._implementation)
    // Put additional implementation details here...
    std::map< std::string, std::string> sm;
    // DO-NOT-DELETE splicer.end(mpitest.script.babel.StringMap._implementation)
#line 66 "src/mpitest_script_babel_StringMap_Impl.hxx"

        bool _wrapped;
      public:
        // default constructor, used for data wrapping(required)
        StringMap_impl();
        // sidl constructor (required)
        // Note: alternate Skel constructor doesn't call addref()
        // (fixes bug #275)
        StringMap_impl( struct mpitest_script_babel_StringMap__object * s ) : 
          StubBase(s,true) { _ctor(); }

        // user defined construction
        void _ctor();

        // virtual destructor (required)
        virtual ~StringMap_impl() { _dtor(); }

        // user defined destruction
        void _dtor();

        // true if this object was created by a user newing the impl
        inline bool _isWrapped() {return _wrapped;}

        // static class initializer
        static void _load();

      public:


        /**
         *  return true if key exists in map. 
         */
        bool
        has_impl (
          /* in */const ::std::string& key
        )
        ;


        /**
         *  return value of key. if key is not defined in the map,
         * has side effect of defining the key with the empty
         * string value before returning the empty string.
         */
        ::std::string
        get_impl (
          /* in */const ::std::string& key
        )
        ;


        /**
         *  add or change the value for a key 
         */
        void
        set_impl (
          /* in */const ::std::string& key,
          /* in */const ::std::string& value
        )
        ;


        /**
         *  remove the key and its value, if it is there. 
         */
        void
        erase_impl (
          /* in */const ::std::string& key
        )
        ;


        /**
         *  ugly c++ pointer returned; type in c++
         * 'std::map<std::string, std::string> '
         * This pointer will be valid until the underlying
         * babel object (which contains the underlying
         * c++ object) is destroyed.
         */
        void*
        getUnderlyingStdMap_impl() ;
      };  // end class StringMap_impl

    } // end namespace babel
  } // end namespace script
} // end namespace mpitest

#line 147 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.12/mpitest/src/mpitest_script_babel_StringMap_Impl.hxx"
// DO-NOT-DELETE splicer.begin(mpitest.script.babel.StringMap._hmisc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(mpitest.script.babel.StringMap._hmisc)
#line 158 "src/mpitest_script_babel_StringMap_Impl.hxx"

#endif
