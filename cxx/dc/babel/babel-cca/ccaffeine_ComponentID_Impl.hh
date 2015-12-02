// 
// File:          ccaffeine_ComponentID_Impl.hh
// Symbol:        ccaffeine.ComponentID-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ComponentID
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_ComponentID_Impl_hh
#define included_ccaffeine_ComponentID_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_ComponentID_IOR_h
#include "ccaffeine_ComponentID_IOR.h"
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
#ifndef included_ccaffeine_ComponentID_hh
#include "ccaffeine_ComponentID.hh"
#endif
#ifndef included_gov_cca_CCAException_hh
#include "gov_cca_CCAException.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.ComponentID._includes)

#include "dc/export/AllExport.hh"
#include "gov_cca_ComponentID.hh"


// DO-NOT-DELETE splicer.end(ccaffeine.ComponentID._includes)

namespace ccaffeine { 

  /**
   * Symbol "ccaffeine.ComponentID" (version 0.3)
   * 
   * This is a wrapper class. It cannot be successfully
   * constructed directly from component or client code.
   * Only the ccaffeine framework internals know how to initialize 
   * this object.
   */
  class ComponentID_impl
  // DO-NOT-DELETE splicer.begin(ccaffeine.ComponentID._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccaffeine.ComponentID._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    ComponentID self;

    // DO-NOT-DELETE splicer.begin(ccaffeine.ComponentID._implementation)

    ::ccafeopq::ComponentID_shared oid;

    int serial;
    static int nextNum() { genSerial++; return genSerial; }
    static int genSerial;

  public:
    static ::ccaffeine::ComponentID babelWrap( ::ccafeopq::ComponentID_shared kernel);

#if 0
    // this a bitch, and needed but not done yet.
    static ::std::vector< ::ccafeopq::ComponentID_shared > 
	    convertToVector( sidl::array< ::gov::cca::ComponentID > & val );
    {
      int len = (val.upper(0) - val.lower(0)) + 1;
      ::std::vector< ::ccafeopq::ComponentID_shared > res;
      int bottom = val.lower(0);
      for(int i=0; i < len ; i++) {
	::ccafeopq::ComponentID_shared w = 
		BabelOpaqueComponentID::opaqueWrap(val.get(bottom+i));
        res.push_back( w );
      }
      return res;
    }
#endif

    static sidl::array< ::gov::cca::ComponentID > 
       convertToSidlArray( ::std::vector< ::ccafeopq::ComponentID_shared > &val );

    // DO-NOT-DELETE splicer.end(ccaffeine.ComponentID._implementation)

  private:
    // private default constructor (required)
    ComponentID_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    ComponentID_impl( struct ccaffeine_ComponentID__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~ComponentID_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:

    /**
     * user defined non-static method.
     */
    void
    initialize (
      /*in*/ void* opaque_ComponentID_addr
    )
    throw () 
    ;


    /**
     * Returns the instance name provided in 
     * <code>BuilderService.createInstance()</code>
     * or in 
     * <code>AbstractFramework.getServices()</code>.
     * @throws CCAException if <code>ComponentID</code> is invalid
     */
    ::std::string
    getInstanceName() throw ( 
      ::gov::cca::CCAException
    );

    /**
     * Returns a framework specific serialization of the ComponentID.
     * @throws CCAException if <code>ComponentID</code> is
     * invalid.
     */
    ::std::string
    getSerialization() throw ( 
      ::gov::cca::CCAException
    );
  };  // end class ComponentID_impl

} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.ComponentID._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.ComponentID._misc)

#endif
