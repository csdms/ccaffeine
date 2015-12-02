// 
// File:          TestScriptBabel_StringMap_Impl.hxx
// Symbol:        TestScriptBabel.StringMap-v0.0
// Symbol Type:   class
// Babel Version: 1.0.0
// Description:   Server-side implementation for TestScriptBabel.StringMap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_TestScriptBabel_StringMap_Impl_hxx
#define included_TestScriptBabel_StringMap_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl_cxx.hxx"
#endif
#ifndef included_TestScriptBabel_StringMap_IOR_h
#include "TestScriptBabel_StringMap_IOR.h"
#endif
#ifndef included_TestScriptBabel_StringMap_hxx
#include "TestScriptBabel_StringMap.hxx"
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


// DO-NOT-DELETE splicer.begin(TestScriptBabel.StringMap._includes)
#include <string>
#include <map>
// DO-NOT-DELETE splicer.end(TestScriptBabel.StringMap._includes)

namespace TestScriptBabel { 

  /**
   * Symbol "TestScriptBabel.StringMap" (version 0.0)
   */
  class StringMap_impl : public virtual ::TestScriptBabel::StringMap 
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.StringMap._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(TestScriptBabel.StringMap._inherits)
  {

  // All data marked protected will be accessable by 
  // descendant Impl classes
  protected:

    bool _wrapped;

    // DO-NOT-DELETE splicer.begin(TestScriptBabel.StringMap._implementation)
    // Put additional implementation details here...
    std::map< std::string, std::string> sm;
    // DO-NOT-DELETE splicer.end(TestScriptBabel.StringMap._implementation)

  public:
    // default constructor, used for data wrapping(required)
    StringMap_impl();
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    StringMap_impl( struct TestScriptBabel_StringMap__object * s ) : StubBase(s,
      true), _wrapped(false) { _ctor(); }

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

} // end namespace TestScriptBabel

// DO-NOT-DELETE splicer.begin(TestScriptBabel.StringMap._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(TestScriptBabel.StringMap._misc)

#endif
