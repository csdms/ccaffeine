// 
// File:          ccaffeine_CcafeTypeMap_Impl.cc
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
#include "ccaffeine_CcafeTypeMap_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap._includes)

// DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap._includes)

// user defined constructor
void ccaffeine::CcafeTypeMap_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap._ctor)
  
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap._ctor)
}

// user defined destructor
void ccaffeine::CcafeTypeMap_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap._dtor)

  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
// referred to by:
//    gov.cca.TypeMap

/**
 * Create an exact copy of this Map 
 */
gov::cca::TypeMap
ccaffeine::CcafeTypeMap_impl::cloneData () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.cloneData)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.cloneData)
}

// referred to by:
//    gov.cca.TypeMap

/**
 * Create a new Map with no key/value associations. 
 */
gov::cca::TypeMap
ccaffeine::CcafeTypeMap_impl::cloneEmpty () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.cloneEmpty)

  ccaffeine::CcafeTypeMap tm = ccaffeine::CcafeTypeMap::_create();
  return tm;

  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.cloneEmpty)
}

// referred to by:
//    gov.cca.Type

/**
 * Get all the names associated with a particular type
 * without exposing the data implementation details.  The keys
 * will be returned in an arbitrary order. If type specified is
 * None (no specification) all keys of all types are returned.
 */
SIDL::array<std::string>
ccaffeine::CcafeTypeMap_impl::getAllKeys (
  /*in*/ gov::cca::Type__enum t ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getAllKeys)

  SIDL::array<std::string> a;
  int32_t len = table.size();
  int32_t dim = 1;
  int32_t lower[1] = {0};
  int32_t upper[1] = {len - 1};
  a.create(dim, lower, upper);
  int count = 0;
  for(Iter p = table.begin(); p != table.end(); ++p) {
    a.set(p->first, count++);
  }
  if(count != len) {
    fprintf(stderr, ":-( ccaffeine::CcafeTypeMap_impl::getAllKeys: "
	    "array size mismatch\n");
  }
  return a;

  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getAllKeys)
}

// referred to by:
//    gov.cca.TypeMismatchException

/**
 * Get the boolean value associated with a given key.  If the key
 * was not found, return the value defaultValue. 
 */
bool
ccaffeine::CcafeTypeMap_impl::getBool (
  /*in*/ std::string key,
  /*in*/ bool defaultValue ) 
throw ( 
  gov::cca::TypeMismatchException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getBool)
// bool
// ccaffeine::CcafeTypeMap_impl::getBool(
//   /*in*/ std::string key,
//   /*in*/ bool defaultValue ) 
// throw ( 
//   gov::cca::TypeMismatchException
// ){

{
  // Fix the assumption of an array

  OPtr optr = table[key]; // I hope this causes a real copy.
  if(optr.get() == 0) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getBool: "
	    "no such key: %s\n", key.c_str());
    return defaultValue;
  }
  if(optr->getType() != Bool) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getBool:"
	    " no such type: %s\n", ObjectBase::getTypeAsString(Bool).c_str());
    // should throw an exception
    // throw new ccaffeine::TypeMismatchException();
  }
  ObjectBase* ob = optr.get();
  Object< bool >* o = 
    dynamic_cast< Object< bool >* >(ob);
  if(o == 0) {
    fprintf(stderr, ":-( could not cast Object< bool >* " 
	    "from ObjectBase*: this can't happen\n");
    // throw new ccaffeine::TypeMismatchException();
  }
  return o->get();
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getBool)
}

// referred to by:
//    gov.cca.TypeMismatchException

/**
 * Get the value associated with a given key.  If the key
 * was not found, return the value defaultValue. 
 */
SIDL::array<bool>
ccaffeine::CcafeTypeMap_impl::getBoolArray (
  /*in*/ std::string key,
  /*in*/ SIDL::array<bool> defaultValue ) 
throw ( 
  gov::cca::TypeMismatchException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getBoolArray)
// SIDL::array<bool>
// ccaffeine::CcafeTypeMap_impl::getBoolArray(
//   /*in*/ std::string key,
//   /*in*/ SIDL::array<bool> defaultValue ) 
// throw ( 
//   gov::cca::TypeMismatchException
// ){

{
  // Fix the assumption of an array

  OPtr optr = table[key]; // I hope this causes a real copy.
  if(optr.get() == 0) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getBoolArray: "
	    "no such key: %s\n", key.c_str());
    return defaultValue;
  }
  if(optr->getType() != BoolArray) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getBoolArray:"
	    " no such type: %s\n", ObjectBase::getTypeAsString(BoolArray).c_str());
    // should throw an exception
    // throw new ccaffeine::TypeMismatchException();
  }
  ObjectBase* ob = optr.get();
  Object< SIDL::array<bool> >* o = 
    dynamic_cast< Object< SIDL::array<bool> >* >(ob);
  if(o == 0) {
    fprintf(stderr, ":-( could not cast Object< SIDL::array<bool> >* " 
	    "from ObjectBase*: this can't happen\n");
    // throw new ccaffeine::TypeMismatchException();
  }
  return o->get();
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getBoolArray)
}

