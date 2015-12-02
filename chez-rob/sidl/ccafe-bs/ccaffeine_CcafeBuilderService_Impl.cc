// 
// File:          ccaffeine_CcafeBuilderService_Impl.cc
// Symbol:        ccaffeine.CcafeBuilderService-v0.0.0
// Symbol Type:   class
// Babel Version: 0.6.2
// SIDL Created:  20020510 17:32:10 PDT
// Generated:     20020510 17:32:21 PDT
// Description:   Server-side implementation for ccaffeine.CcafeBuilderService
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_CcafeBuilderService_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService._includes)
// Put additional includes or other arbitrary code here...
// DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService._includes)

// user defined constructor
void ccaffeine::CcafeBuilderService_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService._ctor)
  
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService._ctor)
}

// user defined destructor
void ccaffeine::CcafeBuilderService_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
// referred to by:
//    gov.cca.ComponentID
//    gov.cca.CCAException
//    gov.cca.ConnectionID

/**
 * Creates a connection between ports on component user and 
 * component provider. Destroying the ConnectionID does not
 * cause a disconnection; for that, see disconnect().
 * @throws CCAException when any one of the following conditions occur:<ul>
 * <li>If either user or provider refer to an invalid component,
 * <li>If either usingPortName or providingPortName refer to a 
 * nonexistent Port on their respective component,
 * <li>If other-- In reality there are a lot of things that can go wrong 
 * with this operation, especially if the underlying connections 
 * involve networking.</ul>
 */
gov::cca::ConnectionID
ccaffeine::CcafeBuilderService_impl::connect (
  /*in*/ gov::cca::ComponentID user,
  /*in*/ std::string usingPortName,
  /*in*/ gov::cca::ComponentID provider,
  /*in*/ std::string providingPortName ) 
throw ( 
  gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.connect)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.connect)
}

// referred to by:
//    gov.cca.ComponentID
//    gov.cca.CCAException
//    gov.cca.TypeMap

/**
 * Creates an instance of a CCA component of the type defined by the 
 * string className.  The string classname uniquely defines the
 * "type" of the component, e.g.
 * doe.cca.Library.GaussianElmination. 
 * It has an instance name given by the string instanceName.
 * The instanceName may be empty (zero length) in which case
 * the instanceName will be assigned to the component automatically.
 * @throws CCAException If the Component className is unknown, or if the
 * instanceName has already been used, a CCAException is thrown.
 * @return A ComponentID corresponding to the created component. Destroying
 * the returned ID does not destroy the component; 
 * see destroyInstance instead.
 */
gov::cca::ComponentID
ccaffeine::CcafeBuilderService_impl::createInstance (
  /*in*/ std::string className,
  /*in*/ std::string instanceName,
  /*in*/ gov::cca::TypeMap properties ) 
throw ( 
  gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.createInstance)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.createInstance)
}

// referred to by:
//    gov.cca.ComponentID
//    gov.cca.CCAException

/**
 * Eliminate the Component instance, from the scope of the framework.
 * @param toDie the component to be removed.
 * @param timeout the allowable wait; 0 means up to the framework.
 * @throws CCAException if toDie refers to an invalid component, or
 * if the operation takes longer than timeout seconds.
 */
void
ccaffeine::CcafeBuilderService_impl::destroyInstance (
  /*in*/ gov::cca::ComponentID toDie,
  /*in*/ float timeout ) 
throw ( 
  gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.destroyInstance)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.destroyInstance)
}

// referred to by:
//    gov.cca.CCAException
//    gov.cca.ConnectionID

/**
 * Disconnect the connection indicated by connID before the indicated
 * timeout in secs. Upon successful completion, connID and the connection
 * it represents become invalid. 
 * @param timeout the time in seconds to wait for a connection to close; 0
 * means to use the framework implementation default.
 * @throws CCAException when any one of the following conditions occur: <ul>
 * <li>id refers to an invalid ConnectionID,
 * <li>timeout is exceeded, after which, if id was valid before 
 * disconnect() was invoked, it remains valid
 * </ul>
 * .
 */
