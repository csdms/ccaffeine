//#include <cca.h>
#include <AllCCA.hh>
#include "dc/export/AllExport.hh"
#include "dc/babel.new/ccafe-bind/BabelOpaqueTypeMap.hh"
#include "dc/babel.new/ccafe-bind/BabelHelper.hh"
#include "util/IO.h"

int BabelOpaqueTypeMap_Interface::genSerial = 0;


::ccafeopq::TypeMap_shared BabelOpaqueTypeMap_Interface::opaqueWrap( ::gov::cca::TypeMap client )
{
  if (!client._is_nil()) {
    BabelOpaqueTypeMap_Interface *btm =
      new BabelOpaqueTypeMap_Interface(client);
    BabelOpaqueTypeMap_ptr btmp(btm);
    ::ccafeopq::TypeMap_shared ctm = btmp;
    return ctm;
  } else {
#ifdef CCAFE_AUDIT
    IO_dn1("BabelOpaqueTypeMap opaqueWrap got nil client");
    IO_dn1("      opaqueWrap returning empty ::ccafeopq::TypeMap_shared ptr");
#endif
    ::ccafeopq::TypeMap_shared ctm;
    return ctm;
    // one good nil deserves another. don't wrap null.
  }
}


BabelOpaqueTypeMap_Interface::BabelOpaqueTypeMap_Interface( ::gov::cca::TypeMap bm)
{
#ifdef CCAFE_AUDIT
  serial = nextNum();
  IO_dn2("BabelOpaqueTypeMap create %d", serial);
#endif
  btm = bm;
}

BabelOpaqueTypeMap_Interface::~BabelOpaqueTypeMap_Interface()
{
#ifdef CCAFE_AUDIT
  serial = -serial;
  IO_dn2("BabelOpaqueTypeMap delete %d", serial);
#endif
}

 /** Create an exact copy of this Map. */
::ccafeopq::TypeMap_shared BabelOpaqueTypeMap_Interface::cloneTypeMap()
{
	return cloneData();
}

 /** Create an exact copy of this Map. */
::ccafeopq::TypeMap_shared BabelOpaqueTypeMap_Interface::cloneData()
{
	if (btm._is_nil()) {
		::ccafeopq::TypeMap_shared dtm;
		return dtm;
	}
	::gov::cca::TypeMap bm = btm.cloneTypeMap();
	BabelOpaqueTypeMap_Interface * tmi = 
		new BabelOpaqueTypeMap_Interface(btm);
	::ccafeopq::TypeMap_shared ctm(tmi);
	return ctm;
}

 /** Create a new Map with no key/value associations. */
::ccafeopq::TypeMap_shared BabelOpaqueTypeMap_Interface::cloneEmpty()
{
	if (btm._is_nil()) {
		::ccafeopq::TypeMap_shared dtm;
		return dtm;
	}
	::gov::cca::TypeMap bm = btm.cloneEmpty();
	BabelOpaqueTypeMap_Interface * tmi = 
		new BabelOpaqueTypeMap_Interface(btm);
	::ccafeopq::TypeMap_shared ctm(tmi);
	return ctm;
}

#define RETHROW1 \
  catch ( ::gov::cca::TypeMismatchException &e) \
  { \
    /* convert */ \
    ::ccafeopq::TypeMismatchException ex( \
      BabelHelper::opaqueType(e.getRequestedType()), \
      BabelHelper::opaqueType(e.getActualType()), \
      e.SIDL_EXCEPTION_getMessage()); \
    throw ex; \
  } \
  catch ( ::gov::cca::CCAException& e2) \
  { \
    ::ccafeopq::Exception ex( \
      BabelHelper::opaqueExceptionType(e2.getCCAExceptionType()), \
      e2.SIDL_EXCEPTION_getMessage()); \
    throw ex; \
  } \
  /* not reached */ \
  return dflt 

  /** rethrow1 with no return value. */
#define RETHROW2 \
  catch ( ::gov::cca::TypeMismatchException &e) \
  { \
    /* convert */ \
    ::ccafeopq::TypeMismatchException ex( \
      BabelHelper::opaqueType(e.getRequestedType()), \
      BabelHelper::opaqueType(e.getActualType()), \
      e.SIDL_EXCEPTION_getMessage()); \
    throw ex; \
  } \
  catch ( ::gov::cca::CCAException& e2) \
  { \
    ::ccafeopq::Exception ex( \
      BabelHelper::opaqueExceptionType(e2.getCCAExceptionType()), \
      e2.SIDL_EXCEPTION_getMessage()); \
    throw ex; \
  } \
  /* not reached */ \
  return

