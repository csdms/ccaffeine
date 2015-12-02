// 
// File:          TestScriptBabel_StringMap_Impl.cxx
// Symbol:        TestScriptBabel.StringMap-v0.0
// Symbol Type:   class
// Babel Version: 1.0.0
// Description:   Server-side implementation for TestScriptBabel.StringMap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "TestScriptBabel_StringMap_Impl.hxx"

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
// DO-NOT-DELETE splicer.begin(TestScriptBabel.StringMap._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(TestScriptBabel.StringMap._includes)

// speical constructor, used for data wrapping(required).  Do not put code here unless you really know what you're doing!
TestScriptBabel::StringMap_impl::StringMap_impl() : StubBase(reinterpret_cast< 
  void*>(::TestScriptBabel::StringMap::_wrapObj(reinterpret_cast< 
  void*>(this))),false) , _wrapped(true){ 
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.StringMap._ctor2)
  // Insert-Code-Here {TestScriptBabel.StringMap._ctor2} (ctor2)
  // DO-NOT-DELETE splicer.end(TestScriptBabel.StringMap._ctor2)
}

// user defined constructor
void TestScriptBabel::StringMap_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.StringMap._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(TestScriptBabel.StringMap._ctor)
}

// user defined destructor
void TestScriptBabel::StringMap_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.StringMap._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(TestScriptBabel.StringMap._dtor)
}

// static class initializer
void TestScriptBabel::StringMap_impl::_load() {
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.StringMap._load)
  // Insert-Code-Here {TestScriptBabel.StringMap._load} (class initialization)
  // DO-NOT-DELETE splicer.end(TestScriptBabel.StringMap._load)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 *  return true if key exists in map. 
 */
bool
TestScriptBabel::StringMap_impl::has_impl (
  /* in */const ::std::string& key ) 
{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.StringMap.has)
	std::map<std::string, std::string >::iterator it = sm.find(key);
	if (it != sm.end())  { return true; }
	return false;
  // DO-NOT-DELETE splicer.end(TestScriptBabel.StringMap.has)
}

/**
 *  return value of key. if key is not defined in the map,
 * has side effect of defining the key with the empty
 * string value before returning the empty string.
 */
::std::string
TestScriptBabel::StringMap_impl::get_impl (
  /* in */const ::std::string& key ) 
{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.StringMap.get)
  return sm[key];
  // DO-NOT-DELETE splicer.end(TestScriptBabel.StringMap.get)
}

/**
 *  add or change the value for a key 
 */
void
TestScriptBabel::StringMap_impl::set_impl (
  /* in */const ::std::string& key,
  /* in */const ::std::string& value ) 
{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.StringMap.set)
  sm[key] = value;
  // DO-NOT-DELETE splicer.end(TestScriptBabel.StringMap.set)
}

/**
 *  remove the key and its value, if it is there. 
 */
void
TestScriptBabel::StringMap_impl::erase_impl (
  /* in */const ::std::string& key ) 
{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.StringMap.erase)
  sm.erase(key);
  // DO-NOT-DELETE splicer.end(TestScriptBabel.StringMap.erase)
}

/**
 *  ugly c++ pointer returned; type in c++
 * 'std::map<std::string, std::string> '
 * This pointer will be valid until the underlying
 * babel object (which contains the underlying
 * c++ object) is destroyed.
 */
void*
TestScriptBabel::StringMap_impl::getUnderlyingStdMap_impl () 

{
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.StringMap.getUnderlyingStdMap)
  return &sm;
  // DO-NOT-DELETE splicer.end(TestScriptBabel.StringMap.getUnderlyingStdMap)
}


// DO-NOT-DELETE splicer.begin(TestScriptBabel.StringMap._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(TestScriptBabel.StringMap._misc)

