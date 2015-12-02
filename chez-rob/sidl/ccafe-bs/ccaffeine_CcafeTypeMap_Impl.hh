// 
// File:          ccaffeine_CcafeTypeMap_Impl.hh
// Symbol:        ccaffeine.CcafeTypeMap-v0.0.0
// Symbol Type:   class
// Babel Version: 0.6.2
// SIDL Created:  20020510 17:32:14 PDT
// Generated:     20020510 17:32:20 PDT
// Description:   Server-side implementation for ccaffeine.CcafeTypeMap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_CcafeTypeMap_Impl_hh
#define included_ccaffeine_CcafeTypeMap_Impl_hh

#ifndef included_SIDL_cxx_hh
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_CcafeTypeMap_IOR_h
#include "ccaffeine_CcafeTypeMap_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_SIDL_BaseInterface_hh
#include "SIDL_BaseInterface.hh"
#endif
#ifndef included_ccaffeine_CcafeTypeMap_hh
#include "ccaffeine_CcafeTypeMap.hh"
#endif
#ifndef included_gov_cca_Type_hh
#include "gov_cca_Type.hh"
#endif
#ifndef included_gov_cca_TypeMap_hh
#include "gov_cca_TypeMap.hh"
#endif
#ifndef included_gov_cca_TypeMismatchException_hh
#include "gov_cca_TypeMismatchException.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap._includes)

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include "Object.hh"

    typedef boost::shared_ptr< ccaffeine::ObjectBase > OPtr;
    typedef std::map<std::string, OPtr> OPtrMap;
    typedef std::map<std::string, OPtr>::const_iterator Iter;

// DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap._includes)

namespace ccaffeine { 

  /**
   * Symbol "ccaffeine.CcafeTypeMap" (version 0.0.0)
   * 
   * A CCA map.  Maps a string key to a particular value. Types are
   * strictly enforced.  For example, values places into the map
   * using putInt can be retrieved only using getInt.  Calls to
   * getLong, getString, getIntArray and other get methods will
   * fail (i.e. return the default value) if the value stored is of type Int.
   */
  class CcafeTypeMap_impl {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    CcafeTypeMap self;

    // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap._implementation)
    OPtrMap table;
    // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap._implementation)

