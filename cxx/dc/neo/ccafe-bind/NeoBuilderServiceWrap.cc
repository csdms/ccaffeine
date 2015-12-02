#include <neocca.hh>
#include <neoports.hh>
#include <dc/export/AllExport.hh>

#include "dc/neo/ccafe-bind/ccafeTypeMap.hh"
#include "dc/neo/ccafe-bind/NeoOpaqueTypeMap.hh"
#include "dc/neo/ccafe-bind/NeoPortConverter.hh"
#include "dc/neo/ccafe-bind/NeoServicesHelper.hh"
#include "dc/neo/ccafe-bind/NeoBuilderServiceWrap.hh"
#include "dc/neo/ccafe-bind/NeoComponentID.hh"
#include "dc/neo/ccafe-bind/NeoConnectionID.hh"
#include "dc/neo/ccafe-bind/NeoHelper.hh"

int NeoBuilderServiceWrap::genSerial = 0;

NeoBuilderServiceWrap::NeoBuilderServiceWrap( ccafeopq::BuilderService *obpp )
{
	cbs = obpp;
#ifdef CCAFE_AUDIT
	serial = nextNum();
	IO_dn2("NeoBuilderServiceWrap CTOR %d", serial);
#endif
}
NeoBuilderServiceWrap::NeoBuilderServiceWrap( int bogon)
{
	cbs = 0;
	serial = 0;
}

NeoBuilderServiceWrap::~NeoBuilderServiceWrap()
{
#ifdef CCAFE_AUDIT
	serial = -serial;
	IO_dn2("NeoBuilderServiceWrap DTOR %d", serial);
#endif
	cbs = 0;
}


void 
NeoBuilderServiceWrap::checkthrow(const char *funcName)
{
	NeoServicesHelper::checkthrow("NeoBuilderServiceWrap", "cbs", 
			static_cast<void *>(cbs), funcName);
}

#include "dc/neo/ccafe-bind/NeoMacros.hh"
#define RETHROW(s) NEO_RETHROW_PREPEND(s)

/** 
 * Creates an instance of a CCA component of the type defined by the
 * string className.
 * Memory lifecycle:
 * The ComponentID_shared can be dropped on the floor if desired;
 * that won't cause the component instance to stop existing.
 */
neo::cca::ComponentID_shared 
NeoBuilderServiceWrap::createInstance(const ::std::string & instanceName, const ::std::string & className, ::neo::cca::TypeMap_shared properties) 
throw ( ::neo::cca::Exception )
{
	checkthrow("createInstance");

	N2OMAP(properties, ctm);
	try {
		::ccafeopq::ComponentID_shared oid =
			cbs->createInstance(instanceName, className, ctm);
		::neo::cca::ComponentID_shared nid =
			NeoComponentID::neoWrap(oid);
		return nid;
	}
	RETHROW("NeoBuilderServiceWrap::createInstance: ");
	neo::cca::ComponentID_shared x; return x; // NOTREACHED
}

/** Convenience function, for those with no interesting properties to
 * put in. */
neo::cca::ComponentID_shared 
NeoBuilderServiceWrap::createInstance(const ::std::string & instanceName, const ::std::string & className) 
throw ( ::neo::cca::Exception ) 
{
	neo::cca::TypeMap_shared ntm;
	return createInstance(instanceName, className, ntm);
}

/** Get component list.
 * Memory lifecycle:
 * The vector is returned on the stack and when it goes out of scope,
 * all the ComponentID_shared take care of themselves.
 * @return a ComponentID for each component currently created.
 */
::std::vector< neo::cca::ComponentID_shared > 
NeoBuilderServiceWrap::getComponentIDs() 
throw ( ::neo::cca::Exception )
{
	checkthrow("getComponentIDs");
	try {
		std::vector< ::ccafeopq::ComponentID_shared > cids = cbs->getComponentIDs();
		std::vector< neo::cca::ComponentID_shared > res;
		res = NeoComponentID::convertToVector(cids);
		return res;
	}
	RETHROW("NeoBuilderServiceWrap::getComponentIDs: ");
	::std::vector< neo::cca::ComponentID_shared >  x; return x; // NOTREACHED



}

