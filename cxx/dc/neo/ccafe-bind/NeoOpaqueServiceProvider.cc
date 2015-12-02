#include <neocca.hh>
#include <neoports.hh>
#include "dc/export/ccafeopq.hh"
#include "dc/export/ccafeopq_support.hh"
#include "dc/neo/ccafe-bind/NeoOpaquePort.hh"
#include "dc/neo/ccafe-bind/NeoOpaqueServiceProvider.hh"
NeoOpaqueServiceProvider::NeoOpaqueServiceProvider( neo::cca::ports::ServiceProvider * nsp, ccafeopq::ComponentID_shared c )
{
	sp = nsp;
	cid = c;
	initNeo();
}

ccafeopq::ComponentID_shared NeoOpaqueServiceProvider::getProviderID()
{
	return cid;
}

neo::cca::Port *
NeoOpaqueServiceProvider::getNeoPort()
{
	return sp;
}

NeoOpaqueServiceProvider::~NeoOpaqueServiceProvider()
{
	sp = 0;
}

ccafeopq::ServiceProvider_shared
NeoOpaqueServiceProvider::createWrap(neo::cca::ports::ServiceProvider * nsp, ccafeopq::ComponentID_shared c)
{
	NeoOpaqueServiceProvider *nosp = new NeoOpaqueServiceProvider(nsp, c);
	ccafeopq::ServiceProvider * osp = nosp;
	ccafeopq::ServiceProvider_shared x(osp);
	return x;
}


const std::string 
NeoOpaqueServiceProvider::createService(const std::string & portType)
{
	std::string pname = sp->createService(portType);
	return pname;
}

void 
NeoOpaqueServiceProvider::destroyService(const std::string & portName)
{
	return sp->destroyService(portName);
}

