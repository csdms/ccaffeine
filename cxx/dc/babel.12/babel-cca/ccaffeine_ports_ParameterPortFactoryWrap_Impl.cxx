// 
// File:          ccaffeine_ports_ParameterPortFactoryWrap_Impl.cc
// Symbol:        ccaffeine.ports.ParameterPortFactoryWrap-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ports.ParameterPortFactoryWrap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_ports_ParameterPortFactoryWrap_Impl.hxx"

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap._includes)
// Put additional includes or other arbitrary code here...
#include "dc/babel.12/babel-cca/BabelCCAHelpers.hxx"
#include "dc/babel.12/ccafe-bind/AllCcafeBind.hh"
#include "ccaffeine_TypeMap_Impl.hxx"

int ccaffeine::ports::ParameterPortFactoryWrap_impl::genSerial = 0;
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap._includes)

// user defined constructor
void ccaffeine::ports::ParameterPortFactoryWrap_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap._ctor)
  // add construction details here
  oppf = 0;
#ifdef CCAFE_AUDIT
  serial = nextNum();
  IO_dn2("ccaffeine::ports::ParameterPortFactoryWrap_impl _ctor %d", serial);
#endif
 

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap._ctor)
}

// user defined destructor
void ccaffeine::ports::ParameterPortFactoryWrap_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap._dtor)
  // add destruction details here
#ifdef CCAFE_AUDIT
  serial = -serial;
  IO_dn2("ccaffeine::ports::ParameterPortFactoryWrap_impl _dtor %d", serial);
#endif
  oppf = 0;

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * passed in is a void * cast pointer of
 *  ccafeopq::ports::ParameterPortFactory *.
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::initialize (
  /*in*/ void* ccafeopq_ports_ParameterPortFactory_star ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.initialize)
  // insert implementation here
#ifdef CCAFE_AUDIT
  IO_dn2("ccaffeine::ports::ParameterPortFactoryWrap_impl init %d", serial);
  if (co_p_ParameterPortFactory_star == 0) {
    IO_dn1("ccaffeine::ports::ParameterPortFactoryWrap_impl init given null.");
  }
#endif
  oppf =
    static_cast< ::ccafeopq::ports::ParameterPortFactory *>(co_p_ParameterPortFactory_star);

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.initialize)
}

/**
 * fetch up a pointer for static casting. if the name
 * supplied is not exactly right, returns null.
 */
void*
ccaffeine::ports::ParameterPortFactoryWrap_impl::getWrapped (
  /*in*/ const ::std::string& className ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.getWrapped)
  // insert implementation here
  if (className == "::ccafeopq::ports::ParameterPortFactory")
  {
    return oppf;
  } 
  return 0;
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.getWrapped)
}

/**
 * Initialize the portData for use in a ParameterPort
 *  with name portName.
 *  More than one such port can be defined.
 *  The given string portName will be cached in the TypeMap
 *  as the result of this function and must not be changed
 *  by the component henceforth.
 *  
 *  @param portData the user-supplied TypeMap associated with the port;
 *       It is somehow shared between the ParameterPortFactory
 *       and the component. The ParameterPortFactory will
 *       not read or change preexisting values in portData except those
 *       requested via the addRequest functions and those
 *       keys starting with the reserved prefix "gcpPPF.".
 *  @param portName The name of the ParameterPort to appear in
 *       the component. It must not conflict with other port
 *       names in the same component. The port name "CONFIG"
 *       is recommended if only one ParameterPort is being defined.
 *  
 * 
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::initParameterData (
  /*inout*/ ::gov::cca::TypeMap& portData,
  /*in*/ const ::std::string& portName ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.initParameterData)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  oppf->createParameterPort(ctm, portName);
  oppf->setBatchTitle(ctm, portName);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.initParameterData)
}

