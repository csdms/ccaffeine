#include "dc/export/ccafeopq.hh"
#include "dc/export/ccafeopq_support.hh"
#include "dc/framework/KernelPort.h"
#include "dc/services/registry/OpqServiceRegistry.hh"
#include "util/IO.h"

OpqServiceRegistry::OpqServiceRegistry()
{
  initKernel();
}

OpqServiceRegistry::~OpqServiceRegistry()
{
}

void 
OpqServiceRegistry::startup(ccafeopq::Services *wall1)
{
	wall = wall1;
}

void 
OpqServiceRegistry::shutdown()
{
	// FIXME -remove singletons
	wall = 0;
}

bool 
OpqServiceRegistry::serverAvailable(const std::string & type, std::string &serverName, std::string & serverPort)
{
	ccafeopq::ComponentID_shared cid;
	std::map< std::string, ccafeopq::Port *>::const_iterator si;
	si = singletons.find(type);
	if (si != singletons.end()) {
		cid = wall->getComponentID();
		serverName = cid->getInstanceName();
		serverPort = singletonNames[type];
		return true;
	}
	std::map< std::string, ccafeopq::ServiceProvider_shared >::const_iterator sj;
	sj = servers.find(type);
	if (sj != servers.end()) {
		ccafeopq::ServiceProvider_shared x = servers[type];
		cid = x->getProviderID();
		serverName = cid->getInstanceName();
		serverPort = x->createService(type);
		return true;
	}
	return false;
}

bool 
OpqServiceRegistry::addService(const std::string & type, ccafeopq::ServiceProvider_shared portProvider)
{
	std::map< std::string, ccafeopq::ServiceProvider_shared >::const_iterator si;
	si = servers.find(type);
	if (si != servers.end()) {
		return false;
	}
	std::map< std::string, ccafeopq::Port *>::const_iterator si2;
	si2 = singletons.find(type);
	if (si2 != singletons.end()) {
		return false;
	}
	servers[type] = portProvider;
	return true;
}

bool 
OpqServiceRegistry::addSingletonService(const std::string & type, ccafeopq::Port * service)
{
	std::map< std::string, ccafeopq::Port *>::const_iterator si;
	si = singletons.find(type);
	if (si != singletons.end()) {
		return false;
	}
	std::map< std::string, ccafeopq::ServiceProvider_shared >::const_iterator si2;
	si2 = servers.find(type);
	if (si2 != servers.end()) {
		return false;
	}
	singletons[type] = service;
	std::string wallPortName = wall->genUniquePortName(type);
	singletonNames[type] = wallPortName;
	ccafeopq::TypeMap_shared dummy;
	wall->addProvidesPort(service, wallPortName, type, dummy);
	return true;
}

void 
OpqServiceRegistry::removeService(const std::string & serviceType)
{
	std::map< std::string, ccafeopq::Port *>::const_iterator si;
	si = singletons.find(serviceType);
	if (si != singletons.end()) {
		// si->first == serviceType
		std::string wallPortName = singletonNames[serviceType];
		singletons.erase(serviceType);
		wall->removeProvidesPort(wallPortName);
		singletonNames.erase(serviceType);
		return;
	}
	
	std::map< std::string, ccafeopq::ServiceProvider_shared >::const_iterator sj;
	sj = servers.find(serviceType);
	if (sj != servers.end()) {
		servers.erase(serviceType);
		return;
	}
	IO_en2("OpqServiceRegistry::removeService called with unknown type: %s",
		serviceType.c_str());
}