// referred to by:
//    gov.cca.TypeMismatchException

/**
 * Get the Dcomplex value associated with a given key.  If the key
 * was not found, return the complex value defaultValue. 
 */
std::complex<double>
ccaffeine::CcafeTypeMap_impl::getDcomplex (
  /*in*/ std::string key,
  /*in*/ std::complex<double> defaultValue ) 
throw ( 
  gov::cca::TypeMismatchException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getDcomplex)
// std::complex<double>
// ccaffeine::CcafeTypeMap_impl::getDcomplex(
//   /*in*/ std::string key,
//   /*in*/ std::complex<double> defaultValue ) 
// throw ( 
//   gov::cca::TypeMismatchException
// ){

{
  // Fix the assumption of an array

  OPtr optr = table[key]; // I hope this causes a real copy.
  if(optr.get() == 0) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getDcomplex: "
	    "no such key: %s\n", key.c_str());
    return defaultValue;
  }
  if(optr->getType() != Dcomplex) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getDcomplex:"
	    " no such type: %s\n", ObjectBase::getTypeAsString(Dcomplex).c_str());
    // should throw an exception
    // throw new ccaffeine::TypeMismatchException();
  }
  ObjectBase* ob = optr.get();
  Object< std::complex<double> >* o = 
    dynamic_cast< Object< std::complex<double> >* >(ob);
  if(o == 0) {
    fprintf(stderr, ":-( could not cast Object< std::complex<double> >* " 
	    "from ObjectBase*: this can't happen\n");
    // throw new ccaffeine::TypeMismatchException();
  }
  return o->get();
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getDcomplex)
}

// referred to by:
//    gov.cca.TypeMismatchException

/**
 * Get the complex value associated with a given key.  If the key
 * was not found, return the complex value defaultValue. 
 */
SIDL::array<SIDL::dcomplex>
ccaffeine::CcafeTypeMap_impl::getDcomplexArray (
  /*in*/ std::string key,
  /*in*/ SIDL::array<SIDL::dcomplex> defaultValue ) 
throw ( 
  gov::cca::TypeMismatchException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getDcomplexArray)
// SIDL::array<SIDL::dcomplex>
// ccaffeine::CcafeTypeMap_impl::getDcomplexArray(
//   /*in*/ std::string key,
//   /*in*/ SIDL::array<SIDL::dcomplex> defaultValue ) 
// throw ( 
//   gov::cca::TypeMismatchException
// ){

{
  // Fix the assumption of an array

  OPtr optr = table[key]; // I hope this causes a real copy.
  if(optr.get() == 0) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getDcomplexArray: "
	    "no such key: %s\n", key.c_str());
    return defaultValue;
  }
  if(optr->getType() != DcomplexArray) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getDcomplexArray:"
	    " no such type: %s\n", ObjectBase::getTypeAsString(DcomplexArray).c_str());
    // should throw an exception
    // throw new ccaffeine::TypeMismatchException();
  }
  ObjectBase* ob = optr.get();
  Object< SIDL::array<SIDL::dcomplex> >* o = 
    dynamic_cast< Object< SIDL::array<SIDL::dcomplex> >* >(ob);
  if(o == 0) {
    fprintf(stderr, ":-( could not cast Object< SIDL::array<SIDL::dcomplex> >* " 
	    "from ObjectBase*: this can't happen\n");
    // throw new ccaffeine::TypeMismatchException();
  }
  return o->get();
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getDcomplexArray)
}

// referred to by:
//    gov.cca.TypeMismatchException

/**
 * Get the Double value associated with a given key.  If the key
 * was not found, return the value defaultValue. 
 */
double
ccaffeine::CcafeTypeMap_impl::getDouble (
  /*in*/ std::string key,
  /*in*/ double defaultValue ) 
throw ( 
  gov::cca::TypeMismatchException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getDouble)
// double
// ccaffeine::CcafeTypeMap_impl::getDouble(
//   /*in*/ std::string key,
//   /*in*/ double defaultValue ) 
// throw ( 
//   gov::cca::TypeMismatchException
// ){

{
  // Fix the assumption of an array

  OPtr optr = table[key]; // I hope this causes a real copy.
  if(optr.get() == 0) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getDouble: "
	    "no such key: %s\n", key.c_str());
    return defaultValue;
  }
  if(optr->getType() != Double) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getDouble:"
	    " no such type: %s\n", ObjectBase::getTypeAsString(Double).c_str());
    // should throw an exception
    // throw new ccaffeine::TypeMismatchException();
  }
  ObjectBase* ob = optr.get();
  Object< double >* o = 
    dynamic_cast< Object< double >* >(ob);
  if(o == 0) {
    fprintf(stderr, ":-( could not cast Object< double >* " 
	    "from ObjectBase*: this can't happen\n");
    // throw new ccaffeine::TypeMismatchException();
  }
  return o->get();
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getDouble)
}

