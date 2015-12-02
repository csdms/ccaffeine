// 
// File:          TestScriptBabel_BabelMain_Impl.hxx
// Symbol:        TestScriptBabel.BabelMain-v0.0
// Symbol Type:   class
// Babel Version: 1.0.0
// Description:   Server-side implementation for TestScriptBabel.BabelMain
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_TestScriptBabel_BabelMain_Impl_hxx
#define included_TestScriptBabel_BabelMain_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl_cxx.hxx"
#endif
#ifndef included_TestScriptBabel_BabelMain_IOR_h
#include "TestScriptBabel_BabelMain_IOR.h"
#endif
#ifndef included_TestScriptBabel_BabelMain_hxx
#include "TestScriptBabel_BabelMain.hxx"
#endif
#ifndef included_TestScriptBabel_StringMap_hxx
#include "TestScriptBabel_StringMap.hxx"
#endif
#ifndef included_ccaffeine_BabelMain_hxx
#include "ccaffeine_BabelMain.hxx"
#endif
#ifndef included_gov_cca_AbstractFramework_hxx
#include "gov_cca_AbstractFramework.hxx"
#endif
#ifndef included_gov_cca_ComponentID_hxx
#include "gov_cca_ComponentID.hxx"
#endif
#ifndef included_gov_cca_Services_hxx
#include "gov_cca_Services.hxx"
#endif
#ifndef included_gov_cca_ports_BuilderService_hxx
#include "gov_cca_ports_BuilderService.hxx"
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


// DO-NOT-DELETE splicer.begin(TestScriptBabel.BabelMain._includes)
#include <map>
#include <string>
// DO-NOT-DELETE splicer.end(TestScriptBabel.BabelMain._includes)

namespace TestScriptBabel { 

  /**
   * Symbol "TestScriptBabel.BabelMain" (version 0.0)
   */
  class BabelMain_impl : public virtual ::TestScriptBabel::BabelMain 
  // DO-NOT-DELETE splicer.begin(TestScriptBabel.BabelMain._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(TestScriptBabel.BabelMain._inherits)
  {

  // All data marked protected will be accessable by 
  // descendant Impl classes
  protected:

    bool _wrapped;

    // DO-NOT-DELETE splicer.begin(TestScriptBabel.BabelMain._implementation)
    
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
    

    // DO-NOT-DELETE splicer.end(TestScriptBabel.BabelMain._implementation)

  public:
    // default constructor, used for data wrapping(required)
    BabelMain_impl();
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    BabelMain_impl( struct TestScriptBabel_BabelMain__object * s ) : StubBase(s,
      true), _wrapped(false) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~BabelMain_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

    // true if this object was created by a user newing the impl
    inline bool _isWrapped() {return _wrapped;}

    // static class initializer
    static void _load();

  public:

    /**
     * user defined non-static method.
     */
    int32_t
    invokeGo_impl (
      /* in */const ::std::string& component,
      /* in */const ::std::string& port,
      /* in */::gov::cca::ComponentID c,
      /* in */::gov::cca::Services services,
      /* in */::gov::cca::ports::BuilderService bs
    )
    ;


    /**
     *  This function handles the configuring of 
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
    setParameters_impl (
      /* in */const ::std::string& component,
      /* in */const ::std::string& port,
      /* in */::gov::cca::ComponentID c,
      /* in */::gov::cca::ports::BuilderService bs,
      /* in */::gov::cca::Services services,
      /* in */::TestScriptBabel::StringMap sm
    )
    ;


    /**
     *  This function returns a stringified version of a parameter value.
     */
    ::std::string
    getParameterValue_impl (
      /* in */::gov::cca::ComponentID c,
      /* in */const ::std::string& portName,
      /* in */const ::std::string& var,
      /* in */::gov::cca::Services services,
      /* in */::gov::cca::ports::BuilderService bs
    )
    ;

    /**
     * user defined non-static method.
     */
    void
    driverBody_impl (
      /* inout */::gov::cca::AbstractFramework& af
    )
    ;

  };  // end class BabelMain_impl

} // end namespace TestScriptBabel

// DO-NOT-DELETE splicer.begin(TestScriptBabel.BabelMain._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(TestScriptBabel.BabelMain._misc)

#endif
