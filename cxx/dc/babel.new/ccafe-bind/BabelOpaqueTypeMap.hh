#ifndef __BABELOPAQUETYPEMAP_H__
#define __BABELOPAQUETYPEMAP_H__

#include <boost/shared_ptr.hpp>
#include <AllCCA.hh>

class BabelOpaqueTypeMap_Interface;

typedef ::boost::shared_ptr< BabelOpaqueTypeMap_Interface > BabelOpaqueTypeMap_ptr; // FIXME

/**
 * This class wraps a Babel typemap and makes it into a ccafeopq typemap.
 * It's necessary because there's no *safe* way to unwrap 
 * a babel critter and prove it originated in the framework.
 */
class BabelOpaqueTypeMap_Interface : public virtual ::ccafeopq::TypeMap_Interface
{
private:
  ::gov::cca::TypeMap btm;
  int serial;
  static int nextNum() { genSerial++; return genSerial; }
  static int genSerial;


public:

  /** wrap a babel map. if the babeler is nil, return and empty
   * shared_ptr, not a shared_ptr to and empty wrapper.
   */
  static ::ccafeopq::TypeMap_shared opaqueWrap( ::gov::cca::TypeMap client );

  virtual ~BabelOpaqueTypeMap_Interface();

  BabelOpaqueTypeMap_Interface( ::gov::cca::TypeMap bm);

  /** Create an exact copy of this Map. */
  virtual ::ccafeopq::TypeMap_shared cloneData();
  virtual ::ccafeopq::TypeMap_shared cloneTypeMap();

  /** Create a new Map with no key/value associations. */
  virtual ::ccafeopq::TypeMap_shared cloneEmpty();

  virtual int32_t getInt( const ::std::string & key,  int32_t dflt) throw ( ::ccafeopq::TypeMismatchException );

  virtual int64_t getLong( const ::std::string & key,  int64_t dflt) throw ( ::ccafeopq::TypeMismatchException );

  virtual float getFloat( const ::std::string & key,  float dflt) throw ( ::ccafeopq::TypeMismatchException );

  virtual double getDouble( const ::std::string & key,  double dflt) throw ( ::ccafeopq::TypeMismatchException );

  virtual ::std::complex<float> getFcomplex( const ::std::string & key, ::std::complex<float> dflt) throw ( ::ccafeopq::TypeMismatchException );

  virtual ::std::complex<double> getDcomplex( const ::std::string & key, ::std::complex<double> dflt) throw ( ::ccafeopq::TypeMismatchException );

  virtual ::std::string  getString( const ::std::string & key, ::std::string dflt) throw ( ::ccafeopq::TypeMismatchException );

  virtual bool  getBool( const ::std::string & key, bool dflt) throw ( ::ccafeopq::TypeMismatchException );

    // ======================================================

  /** Get the value associated with a given key.  If the key
      was not found, return the value dflt. */
  virtual ::std::vector< int32_t > getIntArray( const ::std::string & key,  ::std::vector< int32_t >&  dflt) throw ( ::ccafeopq::TypeMismatchException );

  /** Get the value associated with a given key.  If the key
      was not found, return the value dflt. */
  virtual ::std::vector< int64_t > getLongArray( const ::std::string & key,  ::std::vector< int64_t >&  dflt) throw ( ::ccafeopq::TypeMismatchException );

#if (SIZEOF_LONG_INT != 8)
  virtual ::std::vector< long int > getLongArray( const ::std::string & key,  ::std::vector< long int >&  dflt) throw ( ::ccafeopq::TypeMismatchException );
#endif

  /** Get the value associated with a given key.  If the key
      was not found, return the value dflt. */
  virtual ::std::vector< float >  getFloatArray( const ::std::string & key,  ::std::vector< float >&  dflt) throw ( ::ccafeopq::TypeMismatchException );