// referred to by:
//    gov.cca.TypeMismatchException

/**
 * Get the value associated with a given key.  If the key
 * was not found, return the value defaultValue. 
 */
SIDL::array<double>
ccaffeine::CcafeTypeMap_impl::getDoubleArray (
  /*in*/ std::string key,
  /*in*/ SIDL::array<double> defaultValue ) 
throw ( 
  gov::cca::TypeMismatchException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getDoubleArray)
// SIDL::array<double>
// ccaffeine::CcafeTypeMap_impl::getDoubleArray(
//   /*in*/ std::string key,
//   /*in*/ SIDL::array<double> defaultValue ) 
// throw ( 
//   gov::cca::TypeMismatchException
// ){

{
  // Fix the assumption of an array

  OPtr optr = table[key]; // I hope this causes a real copy.
  if(optr.get() == 0) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getDoubleArray: "
	    "no such key: %s\n", key.c_str());
    return defaultValue;
  }
  if(optr->getType() != DoubleArray) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getDoubleArray:"
	    " no such type: %s\n", ObjectBase::getTypeAsString(DoubleArray).c_str());
    // should throw an exception
    // throw new ccaffeine::TypeMismatchException();
  }
  ObjectBase* ob = optr.get();
  Object< SIDL::array<double> >* o = 
    dynamic_cast< Object< SIDL::array<double> >* >(ob);
  if(o == 0) {
    fprintf(stderr, ":-( could not cast Object< SIDL::array<double> >* " 
	    "from ObjectBase*: this can't happen\n");
    // throw new ccaffeine::TypeMismatchException();
  }
  return o->get();
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getDoubleArray)
}

// referred to by:
//    gov.cca.TypeMismatchException

/**
 * Get the Fcomplex value associated with a given key.  If the key
 * was not found, return complex the value defaultValue. 
 */
std::complex<float>
ccaffeine::CcafeTypeMap_impl::getFcomplex (
  /*in*/ std::string key,
  /*in*/ std::complex<float> defaultValue ) 
throw ( 
  gov::cca::TypeMismatchException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getFcomplex)
// std::complex<float>
// ccaffeine::CcafeTypeMap_impl::getFcomplex(
//   /*in*/ std::string key,
//   /*in*/ std::complex<float> defaultValue ) 
// throw ( 
//   gov::cca::TypeMismatchException
// ){

{
  // Fix the assumption of an array

  OPtr optr = table[key]; // I hope this causes a real copy.
  if(optr.get() == 0) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getFcomplex: "
	    "no such key: %s\n", key.c_str());
    return defaultValue;
  }
  if(optr->getType() != Fcomplex) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getFcomplex:"
	    " no such type: %s\n", ObjectBase::getTypeAsString(Fcomplex).c_str());
    // should throw an exception
    // throw new ccaffeine::TypeMismatchException();
  }
  ObjectBase* ob = optr.get();
  Object< std::complex<float> >* o = 
    dynamic_cast< Object< std::complex<float> >* >(ob);
  if(o == 0) {
    fprintf(stderr, ":-( could not cast Object< std::complex<float> >* " 
	    "from ObjectBase*: this can't happen\n");
    // throw new ccaffeine::TypeMismatchException();
  }
  return o->get();
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getFcomplex)
}

// referred to by:
//    gov.cca.TypeMismatchException

/**
 * Get the complex value associated with a given key.  If the key
 * was not found, return the complex value defaultValue. 
 */
SIDL::array<SIDL::fcomplex>
ccaffeine::CcafeTypeMap_impl::getFcomplexArray (
  /*in*/ std::string key,
  /*in*/ SIDL::array<SIDL::fcomplex> defaultValue ) 
throw ( 
  gov::cca::TypeMismatchException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getFcomplexArray)
// SIDL::array<SIDL::fcomplex>
// ccaffeine::CcafeTypeMap_impl::getFcomplexArray(
//   /*in*/ std::string key,
//   /*in*/ SIDL::array<SIDL::fcomplex> defaultValue ) 
// throw ( 
//   gov::cca::TypeMismatchException
// ){

{
  // Fix the assumption of an array

  OPtr optr = table[key]; // I hope this causes a real copy.
  if(optr.get() == 0) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getFcomplexArray: "
	    "no such key: %s\n", key.c_str());
    return defaultValue;
  }
  if(optr->getType() != FcomplexArray) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getFcomplexArray:"
	    " no such type: %s\n", ObjectBase::getTypeAsString(FcomplexArray).c_str());
    // should throw an exception
    // throw new ccaffeine::TypeMismatchException();
  }
  ObjectBase* ob = optr.get();
  Object< SIDL::array<SIDL::fcomplex> >* o = 
    dynamic_cast< Object< SIDL::array<SIDL::fcomplex> >* >(ob);
  if(o == 0) {
    fprintf(stderr, ":-( could not cast Object< SIDL::array<SIDL::fcomplex> >* " 
	    "from ObjectBase*: this can't happen\n");
    // throw new ccaffeine::TypeMismatchException();
  }
  return o->get();
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getFcomplexArray)
}

