#ifdef HAVE_CLASSIC
#include <cca.h>
#endif
#include <iostream>
#include <map>
#include "util/TypeMap.h"
#include <sstream>
#include "util/IO.h"

using ::ccafeopq::TypeMismatchException;

#define DEBUG_COPY_DATA 1
#undef DEBUG_COPY_DATA
#define DEBUG_COPY_DATA 0

//
// YOU DON'T WANT TO TOUCH anything BETWEEN the AAAAAAs.
//
// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
namespace { // anonymous -- file only.

/** STL-oriented multiple types in a single map wrapper. */
class Item {
protected:
	enum ::ccafeopq::Type t;

public:
	// never use this one.
	Item( ::ccafeopq::Type it) {
		t = it;
	}

	virtual ~Item() { t = ::ccafeopq::NoType; }

	Item( int32_t i) { (void)i;  t =  ::ccafeopq::Int; }
	Item( int64_t i) { (void)i; t =  ::ccafeopq::Long; }
	Item( float i) { (void)i; t =  ::ccafeopq::Float; }
	Item( double i) { (void)i; t =  ::ccafeopq::Double; }
	Item( ::std::complex<double> i) { (void)i; t =  ::ccafeopq::Dcomplex; }
	Item( ::std::complex<float> i) {  (void)i;t =  ::ccafeopq::Fcomplex; }
	Item( bool i ) {  (void)i; t =  ::ccafeopq::Bool; }
	Item( ::std::string & i) { (void)i; t =  ::ccafeopq::String; }
	Item( const std::string & i ) { (void)i; t =  ::ccafeopq::String; }

	Item( ::std::vector< int32_t > & i) { (void)i; t =  ::ccafeopq::IntArray; }
	Item( ::std::vector< int64_t > & i) { (void)i; t =  ::ccafeopq::LongArray; }
	Item( ::std::vector< float > & i) { (void)i; t =  ::ccafeopq::FloatArray; }
	Item( ::std::vector< double > & i) {  (void)i;t =  ::ccafeopq::DoubleArray; }
	Item( ::std::vector< ::std::complex<double> > & i) { (void)i; t =  ::ccafeopq::DcomplexArray; }
	Item( ::std::vector< ::std::complex<float> > & i) { (void)i; t =  ::ccafeopq::FcomplexArray; }
	Item( ::std::vector< bool > & i) { (void)i; t =  ::ccafeopq::BoolArray; }
	Item( ::std::vector< ::std::string > & i) { (void)i; t =  ::ccafeopq::StringArray; }

	enum ::ccafeopq::Type getType(){
                return t;
        }

	static ::ccafeopq::Type scalarToType( int32_t i) { (void)i; return ::ccafeopq::Int; }
	static ::ccafeopq::Type scalarToType( int64_t i) { (void)i; return ::ccafeopq::Long; }
	static ::ccafeopq::Type scalarToType( float i) { (void)i; return ::ccafeopq::Float; }
	static ::ccafeopq::Type scalarToType( double i) { (void)i; return ::ccafeopq::Double; }
	static ::ccafeopq::Type scalarToType( ::std::complex<double> i) { (void)i; return ::ccafeopq::Dcomplex; }
	static ::ccafeopq::Type scalarToType( ::std::complex<float> i) { (void)i; return ::ccafeopq::Fcomplex; }
	static ::ccafeopq::Type scalarToType( bool i ) { (void)i; return ::ccafeopq::Bool; }
	static ::ccafeopq::Type scalarToType( ::std::string & i) { (void)i; return ::ccafeopq::String; }
	static ::ccafeopq::Type scalarToType( const std::string & i ) { (void)i; return ::ccafeopq::String; }

	static ::ccafeopq::Type arrayToType( ::std::vector< int32_t>  i ) { (void)i; return ::ccafeopq::IntArray; }
	static ::ccafeopq::Type arrayToType( ::std::vector< int64_t>  i ) { (void)i; return ::ccafeopq::LongArray; }
	static ::ccafeopq::Type arrayToType( ::std::vector< float>  i ) { (void)i; return ::ccafeopq::FloatArray; }
	static ::ccafeopq::Type arrayToType( ::std::vector< double>  i ) { (void)i; return ::ccafeopq::DoubleArray; }
	static ::ccafeopq::Type arrayToType( ::std::vector< ::std::complex<double> >  i) { (void)i; return ::ccafeopq::DcomplexArray; }
	static ::ccafeopq::Type arrayToType( ::std::vector< ::std::complex<float> > i) { (void)i; return ::ccafeopq::FcomplexArray; }
	static ::ccafeopq::Type arrayToType( ::std::vector< bool >  i ) { (void)i; return ::ccafeopq::BoolArray; }
	static ::ccafeopq::Type arrayToType( ::std::vector< ::std::string > & i) { (void)i; return ::ccafeopq::StringArray; }

	static ::ccafeopq::Type arrayForType( int32_t i ) { (void)i; return ::ccafeopq::IntArray; }
	static ::ccafeopq::Type arrayForType( int64_t i ) { (void)i; return ::ccafeopq::LongArray; }
	static ::ccafeopq::Type arrayForType( float i ) { (void)i; return ::ccafeopq::FloatArray; }
	static ::ccafeopq::Type arrayForType( double i ) { (void)i; return ::ccafeopq::DoubleArray; }
	static ::ccafeopq::Type arrayForType( ::std::complex<double>  i) { (void)i; return ::ccafeopq::DcomplexArray; }
	static ::ccafeopq::Type arrayForType( ::std::complex<float> i) { (void)i; return ::ccafeopq::FcomplexArray; }
	static ::ccafeopq::Type arrayForType( bool  i ) { (void)i; return ::ccafeopq::BoolArray; }
	static ::ccafeopq::Type arrayForType( ::std::string  & i) { (void)i; return ::ccafeopq::StringArray; }


	
	static const ::std::string typeToName( ::ccafeopq::Type t) { 
		switch(t) 
		{
			case ::ccafeopq::NoType: return "NoType"; 
			case ::ccafeopq::Int: return "Int"; 
			case ::ccafeopq::Long: return "Long"; 
			case ::ccafeopq::Float: return "Float"; 
			case ::ccafeopq::Double: return "Double"; 
			case ::ccafeopq::Dcomplex: return "Dcomplex"; 
			case ::ccafeopq::Fcomplex: return "Fcomplex"; 
			case ::ccafeopq::Bool: return "Bool"; 
			case ::ccafeopq::String: return "String"; 

			case ::ccafeopq::IntArray: return "IntArray"; 
			case ::ccafeopq::LongArray: return "LongArray"; 
			case ::ccafeopq::FloatArray: return "FloatArray"; 
			case ::ccafeopq::DoubleArray: return "DoubleArray"; 
			case ::ccafeopq::DcomplexArray: return "DcomplexArray"; 
			case ::ccafeopq::FcomplexArray: return "FcomplexArray"; 
			case ::ccafeopq::BoolArray: return "BoolArray"; 
			case ::ccafeopq::StringArray: return "StringArray"; 
			default: return "unknown";
		}
	}
};

/** scalar item template for map */
template< class Scalar >
class ScalarItem : public Item
{

private:
	Scalar value;

public:
	ScalarItem( Scalar & iv )  : Item( iv ) {
		// done
		value = iv;
	}

	enum ::ccafeopq::Type getType(){
		return t;
	}

	Scalar get() {
		return value;
	}

};


/** array of scalars (using vector) item template for map */
template< class Scalar >
class ArrayItem : public Item
{

private:
	::std::vector< Scalar > array_value;

public:
	
// disallowed for efficiency.
//	ArrayItem( ::std::vector< Scalar  >  av )  : Item( av ), array_value(av) {
//		cout << "val constructor" << endl;
//	}

	ArrayItem( ::std::vector< Scalar, ::std::allocator< Scalar > > &  av )  : Item( av ), array_value(av) {
		// done
	}

	ArrayItem(const Scalar *raw, int rawLength )  : Item( Item::arrayForType( *raw )) , array_value(rawLength) {
		for (int i = 0; i< rawLength; i++) {
			array_value[i] = raw[i];
		}
	}

	enum ::ccafeopq::Type getType(){
		return getType();
	}

	int getSize() {
		return array_value.size();
	}
	/** note non-value semantics for output.
	 * buffer should be right size to start with, or we will have to resize it.
	 */
	void get( ::std::vector<Scalar> & v) {
		size_t len = 0;
		len = v.size();
		if (len < array_value.size() ) { v.resize(array_value.size() ); }
		v = array_value;
	}

