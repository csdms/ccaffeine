// 
// File:          ccaffeine_TypeMap_Impl.hxx
// Symbol:        ccaffeine.TypeMap-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.TypeMap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_TypeMap_Impl_hxx
#define included_ccaffeine_TypeMap_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl_cxx.hxx"
#endif
#ifndef included_ccaffeine_TypeMap_IOR_h
#include "ccaffeine_TypeMap_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_sidl_BaseInterface_hxx
#include "sidl_BaseInterface.hxx"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "sidl_ClassInfo.hxx"
#endif
#ifndef included_ccaffeine_TypeMap_hxx
#include "ccaffeine_TypeMap.hxx"
#endif
#ifndef included_gov_cca_Type_hxx
#include "gov_cca_Type.hxx"
#endif
#ifndef included_gov_cca_TypeMap_hxx
#include "gov_cca_TypeMap.hxx"
#endif
#ifndef included_gov_cca_TypeMismatchException_hxx
#include "gov_cca_TypeMismatchException.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.TypeMap._hincludes)
// #include <map>
// #include <utility> // need pair<T,U>
#include "dc/export/AllExport.hh"
#include "ccaffeine_CCAException.hxx"
/*
 * The implementation here is now that of the pure c++ version
 * done by ben allan, wrapped in babel.
 * It doesn't make evil assumptions about underlying
 * implementations of the sort that require reinterpret cast.
 * 
 */
// DO-NOT-DELETE splicer.end(ccaffeine.TypeMap._hincludes)

namespace ccaffeine { 

  /**
   * Symbol "ccaffeine.TypeMap" (version 0.3)
   * 
   * This is a wrapper class. It cannot be successfully
   * constructed directly from component or client code.
   * Only the ccaffeine framework
   * internals know how to initialize this object.
   * Components must use Services.createTypeMap.
   */
  class TypeMap_impl
  // DO-NOT-DELETE splicer.begin(ccaffeine.TypeMap._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccaffeine.TypeMap._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    TypeMap self;

    // DO-NOT-DELETE splicer.begin(ccaffeine.TypeMap._implementation)
    ::ccafeopq::TypeMap_shared ctm;

    template <class Scalar > sidl::array< Scalar > 
      convertToSidlArray( ::std::vector< Scalar > & val );

    template <class Scalar > ::std::vector< Scalar > 
      convertToVector( sidl::array< Scalar > & val );

    int serial;
    static int nextNum() { genSerial++; return genSerial; }
    static int genSerial;

  public:

    static ::ccaffeine::TypeMap babelWrap( ::ccafeopq::TypeMap_shared ctm_);
    
    // DO-NOT-DELETE splicer.end(ccaffeine.TypeMap._implementation)

