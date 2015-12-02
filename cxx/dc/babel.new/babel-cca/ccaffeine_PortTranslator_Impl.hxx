// 
// File:          ccaffeine_PortTranslator_Impl.hxx
// Symbol:        ccaffeine.PortTranslator-v0.6
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.PortTranslator
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_PortTranslator_Impl_hxx
#define included_ccaffeine_PortTranslator_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_PortTranslator_IOR_h
#include "ccaffeine_PortTranslator_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_sidl_BaseInterface_hxx
#include "SIDL_BaseInterface.hh"
#endif
#ifndef included_ccaffeine_PortTranslator_hxx
#include "ccaffeine_PortTranslator.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.PortTranslator._includes)

#include "dc/export/AllExport.hh"
#include "dc/classic/ccafe-bind/AllCcafeBind.hh"

// DO-NOT-DELETE splicer.end(ccaffeine.PortTranslator._includes)

namespace ccaffeine { 

  /**
   * Symbol "ccaffeine.PortTranslator" (version 0.6)
   * 
   * Foreign ports (i.e. Ports of a different Ccaffeine Religion) are
   * wrapped by Ccaffeine in this class.  If a foreign port is
   * connected to a Babel component, an instance of
   * ccaffeine::PortTranslator is wrapped around it.  Several methods
   * are provided on PortTranslator that will allow access to the
   * other Religions.  The methods return the foreign port as a void*
   * and this is castable to exactly the indicated Port type, and
   * nothing else.  Further cast is required to get the base Port type
   * to a particular Port in the foreign Religion. Example:
   * 
   * PortTranslator pt = getPort("my_classic_parameter_port");
   * classic::gov::cca::Port* port = 
   * (classic::gov::cca::Port*) (pt.getClassicPort());
   * if(port == NULL) {
   * perror("Hey this is not a Classic Port");        
   * }
   * ParameterPort* pp = 
   * dynamic_cast< ParameterPort* > (port);
   * if(pp == NULL) {
   * perror("Hey this is not a ParameterPort");
   * }
   * // use the pp now as you would in Classic Religion ...
   * 
   * Note that the following shortcut will yield unexpected results
   * and does not conform to the C++ standard:
   * 
   * // This is a REALLY BAD IDEA:
   * PortTranslator pt = getPort("my_classic_parameter_port");
   * ParameterPort* pp = (ParameterPort*) (pt.getClassicPort());
   * 
   */
  class PortTranslator_impl
  // DO-NOT-DELETE splicer.begin(ccaffeine.PortTranslator._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccaffeine.PortTranslator._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    PortTranslator self;

    // DO-NOT-DELETE splicer.begin(ccaffeine.PortTranslator._implementation)

    /** This is the OpaquePort that this translator wraps. */
    ccafeopq::Port * port;

    // DO-NOT-DELETE splicer.end(ccaffeine.PortTranslator._implementation)

  private:
    // private default constructor (required)
    PortTranslator_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    PortTranslator_impl( struct ccaffeine_PortTranslator__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~PortTranslator_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:

    /**
     * user defined non-static method.
     */
    void
    initialize (
      /*in*/ void* opaquePort
    )
    throw () 
    ;


    /**
     * Return a classic port.  The void * returned in C++ are
     * directly castable to a C++ classic::gov::cca::Port* and only
     * that type.  Casting to the specific type must occur after. 
     */
    void*
    getClassicPort() throw () 
    ;

    /**
     * unimplemented, returns NULL. 
     */
    void*
    getChasmPort() throw () 
    ;

    /**
     * Return a raw OpaquePort.  The void * in C++ is directly
     * castable to a ccafeopq::Port*.  
     */
    void*
    getRawPort() throw () 
    ;
  };  // end class PortTranslator_impl

} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.PortTranslator._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.PortTranslator._misc)

#endif