  /** Get the value associated with a given key.  If the key
      was not found, return the value dflt. */
  virtual ::std::vector< double > getDoubleArray( const ::std::string & key,  ::std::vector< double >&  dflt) throw ( ::ccafeopq::TypeMismatchException );

  /** Get the complex value associated with a given key.  If the key
      was not found, return the complex value dflt. */
  virtual ::std::vector< ::std::complex<float> > getFcomplexArray( const ::std::string & key,  ::std::vector< ::std::complex<float> >&  dflt) throw ( ::ccafeopq::TypeMismatchException );

  /** Get the complex value associated with a given key.  If the key
      was not found, return the complex value dflt. */
  virtual ::std::vector< ::std::complex<double> > getDcomplexArray( const ::std::string & key,  ::std::vector< ::std::complex<double> >&  dflt) throw ( ::ccafeopq::TypeMismatchException );

  /** Get the value associated with a given key.  If the key
      was not found, return the value dflt. */
  virtual ::std::vector< ::std::string > getStringArray( const ::std::string & key,  ::std::vector< ::std::string >&  dflt) throw ( ::ccafeopq::TypeMismatchException );

  /** Get the value associated with a given key.  If the key
      was not found, return the value dflt. */
  virtual ::std::vector< bool > getBoolArray( const ::std::string & key,  ::std::vector< bool >&  dflt) throw ( ::ccafeopq::TypeMismatchException );


    // ======================================================
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten.  */
  virtual void putInt( const ::std::string & key,  int32_t value) throw (ccafeopq::TypeMismatchException);
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten.  */
  virtual void putLong( const ::std::string & key,  int64_t value) throw (ccafeopq::TypeMismatchException);
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten.  */
  virtual void putFloat( const ::std::string & key,  float value) throw (ccafeopq::TypeMismatchException);
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten.  */
  virtual void putDouble( const ::std::string & key,  double value) throw (ccafeopq::TypeMismatchException);
    
  /** Assign a key and complex value.
      Any complex value previously assigned will be overwritten.  */
  virtual void putFcomplex( const ::std::string & key,  ::std::complex<float> value) throw (ccafeopq::TypeMismatchException);
    
  /** Assign a key and complex value. 
      Any complex value previously assigned will be overwritten. */
  virtual void putDcomplex( const ::std::string & key,  ::std::complex<double> value) throw (ccafeopq::TypeMismatchException);
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten.  */
  virtual void putString( const ::std::string & key, const ::std::string & value) throw (ccafeopq::TypeMismatchException);
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten.  */
  virtual void putBool( const ::std::string & key,  bool value) throw (ccafeopq::TypeMismatchException);

    // ======================================================
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten. Raw arrays and vector content are stored
      by COPY, not by reference. */
  virtual void putIntArray( const ::std::string & key,  int32_t * value ,int length) throw (ccafeopq::TypeMismatchException);
  /** c++ convenience function. */
  virtual void putIntArray( const ::std::string & key,  ::std::vector< int32_t >&  value) throw (ccafeopq::TypeMismatchException);
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten. Arrays are stored
      by COPY, not by reference. */
  virtual void putLongArray( const ::std::string & key,  int64_t * value ,int length) throw (ccafeopq::TypeMismatchException);
  /** c++ convenience function. */
  virtual void putLongArray( const ::std::string & key,  ::std::vector< int64_t >&  value ) throw (ccafeopq::TypeMismatchException);
#if (SIZEOF_LONG_INT != 8)
  virtual void putLongArray( const ::std::string & key,  ::std::vector< long int >&  value ) throw (ccafeopq::TypeMismatchException);
#endif
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten. Arrays are stored
      by COPY, not by reference. */
  virtual void putFloatArray( const ::std::string & key,  float * value ,int length) throw (ccafeopq::TypeMismatchException);
  /** c++ convenience function. */
  virtual void putFloatArray( const ::std::string & key,  ::std::vector< float >&  value ) throw (ccafeopq::TypeMismatchException);
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten. Arrays are stored
      by COPY, not by reference. */
  virtual void putDoubleArray( const ::std::string & key,  double * value ,int length) throw (ccafeopq::TypeMismatchException);
  /** c++ convenience function. */
  virtual void putDoubleArray( const ::std::string & key,  ::std::vector< double >&  value) throw (ccafeopq::TypeMismatchException);
    
