// 
// File:          ccafe5_BasicParameterPortTest_Impl.cxx
// Symbol:        ccafe5.BasicParameterPortTest-v0.0
// Symbol Type:   class
// Babel Version: 1.0.6
// Description:   Server-side implementation for ccafe5.BasicParameterPortTest
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccafe5_BasicParameterPortTest_Impl.hxx"

// 
// Includes for all method dependencies.
// 
#ifndef included_gov_cca_CCAException_hxx
#include "gov_cca_CCAException.hxx"
#endif
#ifndef included_gov_cca_Services_hxx
#include "gov_cca_Services.hxx"
#endif
#ifndef included_gov_cca_TypeMap_hxx
#include "gov_cca_TypeMap.hxx"
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
#ifndef included_sidl_NotImplementedException_hxx
#include "sidl_NotImplementedException.hxx"
#endif
// DO-NOT-DELETE splicer.begin(ccafe5.BasicParameterPortTest._includes)
#include <iostream>
// DO-NOT-DELETE splicer.end(ccafe5.BasicParameterPortTest._includes)

// speical constructor, used for data wrapping(required).  Do not put code here unless you really know what you're doing!
ccafe5::BasicParameterPortTest_impl::BasicParameterPortTest_impl() : StubBase(
  reinterpret_cast< void*>(::ccafe5::BasicParameterPortTest::_wrapObj(
  reinterpret_cast< void*>(this))),false) , _wrapped(true){ 
  // DO-NOT-DELETE splicer.begin(ccafe5.BasicParameterPortTest._ctor2)
  // Insert-Code-Here {ccafe5.BasicParameterPortTest._ctor2} (ctor2)
  // DO-NOT-DELETE splicer.end(ccafe5.BasicParameterPortTest._ctor2)
}

// user defined constructor
void ccafe5::BasicParameterPortTest_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccafe5.BasicParameterPortTest._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(ccafe5.BasicParameterPortTest._ctor)
}

// user defined destructor
void ccafe5::BasicParameterPortTest_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccafe5.BasicParameterPortTest._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccafe5.BasicParameterPortTest._dtor)
}

