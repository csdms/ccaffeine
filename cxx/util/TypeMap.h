#ifndef util_typemap_h_seen
#define util_typemap_h_seen

#include "dc/export/ccafeopq.hh"

namespace gov {
namespace sandia {
namespace util {

typedef ::ccafeopq::TypeMismatchException TypeMismatchException;

typedef ::std::vector< ::std::string > StringVector;
typedef ::std::map< ::std::string, ::std::string > StringMap;
typedef ::std::map< ::std::string, ::ccafeopq::Type > TypeMapFilter;
typedef ::std::map< ::std::string, ::ccafeopq::Type >::const_iterator Filtrator;

/** This is a simply-templated concrete typemap implementation.
 * It doesn't inherit the virtual interface classic::gov::cca::TypeMap.
 * Instead our virtualized version just delegates things to this concrete one.
 * It should never be exposed to any class except our wrapper to avoid leaking 
 * data items or inconsistent state.
 */
class TypeMapImpl;

/**
 * This is our implementation of ccafeopq::TypeMap.
 * It wraps a templated implementation that noone ever has to see.
 * There is a babel wrapper of this (to make one of these into a
 * ::gov::cca::TypeMap) named ccaffeine_TypeMap_Impl.
 * There is an opaque wrapper of ::gov::cca::TypeMap (to make
 * a babel map into an opaque map) named BabelOpaqueTypeMap.
 */
class TypeMap : public virtual ::ccafeopq::TypeMap_Interface
{
private:
    TypeMapImpl *m;
    static void copyInData( TypeMap * tmSrc, ::ccafeopq::TypeMap_shared tmDest);

public:

    TypeMap();

    /** required destructor */
    virtual ~TypeMap();
  
    /** Create an exact copy of this Map. */
    virtual ::ccafeopq::TypeMap_shared cloneData();
    virtual ::ccafeopq::TypeMap_shared cloneTypeMap();
  
    /** Create a new Map with no key/value associations. */
    virtual ::ccafeopq::TypeMap_shared cloneEmpty();
  
    /** Get the Int value associated with a given key.  If the key
        was not found, return the value defaultValue. */
    virtual int32_t      getInt(const ::std::string & key,  int32_t defaultValue) throw (TypeMismatchException ) ;
  
    /** Get the Long value associated with a given key.  If the key
        was not found, return the value defaultValue. */
    virtual int64_t    getLong(const ::std::string & key,  int64_t defaultValue) throw (TypeMismatchException );
  
    /** Get the Float value associated with a given key.  If the key
        was not found, return the value defaultValue. */
    virtual float    getFloat(const ::std::string & key,  float defaultValue) throw (TypeMismatchException );
  
    /** Get the Double value associated with a given key.  If the key
        was not found, return the value defaultValue. */
    virtual double   getDouble(const ::std::string & key,  double defaultValue) throw (TypeMismatchException );
  
    /** Get the Fcomplex value associated with a given key.  If the key
        was not found, return complex the value defaultValue. */
    virtual ::std::complex<float> getFcomplex(const ::std::string & key,  ::std::complex<float> defaultValue) throw (TypeMismatchException );
  
    /** Get the Dcomplex value associated with a given key.  If the key
        was not found, return the complex value defaultValue. */
    virtual ::std::complex<double> getDcomplex(const ::std::string & key,  ::std::complex<double> defaultValue) throw (TypeMismatchException );
  
    /** Get the string value associated with a given key.  If the key
        was not found, return the value defaultValue. */
    virtual ::std::string  getString(const ::std::string & key,  ::std::string defaultValue) throw (TypeMismatchException );
  
    /** Get the boolean value associated with a given key.  If the key
        was not found, return the value defaultValue. */
    virtual bool  getBool(const ::std::string & key,  bool defaultValue) throw (TypeMismatchException );
  
      // ======================================================
  
    /** Get the value associated with a given key.  If the key
        was not found, return the value defaultValue. */
    virtual ::std::vector< int32_t > getIntArray(const ::std::string & key,  ::std::vector< int32_t >&  defaultValue) throw (TypeMismatchException );

  
    /** Get the value associated with a given key.  If the key
        was not found, return the value defaultValue. */
    virtual ::std::vector< int64_t > getLongArray(const ::std::string & key,  ::std::vector< int64_t >&  defaultValue) throw (TypeMismatchException );

#if (SIZEOF_LONG_INT != 8)
    virtual ::std::vector< long int > getLongArray(const ::std::string & key,  ::std::vector< long int >&  defaultValue) throw (TypeMismatchException );
#endif
  
    /** Get the value associated with a given key.  If the key
        was not found, return the value defaultValue. */
    virtual ::std::vector< float >    getFloatArray(const ::std::string & key,  ::std::vector< float >&  defaultValue) throw (TypeMismatchException );
  
