//#include <cca.h>
#include <neocca.hh>
#include "dc/export/AllExport.hh"
#include "dc/neo/ccafe-bind/NeoOpaqueTypeMap.hh"
#include "dc/neo/ccafe-bind/NeoHelper.hh"
#include "util/IO.h"

int NeoOpaqueTypeMap::genSerial = 0;


::ccafeopq::TypeMap_shared NeoOpaqueTypeMap::opaqueWrap( ::neo::cca::TypeMap_shared & client )
{
  if (!client) {
#ifdef CCAFE_AUDIT
    IO_dn1("NeoOpaqueTypeMap opaqueWrap got nil client");
    IO_dn1("      opaqueWrap returning empty ::ccafeopq::TypeMap ptr");
#endif
    ::ccafeopq::TypeMap_shared ctm;
    return ctm;
    // one good nil deserves another. don't wrap null.
  } else {
    NeoOpaqueTypeMap *ntm = new NeoOpaqueTypeMap(client);
    NeoOpaqueTypeMap_shared ntmp(ntm);
    ::ccafeopq::TypeMap_shared ctm = ntmp;
    return ctm;
  }
}


NeoOpaqueTypeMap::NeoOpaqueTypeMap( int bogon )
{
	serial = 0;
}

NeoOpaqueTypeMap::NeoOpaqueTypeMap( ::neo::cca::TypeMap_shared & nm)
{
#ifdef CCAFE_AUDIT
	serial = nextNum();
	IO_dn2("NeoOpaqueTypeMap create %d", serial);
#endif
	ntm = nm;
}

NeoOpaqueTypeMap::~NeoOpaqueTypeMap()
{
#ifdef CCAFE_AUDIT
	serial = -serial;
	IO_dn2("NeoOpaqueTypeMap delete %d", serial);
#endif
}

 /** Create an exact copy of this Map. */
::ccafeopq::TypeMap_shared NeoOpaqueTypeMap::cloneTypeMap()
{
	return cloneData();
}

 /** Create an exact copy of this Map. */
::ccafeopq::TypeMap_shared NeoOpaqueTypeMap::cloneData()
{
	if (!ntm) {
		ccafeopq::TypeMap_shared dtm;
		return dtm;
	}
	// clone data of unknown impl type
	::neo::cca::TypeMap_shared nm = ntm->cloneData();
	// make wrapper object
	NeoOpaqueTypeMap * tmi = new NeoOpaqueTypeMap(ntm);
	// make sharedptr from wrapper.
	ccafeopq::TypeMap_shared ctm(tmi);
	return ctm;
}

 /** Create a new Map with no key/value associations. */
::ccafeopq::TypeMap_shared NeoOpaqueTypeMap::cloneEmpty()
{
	if (!ntm) {
		ccafeopq::TypeMap_shared dtm;
		return dtm;
	}
	::neo::cca::TypeMap_shared nm = ntm->cloneEmpty();
	NeoOpaqueTypeMap * tmi = new NeoOpaqueTypeMap(ntm);
	::ccafeopq::TypeMap_shared ctm(tmi);
	return ctm;
}

#define RETHROW1 \
  catch ( ::neo::cca::TypeMismatchException &e) \
  { \
    /* convert */ \
    ::ccafeopq::TypeMismatchException ex( \
      NeoHelper::opaqueType(e.getRequestedType()), \
      NeoHelper::opaqueType(e.getActualType()), \
      e.getMessage()); \
    throw ex; \
  } \
  catch ( ::neo::cca::Exception& e2) \
  { \
    ::ccafeopq::Exception ex( \
      NeoHelper::opaqueExceptionType(e2.getType()), \
      e2.getMessage()); \
    throw ex; \
  } \
  /* not reached */ \
  return dflt 

  /** rethrow1 with no return value. */
#define RETHROW2 \
  catch ( ::neo::cca::TypeMismatchException &e) \
  { \
    /* convert */ \
    ::ccafeopq::TypeMismatchException ex( \
      NeoHelper::opaqueType(e.getRequestedType()), \
      NeoHelper::opaqueType(e.getActualType()), \
      e.getMessage()); \
    throw ex; \
  } \
  catch ( ::neo::cca::Exception& e2) \
  { \
    ::ccafeopq::Exception ex( \
      NeoHelper::opaqueExceptionType(e2.getType()), \
      e2.getMessage()); \
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
	  if (!ntm) { \
		  NILWHINE(FNAME) \
		  return dflt; \
	  } \
	  return ntm->get##TYPE(key, dflt); \
  } \
  RETHROW1

