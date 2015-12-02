// 
// File:          ccaffeine_ports_ParameterPortWrap_Impl.hxx
// Symbol:        ccaffeine.ports.ParameterPortWrap-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ports.ParameterPortWrap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_ports_ParameterPortWrap_Impl_hxx
#define included_ccaffeine_ports_ParameterPortWrap_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_ports_ParameterPortWrap_IOR_h
#include "ccaffeine_ports_ParameterPortWrap_IOR.h"
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
#ifndef included_ccaffeine_ports_ParameterPortWrap_hxx
#include "ccaffeine_ports_ParameterPortWrap.hxx"
#endif
#ifndef included_gov_cca_CCAException_hxx
#include "gov_cca_CCAException.hxx"
#endif
#ifndef included_gov_cca_TypeMap_hxx
#include "gov_cca_TypeMap.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap._includes)

#include "dc/export/AllExport.hh"
#include "AllCCA.hh"
#include "dc/babel.new/babel-cca/AllBabelCCA.hxx"
// #include "dc/babel.new/ccafe-bind/AllCcafeBind.hh"
// #include "util/IO.h"

// DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap._includes)

namespace ccaffeine { 
  namespace ports { 

    /**
     * Symbol "ccaffeine.ports.ParameterPortWrap" (version 0.3)
     * 
     * The implementation of the babel ParameterPort
     * is a wrapper. The component writer cannot create an instance
     * of this independently and succeed. The component writer
     * must use the port ParameterPortFactory, not this class.
     */
    class ParameterPortWrap_impl
    // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap._inherits)
    // Put additional inheritance here...
    // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap._inherits)
    {

    private:
      // Pointer back to IOR.
      // Use this to dispatch back through IOR vtable.
      ParameterPortWrap self;

      // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap._implementation)
      // Put additional implementation details here...
      ::ccafeopq::ports::ParameterPort *opp;
      int serial;
      static int nextNum() { genSerial++; return genSerial; }
      static int genSerial;
      void checkthrow(const char *funcName);
      // DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap._implementation)

    private:
      // private default constructor (required)
      ParameterPortWrap_impl() {} 

    public:
      // SIDL constructor (required)
      // Note: alternate Skel constructor doesn't call addref()
      // (fixes bug #275)
      ParameterPortWrap_impl( struct ccaffeine_ports_ParameterPortWrap__object 
        * s ) : self(s,true) { _ctor(); }

      // user defined construction
      void _ctor();

      // virtual destructor (required)
      virtual ~ParameterPortWrap_impl() { _dtor(); }

      // user defined destruction
      void _dtor();

    public:


      /**
       * passed in is a void * cast pointer of
       *  ccafeopq::ParameterPort *.
       */
      void
      initialize (
        /*in*/ void* ccafeopq_ports_ParameterPort_ptr
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

      /**
       * Fetch configuration title. 
       * @return Description of data set.
       */
      ::std::string
      readTitle() throw () 
      ;

      /**
       * Fetch the names of groups. Each page in a tabbed dialog
       * goes with a group, for example. Group names should be
       * a simple word without whitespace.
       */
      ::sidl::array< ::std::string>
      readGroupNames() throw () 
      ;

      /**
       * Fetch UI-appropriate name for group.
       * Group name and group title may be the same, if simple.
       * Group title can be complex if desired.
       * @throws gov.cca.CCAException if groupName is unknown.
       */
      ::std::string
      readGroupTitle (
        /*in*/ const ::std::string& groupName
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch data item keys associated with groupName.
       * Array order will be the same as the order in which
       * the additions were made in the ParameterPortFactory interface.
       * @throws gov.cca.CCAException if groupName is unknown.
       */
      ::sidl::array< ::std::string>
      readGroupKeys (
        /*in*/ const ::std::string& groupName
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the help string for key.
       * @throws gov.cca.CCAException if key is unknown.
       */
      ::std::string
      readHelp (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the prompt string for key.
       * @throws gov.cca.CCAException if key is unknown.
       */
      ::std::string
      readPrompt (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * By default, bounds are defined except for complex numbers
       * booleans, and strings. On array types, bounds apply
       * element-wise. i.e.  low <= arr[i] <= high for all i.
       * @return true if simple bounds are defined for a key.
       * @throws gov.cca.CCAException if key is unknown.
       */
      bool
      hasBounds (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * By default, lists of choices are not defined for scalars or arrays.
       * Choices are applied element-wise for array types.
       * I.e. (arr[i] IN choice-set) == true  for all i.
       * @return true if choice list is defined for a key.
       * @throws gov.cca.CCAException if key is unknown.
       */
      bool
      hasChoices (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for boolean-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      bool
      readDefaultBoolean (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for string-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::std::string
      readDefaultString (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for integer-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      int32_t
      readDefaultInt (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for long-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      int64_t
      readDefaultLong (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for float-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      float
      readDefaultFloat (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for double-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      double
      readDefaultDouble (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for fcomplex-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::std::complex<float>
      readDefaultFcomplex (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for dcomplex-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::std::complex<double>
      readDefaultDcomplex (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for string-array-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::sidl::array< ::std::string>
      readDefaultStringArray (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for boolean-array-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::sidl::array<bool>
      readDefaultBooleanArray (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for integer-array-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::sidl::array<int32_t>
      readDefaultIntArray (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for long-array-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::sidl::array<int64_t>
      readDefaultLongArray (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for float-array-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::sidl::array<float>
      readDefaultFloatArray (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for double-array-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::sidl::array<double>
      readDefaultDoubleArray (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for fcomplex-array-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::sidl::array< ::sidl::fcomplex>
      readDefaultFcomplexArray (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for dcomplex-array-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::sidl::array< ::sidl::dcomplex>
      readDefaultDcomplexArray (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the bounds for integer-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      void
      readBoundsInt (
        /*in*/ const ::std::string& key,
        /*out*/ int32_t& low,
        /*out*/ int32_t& high
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for long-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      void
      readBoundsLong (
        /*in*/ const ::std::string& key,
        /*out*/ int64_t& low,
        /*out*/ int64_t& high
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for float-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      void
      readBoundsFloat (
        /*in*/ const ::std::string& key,
        /*out*/ float& low,
        /*out*/ float& high
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for double-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      void
      readBoundsDouble (
        /*in*/ const ::std::string& key,
        /*out*/ double& low,
        /*out*/ double& high
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the choices for string(-array)-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::sidl::array< ::std::string>
      readChoicesString (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the choices for integer(-array)-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::sidl::array<int32_t>
      readChoicesInt (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the choices for long(-array)-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::sidl::array<int64_t>
      readChoicesLong (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the choices for float(-array)-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::sidl::array<float>
      readChoicesFloat (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for double(-array)-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::sidl::array<double>
      readChoicesDouble (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for fcomplex(-array)-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::sidl::array< ::sidl::fcomplex>
      readChoicesFcomplex (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );


      /**
       * Fetch the default for dcomplex(-array)-typed key. 
       * @throws gov.cca.CCAException if key is unknown or mistyped.
       */
      ::sidl::array< ::sidl::dcomplex>
      readChoicesDcomplex (
        /*in*/ const ::std::string& key
      )
      throw ( 
        ::gov::cca::CCAException
      );

    };  // end class ParameterPortWrap_impl

  } // end namespace ports
} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ParameterPortWrap._misc)
// Put miscellaneous things here...
int ccaffeine_ports_ParameterPortWrap_qc(int argc, char *argv[]);
// -Dccaffeine_ports_ParameterPortWrap_MAIN causes
// main() to be defined for instantiation link completeness test.
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ParameterPortWrap._misc)

#endif