// referred to by:
//    gov.cca.TypeMismatchException

/**
 * Get the Float value associated with a given key.  If the key
 * was not found, return the value defaultValue. 
 */
float
ccaffeine::CcafeTypeMap_impl::getFloat (
  /*in*/ std::string key,
  /*in*/ float defaultValue ) 
throw ( 
  gov::cca::TypeMismatchException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getFloat)
// float
// ccaffeine::CcafeTypeMap_impl::getFloat(
//   /*in*/ std::string key,
//   /*in*/ float defaultValue ) 
// throw ( 
//   gov::cca::TypeMismatchException
// ){

{
  // Fix the assumption of an array

  OPtr optr = table[key]; // I hope this causes a real copy.
  if(optr.get() == 0) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getFloat: "
	    "no such key: %s\n", key.c_str());
    return defaultValue;
  }
  if(optr->getType() != Float) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getFloat:"
	    " no such type: %s\n", ObjectBase::getTypeAsString(Float).c_str());
    // should throw an exception
    // throw new ccaffeine::TypeMismatchException();
  }
  ObjectBase* ob = optr.get();
  Object< float >* o = 
    dynamic_cast< Object< float >* >(ob);
  if(o == 0) {
    fprintf(stderr, ":-( could not cast Object< float >* " 
	    "from ObjectBase*: this can't happen\n");
    // throw new ccaffeine::TypeMismatchException();
  }
  return o->get();
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getFloat)
}

// referred to by:
//    gov.cca.TypeMismatchException

/**
 * Get the value associated with a given key.  If the key
 * was not found, return the value defaultValue. 
 */
SIDL::array<float>
ccaffeine::CcafeTypeMap_impl::getFloatArray (
  /*in*/ std::string key,
  /*in*/ SIDL::array<float> defaultValue ) 
throw ( 
  gov::cca::TypeMismatchException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getFloatArray)
// SIDL::array<float>
// ccaffeine::CcafeTypeMap_impl::getFloatArray(
//   /*in*/ std::string key,
//   /*in*/ SIDL::array<float> defaultValue ) 
// throw ( 
//   gov::cca::TypeMismatchException
// ){

{
  // Fix the assumption of an array

  OPtr optr = table[key]; // I hope this causes a real copy.
  if(optr.get() == 0) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getFloatArray: "
	    "no such key: %s\n", key.c_str());
    return defaultValue;
  }
  if(optr->getType() != FloatArray) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getFloatArray:"
	    " no such type: %s\n", ObjectBase::getTypeAsString(FloatArray).c_str());
    // should throw an exception
    // throw new ccaffeine::TypeMismatchException();
  }
  ObjectBase* ob = optr.get();
  Object< SIDL::array<float> >* o = 
    dynamic_cast< Object< SIDL::array<float> >* >(ob);
  if(o == 0) {
    fprintf(stderr, ":-( could not cast Object< SIDL::array<float> >* " 
	    "from ObjectBase*: this can't happen\n");
    // throw new ccaffeine::TypeMismatchException();
  }
  return o->get();
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getFloatArray)
}

// referred to by:
//    gov.cca.TypeMismatchException

/**
 * Get the Int value associated with a given key.  If the key
 * was not found, return the value defaultValue. 
 */
int32_t
ccaffeine::CcafeTypeMap_impl::getInt (
  /*in*/ std::string key,
  /*in*/ int32_t defaultValue ) 
throw ( 
  gov::cca::TypeMismatchException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getInt)
// int
// ccaffeine::CcafeTypeMap_impl::getInt(
//   /*in*/ std::string key,
//   /*in*/ int defaultValue ) 
// throw ( 
//   gov::cca::TypeMismatchException
// ){

{
  // Fix the assumption of an array

  OPtr optr = table[key]; // I hope this causes a real copy.
  if(optr.get() == 0) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getInt: "
	    "no such key: %s\n", key.c_str());
    return defaultValue;
  }
  if(optr->getType() != Int) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getInt:"
	    " no such type: %s\n", ObjectBase::getTypeAsString(Int).c_str());
    // should throw an exception
    // throw new ccaffeine::TypeMismatchException();
  }
  ObjectBase* ob = optr.get();
  Object< int >* o = 
    dynamic_cast< Object< int >* >(ob);
  if(o == 0) {
    fprintf(stderr, ":-( could not cast Object< int >* " 
	    "from ObjectBase*: this can't happen\n");
    // throw new ccaffeine::TypeMismatchException();
  }
  return o->get();
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getInt)
}

// referred to by:
//    gov.cca.TypeMismatchException

/**
 * Get the value associated with a given key.  If the key
 * was not found, return the value defaultValue. 
 */