#define INSERT(TYPE, FNAME) \
    try { \
      if (!ntm) { \
	  NILWHINE(FNAME) \
      } \
      ntm->put##TYPE(key, value); \
    } \
    RETHROW2



int32_t NeoOpaqueTypeMap::getInt( const ::std::string & key, int32_t dflt) throw ( ::ccafeopq::TypeMismatchException )
{
	EXTRACT(Int,"getInt");
}

int64_t NeoOpaqueTypeMap::getLong( const ::std::string & key, int64_t dflt) throw ( ::ccafeopq::TypeMismatchException )
{
	EXTRACT(Long,"getLong");
}

float NeoOpaqueTypeMap::getFloat( const ::std::string & key, float dflt) throw ( ::ccafeopq::TypeMismatchException )
{
	EXTRACT(Float,"getFloat");
}

double NeoOpaqueTypeMap::getDouble( const ::std::string & key, double dflt) throw ( ::ccafeopq::TypeMismatchException )
{
	EXTRACT(Double,"getDouble");
}

::std::complex<float> NeoOpaqueTypeMap::getFcomplex( const ::std::string & key, ::std::complex<float> dflt) throw ( ::ccafeopq::TypeMismatchException )
{
	EXTRACT(Fcomplex,"getFcomplex");
}

::std::complex<double> NeoOpaqueTypeMap::getDcomplex( const ::std::string & key, ::std::complex<double> dflt) throw ( ::ccafeopq::TypeMismatchException )
{
	EXTRACT(Dcomplex,"getDcomplex");
}

::std::string NeoOpaqueTypeMap::getString( const ::std::string & key, ::std::string dflt) throw ( ::ccafeopq::TypeMismatchException )
{
	EXTRACT(String,"getString");
}

bool NeoOpaqueTypeMap::getBool( const ::std::string & key, bool dflt) throw ( ::ccafeopq::TypeMismatchException )
{
	EXTRACT(Bool,"getBool");
}

 // ======================================================

#define EXTRACTARRAY(PRIM, TYPE, FNAME) \
  if (!ntm) { \
    NILWHINE(FNAME) \
    return dflt; \
  } \
  try { \
    return ntm->get##TYPE( key, dflt ); \
  } \
  RETHROW1

#define EXTRACTARRAYI64(PRIM, TYPE, FNAME) \
  if (!ntm) { \
    NILWHINE(FNAME) \
    return dflt; \
  } \
  try { \
    return ntm->get##TYPE( key, dflt ); \
  } \
  RETHROW1

 /** Get the value associated with a given key. If the key
  was not found, return the value dflt. */
::std::vector< int32_t > NeoOpaqueTypeMap::getIntArray( const ::std::string & key, ::std::vector< int32_t >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  EXTRACTARRAY(int32_t, IntArray, "getIntArray");
}

 /** Get the value associated with a given key. If the key
  was not found, return the value dflt. */
::std::vector< int64_t > NeoOpaqueTypeMap::getLongArray( const ::std::string & key, ::std::vector< int64_t >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  if (!ntm) { 
    NILWHINE("getLongArray") // no ; here
    return dflt; 
  } 
  try { 
    return ntm->getLongArray( key, dflt ); 
  } 
  RETHROW1;

}


 /** Get the value associated with a given key. If the key
  was not found, return the value dflt. */
::std::vector< float > NeoOpaqueTypeMap::getFloatArray( const ::std::string & key, ::std::vector< float >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  EXTRACTARRAY(float, FloatArray, "getFloatArray");
}

 /** Get the value associated with a given key. If the key
  was not found, return the value dflt. */
::std::vector< double > NeoOpaqueTypeMap::getDoubleArray( const ::std::string & key, ::std::vector< double >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  EXTRACTARRAY(double, DoubleArray, "getDoubleArray");
}

 /** Get the complex value associated with a given key. If the key
  was not found, return the complex value dflt. */