#ifdef CCAFE_AUDIT
// an evil ;-terminated macro. do not use directly.
#define NILWHINE(FNAME) IO_dn2(" " FNAME " with nil TypeMap %d", serial);
#else
#define NILWHINE(FNAME)
#endif

#define EXTRACT(TYPE, FNAME)  \
  try { \
	  if (btm._is_nil()) { \
		  NILWHINE(FNAME) \
		  return dflt; \
	  } \
	  return btm.get##TYPE(key, dflt); \
  } \
  RETHROW1

#define INSERT(TYPE, FNAME) \
    try { \
      if (btm._is_nil()) { \
	  NILWHINE(FNAME) \
      } \
      btm.put##TYPE(key, value); \
    } \
    RETHROW2



int32_t BabelOpaqueTypeMap_Interface::getInt( const ::std::string & key, int32_t dflt) throw ( ::ccafeopq::TypeMismatchException )
{
	EXTRACT(Int,"getInt");
}

int64_t BabelOpaqueTypeMap_Interface::getLong( const ::std::string & key, int64_t dflt) throw ( ::ccafeopq::TypeMismatchException )
{
	EXTRACT(Long,"getLong");
}

float BabelOpaqueTypeMap_Interface::getFloat( const ::std::string & key, float dflt) throw ( ::ccafeopq::TypeMismatchException )
{
	EXTRACT(Float,"getFloat");
}

double BabelOpaqueTypeMap_Interface::getDouble( const ::std::string & key, double dflt) throw ( ::ccafeopq::TypeMismatchException )
{
	EXTRACT(Double,"getDouble");
}

::std::complex<float> BabelOpaqueTypeMap_Interface::getFcomplex( const ::std::string & key, ::std::complex<float> dflt) throw ( ::ccafeopq::TypeMismatchException )
{
	EXTRACT(Fcomplex,"getFcomplex");
}

::std::complex<double> BabelOpaqueTypeMap_Interface::getDcomplex( const ::std::string & key, ::std::complex<double> dflt) throw ( ::ccafeopq::TypeMismatchException )
{
	EXTRACT(Dcomplex,"getDcomplex");
}

::std::string BabelOpaqueTypeMap_Interface::getString( const ::std::string & key, ::std::string dflt) throw ( ::ccafeopq::TypeMismatchException )
{
	EXTRACT(String,"getString");
}

bool BabelOpaqueTypeMap_Interface::getBool( const ::std::string & key, bool dflt) throw ( ::ccafeopq::TypeMismatchException )
{
	EXTRACT(Bool,"getBool");
}

 // ======================================================

#define EXTRACTARRAY(PRIM, TYPE, FNAME) \
  if (btm._is_nil()) { \
    NILWHINE(FNAME) \
    return dflt; \
  } \
  sidl::array< PRIM > bdflt = convertToSidlArray(dflt); \
  try { \
    sidl::array< PRIM > val = btm.get##TYPE( key, bdflt ); \
    return convertToVector( val ); \
  } \
  RETHROW1

#define EXTRACTARRAYI64(PRIM, TYPE, FNAME) \
  if (btm._is_nil()) { \
    NILWHINE(FNAME) \
    return dflt; \
  } \
  sidl::array< SIDL_LONG_ARRAY1_PRIMITIVE > bdflt = convertToSidlArrayFromI64(dflt); \
  try { \
    sidl::array< SIDL_LONG_ARRAY1_PRIMITIVE > val = btm.get##TYPE( key, bdflt ); \
    return convertToVector( val ); \
  } \
  RETHROW1

 /** Get the value associated with a given key. If the key
  was not found, return the value dflt. */
::std::vector< int32_t > BabelOpaqueTypeMap_Interface::getIntArray( const ::std::string & key, ::std::vector< int32_t >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  EXTRACTARRAY(int32_t, IntArray, "getIntArray");
}

 /** Get the value associated with a given key. If the key
  was not found, return the value dflt. */
