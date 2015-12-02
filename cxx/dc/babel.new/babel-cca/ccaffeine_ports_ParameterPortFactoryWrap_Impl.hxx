// 
// File:          ccaffeine_ports_ParameterPortFactoryWrap_Impl.hxx
// Symbol:        ccaffeine.ports.ParameterPortFactoryWrap-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ports.ParameterPortFactoryWrap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_ports_ParameterPortFactoryWrap_Impl_hxx
#define included_ccaffeine_ports_ParameterPortFactoryWrap_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_ports_ParameterPortFactoryWrap_IOR_h
#include "ccaffeine_ports_ParameterPortFactoryWrap_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_sidl_BaseInterface_hxx
#include "SIDL_BaseInterface.hh"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "SIDL_ClassInfo.hh"
#endif
#ifndef included_ccaffeine_ports_ParameterPortFactoryWrap_hxx
#include "ccaffeine_ports_ParameterPortFactoryWrap.hxx"
#endif
#ifndef included_gov_cca_CCAException_hxx
#include "gov_cca_CCAException.hxx"
#endif
#ifndef included_gov_cca_Services_hxx
#include "gov_cca_Services.hxx"
#endif
#ifndef included_gov_cca_TypeMap_hxx
#include "gov_cca_TypeMap.hxx"
#endif
#ifndef included_gov_cca_ports_ParameterGetListener_hxx
#include "gov_cca_ports_ParameterGetListener.hxx"
#endif
#ifndef included_gov_cca_ports_ParameterSetListener_hxx
#include "gov_cca_ports_ParameterSetListener.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap._includes)
// Put additional includes or other arbitrary code here...
#include "dc/export/AllExport.hh"
#include "AllCCA.hh"
#include "dc/babel.new/babel-cca/AllBabelCCA.hxx"
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap._includes)

namespace ccaffeine { 
  namespace ports { 

