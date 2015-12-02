// 
// File:          ccaffeine_ports_ParameterPortWrap_Impl.cc
// Symbol:        ccaffeine.ports.ParameterPortWrap-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ports.ParameterPortWrap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_ports_ParameterPortWrap_Impl.hxx"

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap._includes)
// Put additional includes or other arbitrary code here...
#include "dc/babel.12/babel-cca/BabelCCAHelpers.hxx"
#include "dc/babel.12/ccafe-bind/AllCcafeBind.hh"
#include "ccaffeine_TypeMap_Impl.hxx"


int ccaffeine::ports::ParameterPortWrap_impl::genSerial = 0;

// DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap._includes)

// user defined constructor
void ccaffeine::ports::ParameterPortWrap_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap._ctor)
  // add construction details here
  opp = 0;
#ifdef CCAFE_AUDIT
  serial = nextNum();
  IO_dn2("ccaffeine::ports::ParameterPortWrap_impl _ctor %d", serial);
#endif

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap._ctor)
}

// user defined destructor
void ccaffeine::ports::ParameterPortWrap_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap._dtor)
  // add destruction details here
#ifdef CCAFE_AUDIT
  serial = -serial;
  IO_dn2("ccaffeine::ports::BuilderService_impl _dtor %d", serial);
#endif
  // delete opp; it was set on us. why are we deleting?
  opp = 0;

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * passed in is a void * cast pointer of
 *  ccafeopq::ParameterPort *.
 */
void
ccaffeine::ports::ParameterPortWrap_impl::initialize (
  /*in*/ void* ccafeopq_ParameterPort_ptr ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.initialize)
#ifdef CCAFE_AUDIT
  IO_dn2("ccaffeine::ports::ParameterPortWrap_impl init %d", serial);
#endif
  opp =
    static_cast< ::ccafeopq::ports::ParameterPort *>( co_p_ParameterPort_star);

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.initialize)
}

/**
 * fetch up a pointer for static casting. if the name
 * supplied is not exactly right, returns null.
 */
void*
ccaffeine::ports::ParameterPortWrap_impl::getWrapped (
  /*in*/ const ::std::string& className ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.getWrapped)
  if (className == "::ccafeopq::ports::ParameterPortWrap")
  {
    return opp;
  } 
  return 0;
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.getWrapped)
}

/**
 * Return a TypeMap of runtime configuration parameters. 
 * It is recommended that the map returned be a clone/copy of the
 * a privately held map, not a shared object reference.
 */
::gov::cca::TypeMap
ccaffeine::ports::ParameterPortWrap_impl::readConfigurationMap () 
throw ( 
  ::gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readConfigurationMap)
  ccafeopq::TypeMap_shared otm = opp->readConfigurationMap();
  gov::cca::TypeMap btm;
  btm = ccaffeine::TypeMap_impl::babelWrap(otm);
  return btm;
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readConfigurationMap)
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
ccaffeine::ports::ParameterPortWrap_impl::writeConfigurationMap (
  /*in*/ ::gov::cca::TypeMap map ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.writeConfigurationMap)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( map );
  opp->writeConfigurationMap(ctm);

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.writeConfigurationMap)
}

/**
 * Fetch the list of keys in the TypeMap that are
 * for public configuration purposes. Other values found in
 * the TypeMap must not be changed.
 */
::sidl::array< ::std::string>
ccaffeine::ports::ParameterPortWrap_impl::readConfigurationKeys () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readConfigurationKeys)
  std::vector< std::string > svec = opp->readConfigurationKeys();
  return BabelHelper::stringVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readConfigurationKeys)
}

/**
 * Fetch configuration title. 
 * @return Description of data set.
 */
::std::string
ccaffeine::ports::ParameterPortWrap_impl::readTitle () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readTitle)
  // insert implementation here
  return opp->readTitle();
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readTitle)
}

/**
 * Fetch the names of groups. Each page in a tabbed dialog
 * goes with a group, for example. Group names should be
 * a simple word without whitespace.
 */