/** 
 * Get property map for component.
 * Memory Lifecycle:
 * The info is returned on the stack and takes care of itself
 * per shared_ptr.
 *  @return the public properties associated with the component 
 *  referred to by ComponentID.
 *  @throws a Exception if the ComponentID is invalid.
*/
::neo::cca::TypeMap_shared 
NeoBuilderServiceWrap::getComponentProperties( neo::cca::ComponentID_shared nid) 
throw ( ::neo::cca::Exception )
{

	checkthrow("getComponentProperties");
	try {
		::ccafeopq::ComponentID_shared oid = findOID(nid);
		::ccafeopq::TypeMap_shared otm;
		otm = cbs->getComponentProperties(oid);
		neo::cca::TypeMap_shared ntm;
		ntm = ccafe::TypeMap::neoWrap(otm);
		return ntm;
	}
	RETHROW("NeoBuilderServiceWrap::getComponentProperties: ");
	neo::cca::TypeMap_shared xtm; return xtm; // notreached
}

/**
 *  Causes the framework implementation to associate the given properties
 *  with the component designated by nid.
 *  @throws Exception if nid is invalid or if there is an attempted
 *  change to a property locked by the framework implementation.
 */
void 
NeoBuilderServiceWrap::setComponentProperties( neo::cca::ComponentID_shared nid, ::neo::cca::TypeMap_shared map)
throw ( ::neo::cca::Exception )
{
	checkthrow("setComponentProperties");
	try {
		ccafeopq::ComponentID_shared oid = findOID(nid);
		N2OMAP(map, otm);
		cbs->setComponentProperties(oid, otm);
	}
	RETHROW("NeoBuilderServiceWrap::setComponentProperties: ");
}

/** 
 * Get component id from stringified reference.
 * Memory Lifecycle:
 * The id is returned on the stack and takes care of itself
 * per shared_ptr.
 * @return a ComponentID from the string produced by
 * ComponentID.getSerialization().
 * @throws Exception if the string does not represent the appropriate
 * serialization of a ComponentID for the underlying framework.
*/
neo::cca::ComponentID_shared 
NeoBuilderServiceWrap::getDeserialization( const ::std::string & s)
throw ( ::neo::cca::Exception )
{
	checkthrow("getDeserialization");
	try {
		::ccafeopq::ComponentID_shared oid = cbs->getDeserialization(s);
		::neo::cca::ComponentID_shared nid = NeoComponentID::neoWrap(oid);
		return nid;
	}
	RETHROW("NeoBuilderServiceWrap::getDeserialization: ");
	neo::cca::ComponentID_shared x; return x; // NOTREACHED
}

/**
 *  Get id from name by which it was created.
 * Memory Lifecycle:
 * The id is returned on the stack and takes care of itself per shared_ptr.
 * @return a ComponentID from the instance name of the component
 * produced by ComponentID.getInstanceName().
 * @throws Exception if there is no component matching the
 * given componentInstanceName.
*/
neo::cca::ComponentID_shared 
NeoBuilderServiceWrap::getComponentID( const ::std::string & componentInstanceName)
throw ( ::neo::cca::Exception )
{
	checkthrow("getComponentID");

	try {
		ccafeopq::ComponentID_shared oid =
			cbs->getComponentID(componentInstanceName);
		neo::cca::ComponentID_shared nid =
			NeoComponentID::neoWrap(oid);
		return nid;
	}
	RETHROW("NeoBuilderServiceWrap::getComponentID: ");
	neo::cca::ComponentID_shared x; return x; // NOTREACHED
	      
}

 /** 
  *  Eliminate the Component instance, from the scope of the framework.
  *  Memory lifecycle:
  *  On return, toDie will still be a valid pointer, but queries
  *  on it should throw exceptions because the component has been 
  *  destroyed.
  *  @param toDie the component to be removed.
  *  @param timeout the allowable wait; 0 means up to the framework.
  *  @throws Exception if toDie refers to an invalid component, or
  *  if the operation takes longer than timeout seconds.
  */