SIDL::array<int>
ccaffeine::CcafeTypeMap_impl::getIntArray (
  /*in*/ std::string key,
  /*in*/ SIDL::array<int> defaultValue ) 
throw ( 
  gov::cca::TypeMismatchException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getIntArray)
// SIDL::array<int>
// ccaffeine::CcafeTypeMap_impl::getIntArray(
//   /*in*/ std::string key,
//   /*in*/ SIDL::array<int> defaultValue ) 
// throw ( 
//   gov::cca::TypeMismatchException
// ){

{
  // Fix the assumption of an array

  OPtr optr = table[key]; // I hope this causes a real copy.
  if(optr.get() == 0) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getIntArray: "
	    "no such key: %s\n", key.c_str());
    return defaultValue;
  }
  if(optr->getType() != IntArray) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getIntArray:"
	    " no such type: %s\n", ObjectBase::getTypeAsString(IntArray).c_str());
    // should throw an exception
    // throw new ccaffeine::TypeMismatchException();
  }
  ObjectBase* ob = optr.get();
  Object< SIDL::array<int> >* o = 
    dynamic_cast< Object< SIDL::array<int> >* >(ob);
  if(o == 0) {
    fprintf(stderr, ":-( could not cast Object< SIDL::array<int> >* " 
	    "from ObjectBase*: this can't happen\n");
    // throw new ccaffeine::TypeMismatchException();
  }
  return o->get();
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getIntArray)
}

// referred to by:
//    gov.cca.TypeMismatchException

/**
 * Get the Long value associated with a given key.  If the key
 * was not found, return the value defaultValue. 
 */
int64_t
ccaffeine::CcafeTypeMap_impl::getLong (
  /*in*/ std::string key,
  /*in*/ int64_t defaultValue ) 
throw ( 
  gov::cca::TypeMismatchException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getLong)
// long
// ccaffeine::CcafeTypeMap_impl::getLong(
//   /*in*/ std::string key,
//   /*in*/ long defaultValue ) 
// throw ( 
//   gov::cca::TypeMismatchException
// ){

{
  // Fix the assumption of an array

  OPtr optr = table[key]; // I hope this causes a real copy.
  if(optr.get() == 0) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getLong: "
	    "no such key: %s\n", key.c_str());
    return defaultValue;
  }
  if(optr->getType() != Long) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getLong:"
	    " no such type: %s\n", ObjectBase::getTypeAsString(Long).c_str());
    // should throw an exception
    // throw new ccaffeine::TypeMismatchException();
  }
  ObjectBase* ob = optr.get();
  Object< long >* o = 
    dynamic_cast< Object< long >* >(ob);
  if(o == 0) {
    fprintf(stderr, ":-( could not cast Object< long >* " 
	    "from ObjectBase*: this can't happen\n");
    // throw new ccaffeine::TypeMismatchException();
  }
  return o->get();
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getLong)
}

// referred to by:
//    gov.cca.TypeMismatchException

/**
 * Get the value associated with a given key.  If the key
 * was not found, return the value defaultValue. 
 */
SIDL::array<long>
ccaffeine::CcafeTypeMap_impl::getLongArray (
  /*in*/ std::string key,
  /*in*/ SIDL::array<long> defaultValue ) 
throw ( 
  gov::cca::TypeMismatchException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getLongArray)
// SIDL::array<long>
// ccaffeine::CcafeTypeMap_impl::getLongArray(
//   /*in*/ std::string key,
//   /*in*/ SIDL::array<long> defaultValue ) 
// throw ( 
//   gov::cca::TypeMismatchException
// ){

{
  // Fix the assumption of an array

  OPtr optr = table[key]; // I hope this causes a real copy.
  if(optr.get() == 0) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getLongArray: "
	    "no such key: %s\n", key.c_str());
    return defaultValue;
  }
  if(optr->getType() != LongArray) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getLongArray:"
	    " no such type: %s\n", ObjectBase::getTypeAsString(LongArray).c_str());
    // should throw an exception
    // throw new ccaffeine::TypeMismatchException();
  }
  ObjectBase* ob = optr.get();
  Object< SIDL::array<long> >* o = 
    dynamic_cast< Object< SIDL::array<long> >* >(ob);
  if(o == 0) {
    fprintf(stderr, ":-( could not cast Object< SIDL::array<long> >* " 
	    "from ObjectBase*: this can't happen\n");
    // throw new ccaffeine::TypeMismatchException();
  }
  return o->get();
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getLongArray)
}

// referred to by:
//    gov.cca.TypeMismatchException

/**
 * Get the string value associated with a given key.  If the key
 * was not found, return the value defaultValue. 
 */
std::string
ccaffeine::CcafeTypeMap_impl::getString (
  /*in*/ std::string key,
  /*in*/ std::string defaultValue ) 
throw ( 
  gov::cca::TypeMismatchException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getString)