  /** Assign a key and complex array value. Any value previously assigned
      to the same key will be overwritten. complex arrays are stored by COPY.*/
  virtual void putFcomplexArray( const ::std::string & key,  ::std::complex<float> * value ,int length) throw (ccafeopq::TypeMismatchException);
  /** c++ convenience function. */
  virtual void putFcomplexArray( const ::std::string & key,  ::std::vector< ::std::complex<float> >&  value) throw (ccafeopq::TypeMismatchException);
    
  /** Assign a key and complex array value. Any value previously assigned
     to the same key will be overwritten. Complex arrays are stored by COPY. */
  virtual void putDcomplexArray( const ::std::string & key,  ::std::complex<double> * value ,int length) throw (ccafeopq::TypeMismatchException);
  /** c++ convenience function. */
  virtual void putDcomplexArray( const ::std::string & key,  ::std::vector< ::std::complex<double> >&  value) throw (ccafeopq::TypeMismatchException);
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten. Arrays are stored
      by COPY, not by reference. */
  virtual void putStringArray( const ::std::string & key,  ::std::vector< ::std::string >&  value) throw (ccafeopq::TypeMismatchException);
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten. Arrays are stored
      by COPY, not by reference. */
  virtual void putBoolArray( const ::std::string & key,  bool * value ,int length) throw (ccafeopq::TypeMismatchException);
  /** c++ convenience function. */
  virtual void putBoolArray( const ::std::string & key,  ::std::vector< bool >&  value) throw (ccafeopq::TypeMismatchException);

    // ======================================================

  /** Make the key and associated value disappear from the object. */
  virtual void remove ( const ::std::string & key);

  /** Get all the names associated with a particular type
      without exposing the data implementation details.  The keys
      will be returned in an arbitrary order. If type specified is
      NoType (no specification) all keys of all types are returned.
      @see Type
  */
  virtual ::std::vector< ::std::string > getAllKeys( enum ::ccafeopq::Type t);

  /** Return true if the key exists in this map */
  virtual bool hasKey( const ::std::string & key);

  /** Return the type of the value associated with this key */
  virtual enum ::ccafeopq::Type typeOf( const ::std::string & key);

	// /** sal to vl */
	/** saX to vX*/
  template <class Scalar >
  ::std::vector< Scalar > convertToVector( sidl::array< Scalar > & val ) ;

	/** vl to saL */
  template <class Scalar > 
	sidl::array< Scalar > convertToSidlArrayFromLong( ::std::vector< long int > & val);

	/** vX to saX */
  template <class Scalar > 
  sidl::array< Scalar > convertToSidlArray( ::std::vector< Scalar > & val );

	/** rX to saX */
  template <class Scalar > 
  sidl::array< Scalar > convertRawToSidlArray( Scalar * val , size_t len);

	/** vi64 to saL */
  template <class Scalar >
  sidl::array< Scalar > convertToSidlArrayFromI64( ::std::vector< int64_t > & val );

	/** ri64 to saL */
  template <class Scalar > 
  sidl::array< Scalar > convertRawToSidlArrayLong( int64_t * val , size_t len);

	/** saL to vi64*/
  template <class Scalar >
  ::std::vector< int64_t > convertToVectorFromSIDLLong( sidl::array< Scalar > & val ) ;

	/** saL to vl */
  template <class Scalar >
  ::std::vector< long int > convertToVectorLongFromSIDLLong( sidl::array< Scalar > & val ) ;


};


#endif //__BABELOPAQUETYPEMAP_H__