::sidl::array< ::std::string>
ccaffeine::ports::ParameterPortWrap_impl::readGroupNames () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readGroupNames)
  std::vector< std::string > svec = opp->readGroupNames();
  return BabelHelper::stringVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readGroupNames)
}

/**
 * Fetch UI-appropriate name for group.
 * Group name and group title may be the same, if simple.
 * Group title can be complex if desired.
 * @throws gov.cca.CCAException if groupName is unknown.
 */
::std::string
ccaffeine::ports::ParameterPortWrap_impl::readGroupTitle (
  /*in*/ const ::std::string& groupName ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readGroupTitle)
  return opp->readGroupTitle(groupName);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readGroupTitle)
}

/**
 * Fetch data item keys associated with groupName.
 * Array order will be the same as the order in which
 * the additions were made in the ParameterPortFactory interface.
 * @throws gov.cca.CCAException if groupName is unknown.
 */
::sidl::array< ::std::string>
ccaffeine::ports::ParameterPortWrap_impl::readGroupKeys (
  /*in*/ const ::std::string& groupName ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readGroupKeys)
  // insert implementation here
  std::vector< std::string > svec = opp->readGroupKeys(groupName);
  return BabelHelper::stringVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readGroupKeys)
}

/**
 * Fetch the help string for key.
 * @throws gov.cca.CCAException if key is unknown.
 */
::std::string
ccaffeine::ports::ParameterPortWrap_impl::readHelp (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readHelp)
  return opp->readHelp(key);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readHelp)
}

/**
 * Fetch the prompt string for key.
 * @throws gov.cca.CCAException if key is unknown.
 */
::std::string
ccaffeine::ports::ParameterPortWrap_impl::readPrompt (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readPrompt)
  return opp->readPrompt(key);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readPrompt)
}

/**
 * By default, bounds are defined except for complex numbers
 * booleans, and strings. On array types, bounds apply
 * element-wise. i.e.  low <= arr[i] <= high for all i.
 * @return true if simple bounds are defined for a key.
 * @throws gov.cca.CCAException if key is unknown.
 */
bool
ccaffeine::ports::ParameterPortWrap_impl::hasBounds (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.hasBounds)
  // subject to interpretation
  return opp->hasBounds(key);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.hasBounds)
}

/**
 * By default, lists of choices are not defined for scalars or arrays.
 * Choices are applied element-wise for array types.
 * I.e. (arr[i] IN choice-set) == true  for all i.
 * @return true if choice list is defined for a key.
 * @throws gov.cca.CCAException if key is unknown.
 */
bool
ccaffeine::ports::ParameterPortWrap_impl::hasChoices (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.hasChoices)
  return opp->hasChoices(key);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.hasChoices)
}