// std::string
// ccaffeine::CcafeTypeMap_impl::getString(
//   /*in*/ std::string key,
//   /*in*/ std::string defaultValue ) 
// throw ( 
//   gov::cca::TypeMismatchException
// ){

{
  // Fix the assumption of an array

  OPtr optr = table[key]; // I hope this causes a real copy.
  if(optr.get() == 0) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getString: "
	    "no such key: %s\n", key.c_str());
    return defaultValue;
  }
  if(optr->getType() != String) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getString:"
	    " no such type: %s\n", ObjectBase::getTypeAsString(String).c_str());
    // should throw an exception
    // throw new ccaffeine::TypeMismatchException();
  }
  ObjectBase* ob = optr.get();
  Object< std::string >* o = 
    dynamic_cast< Object< std::string >* >(ob);
  if(o == 0) {
    fprintf(stderr, ":-( could not cast Object< std::string >* " 
	    "from ObjectBase*: this can't happen\n");
    // throw new ccaffeine::TypeMismatchException();
  }
  return o->get();
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getString)
}

// referred to by:
//    gov.cca.TypeMismatchException

/**
 * Get the value associated with a given key.  If the key
 * was not found, return the value defaultValue. 
 */
SIDL::array<std::string>
ccaffeine::CcafeTypeMap_impl::getStringArray (
  /*in*/ std::string key,
  /*in*/ SIDL::array<std::string> defaultValue ) 
throw ( 
  gov::cca::TypeMismatchException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.getStringArray)
// SIDL::array<std::string>
// ccaffeine::CcafeTypeMap_impl::getStringArray(
//   /*in*/ std::string key,
//   /*in*/ SIDL::array<std::string> defaultValue ) 
// throw ( 
//   gov::cca::TypeMismatchException
// ){

{
  // Fix the assumption of an array

  OPtr optr = table[key]; // I hope this causes a real copy.
  if(optr.get() == 0) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getStringArray: "
	    "no such key: %s\n", key.c_str());
    return defaultValue;
  }
  if(optr->getType() != StringArray) {
    fprintf(stderr, "ccaffeine::CcafeTypeMap_impl::getStringArray:"
	    " no such type: %s\n", ObjectBase::getTypeAsString(StringArray).c_str());
    // should throw an exception
    // throw new ccaffeine::TypeMismatchException();
  }
  ObjectBase* ob = optr.get();
  Object< SIDL::array<std::string> >* o = 
    dynamic_cast< Object< SIDL::array<std::string> >* >(ob);
  if(o == 0) {
    fprintf(stderr, ":-( could not cast Object< SIDL::array<std::string> >* " 
	    "from ObjectBase*: this can't happen\n");
    // throw new ccaffeine::TypeMismatchException();
  }
  return o->get();
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.getStringArray)
}


/**
 * Return true if the key exists in this map 
 */
bool
ccaffeine::CcafeTypeMap_impl::hasKey (
  /*in*/ std::string key ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.hasKey)

  Iter i = table.find(key);
  if(i == table.end()) {
    return false;
  } else {
    return true;
  }

  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.hasKey)
}


/**
 * Assign a key and value. Any value previously assigned
 * to the same key will be overwritten.  
 */
void
ccaffeine::CcafeTypeMap_impl::putBool (
  /*in*/ std::string key,
  /*in*/ bool value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.putBool)


// void
// ccaffeine::CcafeTypeMap_impl::putBool (
//   /*in*/ std::string key,
//   /*in*/ bool value ) 
// throw () 

{
  Object< bool >* ptr = new Object< bool >(Bool);
  ptr->set(value);
  OPtr optr((ObjectBase*)ptr);
  table[key] = optr;
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.putBool)
}


/**
 * Assign a key and value. Any value previously assigned
 * to the same key will be overwritten. Arrays are stored
 * by COPY, not by reference. 
 */
void
ccaffeine::CcafeTypeMap_impl::putBoolArray (
  /*in*/ std::string key,
  /*in*/ SIDL::array<bool> value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.putBoolArray)


// void
// ccaffeine::CcafeTypeMap_impl::putBoolArray (
//   /*in*/ std::string key,
//   /*in*/ SIDL::array<bool> value ) 
// throw () 

{
  Object< SIDL::array<bool> >* ptr = new Object< SIDL::array<bool> >(BoolArray);
  ptr->set(value);
  OPtr optr((ObjectBase*)ptr);
  table[key] = optr;
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.putBoolArray)
}


/**
 * Assign a key and complex value. 
 * Any complex value previously assigned will be overwritten. 
 */
void
ccaffeine::CcafeTypeMap_impl::putDcomplex (
  /*in*/ std::string key,
  /*in*/ std::complex<double> value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.putDcomplex)


// void
// ccaffeine::CcafeTypeMap_impl::putDcomplex (
//   /*in*/ std::string key,
//   /*in*/ std::complex<double> value ) 
// throw () 