// static class initializer
void ccafe5::BasicParameterPortTest_impl::_load() {
  // DO-NOT-DELETE splicer.begin(ccafe5.BasicParameterPortTest._load)
  // Insert-Code-Here {ccafe5.BasicParameterPortTest._load} (class initialization)
  // DO-NOT-DELETE splicer.end(ccafe5.BasicParameterPortTest._load)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 *  Starts up a component presence in the calling framework.
 * @param services the component instance's handle on the framework world.
 * Contracts concerning Svc and setServices:
 * 
 * The component interaction with the CCA framework
 * and Ports begins on the call to setServices by the framework.
 * 
 * This function is called exactly once for each instance created
 * by the framework.
 * 
 * The argument Svc will never be nil/null.
 * 
 * Those uses ports which are automatically connected by the framework
 * (so-called service-ports) may be obtained via getPort during
 * setServices.
 */
void
ccafe5::BasicParameterPortTest_impl::setServices_impl (
  /* in */::gov::cca::Services services ) 
// throws:
//     ::gov::cca::CCAException
//     ::sidl::RuntimeException
{
  // DO-NOT-DELETE splicer.begin(ccafe5.BasicParameterPortTest.setServices)

  try {
    IO_dn1("ccafe5::BasicParameterPortTest_impl::setServices entry");
    svc = services;
    if(svc._not_nil()) {

  
      parms = svc.createTypeMap();
      parms.putInt("i1", 2);
      parms.putString("s1","fred");
      gov::cca::TypeMap tm = svc.createTypeMap();
      gov::cca::ports::BasicParameterPort gp = *this;
      svc.addProvidesPort(gp, std::string("config"), 
			  std::string("gov.cca.ports.BasicParameterPort"), tm);
      svc.registerUsesPort(std::string("useconfig"),
			   std::string("gov.cca.ports.BasicParameterPort"), tm);
    } else {
      IO_dn1(":-( Services Object is nil passed to "
	     "ccafe5::BasicParameterPortTest_impl::setServices");
    }
  
  } catch(std::exception& e) {
    IO_dn2("exception caught: %s", e.what());
  }

  // DO-NOT-DELETE splicer.end(ccafe5.BasicParameterPortTest.setServices)
}


/**
 *  Return a TypeMap of runtime configuration parameters. 
 * It is recommended that the map returned be a clone/copy of the
 * a privately held map, not a shared object reference.
 */
::gov::cca::TypeMap
ccafe5::BasicParameterPortTest_impl::readConfigurationMap_impl () 
// throws:
//     ::gov::cca::CCAException
//     ::sidl::RuntimeException

{
  // DO-NOT-DELETE splicer.begin(ccafe5.BasicParameterPortTest.readConfigurationMap)
   IO_dn1("BasicParameterPortTest returning clone of typemap");
   return parms.cloneTypeMap(); 
  // DO-NOT-DELETE splicer.end(ccafe5.BasicParameterPortTest.readConfigurationMap)
}

/**
 *  Copy the parameter values given in map into the
 * internal map, for those parameters which
 * are already defined by the internal map.
 * The outsider does not get to cause arbitrary
 * keys to be copied into the internal map.
 * @throws gov.cca.CCAException if TypeMap operations fail.
 */
void
ccafe5::BasicParameterPortTest_impl::writeConfigurationMap_impl (
  /* in */::gov::cca::TypeMap map ) 
// throws:
//     ::gov::cca::CCAException
//     ::sidl::RuntimeException
{
  // DO-NOT-DELETE splicer.begin(ccafe5.BasicParameterPortTest.writeConfigurationMap)
#define TRANSFER_CASE(SRC, DEST, BTYPE, FTYPE, DEFVAL) \
    case ::gov::cca::Type_##FTYPE: \
      { \
        BTYPE val = SRC.get##FTYPE(keys[i], DEFVAL); \
        DEST.put##FTYPE(keys[i], val); \
      } \
      break
#define TRANSFER_ARRAY_CASE(SRC, DEST, BTYPE, FTYPE) \
    case ::gov::cca::Type_##FTYPE##Array: \
      { \
        sidl::array< BTYPE > b; \
        sidl::array< BTYPE > val = SRC.get##FTYPE##Array(keys[i], b); \
        DEST.put##FTYPE##Array(keys[i], val);  \
      } \
      break

  IO_en1("ccafe5::BasicParameterPortTest_impl::writeCM attempted.");
  sidl::array< std::string> keys = parms.getAllKeys(gov::cca::Type_NoType);
  int32_t last = keys.upper(0);
  for (int32_t i = keys.lower(0); i <= last; i++) {
    if (! map.hasKey(keys[i])) { continue; }
    gov::cca::Type kt = parms.typeOf(keys[i]);
    gov::cca::Type nt = map.typeOf(keys[i]);
    if ( nt != kt) {
      IO_dn2("Error: BasicParameterPortTest: attempt to set value of wrong type on: %s", keys[i].c_str());
      continue;
    }
    switch (kt) {
    TRANSFER_CASE(map, parms, int32_t, Int, 0);
    TRANSFER_CASE(map, parms, int64_t, Long, 0);
    TRANSFER_CASE(map, parms, float, Float, 0);
    TRANSFER_CASE(map, parms, double, Double, 0);
    TRANSFER_CASE(map, parms,  ::std::complex< float >, Fcomplex, ::std::complex< float >(0,0) );
    TRANSFER_CASE(map, parms,  ::std::complex< double >, Dcomplex, ::std::complex< double >(0,0) );
    TRANSFER_CASE(map, parms, bool, Bool, false);
    TRANSFER_CASE(map, parms, std::string, String, std::string(""));

    TRANSFER_ARRAY_CASE(map, parms, int32_t, Int);
    TRANSFER_ARRAY_CASE(map, parms, int64_t, Long);
    TRANSFER_ARRAY_CASE(map, parms, float, Float);
    TRANSFER_ARRAY_CASE(map, parms, double, Double);
    TRANSFER_ARRAY_CASE(map, parms,  ::std::complex< float >, Fcomplex );
    TRANSFER_ARRAY_CASE(map, parms,  ::std::complex< double >, Dcomplex );
    TRANSFER_ARRAY_CASE(map, parms, bool, Bool);
    TRANSFER_ARRAY_CASE(map, parms,  ::std::string , String);
    default:
      IO_en2("Error: BasicParameterPortTest: attempt to set value of unknown type on: %s", keys[i].c_str());
    }
  }
  // DO-NOT-DELETE splicer.end(ccafe5.BasicParameterPortTest.writeConfigurationMap)
}

/**
 *  Fetch the list of keys in the TypeMap that are
 * for public configuration purposes. Other values found in
 * the TypeMap must not be changed.
 */
::sidl::array< ::std::string>
ccafe5::BasicParameterPortTest_impl::readConfigurationKeys_impl () 

{
  // DO-NOT-DELETE splicer.begin(ccafe5.BasicParameterPortTest.readConfigurationKeys)
  return parms.getAllKeys(gov::cca::Type_NoType);
    
  // DO-NOT-DELETE splicer.end(ccafe5.BasicParameterPortTest.readConfigurationKeys)
}


// DO-NOT-DELETE splicer.begin(ccafe5.BasicParameterPortTest._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccafe5.BasicParameterPortTest._misc)

