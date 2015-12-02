// 
// File:          ccaffeine_ComponentClassDescription_Impl.hxx
// Symbol:        ccaffeine.ComponentClassDescription-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ComponentClassDescription
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_ComponentClassDescription_Impl_hxx
#define included_ccaffeine_ComponentClassDescription_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_ComponentClassDescription_IOR_h
#include "ccaffeine_ComponentClassDescription_IOR.h"
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
#ifndef included_ccaffeine_ComponentClassDescription_hxx
#include "ccaffeine_ComponentClassDescription.hxx"
#endif
#ifndef included_gov_cca_CCAException_hxx
#include "gov_cca_CCAException.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.ComponentClassDescription._includes)
// Put additional includes or other arbitrary code here...
#include "dc/export/AllExport.hh"
#include "ccaffeine_CCAException.hxx"
// DO-NOT-DELETE splicer.end(ccaffeine.ComponentClassDescription._includes)

namespace ccaffeine { 

  /**
   * Symbol "ccaffeine.ComponentClassDescription" (version 0.3)
   * 
   * This is a wrapper class. It cannot be successfully
   * constructed directly from component or client code.
   * Only the ccaffeine framework
   * internals know how to initialize this object.
   */
  class ComponentClassDescription_impl
  // DO-NOT-DELETE splicer.begin(ccaffeine.ComponentClassDescription._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccaffeine.ComponentClassDescription._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    ComponentClassDescription self;

    // DO-NOT-DELETE splicer.begin(ccaffeine.ComponentClassDescription._implementation)
    // Put additional implementation details here...
    ::ccafeopq::ComponentClassDescription_shared occd;
    int serial;
    static int nextNum() { genSerial++; return genSerial; }
    static int genSerial;
    // DO-NOT-DELETE splicer.end(ccaffeine.ComponentClassDescription._implementation)

  private:
    // private default constructor (required)
    ComponentClassDescription_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    ComponentClassDescription_impl( struct 
      ccaffeine_ComponentClassDescription__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~ComponentClassDescription_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:

    /**
     * user defined non-static method.
     */
    void
    initialize (
      /*in*/ void* opaque_ComponentClassDescription_addr
    )
    throw () 
    ;


    /**
     *  Returns the class name provided in 
     *   <code>BuilderService.createInstance()</code>
     *   or in
     *   <code>AbstractFramework.getServices()</code>.
     *  <p>
     *  Throws <code>CCAException</code> if <code>ComponentClassDescription</code> is invalid.
     */
    ::std::string
    getComponentClassName() throw ( 
      ::gov::cca::CCAException
    );
  };  // end class ComponentClassDescription_impl

} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.ComponentClassDescription._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.ComponentClassDescription._misc)

#endif
