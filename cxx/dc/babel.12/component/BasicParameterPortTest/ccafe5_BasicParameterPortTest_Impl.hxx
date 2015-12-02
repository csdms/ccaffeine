// 
// File:          ccafe5_BasicParameterPortTest_Impl.hxx
// Symbol:        ccafe5.BasicParameterPortTest-v0.0
// Symbol Type:   class
// Babel Version: 1.0.6
// Description:   Server-side implementation for ccafe5.BasicParameterPortTest
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccafe5_BasicParameterPortTest_Impl_hxx
#define included_ccafe5_BasicParameterPortTest_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl_cxx.hxx"
#endif
#ifndef included_ccafe5_BasicParameterPortTest_IOR_h
#include "ccafe5_BasicParameterPortTest_IOR.h"
#endif
#ifndef included_ccafe5_BasicParameterPortTest_hxx
#include "ccafe5_BasicParameterPortTest.hxx"
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
#ifndef included_gov_cca_TypeMap_hxx
#include "gov_cca_TypeMap.hxx"
#endif
#ifndef included_gov_cca_ports_BasicParameterPort_hxx
#include "gov_cca_ports_BasicParameterPort.hxx"
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


// DO-NOT-DELETE splicer.begin(ccafe5.BasicParameterPortTest._hincludes)

#include "dc/babel.12/babel-cca/server/ccaffeine_TypeMap.hxx"
#include "gov_cca_ports_GoPort.hxx"
#include "util/IO.h"
// arg FIXME
#include "gov_cca.hxx"

// DO-NOT-DELETE splicer.end(ccafe5.BasicParameterPortTest._hincludes)

namespace ccafe5 { 

  /**
   * Symbol "ccafe5.BasicParameterPortTest" (version 0.0)
   * 
   *  When the GoPort is hit, test bpp. 
   */
  class BasicParameterPortTest_impl : public virtual 
    ::ccafe5::BasicParameterPortTest 
  // DO-NOT-DELETE splicer.begin(ccafe5.BasicParameterPortTest._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccafe5.BasicParameterPortTest._inherits)
  {

  // All data marked protected will be accessable by 
  // descendant Impl classes
  protected:

    bool _wrapped;

    // DO-NOT-DELETE splicer.begin(ccafe5.BasicParameterPortTest._implementation)

    gov::cca::Services svc; 

    gov::cca::TypeMap parms;

    // DO-NOT-DELETE splicer.end(ccafe5.BasicParameterPortTest._implementation)

  public:
    // default constructor, used for data wrapping(required)
    BasicParameterPortTest_impl();
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    BasicParameterPortTest_impl( struct ccafe5_BasicParameterPortTest__object * 
      s ) : StubBase(s,true), _wrapped(false) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~BasicParameterPortTest_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

    // true if this object was created by a user newing the impl
    inline bool _isWrapped() {return _wrapped;}

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
     *  Return a TypeMap of runtime configuration parameters. 
     * It is recommended that the map returned be a clone/copy of the
     * a privately held map, not a shared object reference.
     */
    ::gov::cca::TypeMap
    readConfigurationMap_impl() // throws:
    //     ::gov::cca::CCAException
    //     ::sidl::RuntimeException
    ;

    /**
     *  Copy the parameter values given in map into the
     * internal map, for those parameters which
     * are already defined by the internal map.
     * The outsider does not get to cause arbitrary
     * keys to be copied into the internal map.
     * @throws gov.cca.CCAException if TypeMap operations fail.
     */
    void
    writeConfigurationMap_impl (
      /* in */::gov::cca::TypeMap map
    )
    // throws:
    //     ::gov::cca::CCAException
    //     ::sidl::RuntimeException
    ;


    /**
     *  Fetch the list of keys in the TypeMap that are
     * for public configuration purposes. Other values found in
     * the TypeMap must not be changed.
     */
    ::sidl::array< ::std::string>
    readConfigurationKeys_impl() ;
  };  // end class BasicParameterPortTest_impl

} // end namespace ccafe5

// DO-NOT-DELETE splicer.begin(ccafe5.BasicParameterPortTest._hmisc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccafe5.BasicParameterPortTest._hmisc)

#endif
