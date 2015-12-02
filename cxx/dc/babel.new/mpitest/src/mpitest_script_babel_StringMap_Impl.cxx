// 
// File:          mpitest_script_babel_StringMap_Impl.cxx
// Symbol:        mpitest.script.babel.StringMap-v0.0
// Symbol Type:   class
// Babel Version: 0.99.1
// Description:   Server-side implementation for mpitest.script.babel.StringMap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "mpitest_script_babel_StringMap_Impl.hxx"

// 
// Includes for all method dependencies.
// 
#ifndef included_sidl_BaseInterface_hxx
#include "sidl_BaseInterface.hxx"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "sidl_ClassInfo.hxx"
#endif
#ifndef included_sidl_NotImplementedException_hxx
#include "sidl_NotImplementedException.hxx"
#endif
#line 24 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.new/mpitest/src/mpitest_script_babel_StringMap_Impl.cxx"
// DO-NOT-DELETE splicer.begin(mpitest.script.babel.StringMap._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(mpitest.script.babel.StringMap._includes)
#line 29 "src/mpitest_script_babel_StringMap_Impl.cxx"

// speical constructor, used for data wrapping(required).  Do not put code here unless you really know what you're doing!
mpitest::script::babel::StringMap_impl::StringMap_impl() : 
  StubBase(reinterpret_cast< 
  void*>(::mpitest::script::babel::StringMap::_wrapObj(this)),false) ,
  _wrapped(true){ 
#line 33 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.new/mpitest/src/mpitest_script_babel_StringMap_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.StringMap._ctor2)
  // Insert-Code-Here {mpitest.script.babel.StringMap._ctor2} (ctor2)
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.StringMap._ctor2)
#line 40 "src/mpitest_script_babel_StringMap_Impl.cxx"
}

// user defined constructor
void mpitest::script::babel::StringMap_impl::_ctor() {
#line 40 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.new/mpitest/src/mpitest_script_babel_StringMap_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.StringMap._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.StringMap._ctor)
#line 49 "src/mpitest_script_babel_StringMap_Impl.cxx"
}

// user defined destructor
void mpitest::script::babel::StringMap_impl::_dtor() {
#line 47 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.new/mpitest/src/mpitest_script_babel_StringMap_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.StringMap._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.StringMap._dtor)
#line 58 "src/mpitest_script_babel_StringMap_Impl.cxx"
}

// static class initializer
void mpitest::script::babel::StringMap_impl::_load() {
#line 54 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.new/mpitest/src/mpitest_script_babel_StringMap_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.StringMap._load)
  // Insert-Code-Here {mpitest.script.babel.StringMap._load} (class initialization)
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.StringMap._load)
#line 67 "src/mpitest_script_babel_StringMap_Impl.cxx"
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 *  return true if key exists in map. 
 */
bool
mpitest::script::babel::StringMap_impl::has_impl (
  /* in */const ::std::string& key ) 
{
#line 69 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.new/mpitest/src/mpitest_script_babel_StringMap_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.StringMap.has)
	std::map<std::string, std::string >::iterator it = sm.find(key);
	if (it != sm.end())  { return true; }
	return false;
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.StringMap.has)
#line 86 "src/mpitest_script_babel_StringMap_Impl.cxx"
}

/**
 *  return value of key. if key is not defined in the map,
 * has side effect of defining the key with the empty
 * string value before returning the empty string.
 */
::std::string
mpitest::script::babel::StringMap_impl::get_impl (
  /* in */const ::std::string& key ) 
{
#line 85 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.new/mpitest/src/mpitest_script_babel_StringMap_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.StringMap.get)
  return sm[key];
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.StringMap.get)
#line 102 "src/mpitest_script_babel_StringMap_Impl.cxx"
}

/**
 *  add or change the value for a key 
 */
void
mpitest::script::babel::StringMap_impl::set_impl (
  /* in */const ::std::string& key,
  /* in */const ::std::string& value ) 
{
#line 98 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.new/mpitest/src/mpitest_script_babel_StringMap_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.StringMap.set)
  sm[key] = value;
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.StringMap.set)
#line 117 "src/mpitest_script_babel_StringMap_Impl.cxx"
}

/**
 *  remove the key and its value, if it is there. 
 */
void
mpitest::script::babel::StringMap_impl::erase_impl (
  /* in */const ::std::string& key ) 
{
#line 110 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.new/mpitest/src/mpitest_script_babel_StringMap_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.StringMap.erase)
  sm.erase(key);
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.StringMap.erase)
#line 131 "src/mpitest_script_babel_StringMap_Impl.cxx"
}

/**
 *  ugly c++ pointer returned; type in c++
 * 'std::map<std::string, std::string> '
 * This pointer will be valid until the underlying
 * babel object (which contains the underlying
 * c++ object) is destroyed.
 */
void*
mpitest::script::babel::StringMap_impl::getUnderlyingStdMap_impl () 

{
#line 126 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.new/mpitest/src/mpitest_script_babel_StringMap_Impl.cxx"
  // DO-NOT-DELETE splicer.begin(mpitest.script.babel.StringMap.getUnderlyingStdMap)
  return &sm;
  // DO-NOT-DELETE splicer.end(mpitest.script.babel.StringMap.getUnderlyingStdMap)
#line 149 "src/mpitest_script_babel_StringMap_Impl.cxx"
}


#line 132 "/home/baallan/cca/build/dccafe-99/cxx/dc/babel.new/mpitest/src/mpitest_script_babel_StringMap_Impl.cxx"
// DO-NOT-DELETE splicer.begin(mpitest.script.babel.StringMap._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(mpitest.script.babel.StringMap._misc)
#line 157 "src/mpitest_script_babel_StringMap_Impl.cxx"