	void put( ::std::vector<Scalar> & v) {
		if (v.size() > array_value.size()) {
			array_value.resize(v.size());
		}
		array_value = v;
	}

	void putRaw(const Scalar * v, int rawLength) {
		if (rawLength > int(array_value.size())) {
			array_value.resize(rawLength);
		}
		for (int i = 0; i< rawLength; i++) {
			array_value[i] = v[i];
		}
	}
};


class ScalarsTest {
public:
	void doIt() {
		int iv = 2;
		ScalarItem<int> is(iv);
		int64_t lv=4;
		ScalarItem<int64_t> ls(lv);
		float fv = 5.0;
		ScalarItem<float> fs(fv);
		double dv = 3.0;
		ScalarItem<double> ds(dv);
		::std::complex<float> cfv = 0;
		ScalarItem< ::std::complex<float> > fcs(cfv);
		::std::complex<double> cdv = 0;
		ScalarItem< ::std::complex<double> > dcs(cdv);
		::std::string sv="fred";
		ScalarItem< ::std::string > ss(sv);
		bool bv =false;
		ScalarItem<bool> ib(bv);
	}

};

class ArraysTest {
public:
	void doIt() {
	//	don't do inline constructors of vectors.
	//	ArrayItem< int> is( ::std::vector< int >(2) );
	
		::std::vector<bool> xb(5);
		::std::vector<int> x(5);
		x[0] = x[4] = 1;
		xb[0] = xb[4] = true;
		ArrayItem< int32_t > isr( x );
		ArrayItem< bool > isb( xb );
	}

};

ScalarsTest s;
ArraysTest a;

int cmp_nocase(const std::string & s, const std::string & s2)
{
	std::string::const_iterator p = s.begin();
	std::string::const_iterator p2 = s2.begin();
	while (p != s.end()&& p2!= s2.end()) {
		if (toupper(*p) != toupper(*p2)) return ( toupper(*p) < toupper(*p2)) ? -1: 1;
		++p2;
		++p;
	}
	return (s2.size() == s.size() ) ? 0 : (s.size() < s2.size())? -1:1;
}

}; // end namespace anonymous -- file only.


namespace gov {
namespace sandia {
namespace util {

/** This is a simply-templated concrete typemap implementation.
 * It doesn't inherit the virtual interface ::ccafeopq::TypeMap.
 * Instead our virtualized version just delegates things to this concrete one.
 * It should never be exposed to any class except our wrapper to avoid leaking 
 * data items.
 */
class TypeMapImpl {
	friend class TypeMap;

private:
	::std::map< ::std::string, Item * > data;

public:

	static void whine( ::ccafeopq::Type tFound, ::ccafeopq::Type tRequest) throw(TypeMismatchException)
	{

		::std::string msg = "Mismatch with value found in typemap (requested type ";
		msg += Item::typeToName(tRequest);
		msg += ", actual type ";
		msg += Item::typeToName(tFound);
		msg += ").";
		throw TypeMismatchException(tRequest, tFound, msg);
	}

//
//
// Apparently simple member func templates ICE the pgi 6.x compiler in -g ,
// so we're reverting to macro pain darn it.
//
//
#define WAYITSHOULDBE 0
#if WAYITSHOULDBE

	/** store data. replace item with new one even if there.
	 * @return if ok.
	 * @throw if conflicting type already stored.
	 */
	template< class Scalar > 
	void putScalar(const ::std::string & name, Scalar value) throw(TypeMismatchException)
	{
		Item *i;
		::std::map< ::std::string, Item * >::iterator p = data.find(name);
		// do type check if there, and if there get rid of it.
		if ( p != data.end() ) {
			i = p->second;
			if (i != 0) {
				::ccafeopq::Type t;
				t = Item::scalarToType(value);
				if (i->getType() != t ) {
					whine(i->getType(), t);
					// notreached
				}
				delete i;
				i = 0;
			}
			data.erase(name);
		}
		ScalarItem<Scalar> * s = new ScalarItem<Scalar>(value);
		data[name] = s;
	}

	
	/** Assign the value to map, or throw exception if in map but wrong type. 
	 * reuse vector in map if already there.
	 */
	template< class Scalar >
	void putArray(const ::std::string & name, ::std::vector< Scalar >& value)
	{
		Item *i;
		::std::map< ::std::string, Item * >::iterator p = data.find(name);
		if ( p != data.end() ) {
			i = p->second;
			if (i != 0) {
				::ccafeopq::Type t;
				t = Item::arrayToType(value);
				if ( i->getType() != t ) {
					whine(i->getType(), t);
					// notreached
				}
				ArrayItem< Scalar > *a = 0;
				a = dynamic_cast< ArrayItem< Scalar > * >(i);
				a->put(value);
				return;
			}
		}
		ArrayItem<Scalar> * a = new ArrayItem<Scalar>(value);
		data[name] = a;
	}
	
	/** Assign the value to map, or throw exception if in map but wrong type. 
	 * reuse vector in map if already there.
	 */
	template< class Scalar >
	void putArrayRaw(const ::std::string & name, Scalar * raw, int rawLength)
	{
		Item *i;
		::std::map< ::std::string, Item * >::iterator p = data.find(name);
		if ( p != data.end() ) {
			i = p->second;
			if (i != 0) {
				::ccafeopq::Type t;
				t = Item::arrayForType(*raw);
				if ( i->getType() != t ) {
					whine(i->getType(), t);
					// notreached
				}
				ArrayItem< Scalar > *a = 0;
				a = dynamic_cast< ArrayItem< Scalar > * >(i);
				a->putRaw(raw, rawLength);
				return;
			}
		}
		ArrayItem<Scalar> * a = new ArrayItem<Scalar>(raw, rawLength);
		data[name] = a;
	}
	
	/** Assign the value with data from map, or throw exception if in map
	 * but wrong type. Does nothing if name not in map.
	 */
	template< class Scalar > 
	void getScalar(const ::std::string & name, Scalar & value) {
		Item *i;
		::std::map< ::std::string, Item * >::iterator p = data.find(name);
		if ( p != data.end()) {
			i = p->second;
			if (i != 0) {
				::ccafeopq::Type t;
				t = Item::scalarToType(value);
				if (i->getType() != t ) {
					whine(i->getType(), t);
					// notreached
				}
				ScalarItem< Scalar > *s = 0;
				s = dynamic_cast< ScalarItem< Scalar > * >(i);
				value = s->get();
				return;
			}
		}
	}
        
	/** Assign the value with data from map, or throw exception if in map
	 * but wrong type. If name not in map, copy data from defaultValue to value.
	 */
	template< class Scalar >
	void getArray(const ::std::string & name, ::std::vector< Scalar >& defaultvalue, ::std::vector< Scalar >& value)
	{
		Item *i;
		::std::map< ::std::string, Item * >::iterator p = data.find(name);
		if ( p != data.end()) {
			i = p->second;
			if (i != 0) {
				::ccafeopq::Type t;
				t = Item::arrayToType(value);
				if ( i->getType() != t ) {
					whine(i->getType(), t);
					// notreached
				}
				ArrayItem< Scalar > *a = 0;
				a = dynamic_cast< ArrayItem< Scalar > * >(i);
				size_t asize = 0;
				asize = a->getSize();
				if (value.capacity() < asize) {
					value.resize(asize);
				}
				a->get(value);
				return;
			}
		}
		// if not there or there but unvalued(?!), copy default to result.
		if (value.capacity() < defaultvalue.size()) {
			value.resize(defaultvalue.size());
		}
		value = defaultvalue;
		
	}

#else // WAYITSHOULDBE

