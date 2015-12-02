// 
// File:          ccaffeine_ports_BasicParameterPortWrap_Impl.hxx
// Symbol:        ccaffeine.ports.BasicParameterPortWrap-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ports.BasicParameterPortWrap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_ports_BasicParameterPortWrap_Impl_hxx
#define included_ccaffeine_ports_BasicParameterPortWrap_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_ports_BasicParameterPortWrap_IOR_h
#include "ccaffeine_ports_BasicParameterPortWrap_IOR.h"
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
#ifndef included_ccaffeine_ports_BasicParameterPortWrap_hxx
#include "ccaffeine_ports_BasicParameterPortWrap.hxx"
#endif
#ifndef included_gov_cca_CCAException_hxx
#include "gov_cca_CCAException.hxx"
#endif
#ifndef included_gov_cca_TypeMap_hxx
#include "gov_cca_TypeMap.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.BasicParameterPortWrap._includes)

#include "dc/export/AllExport.hh"
#include "AllCCA.hh"
#include "dc/babel.new/babel-cca/AllBabelCCA.hxx"

// DO-NOT-DELETE splicer.end(ccaffeine.ports.BasicParameterPortWrap._includes)

namespace ccaffeine { 
  namespace ports { 

    /**
     * Symbol "ccaffeine.ports.BasicParameterPortWrap" (version 0.3)
     * 
     * The implementation of the babel ParameterPort
     * is a wrapper. The component writer cannot create an instance
     * of this independently and succeed. The component writer
     * must use the port ParameterPortFactory, not this class.
     */
    class BasicParameterPortWrap_impl
    // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BasicParameterPortWrap._inherits)
    // Put additional inheritance here...
    // DO-NOT-DELETE splicer.end(ccaffeine.ports.BasicParameterPortWrap._inherits)
    {

    private:
      // Pointer back to IOR.
      // Use this to dispatch back through IOR vtable.
      BasicParameterPortWrap self;

      // DO-NOT-DELETE splicer.begin(ccaffeine.ports.BasicParameterPortWrap._implementation)
      // Put additional implementation details here...
      ::ccafeopq::ports::BasicParameterPort *opp;
      int serial;
      static int nextNum() { genSerial++; return genSerial; }
      static int genSerial;
      void checkthrow(const char *funcName);
      // DO-NOT-DELETE splicer.end(ccaffeine.ports.BasicParameterPortWrap._implementation)

    private:
      // private default constructor (required)
      BasicParameterPortWrap_impl() {} 

    public:
      // SIDL constructor (required)
      // Note: alternate Skel constructor doesn't call addref()
      // (fixes bug #275)
      BasicParameterPortWrap_impl( struct 
        ccaffeine_ports_BasicParameterPortWrap__object * s ) : self(s,
        true) { _ctor(); }

      // user defined construction
      void _ctor();

      // virtual destructor (required)
      virtual ~BasicParameterPortWrap_impl() { _dtor(); }

      // user defined destruction
      void _dtor();

    public:


      /**
       * passed in is a void * cast pointer of
       *  ccafeopq::ports::BasicParameterPort *.
       */
      void
      initialize (
        /*in*/ void* ccafeopq_ports_BasicParameterPort_star
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
       * Return a TypeMap of runtime configuration parameters. 
       * It is recommended that the map returned be a clone/copy of the
       * a privately held map, not a shared object reference.
       */
      ::gov::cca::TypeMap
      readConfigurationMap() throw ( 
        ::gov::cca::CCAException
      );

      /**
       * Copy the parameter values given in map into the
       * internal map, for those parameters which
       * are already defined by the internal map.
       * The outsider does not get to cause arbitrary
       * keys to be copied into the internal map.
       * @throws gov.cca.CCAException if TypeMap operations fail.
       */
      void
      writeConfigurationMap (
        /*in*/ ::gov::cca::TypeMap map
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the list of keys in the TypeMap that are
       * for public configuration purposes. Other values found in
       * the TypeMap must not be changed.
       */
      ::sidl::array< ::std::string>
      readConfigurationKeys() throw () 
      ;
    };  // end class BasicParameterPortWrap_impl

  } // end namespace ports
} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.BasicParameterPortWrap._misc)
// Put miscellaneous things here...
int ccaffeine_ports_BasicParameterPortWrap_qc(int argc, char *argv[]);
// -Dccaffeine_ports_BasicParameterPortWrap_MAIN causes
// main() to be defined for instantiation link completeness test.
// DO-NOT-DELETE splicer.end(ccaffeine.ports.BasicParameterPortWrap._misc)

#endif