{
  Object< std::complex<double> >* ptr = new Object< std::complex<double> >(Dcomplex);
  ptr->set(value);
  OPtr optr((ObjectBase*)ptr);
  table[key] = optr;
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.putDcomplex)
}


/**
 * Assign a key and complex array value. Any value previously assigned
 * to the same key will be overwritten. Complex arrays are stored by COPY. 
 */
void
ccaffeine::CcafeTypeMap_impl::putDcomplexArray (
  /*in*/ std::string key,
  /*in*/ SIDL::array<SIDL::dcomplex> value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.putDcomplexArray)


// void
// ccaffeine::CcafeTypeMap_impl::putDcomplexArray (
//   /*in*/ std::string key,
//   /*in*/ SIDL::array<SIDL::dcomplex> value ) 
// throw () 

{
  Object< SIDL::array<SIDL::dcomplex> >* ptr = new Object< SIDL::array<SIDL::dcomplex> >(DcomplexArray);
  ptr->set(value);
  OPtr optr((ObjectBase*)ptr);
  table[key] = optr;
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.putDcomplexArray)
}


/**
 * Assign a key and value. Any value previously assigned
 * to the same key will be overwritten.  
 */
void
ccaffeine::CcafeTypeMap_impl::putDouble (
  /*in*/ std::string key,
  /*in*/ double value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.putDouble)


// void
// ccaffeine::CcafeTypeMap_impl::putDouble (
//   /*in*/ std::string key,
//   /*in*/ double value ) 
// throw () 

{
  Object< double >* ptr = new Object< double >(Double);
  ptr->set(value);
  OPtr optr((ObjectBase*)ptr);
  table[key] = optr;
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.putDouble)
}


/**
 * Assign a key and value. Any value previously assigned
 * to the same key will be overwritten. Arrays are stored
 * by COPY, not by reference. 
 */
void
ccaffeine::CcafeTypeMap_impl::putDoubleArray (
  /*in*/ std::string key,
  /*in*/ SIDL::array<double> value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.putDoubleArray)


// void
// ccaffeine::CcafeTypeMap_impl::putDoubleArray (
//   /*in*/ std::string key,
//   /*in*/ SIDL::array<double> value ) 
// throw () 

{
  Object< SIDL::array<double> >* ptr = new Object< SIDL::array<double> >(DoubleArray);
  ptr->set(value);
  OPtr optr((ObjectBase*)ptr);
  table[key] = optr;
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.putDoubleArray)
}


/**
 * Assign a key and complex value.
 * Any complex value previously assigned will be overwritten.  
 */
void
ccaffeine::CcafeTypeMap_impl::putFcomplex (
  /*in*/ std::string key,
  /*in*/ std::complex<float> value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.putFcomplex)


// void
// ccaffeine::CcafeTypeMap_impl::putFcomplex (
//   /*in*/ std::string key,
//   /*in*/ std::complex<float> value ) 
// throw () 

{
  Object< std::complex<float> >* ptr = new Object< std::complex<float> >(Fcomplex);
  ptr->set(value);
  OPtr optr((ObjectBase*)ptr);
  table[key] = optr;
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.putFcomplex)
}


/**
 * Assign a key and complex array value. Any value previously assigned
 * to the same key will be overwritten. complex arrays are stored by COPY.
 */
void
ccaffeine::CcafeTypeMap_impl::putFcomplexArray (
  /*in*/ std::string key,
  /*in*/ SIDL::array<SIDL::fcomplex> value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.putFcomplexArray)


// void
// ccaffeine::CcafeTypeMap_impl::putFcomplexArray (
//   /*in*/ std::string key,
//   /*in*/ SIDL::array<SIDL::fcomplex> value ) 
// throw () 

{
  Object< SIDL::array<SIDL::fcomplex> >* ptr = new Object< SIDL::array<SIDL::fcomplex> >(FcomplexArray);
  ptr->set(value);
  OPtr optr((ObjectBase*)ptr);
  table[key] = optr;
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.putFcomplexArray)
}


/**
 * Assign a key and value. Any value previously assigned
 * to the same key will be overwritten.  
 */
void
ccaffeine::CcafeTypeMap_impl::putFloat (
  /*in*/ std::string key,
  /*in*/ float value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.putFloat)


// void
// ccaffeine::CcafeTypeMap_impl::putFloat (
//   /*in*/ std::string key,
//   /*in*/ float value ) 
// throw () 

{
  Object< float >* ptr = new Object< float >(Float);
  ptr->set(value);
  OPtr optr((ObjectBase*)ptr);
  table[key] = optr;
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.putFloat)
}


/**
 * Assign a key and value. Any value previously assigned
 * to the same key will be overwritten. Arrays are stored
 * by COPY, not by reference. 
 */
void
ccaffeine::CcafeTypeMap_impl::putFloatArray (
  /*in*/ std::string key,
  /*in*/ SIDL::array<float> value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.putFloatArray)