    /**
     * Symbol "ccaffeine.ports.ParameterPortFactoryWrap" (version 0.3)
     * 
     * ccaffeine implementation of cca standard. 
     */
    class ParameterPortFactoryWrap_impl
    // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap._inherits)
    // Put additional inheritance here...
    // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap._inherits)
    {

    private:
      // Pointer back to IOR.
      // Use this to dispatch back through IOR vtable.
      ParameterPortFactoryWrap self;

      // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap._implementation)
      
      ::ccafeopq::ports::ParameterPortFactory *oppf;
      int serial;
      static int nextNum() { genSerial++; return genSerial; }
      static int genSerial;
      void checkthrow(const char *funcName);
      template <class Scalar > ::std::vector< Scalar >
        convertToVector( sidl::array< Scalar > & val );

      // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap._implementation)

    private:
      // private default constructor (required)
      ParameterPortFactoryWrap_impl() {} 

    public:
      // SIDL constructor (required)
      // Note: alternate Skel constructor doesn't call addref()
      // (fixes bug #275)
      ParameterPortFactoryWrap_impl( struct 
        ccaffeine_ports_ParameterPortFactoryWrap__object * s ) : self(s,
        true) { _ctor(); }

      // user defined construction
      void _ctor();

      // virtual destructor (required)
      virtual ~ParameterPortFactoryWrap_impl() { _dtor(); }

      // user defined destruction
      void _dtor();

    public:


      /**
       * passed in is a void * cast pointer of
       *  ccafeopq::ports::ParameterPortFactory *.
       */
      void
      initialize (
        /*in*/ void* ccafeopq_ports_ParameterPortFactory_star
      )
      throw () 
      ;


      /**
       * fetch up a pointer for static casting. if the name
       * supplied is not exactly right, returns null.
       */
      void*
      getWrapped (
        /*in*/ const ::std::string& className
      )
      throw () 
      ;


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
      initParameterData (
        /*inout*/ ::gov::cca::TypeMap& portData,
        /*in*/ const ::std::string& portName
      )
      throw () 
      ;


      /**
       * Define the window title for the parameter UI dialog.
       * 
       */
      void
      setBatchTitle (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& title
      )
      throw () 
      ;


      /**
       * Define the next tab/group title to use. All
       * addRequest subsequent calls will add to this group.
       * Multiple dialog tabs/groups can be defined in this way.
       * @param newGroupName a one-word name for the group.
       * @param groupTitle an optional title for the group.
       */
      void
      setGroupName (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& newGroupName
      )
      throw () 
      ;

      /**
       * user defined non-static method.
       */
      void
      setGroupName (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& newGroupName,
        /*in*/ const ::std::string& groupTitle
      )
      throw () 
      ;


      /**
       * Define a boolean parameter and its default state.
       * The configured value is always available by
       * portData.getBool(name, ...);
       * @throws gov.cca.CCAException if key is known and mistyped.
       */
      void
      addRequestBoolean (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& name,
        /*in*/ const ::std::string& help,
        /*in*/ const ::std::string& prompt,
        /*in*/ bool bdefault
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Define a int parameter and its default state.
       * The configured value is always available by
       * portData.getInt(name, ...) and it will be
       * in the range [low, high]. The initially given bounds
       * can be replaced with a choice list later.
       * @throws gov.cca.CCAException if key is known and mistyped.
       */
      void
      addRequestInt (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& name,
        /*in*/ const ::std::string& help,
        /*in*/ const ::std::string& prompt,
        /*in*/ int32_t idefault,
        /*in*/ int32_t low,
        /*in*/ int32_t high
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Define a long parameter and its default state.
       * The configured value is always available by
       * portData.getLong(name, ...) and it will be
       * in the range [low, high]. The initially given bounds
       * can be replaced with a choice list later.
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      void
      addRequestLong (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& name,
        /*in*/ const ::std::string& help,
        /*in*/ const ::std::string& prompt,
        /*in*/ int64_t ldefault,
        /*in*/ int64_t low,
        /*in*/ int64_t high
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Define a float parameter and its default state.
       * The configured value is always available by
       * portData.getFloat(name, ...) and it will be
       * in the range [low, high]. The initially given bounds
       * can be replaced with a choice list later.
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      void
      addRequestFloat (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& name,
        /*in*/ const ::std::string& help,
        /*in*/ const ::std::string& prompt,
        /*in*/ float fdefault,
        /*in*/ float low,
        /*in*/ float high
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Define a double parameter and its default state.
       * The configured value is always available by
       * portData.getDouble(name, ...) and it will be
       * in the range [low, high]. The initially given bounds
       * can be replaced with a choice list later.
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      void
      addRequestDouble (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& name,
        /*in*/ const ::std::string& help,
        /*in*/ const ::std::string& prompt,
        /*in*/ double ddefault,
        /*in*/ double low,
        /*in*/ double high
      )
      throw ( 
        ::gov::cca::CCAException
      );


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
      addRequestString (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& name,
        /*in*/ const ::std::string& help,
        /*in*/ const ::std::string& prompt,
        /*in*/ const ::std::string& sdefault
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Define a new choice for a string parameter.
       *  If no calls to this function are made for a given
       *  name, then any form of string will be acceptable input.
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      void
      addRequestStringChoice (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& key,
        /*in*/ const ::std::string& choice
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * As addRequestStringChoice, but in bulk. 
       */
      void
      addStringChoices (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& name,
        /*in*/ ::sidl::array< ::std::string> choices
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Replace the bounds on the named parameter by a list. 
       */
      void
      addIntChoices (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& name,
        /*in*/ ::sidl::array<int32_t> choices
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Replace the bounds on the named parameter by a list. 
       */
      void
      addLongChoices (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& name,
        /*in*/ ::sidl::array<int64_t> choices
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Replace the bounds on the named parameter by a list. 
       */
      void
      addFloatChoices (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& name,
        /*in*/ ::sidl::array<float> choices
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Replace the bounds on the named parameter by a list. 
       */
      void
      addDoubleChoices (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& name,
        /*in*/ ::sidl::array<double> choices
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Replace the bounds on the named parameter by a list. 
       */
      void
      addFcomplexChoices (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& name,
        /*in*/ ::sidl::array< ::sidl::fcomplex> choices
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Replace the bounds on the named parameter by a list. 
       */
      void
      addDcomplexChoices (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ const ::std::string& name,
        /*in*/ ::sidl::array< ::sidl::dcomplex> choices
      )
      throw ( 
        ::gov::cca::CCAException
      );


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
      clearRequests (
        /*in*/ ::gov::cca::TypeMap portData
      )
      throw () 
      ;


      /**
       * Register listener (the component) that wishes to have
       * a chance to change the contents of its ParameterPort
       * just before the parameters TypeMap is read.
       * @param powner a pointer to the listener that will be
       * forgotten when it is no longer needed. 
       */
      void
      registerUpdater (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ ::gov::cca::ports::ParameterGetListener powner
      )
      throw () 
      ;


      /**
       * Register listener (the component) if it wishes to be
       * informed when an parameter is changed via writeConfigurationMap.
       * Listeners are called after values are set.
       */
      void
      registerUpdatedListener (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ ::gov::cca::ports::ParameterSetListener powner
      )
      throw () 
      ;


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
      addParameterPort (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ ::gov::cca::Services svc
      )
      throw () 
      ;


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
      removeParameterPort (
        /*in*/ ::gov::cca::TypeMap portData,
        /*in*/ ::gov::cca::Services svc
      )
      throw () 
      ;

    };  // end class ParameterPortFactoryWrap_impl

  } // end namespace ports
} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortFactoryWrap._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortFactoryWrap._misc)

#endif
