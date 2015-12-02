#include <gov_cca.hh>
#include <gov_cca_ports.hh>
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include "dc/babel/ccafe-bind/BabelOpaquePort.hh"
//#include "dc/babel/babel-cca/server/ccaffeine_ports_ServiceProvider.hh"
#include "dc/babel/ccafe-bind/BabelOpaqueServiceProvider.hh"


BabelOpaqueServiceProvider::BabelOpaqueServiceProvider( gov::cca::ports::ServiceProvider nsp, ccafeopq::ComponentID_shared c )
{
	sp = nsp;
	cid = c;
	initBabel();
}

ccafeopq::ComponentID_shared 
BabelOpaqueServiceProvider::getProviderID()
{
	return cid;
}

gov::cca::Port
BabelOpaqueServiceProvider::getBabelPort()
{
	return sp;
}

BabelOpaqueServiceProvider::~BabelOpaqueServiceProvider()
{
	// sp = 0; unneeded
}

ccafeopq::ServiceProvider_shared
BabelOpaqueServiceProvider::createWrap(gov::cca::ports::ServiceProvider nsp, ccafeopq::ComponentID_shared c)
{
	BabelOpaqueServiceProvider *nosp = new BabelOpaqueServiceProvider(nsp, c);
	ccafeopq::ServiceProvider * osp = nosp;
	ccafeopq::ServiceProvider_shared x(osp);
	return x;
}


const std::string 
BabelOpaqueServiceProvider::createService(const std::string & portType)
{
	std::string pname = sp.createService(portType);
	return pname;
}

void 
BabelOpaqueServiceProvider::destroyService(const std::string & portName)
{
	return sp.destroyService(portName);
}

