// 
// File:          test_script_babel_StringMap_Impl.cc
// Symbol:        test_script_babel.StringMap-v0.0
// Symbol Type:   class
// Babel Version: 0.10.0
// Description:   Server-side implementation for test_script_babel.StringMap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// babel-version = 0.10.0
// 
#include "test_script_babel_StringMap_Impl.hh"

// DO-NOT-DELETE splicer.begin(test_script_babel.StringMap._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(test_script_babel.StringMap._includes)

// user defined constructor
void test_script_babel::StringMap_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(test_script_babel.StringMap._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(test_script_babel.StringMap._ctor)
}

// user defined destructor
void test_script_babel::StringMap_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(test_script_babel.StringMap._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(test_script_babel.StringMap._dtor)
}


// user defined static methods: (none)

// user defined non-static methods:
/**
 * return true if key exists in map. 
 */
bool
test_script_babel::StringMap_impl::has (
  /*in*/ const ::std::string& key ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(test_script_babel.StringMap.has)
	std::map<std::string, std::string >::iterator it = sm.find(key);
	if (it != sm.end())  { return true; }
	return false;
  // DO-NOT-DELETE splicer.end(test_script_babel.StringMap.has)
}

/**
 * return value of key. if key is not defined in the map,
 * has side effect of defining the key with the empty
 * string value before returning the empty string.
 */
::std::string
test_script_babel::StringMap_impl::get (
  /*in*/ const ::std::string& key ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(test_script_babel.StringMap.get)
  return sm[key];
  // DO-NOT-DELETE splicer.end(test_script_babel.StringMap.get)
}

/**
 * add or change the value for a key 
 */
void
test_script_babel::StringMap_impl::set (
  /*in*/ const ::std::string& key,
  /*in*/ const ::std::string& value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(test_script_babel.StringMap.set)
  sm[key] = value;
  // DO-NOT-DELETE splicer.end(test_script_babel.StringMap.set)
}

/**
 * remove the key and its value, if it is there. 
 */
void
test_script_babel::StringMap_impl::erase (
  /*in*/ const ::std::string& key ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(test_script_babel.StringMap.erase)
  sm.erase(key);
  // DO-NOT-DELETE splicer.end(test_script_babel.StringMap.erase)
}

/**
 * ugly c++ pointer returned; type in c++
 * 'std::map<std::string, std::string> *'
 * This pointer will be valid until the underlying
 * babel object (which contains the underlying
 * c++ object) is destroyed.
 */
void*
test_script_babel::StringMap_impl::getUnderlyingStdMap () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(test_script_babel.StringMap.getUnderlyingStdMap)
  return &sm;
  // DO-NOT-DELETE splicer.end(test_script_babel.StringMap.getUnderlyingStdMap)
}


// DO-NOT-DELETE splicer.begin(test_script_babel.StringMap._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(test_script_babel.StringMap._misc)