/**
 * Define the window title for the parameter UI dialog.
 * 
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::setBatchTitle (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& title ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.setBatchTitle)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  oppf->setBatchTitle(ctm, title);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.setBatchTitle)
}

/**
 * Define the next tab/group title to use. All
 * addRequest subsequent calls will add to this group.
 * Multiple dialog tabs/groups can be defined in this way.
 * @param newGroupName a one-word name for the group.
 * @param groupTitle an optional title for the group.
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::setGroupName (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& newGroupName ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.setGroupName)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  oppf->setGroupName(ctm, newGroupName);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.setGroupName)
}

/**
 * Method:  setGroupName[AndTitle]
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::setGroupName (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& newGroupName,
  /*in*/ const ::std::string& groupTitle ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.setGroupNameAndTitle)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  oppf->setGroupNameAndTitle(ctm, newGroupName, groupTitle);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.setGroupNameAndTitle)
}

/**
 * Define a boolean parameter and its default state.
 * The configured value is always available by
 * portData.getBool(name, ...);
 * @throws gov.cca.CCAException if key is known and mistyped.
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::addRequestBoolean (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& name,
  /*in*/ const ::std::string& help,
  /*in*/ const ::std::string& prompt,
  /*in*/ bool bdefault ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.addRequestBoolean)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  oppf->addRequestBoolean(ctm, name, help, prompt, bdefault);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.addRequestBoolean)
}

/**
 * Define a int parameter and its default state.
 * The configured value is always available by
 * portData.getInt(name, ...) and it will be
 * in the range [low, high]. The initially given bounds
 * can be replaced with a choice list later.
 * @throws gov.cca.CCAException if key is known and mistyped.
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::addRequestInt (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& name,
  /*in*/ const ::std::string& help,
  /*in*/ const ::std::string& prompt,
  /*in*/ int32_t idefault,
  /*in*/ int32_t low,
  /*in*/ int32_t high ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.addRequestInt)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  oppf->addRequestInt(ctm, name, help, prompt, idefault, low, high);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.addRequestInt)
}

/**
 * Define a long parameter and its default state.
 * The configured value is always available by
 * portData.getLong(name, ...) and it will be
 * in the range [low, high]. The initially given bounds
 * can be replaced with a choice list later.
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::addRequestLong (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& name,
  /*in*/ const ::std::string& help,
  /*in*/ const ::std::string& prompt,
  /*in*/ int64_t ldefault,
  /*in*/ int64_t low,
  /*in*/ int64_t high ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.addRequestLong)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  oppf->addRequestLong(ctm, name, help, prompt, ldefault, low, high);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.addRequestLong)
}

/**
 * Define a float parameter and its default state.
 * The configured value is always available by
 * portData.getFloat(name, ...) and it will be
 * in the range [low, high]. The initially given bounds
 * can be replaced with a choice list later.
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::addRequestFloat (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& name,
  /*in*/ const ::std::string& help,
  /*in*/ const ::std::string& prompt,
  /*in*/ float fdefault,
  /*in*/ float low,
  /*in*/ float high ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.addRequestFloat)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  oppf->addRequestFloat(ctm, name, help, prompt, fdefault, low, high);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.addRequestFloat)
}

/**
 * Define a double parameter and its default state.
 * The configured value is always available by
 * portData.getDouble(name, ...) and it will be
 * in the range [low, high]. The initially given bounds
 * can be replaced with a choice list later.
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::addRequestDouble (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& name,
  /*in*/ const ::std::string& help,
  /*in*/ const ::std::string& prompt,
  /*in*/ double ddefault,
  /*in*/ double low,
  /*in*/ double high ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.addRequestDouble)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  oppf->addRequestDouble(ctm, name, help, prompt, ddefault, low, high);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.addRequestDouble)
}

/**
 * Define a string parameter and its default state.
 * The configured value is always available by
 * portData.getString(name, ...).
 * If no addRequestStringChoice calls are made, the
 * user input may be any string. If addRequestStringChoice
 * is used, the value will be one among the choices.
 * If addRequestStringChoice is used, deflt must
 * be among the choices defined.
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::addRequestString (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& name,
  /*in*/ const ::std::string& help,
  /*in*/ const ::std::string& prompt,
  /*in*/ const ::std::string& sdefault ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.addRequestString)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  oppf->addRequestString(ctm, name, help, prompt, sdefault);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.addRequestString)
}