::std::vector< int64_t > BabelOpaqueTypeMap_Interface::getLongArray( const ::std::string & key, ::std::vector< int64_t >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  // EXTRACTARRAYI64( SIDL_LONG_ARRAY1_PRIMITIVE, LongArray, "getLongArray");
  if (btm._is_nil()) { 
    NILWHINE("getLongArray") // no ; here
    return dflt; 
  } 
  sidl::array< SIDL_LONG_ARRAY1_PRIMITIVE > bdflt = convertToSidlArrayFromI64<SIDL_LONG_ARRAY1_PRIMITIVE>(dflt); 
  try { 
    sidl::array< SIDL_LONG_ARRAY1_PRIMITIVE > val = btm.getLongArray( key, bdflt ); 
    return convertToVectorFromSIDLLong( val ); 
  } 
  RETHROW1;

}

	/** saX to vX*/
	/** vX to saX */
	/** rX to saX */
	/** vi64 to sal */
	/** ri64 to sal */
	/** sal to vi64 */
  /** vl to sal */
  /** sal to vl */

 /** Get the value associated with a given key. If the key
  was not found, return the value dflt. */
#if (SIZEOF_LONG_INT != 8)
::std::vector< long int > BabelOpaqueTypeMap_Interface::getLongArray( const ::std::string & key, ::std::vector< long int >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  // EXTRACTARRAYI64( SIDL_LONG_ARRAY1_PRIMITIVE, LongArray, "getLongArray");
  if (btm._is_nil()) { 
    NILWHINE("getLongArray") // no ; here
    return dflt; 
  } 
  sidl::array< SIDL_LONG_ARRAY1_PRIMITIVE > bdflt = convertToSidlArrayFromLong<SIDL_LONG_ARRAY1_PRIMITIVE>(dflt); 
  try { 
    sidl::array< SIDL_LONG_ARRAY1_PRIMITIVE > val = btm.getLongArray( key, bdflt ); 
    return convertToVectorLongFromSIDLLong< SIDL_LONG_ARRAY1_PRIMITIVE >( val ); 
  } 
  RETHROW1;

}
#endif

 /** Get the value associated with a given key. If the key
  was not found, return the value dflt. */
::std::vector< float > BabelOpaqueTypeMap_Interface::getFloatArray( const ::std::string & key, ::std::vector< float >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  EXTRACTARRAY(float, FloatArray, "getFloatArray");
}

 /** Get the value associated with a given key. If the key
  was not found, return the value dflt. */
::std::vector< double > BabelOpaqueTypeMap_Interface::getDoubleArray( const ::std::string & key, ::std::vector< double >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  EXTRACTARRAY(double, DoubleArray, "getDoubleArray");
}

 /** Get the complex value associated with a given key. If the key
  was not found, return the complex value dflt. */
::std::vector< ::std::complex<float> > BabelOpaqueTypeMap_Interface::getFcomplexArray( const ::std::string & key, ::std::vector< ::std::complex<float> >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  EXTRACTARRAY( ::std::complex<float> , FcomplexArray, "getFcomplexArray");
}

 /** Get the complex value associated with a given key. If the key
  was not found, return the complex value dflt. */
::std::vector< ::std::complex<double> > BabelOpaqueTypeMap_Interface::getDcomplexArray( const ::std::string & key, ::std::vector< ::std::complex<double> >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  EXTRACTARRAY( ::std::complex<double> , DcomplexArray, "getDcomplexArray");
}

 /** Get the value associated with a given key. If the key
  was not found, return the value dflt. */
::std::vector< ::std::string > BabelOpaqueTypeMap_Interface::getStringArray( const ::std::string & key, ::std::vector< ::std::string >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  EXTRACTARRAY( ::std::string , StringArray, "getStringArray");
}

 /** Get the value associated with a given key. If the key
  was not found, return the value dflt. */
