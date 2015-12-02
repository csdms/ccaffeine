// 
// File:          ccaffeine_ports_BasicParameterPortWrap_Impl.cc
// Symbol:        ccaffeine.ports.BasicParameterPortWrap-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ports.BasicParameterPortWrap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_ports_BasicParameterPortWrap_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.BasicParameterPortWrap._includes)
// Put additional includes or other arbitrary code here...
#include "dc/babel/babel-cca/BabelCCAHelpers.hh"
#include "dc/babel/ccafe-bind/AllCcafeBind.hh"
#include "ccaffeine_TypeMap_Impl.hh"


int ccaffeine::ports::BasicParameterPortWrap_impl::genSerial = 0;

// DO-NOT-DELETE splicer.end(ccaffeine.ports.BasicParameterPortWrap._includes)

// user defined constructor
void ccaffeine::ports::BasicParameterPortWrap_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BasicParameterPortWrap._ctor)
  // add construction details here
  opp = 0;
#ifdef CCAFE_AUDIT
  serial = nextNum();
  IO_dn2("ccaffeine::ports::BasicParameterPortWrap_impl _ctor %d", serial);
#endif

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BasicParameterPortWrap._ctor)
}

// user defined destructor
void ccaffeine::ports::BasicParameterPortWrap_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BasicParameterPortWrap._dtor)
  // add destruction details here
#ifdef CCAFE_AUDIT
  serial = -serial;
  IO_dn2("ccaffeine::ports::BuilderService_impl _dtor %d", serial);
#endif
  // delete opp; it was set on us. why are we deleting?
  opp = 0;

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BasicParameterPortWrap._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * passed in is a void * cast pointer of
 *  ccafeopq::ports::BasicParameterPort *.
 */
void
ccaffeine::ports::BasicParameterPortWrap_impl::initialize (
  /*in*/ void* ccafeopq_ports_BasicParameterPort_star ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BasicParameterPortWrap.initialize)
#ifdef CCAFE_AUDIT
  IO_dn2("ccaffeine::ports::BasicParameterPortWrap_impl init %d", serial);
#endif
  opp =
    static_cast< ::ccafeopq::ports::BasicParameterPort *>( ccafeopq_ports_BasicParameterPort_star);

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BasicParameterPortWrap.initialize)
}

/**
 * fetch up a pointer for static casting. if the name
 * supplied is not exactly right, returns null.
 */
void*
ccaffeine::ports::BasicParameterPortWrap_impl::getWrapped (
  /*in*/ const ::std::string& className ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BasicParameterPortWrap.getWrapped)
  if (className == "::ccafeopq::ports::BasicParameterPortWrap")
  {
    return opp;
  } 
  return 0;
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BasicParameterPortWrap.getWrapped)
}

/**
 * Return a TypeMap of runtime configuration parameters. 
 * It is recommended that the map returned be a clone/copy of the
 * a privately held map, not a shared object reference.
 */
::gov::cca::TypeMap
ccaffeine::ports::BasicParameterPortWrap_impl::readConfigurationMap () 
throw ( 
  ::gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BasicParameterPortWrap.readConfigurationMap)
  ccafeopq::TypeMap_shared otm = opp->readConfigurationMap();
  gov::cca::TypeMap btm;
  btm = ccaffeine::TypeMap_impl::babelWrap(otm);
  return btm;
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BasicParameterPortWrap.readConfigurationMap)
}

/**
 * Copy the parameter values given in map into the
 * internal map, for those parameters which
 * are already defined by the internal map.
 * The outsider does not get to cause arbitrary
 * keys to be copied into the internal map.
 * @throws gov.cca.CCAException if TypeMap operations fail.
 */
void
ccaffeine::ports::BasicParameterPortWrap_impl::writeConfigurationMap (
  /*in*/ ::gov::cca::TypeMap map ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BasicParameterPortWrap.writeConfigurationMap)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( map );
  opp->writeConfigurationMap(ctm);

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BasicParameterPortWrap.writeConfigurationMap)
}

/**
 * Fetch the list of keys in the TypeMap that are
 * for public configuration purposes. Other values found in
 * the TypeMap must not be changed.
 */
::sidl::array< ::std::string>
ccaffeine::ports::BasicParameterPortWrap_impl::readConfigurationKeys () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BasicParameterPortWrap.readConfigurationKeys)
  std::vector< std::string > svec = opp->readConfigurationKeys();
  return BabelHelper::stringVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.BasicParameterPortWrap.readConfigurationKeys)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.BasicParameterPortWrap._misc)
// Put miscellaneous code here

void 
ccaffeine::ports::BasicParameterPortWrap_impl::checkthrow(const char *funcName)
{
  ccafe::BabelCCAHelpers::checkthrow("ccaffeine::ports::BasicParameterPortWrap_impl", "opp", static_cast<void *>(opp), funcName);
}

int ccaffeine_ports_BasicParameterPortWrap_qc(int argc, char *argv[])
{
  ::ccaffeine::ports::BasicParameterPortWrap_impl x();
  return 0;
}

#ifdef ccaffeine_ports_BasicParameterPortWrap_MAIN
int main(int argc, char **argv)
{
  return ccaffeine_ports_BasicParameterPortWrap_qc(argc,argv);
}
#endif // ccaffeine_ports_BasicParameterPortWrap_MAIN

// DO-NOT-DELETE splicer.end(ccaffeine.ports.BasicParameterPortWrap._misc)