/**
 * Fetch the default for boolean-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
bool
ccaffeine::ports::ParameterPortWrap_impl::readDefaultBoolean (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readDefaultBoolean)
  // insert implementation here
  return opp->readDefaultBoolean(key);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readDefaultBoolean)
}

/**
 * Fetch the default for string-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::std::string
ccaffeine::ports::ParameterPortWrap_impl::readDefaultString (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readDefaultString)
  return opp->readDefaultString(key);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readDefaultString)
}

/**
 * Fetch the default for integer-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
int32_t
ccaffeine::ports::ParameterPortWrap_impl::readDefaultInt (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readDefaultInt)
  return opp->readDefaultInt(key);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readDefaultInt)
}

/**
 * Fetch the default for long-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
int64_t
ccaffeine::ports::ParameterPortWrap_impl::readDefaultLong (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readDefaultLong)
  return opp->readDefaultLong(key);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readDefaultLong)
}

/**
 * Fetch the default for float-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
float
ccaffeine::ports::ParameterPortWrap_impl::readDefaultFloat (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readDefaultFloat)
  return opp->readDefaultFloat(key);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readDefaultFloat)
}

/**
 * Fetch the default for double-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
double
ccaffeine::ports::ParameterPortWrap_impl::readDefaultDouble (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readDefaultDouble)
  return opp->readDefaultDouble(key);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readDefaultDouble)
}

/**
 * Fetch the default for fcomplex-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::std::complex<float>
ccaffeine::ports::ParameterPortWrap_impl::readDefaultFcomplex (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readDefaultFcomplex)
  return opp->readDefaultFcomplex(key);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readDefaultFcomplex)
}

/**
 * Fetch the default for dcomplex-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::std::complex<double>
ccaffeine::ports::ParameterPortWrap_impl::readDefaultDcomplex (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readDefaultDcomplex)
  return opp->readDefaultDcomplex(key);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readDefaultDcomplex)
}

/**
 * Fetch the default for string-array-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::sidl::array< ::std::string>
ccaffeine::ports::ParameterPortWrap_impl::readDefaultStringArray (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readDefaultStringArray)
  std::vector< std::string > svec = opp->readDefaultStringArray(key);
  return BabelHelper::stringVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readDefaultStringArray)
}

/**
 * Fetch the default for boolean-array-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::sidl::array<bool>
ccaffeine::ports::ParameterPortWrap_impl::readDefaultBooleanArray (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readDefaultBooleanArray)
  std::vector< bool > svec = opp->readDefaultBooleanArray(key);
  return BabelHelper::boolVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readDefaultBooleanArray)
}

/**
 * Fetch the default for integer-array-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::sidl::array<int32_t>
ccaffeine::ports::ParameterPortWrap_impl::readDefaultIntArray (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readDefaultIntArray)
  std::vector< int32_t > svec = opp->readDefaultIntArray(key);
  return BabelHelper::intVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readDefaultIntArray)
}

/**
 * Fetch the default for long-array-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::sidl::array<int64_t>
ccaffeine::ports::ParameterPortWrap_impl::readDefaultLongArray (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readDefaultLongArray)
  std::vector< int64_t > svec = opp->readDefaultLongArray(key);
  return BabelHelper::longVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readDefaultLongArray)
}

/**
 * Fetch the default for float-array-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::sidl::array<float>
ccaffeine::ports::ParameterPortWrap_impl::readDefaultFloatArray (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readDefaultFloatArray)
  std::vector< float > svec = opp->readDefaultFloatArray(key);
  return BabelHelper::floatVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readDefaultFloatArray)
}

/**
 * Fetch the default for double-array-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::sidl::array<double>
ccaffeine::ports::ParameterPortWrap_impl::readDefaultDoubleArray (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readDefaultDoubleArray)
  std::vector< double > svec = opp->readDefaultDoubleArray(key);
  return BabelHelper::doubleVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readDefaultDoubleArray)
}

/**
 * Fetch the default for fcomplex-array-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::sidl::array< ::sidl::fcomplex>
ccaffeine::ports::ParameterPortWrap_impl::readDefaultFcomplexArray (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readDefaultFcomplexArray)
  std::vector< std::complex< float> > svec = opp->readDefaultFcomplexArray(key);
  return BabelHelper::fcomplexVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readDefaultFcomplexArray)
}

/**
 * Fetch the default for dcomplex-array-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::sidl::array< ::sidl::dcomplex>
ccaffeine::ports::ParameterPortWrap_impl::readDefaultDcomplexArray (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readDefaultDcomplexArray)
  std::vector< std::complex< double > > svec = opp->readDefaultDcomplexArray(key);
  return BabelHelper::dcomplexVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readDefaultDcomplexArray)
}

/**
 * Fetch the bounds for integer-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
void
ccaffeine::ports::ParameterPortWrap_impl::readBoundsInt (
  /*in*/ const ::std::string& key,
  /*out*/ int32_t& low,
  /*out*/ int32_t& high ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readBoundsInt)
  opp->readBoundsInt(key,low,high);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readBoundsInt)
}

/**
 * Fetch the default for long-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
void
ccaffeine::ports::ParameterPortWrap_impl::readBoundsLong (
  /*in*/ const ::std::string& key,
  /*out*/ int64_t& low,
  /*out*/ int64_t& high ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readBoundsLong)
  opp->readBoundsLong(key,low,high);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readBoundsLong)
}

