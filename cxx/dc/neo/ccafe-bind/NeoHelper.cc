//#include <boost/shared_ptr.hpp>
#include <neocca.hh>
#include "dc/export/AllExport.hh"
#include "NeoHelper.hh"

#define REFIX(x) case ::ccafeopq::x: return ::neo::cca::x
neo::cca::ExceptionType NeoHelper::neoExceptionType( ::ccafeopq::ExceptionType ot)
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
	return neo::cca::Unexpected;
	}

}

#undef REFIX
#define REFIX(x) case ::neo::cca::x: return ::ccafeopq::x
::ccafeopq::ExceptionType NeoHelper::opaqueExceptionType( neo::cca::ExceptionType bt)
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
#define REFIX(x) case ::ccafeopq::x: return ::neo::cca::x
::neo::cca::Type NeoHelper::neoType( ::ccafeopq::Type ot)
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
	default: return ::neo::cca::NoType;
	}
}
#undef REFIX
#define REFIX(x) case ::neo::cca::x: return ::ccafeopq::x
::ccafeopq::Type NeoHelper::opaqueType( ::neo::cca::Type bt)
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