    /** Get the value associated with a given key.  If the key
        was not found, return the value defaultValue. */
    virtual ::std::vector< double > getDoubleArray(const ::std::string & key,  ::std::vector< double >&  defaultValue) throw (TypeMismatchException );
  
    /** Get the complex value associated with a given key.  If the key
        was not found, return the complex value defaultValue. */
    virtual ::std::vector< ::std::complex<float> > getFcomplexArray(const ::std::string & key,  ::std::vector< ::std::complex<float> >&  defaultValue) throw (TypeMismatchException );
  
    /** Get the complex value associated with a given key.  If the key
        was not found, return the complex value defaultValue. */
    virtual ::std::vector< ::std::complex<double> > getDcomplexArray(const ::std::string & key,  ::std::vector< ::std::complex<double> >&  defaultValue) throw (TypeMismatchException );
  
    /** Get the value associated with a given key.  If the key
        was not found, return the value defaultValue. */
    virtual ::std::vector< ::std::string > getStringArray(const ::std::string & key,  ::std::vector< ::std::string >&  defaultValue) throw (TypeMismatchException ) ;
  
    /** Get the value associated with a given key.  If the key
      was not found, return the value defaultValue. */
    virtual ::std::vector< bool > getBoolArray(const ::std::string & key,  ::std::vector< bool >&  defaultValue) throw (TypeMismatchException );


      // ======================================================
    
    /** Assign a key and value. Any value previously assigned
        to the same key will be overwritten.  */
    virtual void putInt(const ::std::string & key,  int32_t value) throw (TypeMismatchException );
      
    /** Assign a key and value. Any value previously assigned
        to the same key will be overwritten.  */
    virtual void putLong(const ::std::string & key,  int64_t value) throw (TypeMismatchException );
      
    /** Assign a key and value. Any value previously assigned
        to the same key will be overwritten.  */
    virtual void putFloat(const ::std::string & key,  float value) throw (TypeMismatchException );
      
    /** Assign a key and value. Any value previously assigned
        to the same key will be overwritten.  */
    virtual void putDouble(const ::std::string & key,  double value) throw (TypeMismatchException );
      
    /** Assign a key and complex value.
        Any complex value previously assigned will be overwritten.  */
    virtual void putFcomplex(const ::std::string & key,  ::std::complex<float> value)  throw (TypeMismatchException );
      
    /** Assign a key and complex value. 
        Any complex value previously assigned will be overwritten. */
    virtual void putDcomplex(const ::std::string & key,  ::std::complex<double> value) throw (TypeMismatchException );
      
    /** Assign a key and value. Any value previously assigned
        to the same key will be overwritten.  */
    virtual void putString(const ::std::string & key, const ::std::string & value) throw (TypeMismatchException ) ;
      
    /** Assign a key and value. Any value previously assigned
        to the same key will be overwritten.  */
    virtual void putBool(const ::std::string & key,  bool value) throw (TypeMismatchException ) ;
  
      // ======================================================
      
    /** Assign a key and value. Any value previously assigned
        to the same key will be overwritten. Arrays are stored
        by COPY, not by reference. */
    virtual void putIntArray(const ::std::string & key,  int32_t * value ,int length) throw (TypeMismatchException );

    /** c++ convenience function. */
    virtual void putIntArray(const ::std::string & key,  ::std::vector< int32_t >&  value) throw (TypeMismatchException );
      
    /** Assign a key and value. Any value previously assigned
        to the same key will be overwritten. Arrays are stored
        by COPY, not by reference. */
    virtual void putLongArray(const ::std::string & key,  int64_t * value ,int length) throw (TypeMismatchException );

    /** c++ convenience function. */
    virtual void putLongArray(const ::std::string & key,  ::std::vector< int64_t >&  value ) throw (TypeMismatchException );
#if (SIZEOF_LONG_INT != 8)
    virtual void putLongArray(const ::std::string & key,  ::std::vector< long int >&  value ) throw (TypeMismatchException );
#endif

    /** Assign a key and value. Any value previously assigned
        to the same key will be overwritten. Arrays are stored
        by COPY, not by reference. */
    virtual void putFloatArray(const ::std::string & key,  float * value ,int length) throw (TypeMismatchException ) ;

    /** c++ convenience function. */
    virtual void putFloatArray(const ::std::string & key,  ::std::vector< float >&  value ) throw (TypeMismatchException );
      
    /** Assign a key and value. Any value previously assigned
        to the same key will be overwritten. Arrays are stored
        by COPY, not by reference. */
    virtual void putDoubleArray(const ::std::string & key,  double * value ,int length) throw (TypeMismatchException );

    /** c++ convenience function. */
    virtual void putDoubleArray(const ::std::string & key,  ::std::vector< double >&  value) throw (TypeMismatchException ) ;
      
    /** Assign a key and complex array value. Any value previously assigned
        to the same key will be overwritten. complex arrays are stored by COPY.*/
    virtual void putFcomplexArray(const ::std::string & key,  ::std::complex<float> * value ,int length) throw (TypeMismatchException ) ;