// void
// ccaffeine::CcafeTypeMap_impl::putFloatArray (
//   /*in*/ std::string key,
//   /*in*/ SIDL::array<float> value ) 
// throw () 

{
  Object< SIDL::array<float> >* ptr = new Object< SIDL::array<float> >(FloatArray);
  ptr->set(value);
  OPtr optr((ObjectBase*)ptr);
  table[key] = optr;
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.putFloatArray)
}


/**
 * Assign a key and value. Any value previously assigned
 * to the same key will be overwritten.  
 */
void
ccaffeine::CcafeTypeMap_impl::putInt (
  /*in*/ std::string key,
  /*in*/ int32_t value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.putInt)


// void
// ccaffeine::CcafeTypeMap_impl::putInt (
//   /*in*/ std::string key,
//   /*in*/ int value ) 
// throw () 

{
  Object< int >* ptr = new Object< int >(Int);
  ptr->set(value);
  OPtr optr((ObjectBase*)ptr);
  table[key] = optr;
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.putInt)
}


/**
 * Assign a key and value. Any value previously assigned
 * to the same key will be overwritten. Arrays are stored
 * by COPY, not by reference. 
 */
void
ccaffeine::CcafeTypeMap_impl::putIntArray (
  /*in*/ std::string key,
  /*in*/ SIDL::array<int> value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.putIntArray)


// void
// ccaffeine::CcafeTypeMap_impl::putIntArray (
//   /*in*/ std::string key,
//   /*in*/ SIDL::array<int> value ) 
// throw () 

{
  Object< SIDL::array<int> >* ptr = new Object< SIDL::array<int> >(IntArray);
  ptr->set(value);
  OPtr optr((ObjectBase*)ptr);
  table[key] = optr;
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.putIntArray)
}


/**
 * Assign a key and value. Any value previously assigned
 * to the same key will be overwritten.  
 */
void
ccaffeine::CcafeTypeMap_impl::putLong (
  /*in*/ std::string key,
  /*in*/ int64_t value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.putLong)


// void
// ccaffeine::CcafeTypeMap_impl::putLong (
//   /*in*/ std::string key,
//   /*in*/ long value ) 
// throw () 

{
  Object< long >* ptr = new Object< long >(Long);
  ptr->set(value);
  OPtr optr((ObjectBase*)ptr);
  table[key] = optr;
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.putLong)
}


/**
 * Assign a key and value. Any value previously assigned
 * to the same key will be overwritten. Arrays are stored
 * by COPY, not by reference. 
 */
void
ccaffeine::CcafeTypeMap_impl::putLongArray (
  /*in*/ std::string key,
  /*in*/ SIDL::array<long> value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.putLongArray)


// void
// ccaffeine::CcafeTypeMap_impl::putLongArray (
//   /*in*/ std::string key,
//   /*in*/ SIDL::array<long> value ) 
// throw () 

{
  Object< SIDL::array<long> >* ptr = new Object< SIDL::array<long> >(LongArray);
  ptr->set(value);
  OPtr optr((ObjectBase*)ptr);
  table[key] = optr;
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.putLongArray)
}


/**
 * Assign a key and value. Any value previously assigned
 * to the same key will be overwritten.  
 */
void
ccaffeine::CcafeTypeMap_impl::putString (
  /*in*/ std::string key,
  /*in*/ std::string value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.putString)


// void
// ccaffeine::CcafeTypeMap_impl::putString (
//   /*in*/ std::string key,
//   /*in*/ std::string value ) 
// throw () 

{
  Object< std::string >* ptr = new Object< std::string >(String);
  ptr->set(value);
  OPtr optr((ObjectBase*)ptr);
  table[key] = optr;
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.putString)
}


/**
 * Assign a key and value. Any value previously assigned
 * to the same key will be overwritten. Arrays are stored
 * by COPY, not by reference. 
 */
void
ccaffeine::CcafeTypeMap_impl::putStringArray (
  /*in*/ std::string key,
  /*in*/ SIDL::array<std::string> value ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.putStringArray)


// void
// ccaffeine::CcafeTypeMap_impl::putStringArray (
//   /*in*/ std::string key,
//   /*in*/ SIDL::array<std::string> value ) 
// throw () 

{
  Object< SIDL::array<std::string> >* ptr = new Object< SIDL::array<std::string> >(StringArray);
  ptr->set(value);
  OPtr optr((ObjectBase*)ptr);
  table[key] = optr;
}
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.putStringArray)
}


/**
 * Make the key and associated value disappear from the object. 
 */
void
ccaffeine::CcafeTypeMap_impl::remove (
  /*in*/ std::string key ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.remove)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.remove)
}

// referred to by:
//    gov.cca.Type

/**
 * Return the type of the value associated with this key 
 */
gov::cca::Type__enum
ccaffeine::CcafeTypeMap_impl::typeOf (
  /*in*/ std::string key ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap.typeOf)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap.typeOf)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeTypeMap._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccaffeine.CcafeTypeMap._misc)