/**
 * Define a new choice for a string parameter.
 *  If no calls to this function are made for a given
 *  name, then any form of string will be acceptable input.
 * @throws gov.cca.CCAException if key is unknown or mistyped.
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::addRequestStringChoice (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& key,
  /*in*/ const ::std::string& choice ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.addRequestStringChoice)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  oppf->addRequestStringChoice(ctm, key, choice);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.addRequestStringChoice)
}

/**
 * As addRequestStringChoice, but in bulk. 
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::addStringChoices (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& name,
  /*in*/ ::sidl::array< ::std::string> choices ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.addStringChoices)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  std::vector< ::std::string> ochoices = convertToVector(choices);
  oppf->addStringChoices(ctm , name, ochoices);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.addStringChoices)
}

/**
 * Replace the bounds on the named parameter by a list. 
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::addIntChoices (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& name,
  /*in*/ ::sidl::array<int32_t> choices ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.addIntChoices)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  std::vector< int32_t > ochoices = convertToVector(choices);
  oppf->addIntChoices(ctm, name, ochoices);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.addIntChoices)
}

/**
 * Replace the bounds on the named parameter by a list. 
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::addLongChoices (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& name,
  /*in*/ ::sidl::array<int64_t> choices ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.addLongChoices)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  std::vector< int64_t > ochoices = convertToVector(choices);
  oppf->addLongChoices(ctm, name, ochoices);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.addLongChoices)
}

/**
 * Replace the bounds on the named parameter by a list. 
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::addFloatChoices (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& name,
  /*in*/ ::sidl::array<float> choices ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.addFloatChoices)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  std::vector< float > ochoices = convertToVector(choices);
  oppf->addFloatChoices(ctm, name, ochoices);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.addFloatChoices)
}

/**
 * Replace the bounds on the named parameter by a list. 
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::addDoubleChoices (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& name,
  /*in*/ ::sidl::array<double> choices ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.addDoubleChoices)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  std::vector< double > ochoices = convertToVector(choices);
  oppf->addDoubleChoices(ctm, name, ochoices);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.addDoubleChoices)
}

/**
 * Replace the bounds on the named parameter by a list. 
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::addFcomplexChoices (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& name,
  /*in*/ ::sidl::array< ::sidl::fcomplex> choices ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.addFcomplexChoices)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  std::vector< std::complex< float > > ochoices = convertToVector(choices);
  oppf->addFcomplexChoices(ctm, name, ochoices);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.addFcomplexChoices)
}

/**
 * Replace the bounds on the named parameter by a list. 
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::addDcomplexChoices (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ const ::std::string& name,
  /*in*/ ::sidl::array< ::sidl::dcomplex> choices ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.addDcomplexChoices)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  std::vector< std::complex< double > > ochoices = convertToVector(choices);
  oppf->addDcomplexChoices(ctm, name, ochoices);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.addDcomplexChoices)
}

/**
 * Clear all previously added requests, titles, groups. After
 *  this call, it is as if the ParameterPort has
 *  seen initParameterData but otherwise never configured.
 *  The values of
 *  previously defined parameters (but not bounds, etc)
 *  remain in the TypeMap.
 *  Typically, this is used only by someone implementing
 *  the updateParameterPort function from
 *  interface ParameterGetListener.
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::clearRequests (
  /*in*/ ::gov::cca::TypeMap portData ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.clearRequests)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  oppf->clearRequests(ctm);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.clearRequests)
}

