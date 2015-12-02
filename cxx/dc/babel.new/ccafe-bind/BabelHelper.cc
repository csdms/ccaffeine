//#include <boost/shared_ptr.hpp>
#include <AllCCA.hh>
#include "dc/export/AllExport.hh"
#include "BabelHelper.hh"

#define REFIX(x) case ::ccafeopq::x: return ::gov::cca::CCAExceptionType_##x
gov::cca::CCAExceptionType BabelHelper::babelExceptionType( ::ccafeopq::ExceptionType ot)
{
	switch ( ot) {
	REFIX(Unexpected);
	REFIX(Nonstandard);
	REFIX(PortNotDefined);
	REFIX(PortAlreadyDefined);
	REFIX(PortNotConnected);
	REFIX(PortNotInUse);
	REFIX(UsesPortNotReleased);
	REFIX(BadPortName);
	REFIX(BadPortType );
	REFIX(BadProperties);
	REFIX(BadPortInfo);
	REFIX(OutOfMemory);
	REFIX(NetworkError);
	default:
	return gov::cca::CCAExceptionType_Unexpected;
	}

}

#undef REFIX
#define REFIX(x) case ::gov::cca::CCAExceptionType_##x: return ::ccafeopq::x
::ccafeopq::ExceptionType BabelHelper::opaqueExceptionType( gov::cca::CCAExceptionType bt)
{
	switch ( bt) {
	REFIX(Unexpected);
	REFIX(Nonstandard);
	REFIX(PortNotDefined);
	REFIX(PortAlreadyDefined);
	REFIX(PortNotConnected);
	REFIX(PortNotInUse);
	REFIX(UsesPortNotReleased);
	REFIX(BadPortName);
	REFIX(BadPortType );
	REFIX(BadProperties);
	REFIX(BadPortInfo);
	REFIX(OutOfMemory);
	REFIX(NetworkError);
	default:
	return ::ccafeopq::Unexpected;
	}

}

#undef REFIX
#define REFIX(x) case ::ccafeopq::x: return ::gov::cca::Type_##x
::gov::cca::Type BabelHelper::babelType( ::ccafeopq::Type ot)
{
	switch (ot) {
	REFIX(NoType);
	REFIX(Int);
	REFIX(Long);
	REFIX(Float);
	REFIX(Double);
	REFIX(Dcomplex);
	REFIX(Fcomplex);
	REFIX(Bool);
	REFIX(String);
	REFIX(IntArray);
	REFIX(LongArray);
	REFIX(FloatArray);
	REFIX(DoubleArray);
	REFIX(DcomplexArray);
	REFIX(FcomplexArray);
	REFIX(BoolArray);
	REFIX(StringArray);
	default: return ::gov::cca::Type_NoType;
	}
}
#undef REFIX
#define REFIX(x) case ::gov::cca::Type_##x: return ::ccafeopq::x
::ccafeopq::Type BabelHelper::opaqueType( ::gov::cca::Type bt)
{
	switch (bt) {
	REFIX(NoType);
	REFIX(Int);
	REFIX(Long);
	REFIX(Float);
	REFIX(Double);
	REFIX(Dcomplex);
	REFIX(Fcomplex);
	REFIX(Bool);
	REFIX(String);
	REFIX(IntArray);
	REFIX(LongArray);
	REFIX(FloatArray);
	REFIX(DoubleArray);
	REFIX(DcomplexArray);
	REFIX(FcomplexArray);
	REFIX(BoolArray);
	REFIX(StringArray);
	default: return ::ccafeopq::NoType;
	}
}

namespace {

template <class Scalar >
sidl::array< Scalar > convertToSidlArray( ::std::vector< Scalar > & val )
{
	size_t len = val.size();
	sidl::array< Scalar > myarray = sidl::array< Scalar >::create1d( len );
	size_t i=0;
	for( ; i < len ; i++) {
    /* 074 and later array api */
		myarray.set( i , val[i] );
	}
	return myarray;
}

}

sidl::array< ::std::string > 
BabelHelper::stringVectorToSidlArray( ::std::vector< ::std::string > & val)
{
        return convertToSidlArray( val );
}

sidl::array< bool > 
BabelHelper::boolVectorToSidlArray( ::std::vector< bool > & val)
{
        return convertToSidlArray( val );
}

sidl::array< int32_t > 
BabelHelper::intVectorToSidlArray( ::std::vector< int32_t > & val)
{
        return convertToSidlArray( val );
}

sidl::array< int64_t > 
BabelHelper::longVectorToSidlArray( ::std::vector< int64_t > & val)
{
        return convertToSidlArray( val );
}

sidl::array< float > 
BabelHelper::floatVectorToSidlArray( ::std::vector< float > & val)
{
        return convertToSidlArray( val );
}

sidl::array< double > 
BabelHelper::doubleVectorToSidlArray( ::std::vector< double > & val)
{
        return convertToSidlArray( val );
}

sidl::array< std::complex< double > >
BabelHelper::dcomplexVectorToSidlArray( ::std::vector< std::complex< double > > & val)
{
        return convertToSidlArray( val );
}

sidl::array< std::complex< float > >
BabelHelper::fcomplexVectorToSidlArray( ::std::vector< std::complex< float> > & val)
{
        return convertToSidlArray( val );
}