  private:
    // private default constructor (required)
    TypeMap_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    TypeMap_impl( struct ccaffeine_TypeMap__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~TypeMap_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:


    /**
     * unless this function is properly called,
     * the ccaffeine::TypeMap in question will do
     * nothing but generate exceptions.
     */
    void
    initialize (
      /*in*/ void* opaque_TypeMap_addr
    )
    throw () 
    ;


    /**
     * Create an exact copy of this Map 
     */
    ::gov::cca::TypeMap
    cloneTypeMap() throw () 
    ;

    /**
     * Create a new Map with no key/value associations. 
     */
    ::gov::cca::TypeMap
    cloneEmpty() throw () 
    ;
    /**
     * user defined non-static method.
     */
    int32_t
    getInt (
      /*in*/ const ::std::string& key,
      /*in*/ int32_t dflt
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    int64_t
    getLong (
      /*in*/ const ::std::string& key,
      /*in*/ int64_t dflt
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    float
    getFloat (
      /*in*/ const ::std::string& key,
      /*in*/ float dflt
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    double
    getDouble (
      /*in*/ const ::std::string& key,
      /*in*/ double dflt
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    ::std::complex<float>
    getFcomplex (
      /*in*/ const ::std::string& key,
      /*in*/ const ::std::complex<float>& dflt
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    ::std::complex<double>
    getDcomplex (
      /*in*/ const ::std::string& key,
      /*in*/ const ::std::complex<double>& dflt
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    ::std::string
    getString (
      /*in*/ const ::std::string& key,
      /*in*/ const ::std::string& dflt
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    bool
    getBool (
      /*in*/ const ::std::string& key,
      /*in*/ bool dflt
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    ::sidl::array<int32_t>
    getIntArray (
      /*in*/ const ::std::string& key,
      /*in*/ ::sidl::array<int32_t> dflt
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    ::sidl::array<int64_t>
    getLongArray (
      /*in*/ const ::std::string& key,
      /*in*/ ::sidl::array<int64_t> dflt
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    ::sidl::array<float>
    getFloatArray (
      /*in*/ const ::std::string& key,
      /*in*/ ::sidl::array<float> dflt
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    ::sidl::array<double>
    getDoubleArray (
      /*in*/ const ::std::string& key,
      /*in*/ ::sidl::array<double> dflt
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    ::sidl::array< ::sidl::fcomplex>
    getFcomplexArray (
      /*in*/ const ::std::string& key,
      /*in*/ ::sidl::array< ::sidl::fcomplex> dflt
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    ::sidl::array< ::sidl::dcomplex>
    getDcomplexArray (
      /*in*/ const ::std::string& key,
      /*in*/ ::sidl::array< ::sidl::dcomplex> dflt
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    ::sidl::array< ::std::string>
    getStringArray (
      /*in*/ const ::std::string& key,
      /*in*/ ::sidl::array< ::std::string> dflt
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    ::sidl::array<bool>
    getBoolArray (
      /*in*/ const ::std::string& key,
      /*in*/ ::sidl::array<bool> dflt
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );


    /**
     * Assign a key and value. Any value previously assigned
     * to the same key will be overwritten so long as it
     * is of the same type. If types conflict, an exception occurs.
     */
    void
    putInt (
      /*in*/ const ::std::string& key,
      /*in*/ int32_t value
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    void
    putLong (
      /*in*/ const ::std::string& key,
      /*in*/ int64_t value
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    void
    putFloat (
      /*in*/ const ::std::string& key,
      /*in*/ float value
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    void
    putDouble (
      /*in*/ const ::std::string& key,
      /*in*/ double value
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    void
    putFcomplex (
      /*in*/ const ::std::string& key,
      /*in*/ const ::std::complex<float>& value
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    void
    putDcomplex (
      /*in*/ const ::std::string& key,
      /*in*/ const ::std::complex<double>& value
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    void
    putString (
      /*in*/ const ::std::string& key,
      /*in*/ const ::std::string& value
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    void
    putBool (
      /*in*/ const ::std::string& key,
      /*in*/ bool value
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    void
    putIntArray (
      /*in*/ const ::std::string& key,
      /*in*/ ::sidl::array<int32_t> value
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    void
    putLongArray (
      /*in*/ const ::std::string& key,
      /*in*/ ::sidl::array<int64_t> value
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    void
    putFloatArray (
      /*in*/ const ::std::string& key,
      /*in*/ ::sidl::array<float> value
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    void
    putDoubleArray (
      /*in*/ const ::std::string& key,
      /*in*/ ::sidl::array<double> value
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    void
    putFcomplexArray (
      /*in*/ const ::std::string& key,
      /*in*/ ::sidl::array< ::sidl::fcomplex> value
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    void
    putDcomplexArray (
      /*in*/ const ::std::string& key,
      /*in*/ ::sidl::array< ::sidl::dcomplex> value
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    void
    putStringArray (
      /*in*/ const ::std::string& key,
      /*in*/ ::sidl::array< ::std::string> value
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );

    /**
     * user defined non-static method.
     */
    void
    putBoolArray (
      /*in*/ const ::std::string& key,
      /*in*/ ::sidl::array<bool> value
    )
    throw ( 
      ::gov::cca::TypeMismatchException
    );


    /**
     * Make the key and associated value disappear from the object. 
     */
    void
    remove (
      /*in*/ const ::std::string& key
    )
    throw () 
    ;


    /**
     *  Get all the names associated with a particular type
     *  without exposing the data implementation details.  The keys
     *  will be returned in an arbitrary order. If type specified is
     *  NoType (no specification) all keys of all types are returned.
     */
    ::sidl::array< ::std::string>
    getAllKeys (
      /*in*/ ::gov::cca::Type t
    )
    throw () 
    ;


    /**
     * Return true if the key exists in this map 
     */
    bool
    hasKey (
      /*in*/ const ::std::string& key
    )
    throw () 
    ;


    /**
     * Return the type of the value associated with this key 
     */
    ::gov::cca::Type
    typeOf (
      /*in*/ const ::std::string& key
    )
    throw () 
    ;

  };  // end class TypeMap_impl

} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.TypeMap._hmisc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.TypeMap._hmisc)

#endif