    /** c++ convenience function. */
    virtual void putFcomplexArray(const ::std::string & key,  ::std::vector< ::std::complex<float> >&  value) throw (TypeMismatchException );
      
    /** Assign a key and complex array value. Any value previously assigned
       to the same key will be overwritten. Complex arrays are stored by COPY. */
    virtual void putDcomplexArray(const ::std::string & key,  ::std::complex<double> * value ,int length) throw (TypeMismatchException );

    /** c++ convenience function. */
    virtual void putDcomplexArray(const ::std::string & key,  ::std::vector< ::std::complex<double> >&  value) throw (TypeMismatchException );
      
    /** Assign a key and value. Any value previously assigned
        to the same key will be overwritten. Arrays are stored
        by COPY, not by reference. */
    virtual void putStringArray(const ::std::string & key,  ::std::vector< ::std::string >&  value) throw (TypeMismatchException ) ;
      
    /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten. Arrays are stored
      by COPY, not by reference. */
    virtual void putBoolArray(const ::std::string & key,  bool * value ,int length) throw (TypeMismatchException );

    /** c++ convenience function. */
    virtual void putBoolArray(const ::std::string & key,  ::std::vector< bool >&  value) throw (TypeMismatchException );

      // ======================================================

    /** Make the key and associated value disappear from the object. */
    virtual void remove (const ::std::string & key);

    /** Get all the names associated with a particular type
      without exposing the data implementation details.  The keys
      will be returned in an arbitrary order. If type specified is
      NoType (no specification) all keys of all types are returned.
      @see gov.cca.Type
    */
    virtual ::std::vector< ::std::string > getAllKeys( enum ::ccafeopq::Type t);
  
    /** Return true if the key exists in this map */
    virtual bool hasKey(const ::std::string & key);

    /** Return the type of the value associated with this key */
    virtual enum ::ccafeopq::Type typeOf(const ::std::string & key);

    //===============================================================
    // static util functions for typemaps
    //===============================================================

    static ::ccafeopq::TypeMap_shared createTypeMap();

    /** copy data into typemap from another */
    static void copyInData( ::ccafeopq::TypeMap_shared tmSrc, ::ccafeopq::TypeMap_shared tmDest);

    /** copy data into typemap from another, but ignore keys in tmSrc
     * that match the names in ignoreKeys.
     */
    static void copyInData( ::ccafeopq::TypeMap_shared tmSrc, ::ccafeopq::TypeMap_shared tmDest,
				TypeMapFilter & ignoreKeys);

    /** copy data from tmSrc to tmDest, but only for the keys and types
     * in tmSrc that match the names in srcKeys.
     */
    static void copyInKeys( ::ccafeopq::TypeMap_shared tmSrc, ::ccafeopq::TypeMap_shared tmDest,
				TypeMapFilter & srcKeys);

    /** copy data from tmSrc to tmDest, but only for the keys and types
     * in tmSrc that match the names in destKeys and the type for the
     * given name in destKeys. Names with a different type in src than in
     * dest will be ignored.
     */
    static StringVector copyInKeysTell( ::ccafeopq::TypeMap_shared tmSrc, ::ccafeopq::TypeMap_shared tmDest,
				StringVector & destKeys);

    /** copy k/v/k/v...0 array of strings to typemap.
     * Particularly it pays attention to known standard properties
     * and make everything else strings in the received map.
     */
    static void props2typemap(char** properties, ::ccafeopq::TypeMap_shared tm);

    static ::ccafeopq::TypeMap_shared props2newtypemap(char** properties);

    static StringMap props2stringmap(char ** properties);

    /** copy into typemap from stringmap */
    static void stringmap2typemap( const StringMap & stringmap, ::ccafeopq::TypeMap_shared tm );

    /** create typemap from stringmap */
    static ::ccafeopq::TypeMap_shared stringmap2newtypemap( const StringMap & stringmap );

    static void pi2typemap( ::ccafeopq::PortInfo * pi, ::ccafeopq::TypeMap_shared tm);

    static ::std::vector< ::std::string > typemap2props( ::ccafeopq::TypeMap_shared tm);

    static StringMap typemap2stringmap( ::ccafeopq::TypeMap_shared tm);

    static ::std::string stringType( ::ccafeopq::TypeMap_shared t, const ::std::string &key); 
    static ::std::string stringValue( ::ccafeopq::TypeMap_shared t, const ::std::string &key); 
    static ::ccafeopq::Type typeFromString( const ::std::string & typeName); 

    static int putValueByStrings( ::ccafeopq::TypeMap_shared t, const ::std::string & key, const ::std::string & valType, const ::std::string & val);

    static void dump( ::ccafeopq::TypeMap_shared t );

}; // end class typemap impl wrapper

} ENDSEMI // end namespace util 
} ENDSEMI // end namespace sandia
} ENDSEMI // end namespace gov

#endif // util_typemap_h_seen
