// 
// File:          ccafe_eg_PortTranslatorStarter_Impl.hxx
// Symbol:        ccafe.eg.PortTranslatorStarter-v0.1
// Symbol Type:   class
// Description:   Server-side implementation for ccafe.eg.PortTranslatorStarter
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccafe_eg_PortTranslatorStarter_Impl_hxx
#define included_ccafe_eg_PortTranslatorStarter_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl_cxx.hxx"
#endif
#ifndef included_ccafe_eg_PortTranslatorStarter_IOR_h
#include "ccafe_eg_PortTranslatorStarter_IOR.h"
#endif
#ifndef included_ccafe_eg_PortTranslatorStarter_hxx
#include "ccafe_eg_PortTranslatorStarter.hxx"
#endif
#ifndef included_gov_cca_CCAException_hxx
#include "gov_cca_CCAException.hxx"
#endif
#ifndef included_gov_cca_Component_hxx
#include "gov_cca_Component.hxx"
#endif
#ifndef included_gov_cca_Services_hxx
#include "gov_cca_Services.hxx"
#endif
#ifndef included_gov_cca_ports_GoPort_hxx
#include "gov_cca_ports_GoPort.hxx"
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
#ifndef included_sidl_RuntimeException_hxx
#include "sidl_RuntimeException.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccafe.eg.PortTranslatorStarter._hincludes)
#include "cca.h"
#include "dc/babel.12/component/StringConsumerPort/server/ccafe3_StringConsumerPort.hxx"
#include "dc/babel.12/babel-cca/server/ccaffeine_TypeMap.hxx"
#include "gov_cca_ports_GoPort.hxx"
#include "util/IO.h"
#include "parameters/parametersStar.h"
#include "port/portInterfaces.h"
#include "port/supportInterfaces.h"


// DO-NOT-DELETE splicer.end(ccafe.eg.PortTranslatorStarter._hincludes)

namespace ccafe { 
  namespace eg { 

    /**
     * Symbol "ccafe.eg.PortTranslatorStarter" (version 0.1)
     * 
     *  When the GoPort is hit, use the StringConsumerPort to send a
     * string. 
     */
    class PortTranslatorStarter_impl : public virtual 
      ::ccafe::eg::PortTranslatorStarter 
  // DO-NOT-DELETE splicer.begin(ccafe.eg.PortTranslatorStarter._inherits)

  // This is inheritance for dynamic parameters.
    , public virtual ParameterGetListener 

  // DO-NOT-DELETE splicer.end(ccafe.eg.PortTranslatorStarter._inherits)
    {

    // All data marked protected will be accessable by 
    // descendant Impl classes
    protected:

    // DO-NOT-DELETE splicer.begin(ccafe.eg.PortTranslatorStarter._implementation)

    gov::cca::Services svc;

    // Parameters
    ConfigurableParameterPort *pp;
    StringParameter *prefix;
    BoolParameter *neo;
    BoolParameter *utest;
    DoubleParameter *dtest;
    StringParameter *anything;

    // Test to see if we have done the dynamic param test yet
    bool dynTestDone;
    
    // Extra private method:
    ConfigurableParameterPort * 
    setupParameters(ConfigurableParameterFactory *cpf);

    // extra public method
  public:

    bool updateParameterPort(ConfigurableParameterPort *opp);

  private:


    // DO-NOT-DELETE splicer.end(ccafe.eg.PortTranslatorStarter._implementation)

    public:
      // default constructor, used for data wrapping(required)
      PortTranslatorStarter_impl();
      // sidl constructor (required)
      // Note: alternate Skel constructor doesn't call addref()
      // (fixes bug #275)
      PortTranslatorStarter_impl( struct ccafe_eg_PortTranslatorStarter__object 
        * s ) : StubBase(s,true) { _ctor(); }

      // user defined construction
      void _ctor();

      // virtual destructor (required)
      virtual ~PortTranslatorStarter_impl() { _dtor(); }

      // user defined destruction
      void _dtor();

      // static class initializer
      static void _load();

    public:


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
      setServices_impl (
        /* in */::gov::cca::Services services
      )
      // throws:
      //     ::gov::cca::CCAException
      //     ::sidl::RuntimeException
      ;


      /**
       *  
       * Execute some encapsulated functionality on the component. 
       * Return 0 if ok, -1 if internal error but component may be 
       * used further, and -2 if error so severe that component cannot
       * be further used safely.
       */
      int32_t
      go_impl() ;
    };  // end class PortTranslatorStarter_impl

  } // end namespace eg
} // end namespace ccafe

// DO-NOT-DELETE splicer.begin(ccafe.eg.PortTranslatorStarter._hmisc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccafe.eg.PortTranslatorStarter._hmisc)

#endif
