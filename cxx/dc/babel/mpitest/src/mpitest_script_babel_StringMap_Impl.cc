// 
// File:          mpitest_script_babel_StringMap_Impl.cc
// Symbol:        mpitest_script_babel.StringMap-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for mpitest_script_babel.StringMap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "mpitest_script_babel_StringMap_Impl.hh"

// DO-NOT-DELETE splicer.begin(mpitest_script_babel.StringMap._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(mpitest_script_babel.StringMap._includes)

// user-defined constructor.
void mpitest_script_babel::StringMap_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.StringMap._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.StringMap._ctor)
}

// user-defined destructor.
void mpitest_script_babel::StringMap_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.StringMap._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.StringMap._dtor)
}

// static class initializer.
void mpitest_script_babel::StringMap_impl::_load() {
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.StringMap._load)
  // Insert-Code-Here {mpitest_script_babel.StringMap._load} (class initialization)
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.StringMap._load)
}

// user-defined static methods: (none)

// user-defined non-static methods:
/**
 * return true if key exists in map. 
 */
bool
mpitest_script_babel::StringMap_impl::has (
  /* in */ const ::std::string& key ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.StringMap.has)
	std::map<std::string, std::string >::iterator it = sm.find(key);
	if (it != sm.end())  { return true; }
	return false;
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.StringMap.has)
}

/**
 * return value of key. if key is not defined in the map,
 * has side effect of defining the key with the empty
 * string value before returning the empty string.
 */
::std::string
mpitest_script_babel::StringMap_impl::get (
  /* in */ const ::std::string& key ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.StringMap.get)
  return sm[key];
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.StringMap.get)
}

/**
 * add or change the value for a key 
 */
void
mpitest_script_babel::StringMap_impl::set (
  /* in */ const ::std::string& key,
  /* in */ const ::std::string& value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.StringMap.set)
  sm[key] = value;
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.StringMap.set)
}

/**
 * remove the key and its value, if it is there. 
 */
void
mpitest_script_babel::StringMap_impl::erase (
  /* in */ const ::std::string& key ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.StringMap.erase)
  sm.erase(key);
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.StringMap.erase)
}

/**
 * ugly c++ pointer returned; type in c++
 * 'std::map<std::string, std::string> *'
 * This pointer will be valid until the underlying
 * babel object (which contains the underlying
 * c++ object) is destroyed.
 */
void*
mpitest_script_babel::StringMap_impl::getUnderlyingStdMap ()
throw () 

{
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.StringMap.getUnderlyingStdMap)
  return &sm;
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.StringMap.getUnderlyingStdMap)
}


// DO-NOT-DELETE splicer.begin(mpitest_script_babel.StringMap._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(mpitest_script_babel.StringMap._misc)

