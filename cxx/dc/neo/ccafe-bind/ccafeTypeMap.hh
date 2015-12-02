#ifndef __CCAFE_TYPEMAP_H__
#define __CCAFE_TYPEMAP_H__

/** neoclassic implementation ala ccafe */ 

namespace ccafe {

class TypeMap;

typedef boost::shared_ptr<TypeMap> TypeMap_shared;

/** Wrapper into the neo binding of the raw ccafeopq typemap.
 * This can't be implemented by inheritance due to the 
 * differing return-types on the clone functions.
 */
class TypeMap : public virtual neo::cca::TypeMap
{
private:
  ::ccafeopq::TypeMap_shared ctm;

  int serial;
  static int nextNum() { genSerial++; return genSerial; }
  static int genSerial;

public:

  /** wrap an opq tm in a neo tm. */
  static ::neo::cca::TypeMap_shared neoWrap( ::ccafeopq::TypeMap_shared ctm_);

  /** if map is one of ours, unwrap it. */
  static ::ccafeopq::TypeMap_shared unWrap( neo::cca::TypeMap_shared ctm_, bool & ok);

  /** real constructor */
  TypeMap();

  /** qc test constructor. do not use. */
  TypeMap(int bogon);

  /** required destructor */
  virtual ~TypeMap();
  
  /** Create an exact copy of this Map. */
  virtual neo::cca::TypeMap_shared cloneData();
  
  /** Create a new Map with no key/value associations. */
  virtual neo::cca::TypeMap_shared cloneEmpty();
  
  /** Get the Int value associated with a given key.  If the key
      was not found, return the value defaultValue. */
  virtual int32_t      getInt(const ::std::string & key,  int32_t defaultValue) throw (neo::cca::TypeMismatchException );
  
  /** Get the Long value associated with a given key.  If the key
      was not found, return the value defaultValue. */
  virtual int64_t  getLong(const ::std::string & key,  int64_t defaultValue) throw (neo::cca::TypeMismatchException );
  
  /** Get the Float value associated with a given key.  If the key
      was not found, return the value defaultValue. */
  virtual float    getFloat(const ::std::string & key,  float defaultValue) throw (neo::cca::TypeMismatchException );
  
  /** Get the Double value associated with a given key.  If the key
      was not found, return the value defaultValue. */
  virtual double   getDouble(const ::std::string & key,  double defaultValue) throw (neo::cca::TypeMismatchException );
  
  /** Get the Fcomplex value associated with a given key.  If the key
      was not found, return complex the value defaultValue. */
  virtual ::std::complex<float> getFcomplex(const ::std::string & key,  ::std::complex<float> defaultValue) throw (neo::cca::TypeMismatchException ); 
  
  /** Get the Dcomplex value associated with a given key.  If the key
      was not found, return the complex value defaultValue. */
  virtual ::std::complex<double> getDcomplex(const ::std::string & key,  ::std::complex<double> defaultValue) throw (neo::cca::TypeMismatchException ); 
  
  /** Get the string value associated with a given key.  If the key
      was not found, return the value defaultValue. */
  virtual ::std::string  getString(const ::std::string & key,  ::std::string defaultValue) throw (neo::cca::TypeMismatchException );
  
  /** Get the boolean value associated with a given key.  If the key
      was not found, return the value defaultValue. */
  virtual bool  getBool(const ::std::string & key,  bool defaultValue) throw (neo::cca::TypeMismatchException );
  
    // ======================================================
  
  /** Get the value associated with a given key.  If the key
      was not found, return the value defaultValue. */
  virtual ::std::vector< int32_t > getIntArray(const ::std::string & key,  ::std::vector< int32_t >&  defaultValue) throw (neo::cca::TypeMismatchException );
  
  /** Get the value associated with a given key.  If the key
      was not found, return the value defaultValue. */
  virtual ::std::vector< int64_t > getLongArray(const ::std::string & key,  ::std::vector< int64_t >&  defaultValue) throw (neo::cca::TypeMismatchException );
  
  /** Get the value associated with a given key.  If the key
      was not found, return the value defaultValue. */
  virtual ::std::vector< float >    getFloatArray(const ::std::string & key,  ::std::vector< float >&  defaultValue) throw (neo::cca::TypeMismatchException );
  
  /** Get the value associated with a given key.  If the key
      was not found, return the value defaultValue. */
  virtual ::std::vector< double > getDoubleArray(const ::std::string & key,  ::std::vector< double >&  defaultValue) throw (neo::cca::TypeMismatchException );
  
  /** Get the complex value associated with a given key.  If the key
      was not found, return the complex value defaultValue. */
  virtual ::std::vector< ::std::complex<float> > getFcomplexArray(const ::std::string & key,  ::std::vector< ::std::complex<float> >&  defaultValue) throw (neo::cca::TypeMismatchException );
  
  /** Get the complex value associated with a given key.  If the key
      was not found, return the complex value defaultValue. */
  virtual ::std::vector< ::std::complex<double> > getDcomplexArray(const ::std::string & key,  ::std::vector< ::std::complex<double> >&  defaultValue) throw (neo::cca::TypeMismatchException );
  
  /** Get the value associated with a given key.  If the key
      was not found, return the value defaultValue. */
  virtual ::std::vector< ::std::string > getStringArray(const ::std::string & key,  ::std::vector< ::std::string >&  defaultValue) throw (neo::cca::TypeMismatchException );
  