void 
NeoBuilderServiceWrap::destroyInstance( neo::cca::ComponentID_shared toDie, float timeout )
throw ( ::neo::cca::Exception )
{
	checkthrow("destroyInstance");
	try {
		::ccafeopq::ComponentID_shared oid = findOID(toDie);
		cbs->destroyInstance(oid, timeout);
	}
	RETHROW("NeoBuilderServiceWrap::destroyInstance: ");

}

 /** 
  *  Get the names of Port instances provided by the identified component.
  * Memory lifecycle:
  * The vector is returned on the stack and when it goes out of scope,
  * all the string take care of themselves.
  *  @param cid the component.
  *  @throws Exception if cid refers to an invalid component.
  */
::std::vector< ::std::string > 
NeoBuilderServiceWrap::getProvidedPortNames( neo::cca::ComponentID_shared cid)
throw ( ::neo::cca::Exception ) 
{
	checkthrow("getProvidedPortNames");
	try {
		::ccafeopq::ComponentID_shared oid = findOID(cid);
		::std::vector< ::std::string > names =
			cbs->getProvidedPortNames(oid);
		return names;
	}
	RETHROW("NeoBuilderServiceWrap::getProvidedPortNames: ");
	::std::vector< ::std::string > x; return x; //notreached

}

 /** 
  *  Get the names of Port instances used by the identified component.
  * Memory lifecycle:
  * The vector is returned on the stack and when it goes out of scope,
  * all the string take care of themselves.
  *  @param cid the component.
  *  @throws Exception if cid refers to an invalid component.
  */
::std::vector< ::std::string > 
NeoBuilderServiceWrap::getUsedPortNames( neo::cca::ComponentID_shared cid)
throw ( ::neo::cca::Exception ) 
{
	checkthrow("getUsedPortNames");
	try {
		::ccafeopq::ComponentID_shared oid = findOID(cid);
		::std::vector< ::std::string > names =
			cbs->getUsedPortNames(oid);
		return names;
	}
	RETHROW("NeoBuilderServiceWrap::getUsedPortNames: ");
	::std::vector< ::std::string > x; return x; //notreached

}

/**
 *  Fetch map of Port properties exposed by the framework.
 *  @return the public properties pertaining to the Port instance
 *    portname on the component referred to by cid.
 *  @throws Exception when any one of the following conditions occur:<ul>
 *    <li>portname is not a registered Port on the component indicated by cid,
 *    <li>cid refers to an invalid component. </ul>
 */
::neo::cca::TypeMap_shared 
NeoBuilderServiceWrap::getPortProperties( neo::cca::ComponentID_shared cid, const ::std::string & portName)
throw ( ::neo::cca::Exception )
{
	checkthrow("getPortProperties");
	try {
		::ccafeopq::ComponentID_shared oid = findOID(cid);
		::ccafeopq::TypeMap_shared otm = cbs->getPortProperties(oid,portName);
		neo::cca::TypeMap_shared btm;
		btm = ccafe::TypeMap::neoWrap(otm);
		return btm;
	}
	RETHROW("NeoBuilderServiceWrap::getPortProperties: ");
	neo::cca::TypeMap_shared xtm; return xtm; // notreached

}

/**
 * Associates the properties given in map with the Port indicated by
 *  portname. The component must have a Port known by portname.
 *  @throws Exception if either cid or portname are
 *  invalid, or if this a changed property is locked by
 *   the underlying framework or component.
*/
void 
NeoBuilderServiceWrap::setPortProperties( neo::cca::ComponentID_shared cid, const ::std::string & portName, ::neo::cca::TypeMap_shared map)
throw ( ::neo::cca::Exception )
{
	checkthrow("setPortProperties");
	try {
		::ccafeopq::ComponentID_shared oid = findOID(cid);
		N2OMAP(map,otm);
		cbs->setPortProperties(oid, portName, otm);
	}
	RETHROW("NeoBuilderServiceWrap::setPortProperties: ");
}

