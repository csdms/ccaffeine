// 
// File:          mpitest_script_babel_BabelMain_Impl.hh
// Symbol:        mpitest_script_babel.BabelMain-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for mpitest_script_babel.BabelMain
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_mpitest_script_babel_BabelMain_Impl_hh
#define included_mpitest_script_babel_BabelMain_Impl_hh

#ifndef included_sidl_cxx_hh
#include "sidl_cxx.hh"
#endif
#ifndef included_mpitest_script_babel_BabelMain_IOR_h
#include "mpitest_script_babel_BabelMain_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_gov_cca_AbstractFramework_hh
#include "gov_cca_AbstractFramework.hh"
#endif
#ifndef included_gov_cca_ComponentID_hh
#include "gov_cca_ComponentID.hh"
#endif
#ifndef included_gov_cca_Services_hh
#include "gov_cca_Services.hh"
#endif
#ifndef included_gov_cca_ports_BuilderService_hh
#include "gov_cca_ports_BuilderService.hh"
#endif
#ifndef included_mpitest_script_babel_BabelMain_hh
#include "mpitest_script_babel_BabelMain.hh"
#endif
#ifndef included_mpitest_script_babel_StringMap_hh
#include "mpitest_script_babel_StringMap.hh"
#endif
#ifndef included_sidl_BaseInterface_hh
#include "sidl_BaseInterface.hh"
#endif
#ifndef included_sidl_ClassInfo_hh
#include "sidl_ClassInfo.hh"
#endif


// DO-NOT-DELETE splicer.begin(mpitest_script_babel.BabelMain._includes)
#include <map>
#include <string>
// DO-NOT-DELETE splicer.end(mpitest_script_babel.BabelMain._includes)

namespace mpitest_script_babel { 

  /**
   * Symbol "mpitest_script_babel.BabelMain" (version 0.0)
   */
  class BabelMain_impl
  // DO-NOT-DELETE splicer.begin(mpitest_script_babel.BabelMain._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(mpitest_script_babel.BabelMain._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    BabelMain self;

    // DO-NOT-DELETE splicer.begin(mpitest_script_babel.BabelMain._implementation)
    
    /** stl - babel converter */
    void
    setParamsFromString(gov::cca::TypeMap & tm, std::map< std::string, std::string > & values);

    /* not used just yet */
    // ::gov::cca::Type typeFromString( const ::std::string &typeName);
    
    /** set key with type t from string value v on tm */
    void transformString(const ::std::string & key,
			    ::gov::cca::Type dt,
			    const ::std::string & v, ::gov::cca::TypeMap & tm);

    /** get string value for key in t */
    ::std::string stringValue( ::gov::cca::TypeMap t, const ::std::string &key) ;
    

    // DO-NOT-DELETE splicer.end(mpitest_script_babel.BabelMain._implementation)

  private:
    // private default constructor (required)
    BabelMain_impl() 
    {} 

  public:
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    BabelMain_impl( struct mpitest_script_babel_BabelMain__object * s ) : 
      self(s,true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~BabelMain_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

    // static class initializer
    static void _load();

  public:

    /**
     * user defined non-static method.
     */
    int32_t
    invokeGo (
      /* in */ const ::std::string& component,
      /* in */ const ::std::string& port,
      /* in */ ::gov::cca::ComponentID c,
      /* in */ ::gov::cca::Services services,
      /* in */ ::gov::cca::ports::BuilderService bs
    )
    throw () 
    ;


    /**
     * This function handles the configuring of 
     * parameters when all we know is the
     * info available from a ccaffeine script (which hides 
     * parameter and port types).
     * If component port and config information were 
     * ubiquitous at code generation time, this wouldn't be needed.
     * @param compName name of the component being configured.
     * @param port name of the port being configured.
     * @param comp ComponentID of the component being configured.
     * @param bs BuilderService controlling the frame.
     * @param services Services of the component/driver 
     * doing the parameter setting.
     * @param values  map of keys and values to assign.
     */
    void
    setParameters (
      /* in */ const ::std::string& component,
      /* in */ const ::std::string& port,
      /* in */ ::gov::cca::ComponentID c,
      /* in */ ::gov::cca::ports::BuilderService bs,
      /* in */ ::gov::cca::Services services,
      /* in */ ::mpitest_script_babel::StringMap sm
    )
    throw () 
    ;


    /**
     * This function returns a stringified version of a parameter value.
     */
    ::std::string
    getParameterValue (
      /* in */ ::gov::cca::ComponentID c,
      /* in */ const ::std::string& portName,
      /* in */ const ::std::string& var,
      /* in */ ::gov::cca::Services services,
      /* in */ ::gov::cca::ports::BuilderService bs
    )
    throw () 
    ;

    /**
     * user defined non-static method.
     */
    void
    driverBody (
      /* inout */ ::gov::cca::AbstractFramework& af
    )
    throw () 
    ;

  };  // end class BabelMain_impl

} // end namespace mpitest_script_babel

// DO-NOT-DELETE splicer.begin(mpitest_script_babel.BabelMain._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(mpitest_script_babel.BabelMain._misc)

#endif
