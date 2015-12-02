// 
// File:          ccaffeine_ports_GoPortWrap_Impl.hxx
// Symbol:        ccaffeine.ports.GoPortWrap-v0.3
// Symbol Type:   class
// Babel Version: 0.9.5
// Description:   Server-side implementation for ccaffeine.ports.GoPortWrap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// babel-version = 0.9.5
// 

#ifndef included_ccaffeine_ports_GoPortWrap_Impl_hxx
#define included_ccaffeine_ports_GoPortWrap_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl_cxx.hxx"
#endif
#ifndef included_ccaffeine_ports_GoPortWrap_IOR_h
#include "ccaffeine_ports_GoPortWrap_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_ccaffeine_ports_GoPortWrap_hxx
#include "ccaffeine_ports_GoPortWrap.hxx"
#endif
#ifndef included_sidl_BaseInterface_hxx
#include "sidl_BaseInterface.hxx"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "sidl_ClassInfo.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.GoPortWrap._includes)
// Put additional includes or other arbitrary code here...
#include "dc/export/AllExport.hh"
#include "AllCCA.hh"
#include "dc/babel.new/babel-cca/AllBabelCCA.hxx"

// DO-NOT-DELETE splicer.end(ccaffeine.ports.GoPortWrap._includes)

namespace ccaffeine { 
  namespace ports { 

    /**
     * Symbol "ccaffeine.ports.GoPortWrap" (version 0.3)
     */
    class GoPortWrap_impl
    // DO-NOT-DELETE splicer.begin(ccaffeine.ports.GoPortWrap._inherits)
    // Put additional inheritance here...
    // DO-NOT-DELETE splicer.end(ccaffeine.ports.GoPortWrap._inherits)
    {

    private:
      // Pointer back to IOR.
      // Use this to dispatch back through IOR vtable.
      GoPortWrap self;

      // DO-NOT-DELETE splicer.begin(ccaffeine.ports.GoPortWrap._implementation)
	::ccafeopq::GoPort *gp;
	int serial;
	static int nextNum() { genSerial++; return genSerial; }
	static int genSerial;
	void checkthrow(const char *funcName);
      
      // DO-NOT-DELETE splicer.end(ccaffeine.ports.GoPortWrap._implementation)

    private:
      // private default constructor (required)
      GoPortWrap_impl() {} 

    public:
      // sidl constructor (required)
      // Note: alternate Skel constructor doesn't call addref()
      // (fixes bug #275)
      GoPortWrap_impl( struct ccaffeine_ports_GoPortWrap__object * s ) : self(s,
        true) { _ctor(); }

      // user defined construction
      void _ctor();

      // virtual destructor (required)
      virtual ~GoPortWrap_impl() { _dtor(); }

      // user defined destruction
      void _dtor();

    public:


      /**
       * passed in is a void * cast pointer of
       *  ccafeopq::GoPort *.
       */
      void
      initialize (
        /*in*/ void* ccafeopq_GoPort_star
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
       * Execute some encapsulated functionality on the component. 
       * Return 0 if ok, -1 if internal error but component may be 
       * used further, and -2 if error so severe that component cannot
       * be further used safely.
       */
      int32_t
      go() throw () 
      ;
    };  // end class GoPortWrap_impl

  } // end namespace ports
} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.GoPortWrap._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.ports.GoPortWrap._misc)

#endif