void
ccaffeine::CcafeBuilderService_impl::disconnect (
  /*in*/ gov::cca::ConnectionID connID,
  /*in*/ float timeout ) 
throw ( 
  gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.disconnect)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.disconnect)
}

// referred to by:
//    gov.cca.ComponentID
//    gov.cca.CCAException

/**
 * Remove all connections between components id1 and id2 within 
 * the period of timeout secs. If id2 is null, then all connections 
 * to id1 are removed (within the period of timeout secs).
 * @throws CCAException when any one of the following conditions occur:<ul>
 * <li>id1 or id2 refer to an invalid ComponentID (other than id2 == null),
 * <li>The timeout period is exceeded before the disconnections can be made. 
 * </ul>
 */
void
ccaffeine::CcafeBuilderService_impl::disconnectAll (
  /*in*/ gov::cca::ComponentID id1,
  /*in*/ gov::cca::ComponentID id2,
  /*in*/ float timeout ) 
throw ( 
  gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.disconnectAll)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.disconnectAll)
}

// referred to by:
//    gov.cca.ComponentID
//    gov.cca.CCAException

/**
 * Get id from name by which it was created.
 * @return a ComponentID from the instance name of the component
 * produced by ComponentID.getInstanceName().
 * @throws CCAException if there is no component matching the 
 * given componentInstanceName.
 */
gov::cca::ComponentID
ccaffeine::CcafeBuilderService_impl::getComponentID (
  /*in*/ std::string componentInstanceName ) 
throw ( 
  gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.getComponentID)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.getComponentID)
}

// referred to by:
//    gov.cca.ComponentID
//    gov.cca.CCAException

/**
 * Get component list.
 * @return a ComponentID for each component currently created.
 */
SIDL::array<gov::cca::ComponentID>
ccaffeine::CcafeBuilderService_impl::getComponentIDs () 
throw ( 
  gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.getComponentIDs)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.getComponentIDs)
}

// referred to by:
//    gov.cca.ComponentID
//    gov.cca.CCAException
//    gov.cca.TypeMap

/**
 * Get property map for component.
 * @return the public properties associated with the component referred to by
 * ComponentID. 
 * @throws a CCAException if the ComponentID is invalid.
 */
gov::cca::TypeMap
ccaffeine::CcafeBuilderService_impl::getComponentProperties (
  /*in*/ gov::cca::ComponentID cid ) 
throw ( 
  gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.getComponentProperties)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.getComponentProperties)
}

// referred to by:
//    gov.cca.ComponentID
//    gov.cca.CCAException
//    gov.cca.ConnectionID

/**
 * Returns a list of connections as an array of 
 * handles. This will return all connections involving components 
 * in the given componentList of ComponentIDs. This
 * means that ConnectionID's will be returned even if only one 
 * of the participants in the connection appears in componentList.
 * 
 * @throws CCAException if any component in componentList is invalid.
 */
SIDL::array<gov::cca::ConnectionID>
ccaffeine::CcafeBuilderService_impl::getConnectionIDs (
  /*in*/ SIDL::array<gov::cca::ComponentID> componentList ) 
throw ( 
  gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.getConnectionIDs)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.getConnectionIDs)
}

// referred to by:
//    gov.cca.CCAException
//    gov.cca.ConnectionID
//    gov.cca.TypeMap

/**
 * Fetch property map of a connection.
 * @returns the properties for the given connection.
 * @throws CCAException if connID is invalid.
 */
gov::cca::TypeMap
ccaffeine::CcafeBuilderService_impl::getConnectionProperties (
  /*in*/ gov::cca::ConnectionID connID ) 
throw ( 
  gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.getConnectionProperties)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.getConnectionProperties)
}

// referred to by:
//    gov.cca.ComponentID
//    gov.cca.CCAException

/**
 * Get component id from stringified reference.
 * @return a ComponentID from the string produced by 
 * ComponentID.getSerialization(). 
 * @throws CCAException if the string does not represent the appropriate 
 * serialization of a ComponentID for the underlying framework.
 */