	/** store data. replace item with new one even if there.
		// do type check if there, and if there get rid of it. 
					// notreached is whine, theoretically.
	 * @return if ok.
	 * @throw if conflicting type already stored.
	 */
#define TMI_putScalar(Scalar) \
	void putScalar(const ::std::string & name, Scalar value) throw(TypeMismatchException) \
	{ \
		Item *i; \
		::std::map< ::std::string, Item * >::iterator p = data.find(name); \
		if ( p != data.end() ) { \
			i = p->second; \
			if (i != 0) { \
				::ccafeopq::Type t; \
				t = Item::scalarToType(value); \
				if (i->getType() != t ) { \
					whine(i->getType(), t); \
				} \
				delete i; \
				i = 0; \
			} \
			data.erase(name); \
		} \
		ScalarItem< Scalar > * s = new ScalarItem< Scalar >(value); \
		data[name] = s; \
	}
	TMI_putScalar(std::string) /* ; */
	TMI_putScalar(bool) /* ; */
	TMI_putScalar(int32_t) /* ; */
	TMI_putScalar(int64_t) /* ; */
	TMI_putScalar(float) /* ; */
	TMI_putScalar(double) /* ; */
	TMI_putScalar( ::std::complex<float> ) /* ; */
	TMI_putScalar( ::std::complex<double> ) /* ; */

	
	/** Assign the value to map, or throw exception if in map but wrong type. 
	 * reuse vector in map if already there.
					// notreached is whine, theoretically.
	 */
#define TMI_putArray(Scalar) \
	void putArray(const ::std::string & name, ::std::vector< Scalar >& value) \
	{ \
		Item *i; \
		::std::map< ::std::string, Item * >::iterator p = data.find(name); \
		if ( p != data.end() ) { \
			i = p->second; \
			if (i != 0) { \
				::ccafeopq::Type t; \
				t = Item::arrayToType(value); \
				if ( i->getType() != t ) { \
					whine(i->getType(), t); \
				} \
				ArrayItem< Scalar > *a = 0; \
				a = dynamic_cast< ArrayItem< Scalar > * >(i); \
				a->put(value); \
				return; \
			} \
		} \
		ArrayItem< Scalar > * a = new ArrayItem< Scalar >(value); \
		data[name] = a; \
	}
	TMI_putArray(std::string) /* ; */
	TMI_putArray(bool) /* ; */
	TMI_putArray(int32_t) /* ; */
	TMI_putArray(int64_t) /* ; */
	TMI_putArray(float) /* ; */
	TMI_putArray(double) /* ; */
	TMI_putArray( ::std::complex<float> ) /* ; */
	TMI_putArray( ::std::complex<double> ) /* ; */
	
	/** Assign the value to map, or throw exception if in map but wrong type. 
	 * reuse vector in map if already there.
					// notreached is whine, theoretically.
	no such thing as a raw string array.
	 */
#define TMI_putArrayRaw(Scalar) \
	void putArrayRaw(const ::std::string & name, Scalar * raw, int rawLength) \
	{ \
		Item *i; \
		::std::map< ::std::string, Item * >::iterator p = data.find(name); \
		if ( p != data.end() ) { \
			i = p->second; \
			if (i != 0) { \
				::ccafeopq::Type t; \
				t = Item::arrayForType(*raw); \
				if ( i->getType() != t ) { \
					whine(i->getType(), t); \
				} \
				ArrayItem< Scalar > *a = 0; \
				a = dynamic_cast< ArrayItem< Scalar > * >(i); \
				a->putRaw(raw, rawLength); \
				return; \
			} \
		} \
		ArrayItem< Scalar > * a = new ArrayItem< Scalar >(raw, rawLength); \
		data[name] = a; \
	}
	TMI_putArrayRaw(bool) /* ; */
	TMI_putArrayRaw(int32_t) /* ; */
	TMI_putArrayRaw(int64_t) /* ; */
	TMI_putArrayRaw(float) /* ; */
	TMI_putArrayRaw(double) /* ; */
	TMI_putArrayRaw( ::std::complex<float>) /* ; */
	TMI_putArrayRaw( ::std::complex<double>) /* ; */
	
	/** Assign the value with data from map, or throw exception if in map
	 * but wrong type. Does nothing if name not in map.
					// notreached is whine, theoretically.
	 */
#define TMI_getScalar(Scalar) \
	void getScalar(const ::std::string & name, Scalar & value) { \
		Item *i; \
		::std::map< ::std::string, Item * >::iterator p = data.find(name); \
		if ( p != data.end()) { \
			i = p->second; \
			if (i != 0) { \
				::ccafeopq::Type t; \
				t = Item::scalarToType(value); \
				if (i->getType() != t ) { \
					whine(i->getType(), t); \
				} \
				ScalarItem< Scalar > *s = 0; \
				s = dynamic_cast< ScalarItem< Scalar > * >(i); \
				value = s->get(); \
				return; \
			} \
		} \
	}
	TMI_getScalar(std::string) /* ; */
	TMI_getScalar(bool) /* ; */
	TMI_getScalar(int32_t) /* ; */
	TMI_getScalar(int64_t) /* ; */
	TMI_getScalar(float) /* ; */
	TMI_getScalar(double) /* ; */
	TMI_getScalar( ::std::complex<float>) /* ; */
	TMI_getScalar( ::std::complex<double>) /* ; */
        
	/** Assign the value with data from map, or throw exception if in map
	 * but wrong type. If name not in map, copy data from defaultValue to value.
		// if not there or there but unvalued(?!), copy default to result. \
					// notreached whine theoretically.
	 */
#define TMI_getArray(Scalar) \
	void getArray(const ::std::string & name, ::std::vector< Scalar >& defaultvalue, ::std::vector< Scalar >& value) \
	{ \
		Item *i; \
		::std::map< ::std::string, Item * >::iterator p = data.find(name); \
		if ( p != data.end()) { \
			i = p->second; \
			if (i != 0) { \
				::ccafeopq::Type t; \
				t = Item::arrayToType(value); \
				if ( i->getType() != t ) { \
					whine(i->getType(), t); \
				} \
				ArrayItem< Scalar > *a = 0; \
				a = dynamic_cast< ArrayItem< Scalar > * >(i); \
				size_t asize = 0; \
				asize = a->getSize(); \
				if (value.capacity() < asize) { \
					value.resize(asize); \
				} \
				a->get(value); \
				return; \
			} \
		} \
		if (value.capacity() < defaultvalue.size()) { \
			value.resize(defaultvalue.size()); \
		} \
		value = defaultvalue; \
	}
	TMI_getArray(std::string) /* ; */
	TMI_getArray(bool) /* ; */
	TMI_getArray(int32_t) /* ; */
	TMI_getArray(int64_t) /* ; */
	TMI_getArray(float) /* ; */
	TMI_getArray(double) /* ; */
	TMI_getArray( ::std::complex<float>) /* ; */
	TMI_getArray( ::std::complex<double>) /* ; */

#endif // WAYITSHOULDBE

	enum ::ccafeopq::Type typeOf(const ::std::string & name)
	{
		Item *i;
		::std::map< ::std::string, Item * >::iterator p = data.find(name);
		if ( p != data.end()) {
			i = p->second;
			if (i != 0) {
				return i->getType();
			}
		}
		return ::ccafeopq::NoType;
	}

	void remove(const ::std::string & name)
	{
		Item *i;
		::std::map< ::std::string, Item * >::iterator p = data.find(name);
		if ( p != data.end() ) {
			i = p->second;
			if (i != 0) {
				delete i;
				i = 0;
			}
			data.erase(name);
		}
	}

	::std::vector< ::std::string > getAllKeys( enum ::ccafeopq::Type t)
	{
		//size_t size = data.size();
		::std::vector< ::std::string > v; // (size)
		::std::map< ::std::string, Item * >::iterator p = data.begin();
		Item *i = 0;
		enum ::ccafeopq::Type it;
		while (p != data.end() ) {
			i = p->second;
			if (i != 0 ) {
				it = i->getType();
				if (t == ::ccafeopq::NoType || it == t  ) {
					v.push_back(p->first);
				}
			}
			p++;
		}
		return v;
	}

	~TypeMapImpl()
	{
		::std::map< ::std::string, Item * >::iterator p = data.begin();
		Item *i = 0;
		while (p != data.end() ) {
			i = p->second;
			if (i != 0) {
				delete i;
			}
			data[p->first] = 0;
			p++;
		}
	}