/**
 *   Creates a connection between ports on component user and
 *   component provider. 
 *   Destroying the ConnectionID does not
 *   cause a disconnection; for that, see disconnect().
 *   In anycase, the ConnectionID_shared destroys itself-- that is not
 *   the user's concern.
 *   @param user the caller component.
 *   @param provider the callee component.
 *   @param usingPortName name of the port in the caller.
 *   @param providingPortName name of the port in the callee.
 *   
 *   @throws Exception when any one of the following conditions occur:<ul>
 *   <li>If either user or provider refer to an invalid component,
 *   <li>If either usingPortName or providingPortName refer to a
 *   nonexistent Port on their respective component,
 *   <li>If other-- In reality there are a lot of things that can go wrong
 *   with this operation, especially if the underlying connections
 *   involve networking.</ul>
 */
neo::cca::ConnectionID_shared 
NeoBuilderServiceWrap::connect( neo::cca::ComponentID_shared  user, const ::std::string & usingPortName, neo::cca::ComponentID_shared provider, const ::std::string & providingPortName)
throw ( ::neo::cca::Exception ) 
{
	checkthrow("connect");
	try {
		IO_dn1("entry");
		::ccafeopq::ComponentID_shared uoid = findOID(user);
		::ccafeopq::ComponentID_shared poid = findOID(provider);
		IO_dn1("done with component id");

		::ccafeopq::ConnectionID_shared oconn =
			cbs->connect(uoid, usingPortName, poid, providingPortName);
		IO_dn1("Done with connect");

		neo::cca::ConnectionID_shared nconn;
		nconn = NeoConnectionID::neoWrap(oconn);

		IO_dn1("Done with wrap");
		return nconn;
	}
	RETHROW("NeoBuilderServiceWrap::connect: ");
	neo::cca::ConnectionID_shared x; return x; //notreached
}

/**
* Returns a list of connections as an array of
* handles. This will return all connections involving components
* in the given componentList of ComponentIDs. This
* means that ConnectionID's will be returned even if only one
* of the participants in the connection appears in componentList.
* Memory lifecycle:
* The vector returned and ids therein clean themselves up
* when leaving the calling scope.
*
* @throws Exception if any component in componentList is invalid.
*/
::std::vector < neo::cca::ConnectionID_shared > 
NeoBuilderServiceWrap::getConnectionIDs( ::std::vector< neo::cca::ComponentID_shared > & nList)
throw ( ::neo::cca::Exception ) 
{
	checkthrow("getConnectionIDs");
	try {
		// repackage input
		::std::vector< ::ccafeopq::ComponentID_shared > clist;
		for (size_t i = 0, len = nList.size(); i < len; i++)
		{
			::ccafeopq::ComponentID_shared oid = findOID(nList[i]);
			clist.push_back(oid);
		}
		// repackage output
		::std::vector< ::ccafeopq::ConnectionID_shared > conns;
		conns = cbs->getConnectionIDs(clist);
		::std::vector< ::neo::cca::ConnectionID_shared > nconns;
		nconns = NeoConnectionID::convertToVector(conns);
		return nconns;
	}
	RETHROW("NeoBuilderServiceWrap::getConnectionIDs: ");
	::std::vector < neo::cca::ConnectionID_shared > x; return x; // notreached
}

/**
 *   Fetch property map of a connection.
 *   Memory lifecycle: the map will delete itself when appropriate.
 *   @returns the properties for the given connection.
 *   @throws Exception if connID is invalid.
*/
::neo::cca::TypeMap_shared 
NeoBuilderServiceWrap::getConnectionProperties( neo::cca::ConnectionID_shared & connID)
throw ( ::neo::cca::Exception )
{
	checkthrow("getConnectionProperties");
	try {
		::ccafeopq::ConnectionID_shared ocid = findOConnID(connID);
		::ccafeopq::TypeMap_shared otm =
			cbs->getConnectionProperties(ocid);
		neo::cca::TypeMap_shared ntm;
		ntm = ccafe::TypeMap::neoWrap(otm);
		return ntm;
	}
	RETHROW("NeoBuilderServiceWrap::getConnectionProperties: ");
	neo::cca::TypeMap_shared xtm; return xtm; // notreached
}