/**
 * Fetch the default for float-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
void
ccaffeine::ports::ParameterPortWrap_impl::readBoundsFloat (
  /*in*/ const ::std::string& key,
  /*out*/ float& low,
  /*out*/ float& high ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readBoundsFloat)
  opp->readBoundsFloat(key,low,high);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readBoundsFloat)
}

/**
 * Fetch the default for double-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
void
ccaffeine::ports::ParameterPortWrap_impl::readBoundsDouble (
  /*in*/ const ::std::string& key,
  /*out*/ double& low,
  /*out*/ double& high ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readBoundsDouble)
  opp->readBoundsDouble(key,low,high);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readBoundsDouble)
}

/**
 * Fetch the choices for string(-array)-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::sidl::array< ::std::string>
ccaffeine::ports::ParameterPortWrap_impl::readChoicesString (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readChoicesString)
  std::vector< std::string > svec = opp->readChoicesString(key);
  return BabelHelper::stringVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readChoicesString)
}

/**
 * Fetch the choices for integer(-array)-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::sidl::array<int32_t>
ccaffeine::ports::ParameterPortWrap_impl::readChoicesInt (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readChoicesInt)
  std::vector< int32_t > svec = opp->readChoicesInt(key);
  return BabelHelper::intVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readChoicesInt)
}

/**
 * Fetch the choices for long(-array)-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::sidl::array<int64_t>
ccaffeine::ports::ParameterPortWrap_impl::readChoicesLong (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readChoicesLong)
  std::vector< int64_t > svec = opp->readChoicesLong(key);
  return BabelHelper::longVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readChoicesLong)
}

/**
 * Fetch the choices for float(-array)-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::sidl::array<float>
ccaffeine::ports::ParameterPortWrap_impl::readChoicesFloat (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readChoicesFloat)
  std::vector< float > svec = opp->readChoicesFloat(key);
  return BabelHelper::floatVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readChoicesFloat)
}

/**
 * Fetch the default for double(-array)-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::sidl::array<double>
ccaffeine::ports::ParameterPortWrap_impl::readChoicesDouble (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readChoicesDouble)
  std::vector< double > svec = opp->readChoicesDouble(key);
  return BabelHelper::doubleVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readChoicesDouble)
}

/**
 * Fetch the default for fcomplex(-array)-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::sidl::array< ::sidl::fcomplex>
ccaffeine::ports::ParameterPortWrap_impl::readChoicesFcomplex (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readChoicesFcomplex)
  std::vector< std::complex< float> > svec = opp->readChoicesFcomplex(key);
  return BabelHelper::fcomplexVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readChoicesFcomplex)
}

/**
 * Fetch the default for dcomplex(-array)-typed key. 
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
::sidl::array< ::sidl::dcomplex>
ccaffeine::ports::ParameterPortWrap_impl::readChoicesDcomplex (
  /*in*/ const ::std::string& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap.readChoicesDcomplex)
  std::vector< std::complex< double > > svec = opp->readChoicesDcomplex(key);
  return BabelHelper::dcomplexVectorToSidlArray(svec);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap.readChoicesDcomplex)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap._misc)
// Put miscellaneous code here

void 
ccaffeine::ports::ParameterPortWrap_impl::checkthrow(const char *funcName)
{
  ccafe::BabelCCAHelpers::checkthrow("ccaffeine::ports::ParameterPortWrap_impl", "opp", static_cast<void *>(opp), funcName);
}

int ccaffeine_ports_ParameterPortWrap_qc(int argc, char *argv[])
{
  ::ccaffeine::ports::ParameterPortWrap_impl x();
  return 0;
}
#ifdef ccaffeine_ports_ParameterPortWrap_MAIN
int main(int argc, char **argv)
{
  return ccaffeine_ports_ParameterPortWrap_qc(argc,argv);
}
#endif
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap._misc)