gov::cca::ComponentID
ccaffeine::CcafeBuilderService_impl::getDeserialization (
  /*in*/ std::string s ) 
throw ( 
  gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.getDeserialization)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.getDeserialization)
}

// referred to by:
//    gov.cca.ComponentID
//    gov.cca.CCAException
//    gov.cca.TypeMap

/**
 * Fetch map of Port properties exposed by the framework.
 * @return the public properties pertaining to the Port instance 
 * portname on the component referred to by cid. 
 * @throws CCAException when any one of the following conditions occur:<ul>
 * <li>portname is not a registered Port on the component indicated by cid,
 * <li>cid refers to an invalid component. </ul>
 */
gov::cca::TypeMap
ccaffeine::CcafeBuilderService_impl::getPortProperties (
  /*in*/ gov::cca::ComponentID cid,
  /*in*/ std::string portname ) 
throw ( 
  gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.getPortProperties)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.getPortProperties)
}

// referred to by:
//    gov.cca.ComponentID
//    gov.cca.CCAException

/**
 * Get the names of Port instances provided by the identified component.
 * @param cid the component.
 * @throws CCAException if cid refers to an invalid component.
 */
SIDL::array<std::string>
ccaffeine::CcafeBuilderService_impl::getProvidedPortNames (
  /*in*/ gov::cca::ComponentID cid ) 
throw ( 
  gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.getProvidedPortNames)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.getProvidedPortNames)
}

// referred to by:
//    gov.cca.ComponentID
//    gov.cca.CCAException

/**
 * Get the names of Port instances used by the identified component.
 * @param cid the component.
 * @throws CCAException if cid refers to an invalid component. 
 */
SIDL::array<std::string>
ccaffeine::CcafeBuilderService_impl::getUsedPortNames (
  /*in*/ gov::cca::ComponentID cid ) 
throw ( 
  gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.getUsedPortNames)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.getUsedPortNames)
}

// referred to by:
//    gov.cca.ComponentID
//    gov.cca.CCAException
//    gov.cca.TypeMap

/**
 * Causes the framework implementation to associate the given properties 
 * with the component designated by cid. 
 * @throws CCAException if cid is invalid or if there is an attempted
 * change to a property locked by the framework implementation.
 */
void
ccaffeine::CcafeBuilderService_impl::setComponentProperties (
  /*in*/ gov::cca::ComponentID cid,
  /*in*/ gov::cca::TypeMap map ) 
throw ( 
  gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.setComponentProperties)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.setComponentProperties)
}

// referred to by:
//    gov.cca.CCAException
//    gov.cca.ConnectionID
//    gov.cca.TypeMap

/**
 * Associates the properties with the connection.
 * @param map the source of the properties.
 * @param connID connection to receive property values.
 * @throws CCAException if connID is invalid, or if this changes 
 * a property locked by the underlying framework.
 */
void
ccaffeine::CcafeBuilderService_impl::setConnectionProperties (
  /*in*/ gov::cca::ConnectionID connID,
  /*in*/ gov::cca::TypeMap map ) 
throw ( 
  gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.setConnectionProperties)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.setConnectionProperties)
}

// referred to by:
//    gov.cca.ComponentID
//    gov.cca.CCAException
//    gov.cca.TypeMap

/**
 * Associates the properties given in map with the Port indicated by 
 * portname. The component must have a Port known by portname.
 * @throws CCAException if either cid or portname are
 * invalid, or if this a changed property is locked by 
 * the underlying framework or component.
 */
void
ccaffeine::CcafeBuilderService_impl::setPortProperties (
  /*in*/ gov::cca::ComponentID cid,
  /*in*/ std::string portname,
  /*in*/ gov::cca::TypeMap map ) 
throw ( 
  gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService.setPortProperties)
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService.setPortProperties)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.CcafeBuilderService._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccaffeine.CcafeBuilderService._misc)