::std::vector< ::std::complex<float> > NeoOpaqueTypeMap::getFcomplexArray( const ::std::string & key, ::std::vector< ::std::complex<float> >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  EXTRACTARRAY( ::std::complex<float> , FcomplexArray, "getFcomplexArray");
}

 /** Get the complex value associated with a given key. If the key
  was not found, return the complex value dflt. */
::std::vector< ::std::complex<double> > NeoOpaqueTypeMap::getDcomplexArray( const ::std::string & key, ::std::vector< ::std::complex<double> >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  EXTRACTARRAY( ::std::complex<double> , DcomplexArray, "getDcomplexArray");
}

 /** Get the value associated with a given key. If the key
  was not found, return the value dflt. */
::std::vector< ::std::string > NeoOpaqueTypeMap::getStringArray( const ::std::string & key, ::std::vector< ::std::string >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  EXTRACTARRAY( ::std::string , StringArray, "getStringArray");
}

 /** Get the value associated with a given key. If the key
  was not found, return the value dflt. */
::std::vector< bool > NeoOpaqueTypeMap::getBoolArray( const ::std::string & key, ::std::vector< bool >& dflt) throw ( ::ccafeopq::TypeMismatchException )
{
  EXTRACTARRAY( bool , BoolArray, "getBoolArray");
}


 // ======================================================
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. */
void NeoOpaqueTypeMap::putInt( const ::std::string & key, int32_t value)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERT(Int,"putInt");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. */
void NeoOpaqueTypeMap::putLong( const ::std::string & key, int64_t value)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERT(Long,"putLong");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. */
void NeoOpaqueTypeMap::putFloat( const ::std::string & key, float value)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERT(Float,"putFloat");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. */
void NeoOpaqueTypeMap::putDouble( const ::std::string & key, double value)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERT(Double,"putDouble");
}
 
 /** Assign a key and complex value.
  Any complex value previously assigned will be overwritten. */
void NeoOpaqueTypeMap::putFcomplex( const ::std::string & key, ::std::complex<float> value)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERT(Fcomplex,"putFcomplex");
}
 
 /** Assign a key and complex value. 
  Any complex value previously assigned will be overwritten. */
void NeoOpaqueTypeMap::putDcomplex( const ::std::string & key, ::std::complex<double> value)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERT(Dcomplex,"putDcomplex");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. */
void NeoOpaqueTypeMap::putString( const ::std::string & key, const ::std::string & value)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERT(String,"putString");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. */
void NeoOpaqueTypeMap::putBool( const ::std::string & key, bool value)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERT(Bool,"putBool");
}

 // ======================================================
 
#define INSERTARRAY(PRIM, TYPE, FNAME) \
  if (!ntm) { \
    NILWHINE(FNAME) \
    return; \
  } \
  try { \
    ntm->put##TYPE( key, value ); \
  } \
  RETHROW2

#define INSERTARRAYRAW(PRIM, TYPE, FNAME) \
  try { \
    ntm->put##TYPE( key, value, length ); \
  } \
  RETHROW2

 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. Raw arrays and vector
  content are stored by COPY, not by reference. 
  no redefinitions of type allowed.
  */
void NeoOpaqueTypeMap::putIntArray( const ::std::string & key, int32_t * value ,int length)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERTARRAYRAW(int32_t, IntArray, "putIntArray");
}

 /** c++ convenience function. */
void NeoOpaqueTypeMap::putIntArray( const ::std::string & key, ::std::vector< int32_t >& value)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERTARRAY(int32_t, IntArray, "putIntArray");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. Arrays are stored
  by COPY, not by reference. */
void NeoOpaqueTypeMap::putLongArray( const ::std::string & key, int64_t * value ,int length)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERTARRAYRAW(int64_t, LongArray, "putLongArray");
}

 /** c++ convenience function. */
void NeoOpaqueTypeMap::putLongArray( const ::std::string & key, ::std::vector< int64_t >& value )
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERTARRAY(int64_t, LongArray, "putLongArray");
}
 

 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. Arrays are stored
  by COPY, not by reference. */
void NeoOpaqueTypeMap::putFloatArray( const ::std::string & key, float * value ,int length)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERTARRAYRAW(float, FloatArray, "putFloatArray");
}
 /** c++ convenience function. */