/**
 * Associates the properties with the connection.
 * @param map the source of the properties.
 *   @param connID connection to receive property values.
 *   @throws Exception if connID is invalid, or if this changes
 *   a property locked by the underlying framework.
 */
void 
NeoBuilderServiceWrap::setConnectionProperties( neo::cca::ConnectionID_shared & connID, ::neo::cca::TypeMap_shared map)
throw ( ::neo::cca::Exception )
{
	checkthrow("setConnectionProperties");
	try {
		::ccafeopq::ConnectionID_shared ocid = findOConnID(connID);
		N2OMAP(map,ctm);
		cbs->setConnectionProperties(ocid,ctm);
	}
	RETHROW("NeoBuilderServiceWrap::setConnectionProperties: ");
}

/** 
 * Disconnect the connection indicated by connID before the indicated
 * timeout in secs. Upon successful completion, connID and the connection
 * it represents become invalid.
 * @param timeout the time in seconds to wait for a connection to close; 0
 * means to use the framework implementation default.
 * @param connID the one to break.
 * @throws Exception when any one of the following conditions occur: <ul>
 * <li>id refers to an invalid ConnectionID,
 * <li>timeout is exceeded, after which, if id was valid before
 * disconnect() was invoked, it remains valid
 * </ul>
 */
void 
NeoBuilderServiceWrap::disconnect( neo::cca::ConnectionID_shared & connID, float timeout)
throw ( ::neo::cca::Exception ) 
{
	checkthrow("disconnect");
	try {
		::ccafeopq::ConnectionID_shared ocid = findOConnID(connID);
		cbs->disconnect(ocid, timeout);
	}
	RETHROW("NeoBuilderServiceWrap::disconnect: ");

}

/**
 * Remove all connections between components id1 and id2 within
 * the period of timeout secs. If id2 is null, then all connections
 * to id1 are removed (within the period of timeout secs).
 * @throws Exception when any one of the following conditions occur:<ul>
 *  <li>id1 or id2 refer to an invalid ComponentID (other than id2 == null),
 *  <li>The timeout period is exceeded before the disconnections can be made.
 *  </ul>
 */
void 
NeoBuilderServiceWrap::disconnectAll( neo::cca::ComponentID_shared & id1, neo::cca::ComponentID_shared & id2, float timeout)
throw ( ::neo::cca::Exception ) 
{
	checkthrow("disconnectAll");
	try {
		::ccafeopq::ComponentID_shared uoid = findOID(id1);
		::ccafeopq::ComponentID_shared poid = findOID(id2);
		cbs->disconnectAll(uoid, poid, timeout);
	}
	RETHROW("NeoBuilderServiceWrap::disconnectAll: ");
}

ccafeopq::ComponentID_shared 
NeoBuilderServiceWrap::findOID( neo::cca::ComponentID_shared nid)
{
	std::string cname = nid->getInstanceName();
	ccafeopq::ComponentID_shared oid;
	oid = cbs->getComponentID(cname);
	return oid;
}


::ccafeopq::ConnectionID_shared
NeoBuilderServiceWrap::findOConnID( neo::cca::ConnectionID_shared bconn)
{
	std::vector< ::ccafeopq::ConnectionID_shared > matches = findOConnIDs(bconn);
	if ( matches.size() != 1 )
	{
		::ccafeopq::ConnectionID_shared nilconn;
		return nilconn;
	} else {
		return matches[0];
	}
}

std::vector< ::ccafeopq::ConnectionID_shared > 
NeoBuilderServiceWrap::findOConnIDs( neo::cca::ConnectionID_shared bconn)
{
	std::vector< ::ccafeopq::ConnectionID_shared > matches;
	if (bconn == 0) {
		return matches;
	}

	neo::cca::ComponentID_shared uid = bconn->getUser();
	neo::cca::ComponentID_shared pid = bconn->getProvider();

	std::string uname = uid->getInstanceName();
	std::string pname = pid->getInstanceName();
	std::string uport = bconn->getUserPortName();
	std::string pport = bconn->getProviderPortName();

	matches = cbs->getConnectionIDs(uname, uport, pname, pport);
	return matches;
}

NeoBuilderServiceWrap NeoBuilderServiceWrap_test(1);
