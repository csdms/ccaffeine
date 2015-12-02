// 
// File:          ccafe_eg_PortTranslatorStarter_Impl.hh
// Symbol:        ccafe_eg.PortTranslatorStarter-v0.1
// Symbol Type:   class
// Description:   Server-side implementation for ccafe_eg.PortTranslatorStarter
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccafe_eg_PortTranslatorStarter_Impl_hh
#define included_ccafe_eg_PortTranslatorStarter_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccafe_eg_PortTranslatorStarter_IOR_h
#include "ccafe_eg_PortTranslatorStarter_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_SIDL_BaseInterface_hh
#include "SIDL_BaseInterface.hh"
#endif
#ifndef included_SIDL_ClassInfo_hh
#include "SIDL_ClassInfo.hh"
#endif
#ifndef included_ccafe_eg_PortTranslatorStarter_hh
#include "ccafe_eg_PortTranslatorStarter.hh"
#endif
#ifndef included_gov_cca_Services_hh
#include "gov_cca_Services.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccafe_eg.PortTranslatorStarter._includes)
#include "cca.h"
#include "dc/babel/component/StringConsumerPort/server/ccafe3_StringConsumerPort.hh"
#include "dc/babel/babel-cca/server/ccaffeine_TypeMap.hh"
#include "gov_cca_ports_GoPort.hh"
#include "util/IO.h"
#include "parameters/parametersStar.h"
#include "port/portInterfaces.h"
#include "port/supportInterfaces.h"


// DO-NOT-DELETE splicer.end(ccafe_eg.PortTranslatorStarter._includes)

namespace ccafe_eg { 

  /**
   * Symbol "ccafe_eg.PortTranslatorStarter" (version 0.1)
   * 
   * When the GoPort is hit, use the StringConsumerPort to send a
   * string. 
   */
  class PortTranslatorStarter_impl
  // DO-NOT-DELETE splicer.begin(ccafe_eg.PortTranslatorStarter._inherits)

  // This is inheritance for dynamic parameters.
    : public virtual ParameterGetListener 

  // DO-NOT-DELETE splicer.end(ccafe_eg.PortTranslatorStarter._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    PortTranslatorStarter self;

    // DO-NOT-DELETE splicer.begin(ccafe_eg.PortTranslatorStarter._implementation)

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


    // DO-NOT-DELETE splicer.end(ccafe_eg.PortTranslatorStarter._implementation)

  private:
    // private default constructor (required)
    PortTranslatorStarter_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    PortTranslatorStarter_impl( struct ccafe_eg_PortTranslatorStarter__object * 
      s ) : self(s,true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~PortTranslatorStarter_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:


    /**
     * Execute some encapsulated functionality on the component. 
     * Return 0 if ok, -1 if internal error but component may be 
     * used further, and -2 if error so severe that component cannot
     * be further used safely.
     */
    int32_t
    go() throw () 
    ;

    /**
     * Obtain Services handle, through which the 
     * component communicates with the framework. 
     * This is the one method that every CCA Component
     * must implement. The component will be called
     * with a nil/null Services pointer when it is
     * to shut itself down.
     */
    void
    setServices (
      /*in*/ ::gov::cca::Services services
    )
    throw () 
    ;

  };  // end class PortTranslatorStarter_impl

} // end namespace ccafe_eg

// DO-NOT-DELETE splicer.begin(ccafe_eg.PortTranslatorStarter._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccafe_eg.PortTranslatorStarter._misc)

#endif
