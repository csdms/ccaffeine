// 
// File:          test_script_babel_StringMap_Impl.hh
// Symbol:        test_script_babel.StringMap-v0.0
// Symbol Type:   class
// Babel Version: 0.10.0
// Description:   Server-side implementation for test_script_babel.StringMap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// babel-version = 0.10.0
// 

#ifndef included_test_script_babel_StringMap_Impl_hh
#define included_test_script_babel_StringMap_Impl_hh

#ifndef included_sidl_cxx_hh
#include "sidl_cxx.hh"
#endif
#ifndef included_test_script_babel_StringMap_IOR_h
#include "test_script_babel_StringMap_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_sidl_BaseInterface_hh
#include "sidl_BaseInterface.hh"
#endif
#ifndef included_sidl_ClassInfo_hh
#include "sidl_ClassInfo.hh"
#endif
#ifndef included_test_script_babel_StringMap_hh
#include "test_script_babel_StringMap.hh"
#endif


// DO-NOT-DELETE splicer.begin(test_script_babel.StringMap._includes)
#include <string>
#include <map>
// DO-NOT-DELETE splicer.end(test_script_babel.StringMap._includes)

namespace test_script_babel { 

  /**
   * Symbol "test_script_babel.StringMap" (version 0.0)
   */
  class StringMap_impl
  // DO-NOT-DELETE splicer.begin(test_script_babel.StringMap._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(test_script_babel.StringMap._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    StringMap self;

    // DO-NOT-DELETE splicer.begin(test_script_babel.StringMap._implementation)
    // Put additional implementation details here...
    std::map< std::string, std::string> sm;
    // DO-NOT-DELETE splicer.end(test_script_babel.StringMap._implementation)

  private:
    // private default constructor (required)
    StringMap_impl() {} 

  public:
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    StringMap_impl( struct test_script_babel_StringMap__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~StringMap_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

    // static class initializer
    static void _load();

  public:


    /**
     * return true if key exists in map. 
     */
    bool
    has (
      /*in*/ const ::std::string& key
    )
    throw () 
    ;


    /**
     * return value of key. if key is not defined in the map,
     * has side effect of defining the key with the empty
     * string value before returning the empty string.
     */
    ::std::string
    get (
      /*in*/ const ::std::string& key
    )
    throw () 
    ;


    /**
     * add or change the value for a key 
     */
    void
    set (
      /*in*/ const ::std::string& key,
      /*in*/ const ::std::string& value
    )
    throw () 
    ;


    /**
     * remove the key and its value, if it is there. 
     */
    void
    erase (
      /*in*/ const ::std::string& key
    )
    throw () 
    ;


    /**
     * ugly c++ pointer returned; type in c++
     * 'std::map<std::string, std::string> *'
     * This pointer will be valid until the underlying
     * babel object (which contains the underlying
     * c++ object) is destroyed.
     */
    void*
    getUnderlyingStdMap() throw () 
    ;
  };  // end class StringMap_impl

} // end namespace test_script_babel

// DO-NOT-DELETE splicer.begin(test_script_babel.StringMap._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(test_script_babel.StringMap._misc)

#endif
