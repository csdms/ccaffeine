#include "dc/export/AllExport.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#define NS ccafeopq::event::PortDefinitionEventImplementation

NS::PortDefinitionEventImplementation(enum ccafeopq::event::type::ContextEventType cet, const std::string & name, const std::string & type, ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum, ccafeopq::ComponentID_shared  portSource, ccafeopq::TypeMap_shared portProps)
: ContextEventImplementation(cet,cid,sKey,seqNum)
{
	portCID = portSource;
	prop = portProps;
	pName = name;
	pType = type;
	if (prop != 0)
	{
		pName = prop->getString(ccafeopq::Keys::CCA_PORTNAME, pName);
		pType = prop->getString(ccafeopq::Keys::CCA_PORTTYPE, pType);
	}
	std::string cname = "(null ccafeopq::ComponentID_shared)";
	if (portSource != 0) // fixme: we shouldn't check this.
	{
		cname = portSource->getInstanceName();
	}
	cname += "."; cname += pName;
	setContextEventDescription(cname);
}

NS::~PortDefinitionEventImplementation()
{
// dummy constructor for unit test
}

NS::PortDefinitionEventImplementation()
{
// dummy constructor for unit test
}

ccafeopq::ComponentID_shared 
NS::getComponent()
{
	return portCID;
}

ccafeopq::TypeMap_shared
NS::getPortProperties()
{
	return prop;
}

const std::string 
NS::getPortName()
{
	return pName;
}

const std::string 
NS::getPortType()
{
	return pType;
}
