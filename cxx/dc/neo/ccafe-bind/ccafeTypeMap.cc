#include "dc/export/AllExport.hh"
#include <neocca.hh>
#include "dc/neo/ccafe-bind/ccafeTypeMap.hh"
#include "dc/neo/ccafe-bind/NeoHelper.hh"
#include "dc/neo/ccafe-bind/NeoMacros.hh"



int ccafe::TypeMap::genSerial = 0;

ccafe::TypeMap::TypeMap()
{
	serial = nextNum();
}

ccafe::TypeMap::~TypeMap()
{
	serial = -serial;
}

ccafe::TypeMap::TypeMap(int bogon)
{
	serial = 0;
}

::neo::cca::TypeMap_shared 
ccafe::TypeMap::neoWrap( ::ccafeopq::TypeMap_shared ctm_)
{
  ccafe::TypeMap * ctm = new ccafe::TypeMap();
  ctm->ctm = ctm_;
  ccafe::TypeMap_shared ctms(ctm);
  ::neo::cca::TypeMap_shared ntms = ctms;
  return ntms;
}

::ccafeopq::TypeMap_shared 
ccafe::TypeMap::unWrap( neo::cca::TypeMap_shared ctm_, bool & ok)
{
	::ccafeopq::TypeMap_shared bogon;
	if (ctm_ == 0) {
		ok = true; // one good nil deserves another.
		return bogon;
	}
	ccafe::TypeMap_shared mtm;
	mtm = boost::dynamic_pointer_cast< ccafe::TypeMap >(ctm_);
	if (mtm == 0) {
		ok = false; // not one of ours. sorry.
		return bogon;
	}
	ok = true;
	return mtm->ctm; // return the wrapped opq tm
}

neo::cca::TypeMap_shared 
ccafe::TypeMap::cloneData()
{
  if ( !ctm  ) {
#ifdef CCAFE_AUDIT
   IO_dn2("cloneTypeMap called on empty wrapper %d",serial);
#endif
    ccafe::TypeMap_shared empty;
    return empty;
  }
  else {
    ::ccafeopq::TypeMap_shared newguts = ctm->cloneData();
    return ccafe::TypeMap::neoWrap(newguts);
  }
}

neo::cca::TypeMap_shared 
ccafe::TypeMap::cloneEmpty()
{
  if ( !ctm  ) {
#ifdef CCAFE_AUDIT
   IO_dn2("cloneEmpt called on empty wrapper %d",serial);
#endif
    ccafe::TypeMap_shared empty;
    return empty;
  }
  else {
    ::ccafeopq::TypeMap_shared newguts = ctm->cloneEmpty();
    return ccafe::TypeMap::neoWrap(newguts);
  }
}

int32_t      
ccafe::TypeMap::getInt(const ::std::string & key,  int32_t defaultValue) 
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->getInt(key,defaultValue);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
	return defaultValue; // NOTREACHED
}

int64_t  
ccafe::TypeMap::getLong(const ::std::string & key,  int64_t defaultValue) 
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->getLong(key,defaultValue);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
	return defaultValue; // NOTREACHED
}

float    
ccafe::TypeMap::getFloat(const ::std::string & key,  float defaultValue) 
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->getFloat(key,defaultValue);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
	return defaultValue; // NOTREACHED
}

double   
ccafe::TypeMap::getDouble(const ::std::string & key,  double defaultValue) 
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->getDouble(key,defaultValue);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
	return defaultValue; // NOTREACHED
}

::std::complex<float> 
ccafe::TypeMap::getFcomplex(const ::std::string & key,  ::std::complex<float> defaultValue) 
throw (neo::cca::TypeMismatchException ) 
{
	try {
		return ctm->getFcomplex(key,defaultValue);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
	return defaultValue; // NOTREACHED
}

::std::complex<double> 
ccafe::TypeMap::getDcomplex(const ::std::string & key,  ::std::complex<double> defaultValue) 
throw (neo::cca::TypeMismatchException ) 
{
	try {
		return ctm->getDcomplex(key,defaultValue);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
	return defaultValue; // NOTREACHED
}

::std::string  
ccafe::TypeMap::getString(const ::std::string & key,  ::std::string defaultValue) 
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->getString(key,defaultValue);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
	return defaultValue; // NOTREACHED
}

bool  
ccafe::TypeMap::getBool(const ::std::string & key,  bool defaultValue) 
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->getBool(key,defaultValue);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
	return defaultValue; // NOTREACHED
}

::std::vector< int32_t > 
ccafe::TypeMap::getIntArray(const ::std::string & key,  ::std::vector< int32_t >&  defaultValue) 
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->getIntArray(key,defaultValue);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
	return defaultValue; // NOTREACHED
}

::std::vector< int64_t > 
ccafe::TypeMap::getLongArray(const ::std::string & key,  ::std::vector< int64_t >&  defaultValue) 
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->getLongArray(key,defaultValue);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
	return defaultValue; // NOTREACHED
}

