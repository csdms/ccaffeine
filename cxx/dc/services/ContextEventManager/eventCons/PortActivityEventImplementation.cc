#include "dc/export/AllExport.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#define NS ccafeopq::event::PortActivityEventImplementation

NS::PortActivityEventImplementation( enum ccafeopq::event::type::ContextEventType portActivityEventType, ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum, ccafeopq::ConnectionID_shared  conn, const std::string & pName, const std::string & pType, ccafeopq::ComponentID_shared userid)
: ContextEventImplementation(portActivityEventType,cid,sKey,seqNum)
{
	connID = conn; // if conn null, pname, ptype must not be.
	user = userid;
	userPortType = pType;
	userPortName = pName;
}


NS::~PortActivityEventImplementation()
{
// dummy constructor for unit test
}

NS::PortActivityEventImplementation()
{
// dummy constructor for unit test
}

ccafeopq::ConnectionID_shared 
NS::getConnection() 
{
	return connID;
}

ccafeopq::ComponentID_shared 
NS::getComponent()
{
	return user;
}

const std::string 
NS::getPortName()
{
	return userPortName;
}

/** @return type of port being affected. */
const std::string 
NS::getPortType()
{
	return userPortType;
}