	/** key, tm, the destination info. dt, the required type.
	 * v, the value to parse into type dt. */
  static void transformString(const ::std::string & key, ::ccafeopq::Type dt,
                              const ::std::string & v, ::ccafeopq::TypeMap_shared tm)
  {
    // fixme. try parsing string v to type dt and put it in tm
    // at present this has the effect of dropping the string onthe floor
    // if the parse is not supported.
    if (!tm) { return; }
    ::std::istringstream ist(v);
#define UNSTRINGVAL(FTYPE,PRIM) \
    case ::ccafeopq::FTYPE: \
    { PRIM val; \
      ist >> val; \
      tm->put##FTYPE(key, val); \
    } \
    return 
    switch(dt) 
    {
    case ::ccafeopq::String: 
      tm->putString(key, v); 
      return;
    UNSTRINGVAL(Int, int32_t);
    UNSTRINGVAL(Long,  int64_t);
    UNSTRINGVAL(Double, double);
    UNSTRINGVAL(Float, float);
    UNSTRINGVAL(Dcomplex, ::std::complex<double> );
    UNSTRINGVAL(Fcomplex, ::std::complex<float> );
    case ::ccafeopq::Bool:
    {  
      bool val = false;
      if ( 
	cmp_nocase(v, "y") == 0 ||
	cmp_nocase(v, "yes") == 0 ||
	cmp_nocase(v, "da") == 0 ||
	cmp_nocase(v, "si") == 0 ||
	cmp_nocase(v, "neh") == 0 ||
	cmp_nocase(v, "yah") == 0 ||
	cmp_nocase(v, "yep") == 0 ||
	cmp_nocase(v, "t") == 0 ||
	cmp_nocase(v, "true") == 0 ||
	cmp_nocase(v, "1") == 0 ||
	cmp_nocase(v, "right") == 0 ||
	cmp_nocase(v, "correct") == 0 ||
	cmp_nocase(v, "bingo") == 0 ||
	cmp_nocase(v, "ding") == 0 ||
	cmp_nocase(v, "ok") == 0
	) {
          val = true;
      }
      tm->putBool(key,val);
      return;
    }
    case ::ccafeopq::NoType: return ;
    case ::ccafeopq::IntArray:
    case ::ccafeopq::LongArray:
    case ::ccafeopq::FloatArray:
    case ::ccafeopq::DoubleArray:
    case ::ccafeopq::DcomplexArray:
    case ::ccafeopq::FcomplexArray:
    case ::ccafeopq::BoolArray: 
    case ::ccafeopq::StringArray:
    // fixme whine here.
    default:
      return;
    }
  }

}; // class TypeMapImpl 

// YOU DON'T WANT TO TOUCH anything above here. 
// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//
//====================================================================
// the cca-like typemap implementation.
//====================================================================

//---------------------------------------------------------- 
TypeMap::TypeMap(){
       	m = new TypeMapImpl();
#if (defined(UTIL_TYPEMAP_MAIN) || defined(CCAFE_AUDIT))
	::std::cout << "opq tm created" << ::std::endl;
#endif
}
TypeMap::~TypeMap(){
       	delete m;
#if (defined(UTIL_TYPEMAP_MAIN) || defined(CCAFE_AUDIT))
	::std::cout << "opq tm deleted" << ::std::endl;
#endif
}
  
::ccafeopq::TypeMap_shared TypeMap::cloneTypeMap()
{	
	return cloneData();
}

::ccafeopq::TypeMap_shared TypeMap::cloneData()
{	
	::gov::sandia::util::TypeMap *tm = new ::gov::sandia::util::TypeMap();
	::ccafeopq::TypeMap_Interface *ctm = 0;
	ctm = tm;
	::ccafeopq::TypeMap_shared otm(ctm);
	copyInData(this, otm);
	return otm;
}

//---------------------------------------------------------- 
::ccafeopq::TypeMap_shared TypeMap::cloneEmpty() 
{	
	TypeMap *tm = new TypeMap();
	::ccafeopq::TypeMap_Interface *ctm = 0;
	ctm = tm;
	return ::ccafeopq::TypeMap_shared(ctm);
}

//---------------------------------------------------------- 
int32_t      TypeMap::getInt(const ::std::string & key,  int32_t defaultValue) throw (TypeMismatchException ) 
{	m->getScalar(key, defaultValue); return defaultValue; } 

//---------------------------------------------------------- 
int64_t    TypeMap::getLong(const ::std::string & key,  int64_t defaultValue) throw (TypeMismatchException )
{	m->getScalar(key, defaultValue); return defaultValue; } 

//---------------------------------------------------------- 
float    TypeMap::getFloat(const ::std::string & key,  float defaultValue) throw (TypeMismatchException )
{	m->getScalar(key, defaultValue); return defaultValue; } 

//---------------------------------------------------------- 
double   TypeMap::getDouble(const ::std::string & key,  double defaultValue) throw (TypeMismatchException )
{	m->getScalar(key, defaultValue); return defaultValue; } 

//---------------------------------------------------------- 
::std::complex<float> TypeMap::getFcomplex(const ::std::string & key,  ::std::complex<float> defaultValue) throw (TypeMismatchException )
{	m->getScalar(key, defaultValue); return defaultValue; } 

//---------------------------------------------------------- 
::std::complex<double> TypeMap::getDcomplex(const ::std::string & key,  ::std::complex<double> defaultValue) throw (TypeMismatchException )
{	m->getScalar(key, defaultValue); return defaultValue; } 

//---------------------------------------------------------- 
::std::string  TypeMap::getString(const ::std::string & key,  ::std::string defaultValue) throw (TypeMismatchException )
{	m->getScalar(key, defaultValue); return defaultValue; } 

//---------------------------------------------------------- 
bool  TypeMap::getBool(const ::std::string & key,  bool defaultValue) throw (TypeMismatchException )
{	m->getScalar(key, defaultValue); return defaultValue; } 

// ======================================================

::std::vector< int32_t > TypeMap::getIntArray(const ::std::string & key,  ::std::vector< int32_t >&  defaultValue) throw (TypeMismatchException )
{ 
	::std::vector< int32_t > result;
       	m->getArray(key, defaultValue, result);
       	return result; 
}

//---------------------------------------------------------- 

#if (SIZEOF_LONG_INT != 8)
::std::vector< long int > TypeMap::getLongArray(const ::std::string & key,  ::std::vector< long int >&  defaultValue) throw (TypeMismatchException )
{
				// BUG FIXME range checking the int conversions. ugh.
	size_t i;
	size_t n = defaultValue.size();
	::std::vector< int64_t > value(n);
	assert(value.size() == n);
	for (i = 0; i < n ; i++) {
		value[i] = defaultValue[i];
	}

	::std::vector< int64_t > result;
	m->getArray(key, value, result);
	size_t p = result.size();
	::std::vector< long int > rval(p);
	for (i = 0; i < n ; i++) {
		rval[i] = result[i];
	}
  
	return rval;
}
#endif

//---------------------------------------------------------- 

::std::vector< int64_t > TypeMap::getLongArray(const ::std::string & key,  ::std::vector< int64_t >&  defaultValue) throw (TypeMismatchException )
{ ::std::vector< int64_t > result; m->getArray(key, defaultValue, result); return result; }

//---------------------------------------------------------- 
::std::vector< float >    TypeMap::getFloatArray(const ::std::string & key,  ::std::vector< float >&  defaultValue) throw (TypeMismatchException )
{ ::std::vector< float > result; m->getArray(key, defaultValue, result); return result; }

//---------------------------------------------------------- 
::std::vector< double > TypeMap::getDoubleArray(const ::std::string & key,  ::std::vector< double >&  defaultValue) throw (TypeMismatchException )
{ ::std::vector< double > result; m->getArray(key, defaultValue, result); return result; }

//---------------------------------------------------------- 
::std::vector< ::std::complex<float> > TypeMap::getFcomplexArray(const ::std::string & key,  ::std::vector< ::std::complex<float> >&  defaultValue) throw (TypeMismatchException )
{ ::std::vector< ::std::complex<float> > result; m->getArray(key, defaultValue, result); return result; }

//---------------------------------------------------------- 
::std::vector< ::std::complex<double> > TypeMap::getDcomplexArray(const ::std::string & key,  ::std::vector< ::std::complex<double> >&  defaultValue) throw (TypeMismatchException )
{ ::std::vector< ::std::complex<double> > result; m->getArray(key, defaultValue, result); return result; }

//---------------------------------------------------------- 
::std::vector< ::std::string > TypeMap::getStringArray(const ::std::string & key,  ::std::vector< ::std::string >&  defaultValue) throw (TypeMismatchException ) 
{ ::std::vector< ::std::string > result; m->getArray(key, defaultValue, result); return result; }

//---------------------------------------------------------- 
::std::vector< bool > TypeMap::getBoolArray(const ::std::string & key,  ::std::vector< bool >&  defaultValue) throw (TypeMismatchException )
{ ::std::vector< bool > result; m->getArray(key, defaultValue, result); return result; }


// ======================================================

void TypeMap::putInt(const ::std::string & key,  int32_t value)
throw (TypeMismatchException )
{	m->putScalar(key, value); } 

//---------------------------------------------------------- 
void TypeMap::putLong(const ::std::string & key,  int64_t value)
throw (TypeMismatchException )
{	m->putScalar(key, value); } 

//---------------------------------------------------------- 
void TypeMap::putFloat(const ::std::string & key,  float value)
throw (TypeMismatchException )
{	m->putScalar(key, value); } 

//---------------------------------------------------------- 
void TypeMap::putDouble(const ::std::string & key,  double value)
throw (TypeMismatchException )
{	m->putScalar(key, value); } 

//---------------------------------------------------------- 
void TypeMap::putFcomplex(const ::std::string & key,  ::std::complex<float> value) 
throw (TypeMismatchException )
{	m->putScalar(key, value); } 

//---------------------------------------------------------- 
void TypeMap::putDcomplex(const ::std::string & key,  ::std::complex<double> value)
throw (TypeMismatchException )
{	m->putScalar(key, value); } 

//---------------------------------------------------------- 
void TypeMap::putString(const ::std::string & key, const ::std::string & value) 
throw (TypeMismatchException )
{	m->putScalar(key, value); } 

//---------------------------------------------------------- 
void TypeMap::putBool(const ::std::string & key,  bool value) 
throw (TypeMismatchException )
{	m->putScalar(key, value); } 

// ======================================================

void TypeMap::putIntArray(const ::std::string & key,  int32_t * value ,int length)
throw (TypeMismatchException )
{ m->putArrayRaw(key, value, length); }

//---------------------------------------------------------- 
void TypeMap::putIntArray(const ::std::string & key,  ::std::vector< int32_t >&  value)
throw (TypeMismatchException )
{ m->putArray(key,value); }

//---------------------------------------------------------- 
void TypeMap::putLongArray(const ::std::string & key,  int64_t * value ,int length)
throw (TypeMismatchException )
{ m->putArrayRaw(key, value, length); }

//---------------------------------------------------------- 
void TypeMap::putLongArray(const ::std::string & key,  ::std::vector< int64_t >&  value )
throw (TypeMismatchException )
{ m->putArray(key,value); }

#if (SIZEOF_LONG_INT != 8)
void TypeMap::putLongArray(const ::std::string & key,  ::std::vector< long int >& lvalue )
throw (TypeMismatchException )
{
	size_t n = lvalue.size();
	::std::vector< int64_t > value(n);
	for (size_t i = 0; i < n ; i++) {
		value[i] = lvalue[i];
	}
	m->putArray(key,value);
}
#endif

//---------------------------------------------------------- 
void TypeMap::putFloatArray(const ::std::string & key,  float * value ,int length) 
throw (TypeMismatchException )
{ m->putArrayRaw(key, value, length); }

//---------------------------------------------------------- 
void TypeMap::putFloatArray(const ::std::string & key,  ::std::vector< float >&  value )
throw (TypeMismatchException )
{ m->putArray(key,value); }

//---------------------------------------------------------- 
void TypeMap::putDoubleArray(const ::std::string & key,  double * value ,int length)
throw (TypeMismatchException )
{ m->putArrayRaw(key, value, length); }

//---------------------------------------------------------- 
void TypeMap::putDoubleArray(const ::std::string & key,  ::std::vector< double >&  value) 
throw (TypeMismatchException )
{ m->putArray(key,value); }

//---------------------------------------------------------- 
void TypeMap::putFcomplexArray(const ::std::string & key,  ::std::complex<float> * value ,int length) 
throw (TypeMismatchException )
{ m->putArrayRaw(key, value, length); }

//---------------------------------------------------------- 
void TypeMap::putFcomplexArray(const ::std::string & key,  ::std::vector< ::std::complex<float> >&  value)
throw (TypeMismatchException )
{ m->putArray(key,value); }

//---------------------------------------------------------- 
void TypeMap::putDcomplexArray(const ::std::string & key,  ::std::complex<double> * value ,int length)
throw (TypeMismatchException )
{ m->putArrayRaw(key, value, length); }

//---------------------------------------------------------- 
void TypeMap::putDcomplexArray(const ::std::string & key,  ::std::vector< ::std::complex<double> >&  value)
throw (TypeMismatchException )
{ m->putArray(key,value); }

//---------------------------------------------------------- 
void TypeMap::putStringArray(const ::std::string & key,  ::std::vector< ::std::string >&  value) 
throw (TypeMismatchException )
{ m->putArray(key,value); }

//---------------------------------------------------------- 
void TypeMap::putBoolArray(const ::std::string & key,  bool * value ,int length)
throw (TypeMismatchException )
{ m->putArrayRaw(key, value, length); }

//---------------------------------------------------------- 
void TypeMap::putBoolArray(const ::std::string & key,  ::std::vector< bool >&  value)
throw (TypeMismatchException )
{ m->putArray(key,value); }

// ======================================================

void TypeMap::remove (const ::std::string & key) { m->remove(key); }

//---------------------------------------------------------- 
::std::vector< ::std::string > TypeMap::getAllKeys( enum ::ccafeopq::Type t)
{ return m->getAllKeys(t); }

//---------------------------------------------------------- 
bool TypeMap::hasKey(const ::std::string & key)
{ return (m->typeOf(key) != ::ccafeopq::NoType); }

//---------------------------------------------------------- 
enum ::ccafeopq::Type TypeMap::typeOf(const ::std::string & key)
{ return m->typeOf(key); }

//---------------------------------------------------------- 
// some things templates still won't do that macro will. damn.
// e.g. TRANSFER_CASE(int32_t, Int, 0)
// moving scalar values from one map to another is a pain.
// When there's a mismatch, an exception would occur. We're
// not in the remove/overwrite business, so we just skip
// it if mismatch detected.
#define TRANSFER_CASE(BTYPE, FTYPE, DEFVAL) \
    case ::ccafeopq::FTYPE: \
      { \
        BTYPE val = tmSrc->get##FTYPE(keys[i], DEFVAL); \
        enum ::ccafeopq::Type dt = tmDest->typeOf(keys[i]); \
        if (dt == ::ccafeopq::NoType || dt == ::ccafeopq::FTYPE ) \
        { \
           tmDest->put##FTYPE(keys[i], val); \
        } \
      } \
      break

// This macro assumes the key types match and we want
// instead to know if the value has changed with the
// copying. If so, the value gets added to changedKeys.
#define CHANGE_TRANSFER_CASE(BTYPE, FTYPE, DEFVAL) \
    case ::ccafeopq::FTYPE: \
      { \
        BTYPE val = tmSrc->get##FTYPE(keys[i], DEFVAL); \
        BTYPE oldval = tmSrc->get##FTYPE(keys[i], DEFVAL); \
        if (oldval != val ) \
        { \
           tmDest->put##FTYPE(keys[i], val); \
	   changedKeys.push_back(keys[i]); \
        } \
      } \
      break

// moving array values from one map to another is a pain.
// When there's a mismatch, an exception would occur. We're
// not in the remove/overwrite business, so we just skip
// it if mismatch detected.
#define TRANSFER_ARRAY_CASE(BTYPE, FTYPE) \
    case ::ccafeopq::FTYPE##Array: \
      { \
        ::std::vector< BTYPE > b(0); \
        ::std::vector< BTYPE > val = tmSrc->get##FTYPE##Array(keys[i], b); \
        enum ::ccafeopq::Type dt = tmDest->typeOf(keys[i]);  \
        if (dt == ::ccafeopq::NoType || dt == ::ccafeopq::FTYPE##Array )  \
        {  \
           tmDest->put##FTYPE##Array(keys[i], val);  \
        } \
      } \
      break

// Assumes types are matched. performs put only when
// values are different. changedKeys is updated for keys
// where put is used.
#define CHANGE_TRANSFER_ARRAY_CASE(BTYPE, FTYPE) \
    case ::ccafeopq::FTYPE##Array: \
      { \
        ::std::vector< BTYPE > b(0); \
        ::std::vector< BTYPE > val = tmSrc->get##FTYPE##Array(keys[i], b); \
        ::std::vector< BTYPE > oldval = tmDest->get##FTYPE##Array(keys[i], b); \
        if (val.size() != oldval.size() ) \
        {  \
           tmDest->put##FTYPE##Array(keys[i], val);  \
	   changedKeys.push_back(keys[i]); \
        } else { \
	  for (size_t p = 0; p < val.size(); p++) \
	  { \
            if (val[i] != oldval[i]) \
            { \
              tmDest->put##FTYPE##Array(keys[i], val);  \
	      changedKeys.push_back(keys[i]); \
	      break; \
	    } \
	  } \
        } \
      } \
      break


/** copy data into typemap from another.
    Assumes nothing, i.e. can cope with a babel tm if it
    behaves according to the opq spec.
 */
void TypeMap::copyInData( ::ccafeopq::TypeMap_shared tmSrc, ::ccafeopq::TypeMap_shared tmDest)
{
  if (!tmSrc) { return; }
  if (!tmDest) { return; }
	::std::vector< ::std::string > keys = tmSrc->getAllKeys(::ccafeopq::NoType);
  for (size_t i = 0; i < keys.size(); i++) 
  {
#if	  DEBUG_COPY_DATA
	  IO_en2(" TypeMap::copyInData(ts,ts) from key %s", keys[i].c_str());
#endif
    enum ::ccafeopq::Type st = tmSrc->typeOf(keys[i]);
    switch (st) {
    case ::ccafeopq::NoType:
    break; // ??????????
    TRANSFER_CASE(int32_t, Int, 0);
    TRANSFER_CASE(int64_t, Long, 0);
    TRANSFER_CASE(float, Float, 0);
    TRANSFER_CASE(double, Double, 0);
    TRANSFER_CASE( ::std::complex< float >, Fcomplex, ::std::complex< float >(0,0) );
    TRANSFER_CASE( ::std::complex< double >, Dcomplex, ::std::complex< double >(0,0) );
    TRANSFER_CASE(bool, Bool, false);
    TRANSFER_ARRAY_CASE(int32_t, Int);
    TRANSFER_ARRAY_CASE(int64_t, Long);
    TRANSFER_ARRAY_CASE(float, Float);
    TRANSFER_ARRAY_CASE(double, Double);
    TRANSFER_ARRAY_CASE( ::std::complex< float >, Fcomplex );
    TRANSFER_ARRAY_CASE( ::std::complex< double >, Dcomplex );
    TRANSFER_ARRAY_CASE(bool, Bool);
    TRANSFER_ARRAY_CASE( ::std::string , String);
    case ::ccafeopq::String:
    {
      enum ::ccafeopq::Type dt = tmDest->typeOf(keys[i]);
      ::std::string val = 
        tmSrc->getString(keys[i], ""); 
      if (dt == ::ccafeopq::NoType || dt == ::ccafeopq::String ) 
      {
#if	  DEBUG_COPY_DATA
	  IO_en2("          TypeMap::copyInData val %s", val.c_str());
#endif
        tmDest->putString(keys[i], val); 
      } else {
        // some witless turd has put in a string value
        // instead of the blessed type for the key.
        // or got caught in classic space...
        TypeMapImpl::transformString(keys[i], dt, val, tmDest);
      }
    }
    break;
    default:
    break;
    }
  }
}
// it's disgusting, but unavoidable. we can't wrap the same
// pointer twice, which is exactly the situation inside clone
// Actually, if we worked out a proper copy operator definition on
// TypeMapImpl and TypeMap, this is a 2-liner. until then...
// copying a map full of pointers in TypeMapImpl is nontrivial.
void TypeMap::copyInData( TypeMap *tmSrc, ::ccafeopq::TypeMap_shared tmDest)
{
  if (!tmSrc) { return; }
  if (!tmDest) { return; }
	::std::vector< ::std::string > keys = tmSrc->getAllKeys(::ccafeopq::NoType);
  for (size_t i = 0; i < keys.size(); i++) 
  {
#if	  DEBUG_COPY_DATA
	  IO_en2(" TypeMap::copyInData(tptr,ts) from key %s", keys[i].c_str());
#endif
    enum ::ccafeopq::Type st = tmSrc->typeOf(keys[i]);
    switch (st) {
    case ::ccafeopq::NoType:
    break; // ??????????
    TRANSFER_CASE(int32_t, Int, 0);
    TRANSFER_CASE(int64_t, Long, 0);
    TRANSFER_CASE(float, Float, 0);
    TRANSFER_CASE(double, Double, 0);
    TRANSFER_CASE( ::std::complex< float >, Fcomplex, ::std::complex< float >(0,0) );
    TRANSFER_CASE( ::std::complex< double >, Dcomplex, ::std::complex< double >(0,0) );
    TRANSFER_CASE(bool, Bool, false);
    TRANSFER_ARRAY_CASE(int32_t, Int);
    TRANSFER_ARRAY_CASE(int64_t, Long);
    TRANSFER_ARRAY_CASE(float, Float);
    TRANSFER_ARRAY_CASE(double, Double);
    TRANSFER_ARRAY_CASE( ::std::complex< float >, Fcomplex );
    TRANSFER_ARRAY_CASE( ::std::complex< double >, Dcomplex );
    TRANSFER_ARRAY_CASE(bool, Bool);
    TRANSFER_ARRAY_CASE( ::std::string , String);
    case ::ccafeopq::String:
    {
      enum ::ccafeopq::Type dt = tmDest->typeOf(keys[i]);
      ::std::string val = 
        tmSrc->getString(keys[i], ""); 
      if (dt == ::ccafeopq::NoType || dt == ::ccafeopq::String ) 
      {
#if	  DEBUG_COPY_DATA
	  IO_en2("          val %s", val.c_str());
#endif
        tmDest->putString(keys[i], val); 
      } else {
        // some witless turd has put in a string value
        // instead of the blessed type for the key.
        TypeMapImpl::transformString(keys[i], dt, val, tmDest);
      }
    }
    break;
    default:
    break;
    }
  }
}

/** copy data into typemap from another, but ignore keys in tmSrc
 * that match the names in ignoreKeys.
 */
void TypeMap::copyInData( ::ccafeopq::TypeMap_shared tmSrc,
	       	          ::ccafeopq::TypeMap_shared tmDest,
		          TypeMapFilter & ignoreKeys)
{
  if (!tmSrc) { return; }
  if (!tmDest) { return; }
  ::std::vector< ::std::string > keys = tmSrc->getAllKeys(::ccafeopq::NoType);
  Filtrator fi;
  for (size_t i = 0; i < keys.size(); i++) 
  {
    fi = ignoreKeys.find(keys[i]);
    if (fi != ignoreKeys.end()) {
      continue;
    }

    enum ::ccafeopq::Type st = tmSrc->typeOf(keys[i]);
    switch (st) {
    case ::ccafeopq::NoType:
    break; // ??????????
    TRANSFER_CASE(int32_t, Int, 0);
    TRANSFER_CASE(int64_t, Long, 0);
    TRANSFER_CASE(float, Float, 0);
    TRANSFER_CASE(double, Double, 0);
    TRANSFER_CASE( ::std::complex< float >, Fcomplex, ::std::complex< float >(0,0) );
    TRANSFER_CASE( ::std::complex< double >, Dcomplex, ::std::complex< double >(0,0) );
    TRANSFER_CASE(bool, Bool, false);
    TRANSFER_ARRAY_CASE(int32_t, Int);
    TRANSFER_ARRAY_CASE(int64_t, Long);
    TRANSFER_ARRAY_CASE(float, Float);
    TRANSFER_ARRAY_CASE(double, Double);
    TRANSFER_ARRAY_CASE( ::std::complex< float >, Fcomplex );
    TRANSFER_ARRAY_CASE( ::std::complex< double >, Dcomplex );
    TRANSFER_ARRAY_CASE(bool, Bool);
    TRANSFER_ARRAY_CASE( ::std::string , String);
    case ::ccafeopq::String:
    {
      enum ::ccafeopq::Type dt = tmDest->typeOf(keys[i]);
      ::std::string val = 
        tmSrc->getString(keys[i], ""); 
      if (dt == ::ccafeopq::NoType || dt == ::ccafeopq::String ) 
      {
        tmDest->putString(keys[i], val); 
      } else {
        // some witless turd has put in a string value
        // instead of the blessed type for the key.
        // or got caught in classic space...
        TypeMapImpl::transformString(keys[i], dt, val, tmDest);
      }
    }
    break;
    default:
    break;
    }
  }
}

/** copy data from tmSrc to tmDest, but only for the keys and types
 * in tmSrc that match the names in srcKeys.
 */
void TypeMap::copyInKeys( ::ccafeopq::TypeMap_shared tmSrc,
                          ::ccafeopq::TypeMap_shared tmDest,
		          TypeMapFilter & srcKeys)
{
  if (!tmSrc) { return; }
  if (!tmDest) { return; }
  ::std::vector< ::std::string > keys = tmSrc->getAllKeys(::ccafeopq::NoType);
  Filtrator fi;
  for (size_t i = 0; i < keys.size(); i++) 
  {
    fi = srcKeys.find(keys[i]);
    if (fi == srcKeys.end()) {
      continue;
    }
    enum ::ccafeopq::Type st = tmSrc->typeOf(keys[i]);
    if (st != fi->second) {
      continue;
    }
    switch (st) {
    case ::ccafeopq::NoType:
    break; // ??????????
    TRANSFER_CASE(int32_t, Int, 0);
    TRANSFER_CASE(int64_t, Long, 0);
    TRANSFER_CASE(float, Float, 0);
    TRANSFER_CASE(double, Double, 0);
    TRANSFER_CASE( ::std::complex< float >, Fcomplex, ::std::complex< float >(0,0) );
    TRANSFER_CASE( ::std::complex< double >, Dcomplex, ::std::complex< double >(0,0) );
    TRANSFER_CASE(bool, Bool, false);
    TRANSFER_ARRAY_CASE(int32_t, Int);
    TRANSFER_ARRAY_CASE(int64_t, Long);
    TRANSFER_ARRAY_CASE(float, Float);
    TRANSFER_ARRAY_CASE(double, Double);
    TRANSFER_ARRAY_CASE( ::std::complex< float >, Fcomplex );
    TRANSFER_ARRAY_CASE( ::std::complex< double >, Dcomplex );
    TRANSFER_ARRAY_CASE(bool, Bool);
    TRANSFER_ARRAY_CASE( ::std::string , String);
    case ::ccafeopq::String:
    {
      enum ::ccafeopq::Type dt = tmDest->typeOf(keys[i]);
      ::std::string val = 
        tmSrc->getString(keys[i], ""); 
      if (dt == ::ccafeopq::NoType || dt == ::ccafeopq::String ) 
      {
        tmDest->putString(keys[i], val); 
      } else {
        // some witless turd has put in a string value
        // instead of the blessed type for the key.
        // or got caught in classic space...
        TypeMapImpl::transformString(keys[i], dt, val, tmDest);
      }
    }
    break;
    default:
    break;
    }
  }
}

/** copy data from tmSrc to tmDest, but only for the keys and types
 * in tmSrc that match the names in srcKeys.
 */
StringVector TypeMap::copyInKeysTell( ::ccafeopq::TypeMap_shared tmSrc,
                          ::ccafeopq::TypeMap_shared tmDest,
		          StringVector & keys)
{
  StringVector changedKeys;
  if (!tmSrc) { return changedKeys; }
  if (!tmDest) { return changedKeys; }
  if (keys.size() == 0) { return changedKeys; }
  for (size_t i = 0; i < keys.size(); i++) 
  {
    if (! tmSrc->hasKey(keys[i]) )
    { continue; }
    if (! tmDest->hasKey(keys[i]) )
    { continue; }
    enum ::ccafeopq::Type st = tmSrc->typeOf(keys[i]);
    if (tmDest->typeOf(keys[i]) != st )
    { continue; } // fixme-feature could have a reject list returned.

    switch (st) {
    case ::ccafeopq::NoType:
    break; // ??????????
    CHANGE_TRANSFER_CASE(int32_t, Int, 0);
    CHANGE_TRANSFER_CASE(int64_t, Long, 0);
    CHANGE_TRANSFER_CASE(float, Float, 0);
    CHANGE_TRANSFER_CASE(double, Double, 0);
    CHANGE_TRANSFER_CASE( ::std::complex< float >, Fcomplex, ::std::complex< float >(0,0) );
    CHANGE_TRANSFER_CASE( ::std::complex< double >, Dcomplex, ::std::complex< double >(0,0) );
    CHANGE_TRANSFER_CASE(bool, Bool, false);
    CHANGE_TRANSFER_CASE( ::std::string, String, "");
    CHANGE_TRANSFER_ARRAY_CASE(int32_t, Int);
    CHANGE_TRANSFER_ARRAY_CASE(int64_t, Long);
    CHANGE_TRANSFER_ARRAY_CASE(float, Float);
    CHANGE_TRANSFER_ARRAY_CASE(double, Double);
    CHANGE_TRANSFER_ARRAY_CASE( ::std::complex< float >, Fcomplex );
    CHANGE_TRANSFER_ARRAY_CASE( ::std::complex< double >, Dcomplex );
    CHANGE_TRANSFER_ARRAY_CASE(bool, Bool);
    CHANGE_TRANSFER_ARRAY_CASE( ::std::string , String);
    default:
    break;
    }
  }
  return changedKeys;
}

#undef TRANSFER_CASE
#undef TRANSFER_ARRAY_CASE

//---------------------------------------------------------- 
/** copy k/v/k/v...0 array of strings to typemap.
* Particularly it pays attention to already known properties
* and make everything else strings in the received map.
**/
void TypeMap::props2typemap(char** properties, ::ccafeopq::TypeMap_shared tm)
{
  if (!tm || !properties) { return; }
  int i = 0;
  const char* key = properties[i];
  const char* value = properties[i+1];
  ::ccafeopq::TypeMap_shared scratch = tm->cloneEmpty();
  if (key != 0) {
    do {
      scratch->putString(key,value);
      i += 2;
      key = properties[i];
      value = properties[i+1];
    } while (key != 0);
  }
  copyInData(scratch, tm);
}

//---------------------------------------------------------- 
::ccafeopq::TypeMap_shared TypeMap::props2newtypemap(char** properties)
{
	::gov::sandia::util::TypeMap *tm = new ::gov::sandia::util::TypeMap();
	::ccafeopq::TypeMap_Interface *ctm = 0;
	ctm = tm;
	::ccafeopq::TypeMap_shared otm(ctm);
  props2typemap(properties, otm);
  return otm;
}

//---------------------------------------------------------- 
::ccafeopq::TypeMap_shared TypeMap::createTypeMap()
{
	::gov::sandia::util::TypeMap *tm = new ::gov::sandia::util::TypeMap();
	::ccafeopq::TypeMap_Interface *ctm = 0;
	ctm = tm;
	::ccafeopq::TypeMap_shared otm(ctm);
	return otm;
}

//---------------------------------------------------------- 
StringMap TypeMap::props2stringmap(char **properties)
{
  StringMap sm;
  if ( !properties) { return sm; }
  int i = 0;
  const char* key = properties[i];
  const char* value = properties[i+1];
  if (key != 0 && value != 0) {
    do {
      sm[key] = value;
      i += 2;
      key = properties[i];
      value = properties[i+1];
    } while (key != 0 && value != 0);
  }
  return sm;
}

//---------------------------------------------------------- 
 /** copy into typemap from stringmap */
void TypeMap::stringmap2typemap( const StringMap & stringmap, ::ccafeopq::TypeMap_shared tm )
{
	// this should probably be smarter. for now, all strings
	// mapped as string, regardless of content. this is likely to
	// draw an exception and we should parse according to type
	// of matching key in tm if there is one.
  // fixme stringmap2typemap(sm,tm)
		StringMap::const_iterator p = stringmap.begin();
		while ( stringmap.end() != p ) {
			tm->putString(p->first, p->second);
			++p;
		}
}

//---------------------------------------------------------- 
    /** create typemap from stringmap */
::ccafeopq::TypeMap_shared TypeMap::stringmap2newtypemap( const StringMap & stringmap )
{
  ::gov::sandia::util::TypeMap *tm = new ::gov::sandia::util::TypeMap();
  ::ccafeopq::TypeMap_Interface *ctm = 0;
  ctm = tm;
  ::ccafeopq::TypeMap_shared otm(ctm);
  stringmap2typemap(stringmap, otm);
  return otm;
}

//---------------------------------------------------------- 
void TypeMap::pi2typemap( ::ccafeopq::PortInfo * pi, ::ccafeopq::TypeMap_shared tm)
{
  if (!tm || !pi) { return; }
  // IO_en1("TypeMap::pi2typemap: not implemented!");
  // FIXME.  need some type checking here.
  ::std::vector< ::std::string > k = pi->getKeys();
  for(std::vector< ::std::string >::iterator i = k.begin();i != k.end();++i) {
    std::string key = *i;
    std::string val = pi->getProperty(key);
    IO_en3("! PI2tyepmap: key = %s; property = %s", key.c_str(), val.c_str());
    tm->putString(key, val);
  }

}

//---------------------------------------------------------- 
StringVector TypeMap::typemap2props( ::ccafeopq::TypeMap_shared tm)
{
  StringVector v;
  // fixme typemap2props
  TypeMapImpl::whine( ::ccafeopq::NoType, ::ccafeopq::String );
  return v;
}
//---------------------------------------------------------- 
StringMap TypeMap::typemap2stringmap( ::ccafeopq::TypeMap_shared tm)
{
	StringMap sm;
	// fixme typemap2stringmap
	TypeMapImpl::whine( ::ccafeopq::NoType, ::ccafeopq::String );
	return sm;
}
//---------------------------------------------------------- 
//
::std::string TypeMap::stringType( ::ccafeopq::TypeMap_shared t, const ::std::string &key)
{
	if (!t) {
		return "";
	}
	enum ::ccafeopq::Type kt = t->typeOf(key);
	return Item::typeToName(kt);
}

//---------------------------------------------------------- 
//
#define REFIX(x,y) if (typeName == y)  return ccafeopq::x
::ccafeopq::Type TypeMap::typeFromString( const ::std::string &typeName)
{
	REFIX(NoType,"NoType");
	REFIX(Int,"Int");
	REFIX(Long,"Long");
	REFIX(Float,"Float");
	REFIX(Double,"Double");
	REFIX(Dcomplex,"Dcomplex");
	REFIX(Fcomplex,"Fcomplex");
	REFIX(Bool,"Bool");
	REFIX(String,"String");
	REFIX(IntArray,"IntArray");
	REFIX(LongArray,"LongArray");
	REFIX(FloatArray,"FloatArray");
	REFIX(DoubleArray,"DoubleArray");
	REFIX(DcomplexArray,"DcomplexArray");
	REFIX(FcomplexArray,"FcomplexArray");
	REFIX(BoolArray,"BoolArray");
	REFIX(StringArray,"StringArray");
	return ccafeopq::NoType;
}

//---------------------------------------------------------- 
//
int TypeMap::putValueByStrings( ::ccafeopq::TypeMap_shared t, const ::std::string & key, const ::std::string &vtype, const ::std::string & val)
{
	if (!t || key.size() == 0) { return -1; }
	::ccafeopq::Type kt = typeFromString(vtype); 
	if (kt ==  ::ccafeopq::NoType) { return -1; }
	try {
	  TypeMapImpl::transformString( key, kt, val, t);
	  return 0;
	}
	catch ( std::exception &e )
	{
		return -3;
	}

}

//---------------------------------------------------------- 
// there's a nice nonportable way to do this with strstream
#define STRINGVAL(BTYPE, FTYPE, DEFVAL, FMT) \
  case ::ccafeopq::FTYPE: \
    { \
      BTYPE v = t->get##FTYPE(key, DEFVAL); \
      sprintf(buf, FMT, v); \
      s += buf; \
      return s; \
    } \
  break
#undef STRINGVAL
#define STRINGVAL(FTYPE,DEFVAL) \
  case ::ccafeopq::FTYPE: \
    ost << t->get##FTYPE(key, DEFVAL); \
    return ost.str(); \
  break
        
#define ARRAYVAL(FTYPE,VTYPE) \
  case ::ccafeopq::FTYPE##Array: \
  { \
    ::std::vector< VTYPE > v; \
    v = t->get##FTYPE##Array( key, v ); \
    for (size_t i = 0; i < v.size(); i++) \
    { \
      ost << v[i] << " "; \
    } \
    return ost.str(); \
  } \
  break
        
::std::string TypeMap::stringValue( ::ccafeopq::TypeMap_shared t, const ::std::string &key)
{
  ::std::string s;
  if (!t) { return s; }
  ::std::ostringstream ost;
  enum ::ccafeopq::Type kt = t->typeOf(key);
  // char buf[128];
  switch (kt) {
  case ::ccafeopq::NoType: return s;
  STRINGVAL(Int,0);
  STRINGVAL(Long, 0);
  STRINGVAL(Double, 0);
  STRINGVAL(Float, 0);
  STRINGVAL(Bool, false);
  STRINGVAL(String, "");
  STRINGVAL(Dcomplex, ::std::complex<double>(0,0) );
  STRINGVAL(Fcomplex, ::std::complex<float>(0,0) );
  ARRAYVAL(Int, int32_t);
  ARRAYVAL(Long, int64_t);
  ARRAYVAL(Double, double);
  ARRAYVAL(Float, float);
  ARRAYVAL(Bool, bool);
  ARRAYVAL(String, ::std::string );
  ARRAYVAL(Dcomplex, ::std::complex<double> );
  ARRAYVAL(Fcomplex, ::std::complex<float> );
  default:
    return s;
  }
  return "unexpected error in TypeMap::stringValue";
}
#undef STRINGVAL

void TypeMap::dump(::ccafeopq::TypeMap_shared t)
{
	StringVector keys = t->getAllKeys( ::ccafeopq::NoType );
	std::sort(keys.begin(), keys.end());
	for (size_t i = 0; i < keys.size(); i++) {
		::std::cout << "["<< keys[i] << "](" <<
		       	TypeMap::stringType(t,keys[i]) << ") " <<
			TypeMap::stringValue(t,keys[i]) << std::endl;
	}
}
//---------------------------------------------------------- 
}; // end namespace util 
}; // end namespace sandia
}; // end namespace gov

#ifdef UTIL_TYPEMAP_MAIN
int main() { 

	gov::sandia::util::TypeMap tm;
	gov::sandia::util::TypeMapImpl t;
	::std::string s("fred");
	::std::string s2("barney");
	t.putScalar(s,3);
	t.putScalar(s2,4.0);
	t.putScalar(s2,5.0);
	try {
		t.putScalar(s,5.0);
	}
	catch ( ::ccafeopq::Exception &e)
	{
		::std::cout << "Expected " << e.what() << ::std::endl;
	}
	catch ( ::std::exception &e)
	{
		::std::cout << "Unexpected " << e.what() << ::std::endl;
	}
		
	int n1 = 4;
	int n2 = 4;
	tm.putInt("n1",1);
	tm.putInt("n2",2);
	n1 = tm.getInt("n1",3);
	n2 = tm.getInt("n2",3);
	::std::cout << "n1= " << n1 << " n2= "<< n2 << ::std::endl;

	tm.putString("x","yval");

	float  d1o, d1 =3.14159;
	double  d2o, d2 = 3.14159257;

	tm.putFloat("d1",d1);
	tm.putDouble("d2",d2);
	d1o = tm.getFloat("d1",3);
	d2o = tm.getDouble("d2",3);
	::std::cout << "d1= " << d1 << " d2= "<< d2*2 << ::std::endl;
	
	double x[10] = {10,9,8,7,6,5,4,3,2,1};
	// double xdef[10] = {2,2,2,2,2,2,2,2,2,2};
	::std::vector< double > dv(10,11);
	::std::vector< double > ddef(10,3);
	
	tm.putDoubleArray("da1",x,10);
	dv = tm.getDoubleArray("da1", ddef);
	::std::cout << "da1: ";
	for (int i = 0; i < 10; i++) {
		::std::cout << " " <<  dv[i] ;
	}
	::std::cout << ::std::endl;

	tm.putDoubleArray("da2",ddef);
	::std::vector < int > ixo(3,-1);
	try {
		::std::vector < int > ix = tm.getIntArray("da2",ixo);
	}
	catch ( ::ccafeopq::Exception &e)
	{
		::std::cout << "Expected " << e.what() << ::std::endl;
	}
	::std::cout << "dumping map" << ::std::endl;

	::ccafeopq::TypeMap_Interface * ctm =new ::gov::sandia::util::TypeMap();
	::ccafeopq::TypeMap_shared otm(ctm);
	ctm->putInt("n1",1);
	ctm->putInt("n2",2);
	ctm->putString("x","yval");
	ctm->putFloat("d1",d1);
	ctm->putDouble("d2",d2);
	ctm->putDoubleArray("da1",x,10);
	::gov::sandia::util::TypeMap::dump(otm);

	return 0;
}

#endif // UTIL_TYPEMAP_MAIN