::std::vector< float >    
ccafe::TypeMap::getFloatArray(const ::std::string & key,  ::std::vector< float >&  defaultValue) 
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->getFloatArray(key,defaultValue);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
	return defaultValue; // NOTREACHED
}

::std::vector< double > 
ccafe::TypeMap::getDoubleArray(const ::std::string & key,  ::std::vector< double >&  defaultValue) 
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->getDoubleArray(key,defaultValue);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
	return defaultValue; // NOTREACHED
}

::std::vector< ::std::complex<float> > 
ccafe::TypeMap::getFcomplexArray(const ::std::string & key,  ::std::vector< ::std::complex<float> >&  defaultValue) 
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->getFcomplexArray(key,defaultValue);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
	return defaultValue; // NOTREACHED
}

::std::vector< ::std::complex<double> > 
ccafe::TypeMap::getDcomplexArray(const ::std::string & key,  ::std::vector< ::std::complex<double> >&  defaultValue) 
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->getDcomplexArray(key,defaultValue);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
	return defaultValue; // NOTREACHED
}

::std::vector< ::std::string > 
ccafe::TypeMap::getStringArray(const ::std::string & key,  ::std::vector< ::std::string >&  defaultValue) 
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->getStringArray(key,defaultValue);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
	return defaultValue; // NOTREACHED
}

::std::vector< bool > 
ccafe::TypeMap::getBoolArray(const ::std::string & key,  ::std::vector< bool >&  defaultValue) 
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->getBoolArray(key,defaultValue);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
	return defaultValue; // NOTREACHED
}

void 
ccafe::TypeMap::putInt(const ::std::string & key,  int value)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putInt(key, value);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putLong(const ::std::string & key,  int64_t value)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putLong(key, value);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putFloat(const ::std::string & key,  float value)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putFloat(key, value);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putDouble(const ::std::string & key,  double value)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putDouble(key, value);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putFcomplex(const ::std::string & key,  ::std::complex<float> value) 
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putFcomplex(key, value);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putDcomplex(const ::std::string & key,  ::std::complex<double> value)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putDcomplex(key, value);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putString(const ::std::string & key, const ::std::string & value)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putString(key, value);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putBool(const ::std::string & key,  bool value)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putBool(key, value);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putIntArray(const ::std::string & key,  int * value ,int length)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putIntArray(key, value, length);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putIntArray(const ::std::string & key,  ::std::vector< int >&  value)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putIntArray(key, value);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putLongArray(const ::std::string & key,  int64_t * value ,int length)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putLongArray(key, value, length);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putLongArray(const ::std::string & key,  ::std::vector< int64_t >&  value )
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putLongArray(key, value);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putFloatArray(const ::std::string & key,  float * value ,int length)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putFloatArray(key, value, length);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putFloatArray(const ::std::string & key,  ::std::vector< float >&  value )
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putFloatArray(key, value);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putDoubleArray(const ::std::string & key,  double * value ,int length)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putDoubleArray(key, value, length);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putDoubleArray(const ::std::string & key,  ::std::vector< double >&  value)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putDoubleArray(key, value);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putFcomplexArray(const ::std::string & key,  ::std::complex<float> * value ,int length)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putFcomplexArray(key, value, length);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putFcomplexArray(const ::std::string & key,  ::std::vector< ::std::complex<float> >&  value)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putFcomplexArray(key, value);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putDcomplexArray(const ::std::string & key,  ::std::complex<double> * value ,int length)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putDcomplexArray(key, value, length);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putDcomplexArray(const ::std::string & key,  ::std::vector< ::std::complex<double> >&  value)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putDcomplexArray(key, value);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putStringArray(const ::std::string & key,  ::std::vector< ::std::string >&  value)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putStringArray(key, value);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putBoolArray(const ::std::string & key,  bool * value ,int length)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putBoolArray(key, value, length);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::putBoolArray(const ::std::string & key,  ::std::vector< bool >&  value)
throw (neo::cca::TypeMismatchException )
{
	try {
		return ctm->putBoolArray(key, value);
	}
	NEO_RETHROW_PREPEND("neo TypeMap: ");
}

void 
ccafe::TypeMap::remove (const ::std::string & key)
{
	return ctm->remove(key);
}

::std::vector< ::std::string > 
ccafe::TypeMap::getAllKeys( enum neo::cca::Type t)
{
	ccafeopq::Type ot;
	ot = NeoHelper::opaqueType(t);
	return ctm->getAllKeys( ot );
}

bool 
ccafe::TypeMap::hasKey(const ::std::string & key)
{
	return ctm->hasKey( key );
}

enum neo::cca::Type 
ccafe::TypeMap::typeOf(const ::std::string & key)
{
	neo::cca::Type nt;
	ccafeopq::Type ot = ctm->typeOf( key );
	nt = NeoHelper::neoType(ot);
	return nt;
}