::std::vector< bool > BabelOpaqueTypeMap_Interface::getBoolArray( const ::std::string & key, ::std::vector< bool >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  EXTRACTARRAY( bool , BoolArray, "getBoolArray");
}


 // ======================================================
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. */
void BabelOpaqueTypeMap_Interface::putInt( const ::std::string & key, int32_t value)
throw (ccafeopq::TypeMismatchException)
{
	INSERT(Int,"putInt");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. */
void BabelOpaqueTypeMap_Interface::putLong( const ::std::string & key, int64_t value)
throw (ccafeopq::TypeMismatchException)
{
	INSERT(Long,"putLong");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. */
void BabelOpaqueTypeMap_Interface::putFloat( const ::std::string & key, float value)
throw (ccafeopq::TypeMismatchException)
{
	INSERT(Float,"putFloat");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. */
void BabelOpaqueTypeMap_Interface::putDouble( const ::std::string & key, double value)
throw (ccafeopq::TypeMismatchException)
{
	INSERT(Double,"putDouble");
}
 
 /** Assign a key and complex value.
  Any complex value previously assigned will be overwritten. */
void BabelOpaqueTypeMap_Interface::putFcomplex( const ::std::string & key, ::std::complex<float> value)
throw (ccafeopq::TypeMismatchException)
{
	INSERT(Fcomplex,"putFcomplex");
}
 
 /** Assign a key and complex value. 
  Any complex value previously assigned will be overwritten. */
void BabelOpaqueTypeMap_Interface::putDcomplex( const ::std::string & key, ::std::complex<double> value)
throw (ccafeopq::TypeMismatchException)
{
	INSERT(Dcomplex,"putDcomplex");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. */
void BabelOpaqueTypeMap_Interface::putString( const ::std::string & key, const ::std::string & value)
throw (ccafeopq::TypeMismatchException)
{
	INSERT(String,"putString");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. */
void BabelOpaqueTypeMap_Interface::putBool( const ::std::string & key, bool value)
throw (ccafeopq::TypeMismatchException)
{
	INSERT(Bool,"putBool");
}

 // ======================================================
 
#define INSERTARRAY(PRIM, TYPE, FNAME) \
  if (btm._is_nil()) { \
    NILWHINE(FNAME) \
    return; \
  } \
  sidl::array< PRIM > bdflt = convertToSidlArray(value); \
  try { \
    btm.put##TYPE( key, bdflt ); \
  } \
  RETHROW2

#define INSERTARRAYRAW(PRIM, TYPE, FNAME) \
  sidl::array< PRIM > bdflt = convertRawToSidlArray(value,length); \
  try { \
    btm.put##TYPE( key, bdflt ); \
  } \
  RETHROW2

 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. Raw arrays and vector
  content are stored by COPY, not by reference. 
  no redefinitions of type allowed.
  */
void BabelOpaqueTypeMap_Interface::putIntArray( const ::std::string & key, int32_t * value ,int length)
throw (ccafeopq::TypeMismatchException)
{
	INSERTARRAYRAW(int32_t, IntArray, "putIntArray");
}

 /** c++ convenience function. */
void BabelOpaqueTypeMap_Interface::putIntArray( const ::std::string & key, ::std::vector< int32_t >& value)
throw (ccafeopq::TypeMismatchException)
{
	INSERTARRAY(int32_t, IntArray, "putIntArray");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. Arrays are stored
  by COPY, not by reference. */
void BabelOpaqueTypeMap_Interface::putLongArray( const ::std::string & key, int64_t * value ,int length)
throw (ccafeopq::TypeMismatchException)
{
//	INSERTARRAYRAW(SIDL_LONG_ARRAY1_PRIMITIVE, LongArray, "putLongArray");
// define INSERTARRAYRAW(PRIM, TYPE, FNAME) 
  sidl::array< SIDL_LONG_ARRAY1_PRIMITIVE > bdflt = convertRawToSidlArrayLong< SIDL_LONG_ARRAY1_PRIMITIVE >(value,length); 
  try { 
    btm.putLongArray( key, bdflt ); 
  } 
  RETHROW2;
}

 /** c++ convenience function. */
void BabelOpaqueTypeMap_Interface::putLongArray( const ::std::string & key, ::std::vector< int64_t >& value )
throw (ccafeopq::TypeMismatchException)
{
  //   INSERTARRAY(int64_t, LongArray, "putLongArray");
  sidl::array< SIDL_LONG_ARRAY1_PRIMITIVE > bdflt = convertToSidlArrayFromI64< SIDL_LONG_ARRAY1_PRIMITIVE >(value); 
  try { 
    btm.putLongArray( key, bdflt ); 
  } 
  RETHROW2;

}
 
#if (SIZEOF_LONG_INT != 8)
 /** c++ convenience function. */
void BabelOpaqueTypeMap_Interface::putLongArray( const ::std::string & key, ::std::vector< long int >& value )
throw (ccafeopq::TypeMismatchException)
{
#if BABEL_REPAIRED
      INSERTARRAY(int64_t, LongArray, "putLongArray");
#else
  throw ::ccafeopq::Exception( ::ccafeopq::Nonstandard, "putLongArray has incorrect return type because of babel error.");
#endif

}
#endif
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. Arrays are stored
  by COPY, not by reference. */
void BabelOpaqueTypeMap_Interface::putFloatArray( const ::std::string & key, float * value ,int length)
throw (ccafeopq::TypeMismatchException)
{
	INSERTARRAYRAW(float, FloatArray, "putFloatArray");
}
 /** c++ convenience function. */
void BabelOpaqueTypeMap_Interface::putFloatArray( const ::std::string & key, ::std::vector< float >& value )
throw (ccafeopq::TypeMismatchException)
{
	INSERTARRAY(float, FloatArray, "putFloatArray");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. Arrays are stored
  by COPY, not by reference. */
void BabelOpaqueTypeMap_Interface::putDoubleArray( const ::std::string & key, double * value ,int length)
throw (ccafeopq::TypeMismatchException)
{
	INSERTARRAYRAW(double, DoubleArray, "putDoubleArray");
}
 /** c++ convenience function. */
void BabelOpaqueTypeMap_Interface::putDoubleArray( const ::std::string & key, ::std::vector< double >& value)
throw (ccafeopq::TypeMismatchException)
{
	INSERTARRAY(double, DoubleArray, "putDoubleArray");
}
 
 /** Assign a key and complex array value. Any value previously assigned
  to the same key will be overwritten. complex arrays are stored by COPY.*/
void BabelOpaqueTypeMap_Interface::putFcomplexArray( const ::std::string & key, ::std::complex<float> * value ,int length)
throw (ccafeopq::TypeMismatchException)
{
	INSERTARRAYRAW( ::std::complex<float>, FcomplexArray, "putFcomplexArray");
}
 /** c++ convenience function. */
void BabelOpaqueTypeMap_Interface::putFcomplexArray( const ::std::string & key, ::std::vector< ::std::complex<float> >& value)
throw (ccafeopq::TypeMismatchException)
{
	INSERTARRAY( ::std::complex<float>, FcomplexArray, "putFcomplexArray");
}
 
 /** Assign a key and complex array value. Any value previously assigned
  to the same key will be overwritten. Complex arrays are stored by COPY. */
void BabelOpaqueTypeMap_Interface::putDcomplexArray( const ::std::string & key, ::std::complex<double> * value ,int length)
throw (ccafeopq::TypeMismatchException)
{
	INSERTARRAYRAW( ::std::complex<double>, DcomplexArray, "putDcomplexArray");
}
 /** c++ convenience function. */
void BabelOpaqueTypeMap_Interface::putDcomplexArray( const ::std::string & key, ::std::vector< ::std::complex<double> >& value)
throw (ccafeopq::TypeMismatchException)
{
	INSERTARRAY( ::std::complex<double>, DcomplexArray, "putDcomplexArray");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. Arrays are stored
  by COPY, not by reference. */
void BabelOpaqueTypeMap_Interface::putStringArray( const ::std::string & key, ::std::vector< ::std::string >& value)
throw (ccafeopq::TypeMismatchException)
{
	INSERTARRAY( ::std::string, StringArray, "putStringArray");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. Arrays are stored
  by COPY, not by reference. */
void BabelOpaqueTypeMap_Interface::putBoolArray( const ::std::string & key, bool * value ,int length)
throw (ccafeopq::TypeMismatchException)
{
	INSERTARRAYRAW( bool, BoolArray, "putBoolArray");
}
 /** c++ convenience function. */
void BabelOpaqueTypeMap_Interface::putBoolArray( const ::std::string & key, ::std::vector< bool >& value)
throw (ccafeopq::TypeMismatchException)
{
	INSERTARRAY( bool, BoolArray, "putBoolArray");
}

 // ======================================================

 /** Make the key and associated value disappear from the object. */
void BabelOpaqueTypeMap_Interface::remove ( const ::std::string & key)
{
  if (btm._is_nil()) {
    IO_en2(" remove(key)  with nil TypeMap %d", serial);
    return; 
  } 
  btm.remove(key);
}

 /** Get all the names associated with a particular type
  without exposing the data implementation details. The keys
  will be returned in an arbitrary order. If type specified is
  NoType (no specification) all keys of all types are returned.
  @see Type
 */
::std::vector< ::std::string > BabelOpaqueTypeMap_Interface::getAllKeys( enum ::ccafeopq::Type t)
{
  if (btm._is_nil()) {
    IO_en2(" getAllKeys with nil TypeMap %d", serial);
    ::std::vector< std::string > v;
    return v; 
  } 
	sidl::array< ::std::string > bdflt =
	       	btm.getAllKeys( BabelHelper::babelType(t));
	return convertToVector(bdflt);
}

 /** Return true if the key exists in this map */
bool BabelOpaqueTypeMap_Interface::hasKey( const ::std::string & key)
{
  if (btm._is_nil()) {
    IO_en2(" getAllKeys with nil TypeMap %d", serial);
    return false; 
  } 
  return btm.hasKey(key);
}

 /** Return the type of the value associated with this key */
enum ::ccafeopq::Type BabelOpaqueTypeMap_Interface::typeOf( const ::std::string & key)
{
  if (btm._is_nil()) {
    IO_dn2(" typeOf with nil TypeMap %d", serial);
    return ::ccafeopq::NoType; 
  } 
	return BabelHelper::opaqueType(btm.typeOf(key));
}

    /* 074 and later array api */
#define ASET myarray.set( i , val[i] )

template <class Scalar >
sidl::array< Scalar > BabelOpaqueTypeMap_Interface::convertToSidlArray( ::std::vector< Scalar > & val )
{
  size_t len = val.size();
  sidl::array< Scalar > myarray = sidl::array< Scalar >::create1d( len );
  size_t i=0;
  for( ; i < len ; i++) {
    myarray.set( i , val[i] );
  }
  return myarray;
}

template <class Scalar >
sidl::array< Scalar > BabelOpaqueTypeMap_Interface::convertToSidlArrayFromI64( ::std::vector< int64_t > & val )
{
  size_t len = val.size();
  sidl::array< Scalar > myarray = sidl::array< Scalar >::create1d( len );
  size_t i=0;
  for( ; i < len ; i++) {
    myarray.set( i , val[i] );
  }
  return myarray;
}

template <class Scalar >
sidl::array< Scalar > BabelOpaqueTypeMap_Interface::convertToSidlArrayFromLong( ::std::vector< long int > & val)
{
  size_t len = val.size();
  sidl::array< Scalar > myarray = sidl::array< Scalar >::create1d( len );
  size_t i=0;
  for( ; i < len ; i++) {
    myarray.set( i , val[i] );
  }
  return myarray;
}

template <class Scalar >
sidl::array< Scalar > BabelOpaqueTypeMap_Interface::convertRawToSidlArray( Scalar * val , size_t len)
{
  sidl::array< Scalar > myarray = sidl::array< Scalar >::create1d( len );
  size_t i=0;
  for( ; i < len ; i++) {
    myarray.set( i , val[i] );
  }
  return myarray;
}

template <class Scalar >
sidl::array< Scalar > BabelOpaqueTypeMap_Interface::convertRawToSidlArrayLong( int64_t * val , size_t len)
{
  sidl::array< Scalar > myarray = sidl::array< Scalar >::create1d( len );
  size_t i=0;
  for( ; i < len ; i++) {
    myarray.set( i , val[i] );
  }
  return myarray;
}


template <class Scalar >
::std::vector< Scalar > BabelOpaqueTypeMap_Interface::convertToVector( sidl::array< Scalar > & val )
{
	int len = (val.upper(0) - val.lower(0)) + 1;
	::std::vector< Scalar > res(len);
	int bottom = val.lower(0);
	for(int i=0; i < len ; i++) {
		res[i] =  ( val.get(bottom + i) );
	}
	return res;
}

template <class Scalar >
::std::vector< int64_t > BabelOpaqueTypeMap_Interface::convertToVectorFromSIDLLong( sidl::array< Scalar > & val )
{
	int len = (val.upper(0) - val.lower(0)) + 1;
	::std::vector< int64_t > res(len);
	int bottom = val.lower(0);
	for(int i=0; i < len ; i++) {
		res[i] =  ( val.get(bottom + i) );
	}
	return res;
}

template <class Scalar >
::std::vector< long int > BabelOpaqueTypeMap_Interface::convertToVectorLongFromSIDLLong( sidl::array< Scalar > & val ) 
{
	int len = (val.upper(0) - val.lower(0)) + 1;
	::std::vector< long int > res(len);
	int bottom = val.lower(0);
	for(int i=0; i < len ; i++) {
		res[i] =  ( val.get(bottom + i) );
	}
	return res;
}