/**
 * Register listener (the component) that wishes to have
 * a chance to change the contents of its ParameterPort
 * just before the parameters TypeMap is read.
 * @param powner a pointer to the listener that will be
 * forgotten when it is no longer needed. 
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::registerUpdater (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ ::gov::cca::ports::ParameterGetListener powner ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.registerUpdater)
  // insert implementation here
	// FIXME  registerUpdater
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.registerUpdater)
}

/**
 * Register listener (the component) if it wishes to be
 * informed when an parameter is changed via writeConfigurationMap.
 * Listeners are called after values are set.
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::registerUpdatedListener (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ ::gov::cca::ports::ParameterSetListener powner ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.registerUpdatedListener)
  // insert implementation here
	// FIXME  registerUpdatedListener
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.registerUpdatedListener)
}

/**
 * Signal that the ParameterPort is fully defined and should
 * now pop out on the component.
 * The component is free to hold the portData map internally
 * without adding it until some desired time.
 * The Services passed here
 * must be the component's own Services handle.
 * The ParameterPortFactory takes care of addProvidesPort.
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::addParameterPort (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ ::gov::cca::Services services ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.addParameterPort)
#ifdef CCAFE_AUDIT
  IO_dn2("ccaffeine::ports::ParameterPortFactoryWrap_impl: addPP %d", serial);
#endif
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );

  if ( services.isType("ccaffeine.Services") ) {
#ifdef CCAFE_AUDIT
  IO_dn1("ccaffeine::ports::ParameterPortFactoryWrap_impl: addPP cS ok");
#endif
    
    ccaffeine::Services cs = ::babel_cast<ccaffeine::Services> (services); // CAST
    void * vos = cs.getWrapped("::ccafeopq::Services");
#ifdef CCAFE_AUDIT
    if (vos == 0) {
      IO_dn1("ccaffeine::ports::ParameterPortFactoryWrap_impl: svcs core is null. BAD");
      return;
    } else {
      IO_dn1("ccaffeine::ports::ParameterPortFactoryWrap_impl: got vos ok.");
    }
    if (oppf == 0) {
      IO_dn1("ccaffeine::ports::ParameterPortFactoryWrap_impl: no oppf. BAD!");
      return;
    }
#endif
    ::ccafeopq::Services * os = 0;
    os = static_cast< ::ccafeopq::Services * >(vos);
    oppf->addParameterPort(ctm, os);
  } 

#ifdef CCAFE_AUDIT
  else {
    IO_dn1("ccaffeine::ports::ParameterPortFactoryWrap_impl: BAD cS. not added");
  }
#endif

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.addParameterPort)
}

/**
 * Cause a previously defined parameter port to go away.
 * This function should be called at component shutdown
 * (setService(0)) time for any parameter ports that have
 * been added but not yet removed.
 * The ParameterPortFactory takes care of removeProvidesPort.
 * This does not change the parameter values in the
 * TypeMap.
 */
void
ccaffeine::ports::ParameterPortFactoryWrap_impl::removeParameterPort (
  /*in*/ ::gov::cca::TypeMap portData,
  /*in*/ ::gov::cca::Services services ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap.removeParameterPort)
  ::ccafeopq::TypeMap_shared ctm =
    BabelOpaqueTypeMap_Interface::opaqueWrap( portData );
  if (services.isType("ccaffeine.Services") ) {
    ccaffeine::Services cs = ::babel_cast<ccaffeine::Services> (services); // CAST
    void * vos = cs.getWrapped("ccaffeine.Services");
    ::ccafeopq::Services * os = 0;
    os = static_cast< ::ccafeopq::Services * >(vos);
    oppf->removeParameterPort(ctm, os);
  }
  // FIXME removeParameterPort need whinage
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap.removeParameterPort)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap._misc)
// Put miscellaneous code here
void 
ccaffeine::ports::ParameterPortFactoryWrap_impl::checkthrow(const char *funcName)
{
  ccafe::BabelCCAHelpers::checkthrow("ccaffeine::ports::ParameterPortFactoryWrap_impl", "oppf", static_cast<void *>(oppf), funcName);
}

template <class Scalar >
::std::vector< Scalar > ccaffeine::ports::ParameterPortFactoryWrap_impl::convertToVector( sidl::array< Scalar > & val )
{
  int len = (val.upper(0) - val.lower(0)) + 1;
  ::std::vector< Scalar > res(len);
  int bottom = val.lower(0);
  for(int i=0; i < len ; i++) {
    res[i] = ( val.get(bottom + i) );
  }
  return res;
}


// DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap._misc)