  private:
    // private default constructor (required)
    CcafeTypeMap_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    CcafeTypeMap_impl( struct ccaffeine_CcafeTypeMap__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~CcafeTypeMap_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:


    /**
     * Create an exact copy of this Map 
     */
    gov::cca::TypeMap
    cloneData() throw () 
    ;

    /**
     * Create a new Map with no key/value associations. 
     */
    gov::cca::TypeMap
    cloneEmpty() throw () 
    ;

    /**
     * Get all the names associated with a particular type
     * without exposing the data implementation details.  The keys
     * will be returned in an arbitrary order. If type specified is
     * None (no specification) all keys of all types are returned.
     */
    SIDL::array<std::string>
    getAllKeys (
      /*in*/ gov::cca::Type__enum t
    )
    throw () 
    ;


    /**
     * Get the boolean value associated with a given key.  If the key
     * was not found, return the value defaultValue. 
     */
    bool
    getBool (
      /*in*/ std::string key,
      /*in*/ bool defaultValue
    )
    throw ( 
      gov::cca::TypeMismatchException
    );


    /**
     * Get the value associated with a given key.  If the key
     * was not found, return the value defaultValue. 
     */
    SIDL::array<bool>
    getBoolArray (
      /*in*/ std::string key,
      /*in*/ SIDL::array<bool> defaultValue
    )
    throw ( 
      gov::cca::TypeMismatchException
    );


    /**
     * Get the Dcomplex value associated with a given key.  If the key
     * was not found, return the complex value defaultValue. 
     */
    std::complex<double>
    getDcomplex (
      /*in*/ std::string key,
      /*in*/ std::complex<double> defaultValue
    )
    throw ( 
      gov::cca::TypeMismatchException
    );


    /**
     * Get the complex value associated with a given key.  If the key
     * was not found, return the complex value defaultValue. 
     */
    SIDL::array<SIDL::dcomplex>
    getDcomplexArray (
      /*in*/ std::string key,
      /*in*/ SIDL::array<SIDL::dcomplex> defaultValue
    )
    throw ( 
      gov::cca::TypeMismatchException
    );


    /**
     * Get the Double value associated with a given key.  If the key
     * was not found, return the value defaultValue. 
     */
    double
    getDouble (
      /*in*/ std::string key,
      /*in*/ double defaultValue
    )
    throw ( 
      gov::cca::TypeMismatchException
    );


    /**
     * Get the value associated with a given key.  If the key
     * was not found, return the value defaultValue. 
     */
    SIDL::array<double>
    getDoubleArray (
      /*in*/ std::string key,
      /*in*/ SIDL::array<double> defaultValue
    )
    throw ( 
      gov::cca::TypeMismatchException
    );


    /**
     * Get the Fcomplex value associated with a given key.  If the key
     * was not found, return complex the value defaultValue. 
     */
    std::complex<float>
    getFcomplex (
      /*in*/ std::string key,
      /*in*/ std::complex<float> defaultValue
    )
    throw ( 
      gov::cca::TypeMismatchException
    );


    /**
     * Get the complex value associated with a given key.  If the key
     * was not found, return the complex value defaultValue. 
     */
    SIDL::array<SIDL::fcomplex>
    getFcomplexArray (
      /*in*/ std::string key,
      /*in*/ SIDL::array<SIDL::fcomplex> defaultValue
    )
    throw ( 
      gov::cca::TypeMismatchException
    );


    /**
     * Get the Float value associated with a given key.  If the key
     * was not found, return the value defaultValue. 
     */
    float
    getFloat (
      /*in*/ std::string key,
      /*in*/ float defaultValue
    )
    throw ( 
      gov::cca::TypeMismatchException
    );


    /**
     * Get the value associated with a given key.  If the key
     * was not found, return the value defaultValue. 
     */
    SIDL::array<float>
    getFloatArray (
      /*in*/ std::string key,
      /*in*/ SIDL::array<float> defaultValue
    )
    throw ( 
      gov::cca::TypeMismatchException
    );


    /**
     * Get the Int value associated with a given key.  If the key
     * was not found, return the value defaultValue. 
     */
    int32_t
    getInt (
      /*in*/ std::string key,
      /*in*/ int32_t defaultValue
    )
    throw ( 
      gov::cca::TypeMismatchException
    );


    /**
     * Get the value associated with a given key.  If the key
     * was not found, return the value defaultValue. 
     */
    SIDL::array<int>
    getIntArray (
      /*in*/ std::string key,
      /*in*/ SIDL::array<int> defaultValue
    )
    throw ( 
      gov::cca::TypeMismatchException
    );


    /**
     * Get the Long value associated with a given key.  If the key
     * was not found, return the value defaultValue. 
     */
    int64_t
    getLong (
      /*in*/ std::string key,
      /*in*/ int64_t defaultValue
    )
    throw ( 
      gov::cca::TypeMismatchException
    );


    /**
     * Get the value associated with a given key.  If the key
     * was not found, return the value defaultValue. 
     */
    SIDL::array<long>
    getLongArray (
      /*in*/ std::string key,
      /*in*/ SIDL::array<long> defaultValue
    )
    throw ( 
      gov::cca::TypeMismatchException
    );


    /**
     * Get the string value associated with a given key.  If the key
     * was not found, return the value defaultValue. 
     */
    std::string
    getString (
      /*in*/ std::string key,
      /*in*/ std::string defaultValue
    )
    throw ( 
      gov::cca::TypeMismatchException
    );


    /**
     * Get the value associated with a given key.  If the key
     * was not found, return the value defaultValue. 
     */
    SIDL::array<std::string>
    getStringArray (
      /*in*/ std::string key,
      /*in*/ SIDL::array<std::string> defaultValue
    )
    throw ( 
      gov::cca::TypeMismatchException
    );


    /**
     * Return true if the key exists in this map 
     */
    bool
    hasKey (
      /*in*/ std::string key
    )
    throw () 
    ;


    /**
     * Assign a key and value. Any value previously assigned
     * to the same key will be overwritten.  
     */
    void
    putBool (
      /*in*/ std::string key,
      /*in*/ bool value
    )
    throw () 
    ;


    /**
     * Assign a key and value. Any value previously assigned
     * to the same key will be overwritten. Arrays are stored
     * by COPY, not by reference. 
     */
    void
    putBoolArray (
      /*in*/ std::string key,
      /*in*/ SIDL::array<bool> value
    )
    throw () 
    ;


    /**
     * Assign a key and complex value. 
     * Any complex value previously assigned will be overwritten. 
     */
    void
    putDcomplex (
      /*in*/ std::string key,
      /*in*/ std::complex<double> value
    )
    throw () 
    ;


    /**
     * Assign a key and complex array value. Any value previously assigned
     * to the same key will be overwritten. Complex arrays are stored by COPY. 
     */
    void
    putDcomplexArray (
      /*in*/ std::string key,
      /*in*/ SIDL::array<SIDL::dcomplex> value
    )
    throw () 
    ;


    /**
     * Assign a key and value. Any value previously assigned
     * to the same key will be overwritten.  
     */
    void
    putDouble (
      /*in*/ std::string key,
      /*in*/ double value
    )
    throw () 
    ;


    /**
     * Assign a key and value. Any value previously assigned
     * to the same key will be overwritten. Arrays are stored
     * by COPY, not by reference. 
     */
    void
    putDoubleArray (
      /*in*/ std::string key,
      /*in*/ SIDL::array<double> value
    )
    throw () 
    ;


    /**
     * Assign a key and complex value.
     * Any complex value previously assigned will be overwritten.  
     */
    void
    putFcomplex (
      /*in*/ std::string key,
      /*in*/ std::complex<float> value
    )
    throw () 
    ;


    /**
     * Assign a key and complex array value. Any value previously assigned
     * to the same key will be overwritten. complex arrays are stored by COPY.
     */
    void
    putFcomplexArray (
      /*in*/ std::string key,
      /*in*/ SIDL::array<SIDL::fcomplex> value
    )
    throw () 
    ;


    /**
     * Assign a key and value. Any value previously assigned
     * to the same key will be overwritten.  
     */
    void
    putFloat (
      /*in*/ std::string key,
      /*in*/ float value
    )
    throw () 
    ;


    /**
     * Assign a key and value. Any value previously assigned
     * to the same key will be overwritten. Arrays are stored
     * by COPY, not by reference. 
     */
    void
    putFloatArray (
      /*in*/ std::string key,
      /*in*/ SIDL::array<float> value
    )
    throw () 
    ;


    /**
     * Assign a key and value. Any value previously assigned
     * to the same key will be overwritten.  
     */
    void
    putInt (
      /*in*/ std::string key,
      /*in*/ int32_t value
    )
    throw () 
    ;


    /**
     * Assign a key and value. Any value previously assigned
     * to the same key will be overwritten. Arrays are stored
     * by COPY, not by reference. 
     */
    void
    putIntArray (
      /*in*/ std::string key,
      /*in*/ SIDL::array<int> value
    )
    throw () 
    ;


    /**
     * Assign a key and value. Any value previously assigned
     * to the same key will be overwritten.  
     */
    void
    putLong (
      /*in*/ std::string key,
      /*in*/ int64_t value
    )
    throw () 
    ;


    /**
     * Assign a key and value. Any value previously assigned
     * to the same key will be overwritten. Arrays are stored
     * by COPY, not by reference. 
     */
    void
    putLongArray (
      /*in*/ std::string key,
      /*in*/ SIDL::array<long> value
    )
    throw () 
    ;


    /**
     * Assign a key and value. Any value previously assigned
     * to the same key will be overwritten.  
     */
    void
    putString (
      /*in*/ std::string key,
      /*in*/ std::string value
    )
    throw () 
    ;


    /**
     * Assign a key and value. Any value previously assigned
     * to the same key will be overwritten. Arrays are stored
     * by COPY, not by reference. 
     */
    void
    putStringArray (
      /*in*/ std::string key,
      /*in*/ SIDL::array<std::string> value
    )
    throw () 
    ;


    /**
     * Make the key and associated value disappear from the object. 
     */
    void
    remove (
      /*in*/ std::string key
    )
    throw () 
    ;


    /**
     * Return the type of the value associated with this key 
     */
    gov::cca::Type__enum
    typeOf (
      /*in*/ std::string key
    )
    throw () 
    ;

  };  // end class CcafeTypeMap_impl

} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap._misc)

#endif