  /** Get the value associated with a given key.  If the key
    was not found, return the value defaultValue. */
  virtual ::std::vector< bool > getBoolArray(const ::std::string & key,  ::std::vector< bool >&  defaultValue) throw (neo::cca::TypeMismatchException );


    // ======================================================
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten if type identical.  */
  virtual void putInt(const ::std::string & key,  int value) throw (neo::cca::TypeMismatchException );
      
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten if type identical.  */
  virtual void putLong(const ::std::string & key,  int64_t value) throw (neo::cca::TypeMismatchException );
      
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten if type identical.  */
  virtual void putFloat(const ::std::string & key,  float value) throw (neo::cca::TypeMismatchException );
      
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten if type identical.  */
  virtual void putDouble(const ::std::string & key,  double value) throw (neo::cca::TypeMismatchException );
      
  /** Assign a key and complex value.
      Any complex value previously assigned will be overwritten.  */
  virtual void putFcomplex(const ::std::string & key,  ::std::complex<float> value) throw (neo::cca::TypeMismatchException ); 
      
  /** Assign a key and complex value. 
      Any complex value previously assigned will be overwritten. */
  virtual void putDcomplex(const ::std::string & key,  ::std::complex<double> value) throw (neo::cca::TypeMismatchException );
      
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten if type identical.  */
  virtual void putString(const ::std::string & key, const ::std::string & value) throw (neo::cca::TypeMismatchException );
      
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten if type identical.  */
  virtual void putBool(const ::std::string & key,  bool value) throw (neo::cca::TypeMismatchException );
  
      // ======================================================
      
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten if type identical.
      Arrays are stored by COPY, not by reference. */
  virtual void putIntArray(const ::std::string & key,  int * value ,int length) throw (neo::cca::TypeMismatchException );
  /** c++ convenience function. */
  virtual void putIntArray(const ::std::string & key,  ::std::vector< int >&  value) throw (neo::cca::TypeMismatchException );
      
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten if type identical.
      Arrays are stored by COPY, not by reference. */
  virtual void putLongArray(const ::std::string & key,  int64_t * value ,int length) throw (neo::cca::TypeMismatchException );
  /** c++ convenience function. */
  virtual void putLongArray(const ::std::string & key,  ::std::vector< int64_t >&  value ) throw (neo::cca::TypeMismatchException );
      
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten if type identical.
      Arrays are stored by COPY, not by reference. */
  virtual void putFloatArray(const ::std::string & key,  float * value ,int length) throw (neo::cca::TypeMismatchException );
  /** c++ convenience function. */
  virtual void putFloatArray(const ::std::string & key,  ::std::vector< float >&  value ) throw (neo::cca::TypeMismatchException );
      
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten if type identical.
      Arrays are stored by COPY, not by reference. */
  virtual void putDoubleArray(const ::std::string & key,  double * value ,int length) throw (neo::cca::TypeMismatchException );
  /** c++ convenience function. */
  virtual void putDoubleArray(const ::std::string & key,  ::std::vector< double >&  value) throw (neo::cca::TypeMismatchException );
      
  /** Assign a key and complex array value. Any value previously assigned
      to the same key will be overwritten if type identical.
      Complex arrays are stored by COPY.*/
  virtual void putFcomplexArray(const ::std::string & key,  ::std::complex<float> * value ,int length) throw (neo::cca::TypeMismatchException );
  /** c++ convenience function. */
  virtual void putFcomplexArray(const ::std::string & key,  ::std::vector< ::std::complex<float> >&  value) throw (neo::cca::TypeMismatchException );
      
  /** Assign a key and complex array value. Any value previously assigned
     to the same key will be overwritten if type identical.
     Complex arrays are stored by COPY. */
  virtual void putDcomplexArray(const ::std::string & key,  ::std::complex<double> * value ,int length) throw (neo::cca::TypeMismatchException );
  /** c++ convenience function. */
  virtual void putDcomplexArray(const ::std::string & key,  ::std::vector< ::std::complex<double> >&  value) throw (neo::cca::TypeMismatchException );
      
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten if type identical..
      Arrays are stored by COPY, not by reference. */
  virtual void putStringArray(const ::std::string & key,  ::std::vector< ::std::string >&  value) throw (neo::cca::TypeMismatchException );
      
  /** Assign a key and value. Any value previously assigned
    to the same key will be overwritten if type identical. 
    Arrays are stored by COPY, not by reference. */
  virtual void putBoolArray(const ::std::string & key,  bool * value ,int length) throw (neo::cca::TypeMismatchException );
  /** c++ convenience function. */
  virtual void putBoolArray(const ::std::string & key,  ::std::vector< bool >&  value) throw (neo::cca::TypeMismatchException );

    // ======================================================

  /** Make the key and associated value disappear from the object. */
  virtual void remove (const ::std::string & key);

  /** Get all the names associated with a particular type
    without exposing the data implementation details.  The keys
    will be returned in an arbitrary order. If type specified is
    NoType (no specification) all keys of all types are returned.
    @see neo.cca.Type
  */
  virtual ::std::vector< ::std::string > getAllKeys( enum neo::cca::Type t);
  
  /** Return true if the key exists in this map */
  virtual bool hasKey(const ::std::string & key);

  /** Return the type of the value associated with this key */
  virtual enum neo::cca::Type typeOf(const ::std::string & key);

} ; // end implementation neo TypeMap

} ENDSEMI  // end namespace ccafe

#endif //__CCAFE_TYPEMAP_H_ 