void NeoOpaqueTypeMap::putFloatArray( const ::std::string & key, ::std::vector< float >& value )
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERTARRAY(float, FloatArray, "putFloatArray");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. Arrays are stored
  by COPY, not by reference. */
void NeoOpaqueTypeMap::putDoubleArray( const ::std::string & key, double * value ,int length)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERTARRAYRAW(double, DoubleArray, "putDoubleArray");
}
 /** c++ convenience function. */
void NeoOpaqueTypeMap::putDoubleArray( const ::std::string & key, ::std::vector< double >& value)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERTARRAY(double, DoubleArray, "putDoubleArray");
}
 
 /** Assign a key and complex array value. Any value previously assigned
  to the same key will be overwritten. complex arrays are stored by COPY.*/
void NeoOpaqueTypeMap::putFcomplexArray( const ::std::string & key, ::std::complex<float> * value ,int length)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERTARRAYRAW( ::std::complex<float>, FcomplexArray, "putFcomplexArray");
}
 /** c++ convenience function. */
void NeoOpaqueTypeMap::putFcomplexArray( const ::std::string & key, ::std::vector< ::std::complex<float> >& value)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERTARRAY( ::std::complex<float>, FcomplexArray, "putFcomplexArray");
}
 
 /** Assign a key and complex array value. Any value previously assigned
  to the same key will be overwritten. Complex arrays are stored by COPY. */
void NeoOpaqueTypeMap::putDcomplexArray( const ::std::string & key, ::std::complex<double> * value ,int length)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERTARRAYRAW( ::std::complex<double>, DcomplexArray, "putDcomplexArray");
}
 /** c++ convenience function. */
void NeoOpaqueTypeMap::putDcomplexArray( const ::std::string & key, ::std::vector< ::std::complex<double> >& value)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERTARRAY( ::std::complex<double>, DcomplexArray, "putDcomplexArray");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. Arrays are stored
  by COPY, not by reference. */
void NeoOpaqueTypeMap::putStringArray( const ::std::string & key, ::std::vector< ::std::string >& value)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERTARRAY( ::std::string, StringArray, "putStringArray");
}
 
 /** Assign a key and value. Any value previously assigned
  to the same key will be overwritten. Arrays are stored
  by COPY, not by reference. */
void NeoOpaqueTypeMap::putBoolArray( const ::std::string & key, bool * value ,int length)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERTARRAYRAW( bool, BoolArray, "putBoolArray");
}
 /** c++ convenience function. */
void NeoOpaqueTypeMap::putBoolArray( const ::std::string & key, ::std::vector< bool >& value)
throw ( ::ccafeopq::TypeMismatchException )
{
	INSERTARRAY( bool, BoolArray, "putBoolArray");
}

 // ======================================================

 /** Make the key and associated value disappear from the object. */
void NeoOpaqueTypeMap::remove ( const ::std::string & key)
{
  if (!ntm) {
    IO_en2(" remove(key)  with nil TypeMap %d", serial);
    return; 
  } 
  ntm->remove(key);
}

 /** Get all the names associated with a particular type
  without exposing the data implementation details. The keys
  will be returned in an arbitrary order. If type specified is
  NoType (no specification) all keys of all types are returned.
  @see Type
 */
::std::vector< ::std::string > NeoOpaqueTypeMap::getAllKeys( enum ::ccafeopq::Type t)
{
  if (!ntm) {
    IO_en2(" getAllKeys with nil TypeMap %d", serial);
    ::std::vector< std::string > v;
    return v; 
  } 
  return ntm->getAllKeys( NeoHelper::neoType(t));
}

 /** Return true if the key exists in this map */
bool NeoOpaqueTypeMap::hasKey( const ::std::string & key)
{
  if (!ntm) {
    IO_en2(" getAllKeys with nil TypeMap %d", serial);
    return false; 
  } 
  return ntm->hasKey(key);
}

 /** Return the type of the value associated with this key */
enum ::ccafeopq::Type NeoOpaqueTypeMap::typeOf( const ::std::string & key)
{
  if (!ntm) {
    IO_dn2(" typeOf with nil TypeMap %d", serial);
    return ::ccafeopq::NoType; 
  } 
  return NeoHelper::opaqueType(ntm->typeOf(key));
}

