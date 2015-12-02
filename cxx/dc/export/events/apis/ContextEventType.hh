#ifndef __ccafeopq__ContextEventType_H__
#define __ccafeopq__ContextEventType_H__

namespace ccafeopq {
namespace event {
namespace type {


/** Mapping of standard event types in the component lifecycle to
    integers (and by function, to strings). In any high performance
    language this maps to an enum or header full of defines or
    constant parameters.
<p>
    In decoding the ContextEvent messages, each kind of event here
    requires possibly many details to make sense. The details are provided
    as event subclasses. The generic std::string of Event should be ok, however,
    if you are just printing at a human.
</p>
<p>
    This could be a good candidate for a CCA standard type.</p>
</p>
<p>
	C++ usage note:
type:
	enum ccafeopq::event::type::ContextEventType t;
values:
	ccafeopq::event::type::XXX;
</p>
*/
enum ContextEventType
{

  /** When digesting an alleged std::string or int type,
      it was found not to be in the standard. 
   */
  NONE = -2, 

  /** Somebody fouled up; Should never be deliberately sent 
      or received.
    */
  Error = -1, 

  /** The enumerated value type for a listener to indicate it wants all
      notices. Never delivered to a listener.
   */
  ALL = 0, 

  /** A connection may soon be made.  Assuming no errors occur in process.
<pre>
      The details must have the following keys with defined values:
      callerComponentName, callerUsesPortName,
      calleeComponentName, calleeProvidesPortName.

      The details may additionally have 
      callerComponentClass, callerUsesPortType,
      calleeComponentClass, calleeProvidesPortType,
      frameworkClass, frameworkToString, 
      containerToString, containerFQIName, 
      callerComponentFQIName, calleeComponentFQIName.
</pre>
   */
  ConnectPending = 1, 

  /** A connection recently made. The details are
      per ConnectPending.
   */
  Connected = 2, 

  /** A connection may soon be unmade. Assuming no errors occur in process.
   */
  DisconnectPending = 3, 

  /** A connection recently unmade.
      The details are per ConnectPending.
   */
  Disconnected = 4, 

  /** A component creation requested.
<pre>
      The details must have the following keys with defined values:
      componentClass, componentNameRequested.

      The details may additionally have keys with defined values:
      frameworkClass, frameworkToString, 
      containerToString, containerFQIName.
</pre>
   */ 
  ComponentInstanceAddPending = 5, 

  /** A component newly created.
<pre>
      The details must have the following keys with defined values:
      componentClass, componentNameRequested, componentName.

      The details may additionally have keys with defined values:
      frameworkClass, frameworkToString, 
      containerToString, containerFQIName,
      factoryComponentName.
</pre>
   */
  ComponentInstanceAdded = 6, 

  /** A component deletion requested. 
<pre>
      The details must have the following keys with defined values:
      componentName.

      The details may additionally have keys with defined values:
      frameworkClass, frameworkToString, 
      containerToString, containerFQIName.
</pre>
   */
  ComponentInstanceDeletePending = 7, 

  /** A component deletion completed.
<pre>
      The details must have the following keys with defined values:
      componentName.

      The details may additionally have keys with defined values:
      frameworkClass, frameworkToString, 
      containerToString, containerFQIName,
      factoryComponentName.
</pre>
   */
  ComponentInstanceDeleted = 8, 

  /** A provides port is being added (but not yet available). 
      Assuming no errors in the process.
<pre>
      The details must have the following keys with defined values:
      componentName, portType, portNameRequested.

      The details may additionally have keys with defined values:
      componentClass, componentFQIName,
      frameworkClass, frameworkToString, 
      containerToString, containerFQIName.
</pre>
   */
  PortAddPending = 9, 

  /** A provides port was added and is available.
<pre>
      The details must have the following keys with defined values:
      componentName, portType, portName.

      The details may additionally have keys with defined values:
      componentClass, componentFQIName, portNameRequested,
      frameworkClass, frameworkToString, 
      containerToString, containerFQIName.
</pre>
   */
  PortAdded = 10, 

  /** A provides port is being removed, but is still available.
<pre>
      The details must have the following keys with defined values:
      componentName, portName.

      The details may additionally have keys with defined values:
      componentClass, componentFQIName, portType,
      frameworkClass, frameworkToString, 
      containerToString, containerFQIName.
</pre>
   */
  PortRemovePending = 11, 

  /** A provides port has been removed and is no longer available.
      The details are per PortRemovePending.
   */
  PortRemoved = 12, 
  
  /** A uses port is about to be registered. (Assuming no errors in process).
      The details are per PortAddPending.
   */
  PortRegisterPending = 13, 

  /** A uses port was registered.
      The details are per PortAdded.
   */
  PortRegistered = 14, 

  /** A uses port is about to be unregistered.
      The details are per PortRemovePending.
   */
  PortUnregisterPending = 15, 

  /** A uses port has been unregistered.
      The details are per PortRemovePending.
   */
  PortUnregistered = 16, 

  /** A port is about to be fetched for use with getPort.
<pre>
      The details must have the following keys with defined values:
      callerComponentName, callerUsesPortName.

      The details may additionally have keys with defined values:
      callerComponentClass, callerComponentFQIName, callerUsesPortType,
      frameworkClass, frameworkToString, 
      containerToString, containerFQIName.
</pre>
   */
  PortFetchPending = 17, 

  /** A port has been fetched with getPort.
<pre>
      The details must have the following keys with defined values:
      callerComponentName, callerUsesPortName.

      The details may additionally have keys with defined values:
      callerComponentClass, callerComponentFQIName, callerUsesPortType,
      calleeComponentName,    calleeComponentClass,
      calleeProvidesPortName, calleeProvidesPortType,
      frameworkClass, frameworkToString, 
      containerToString, containerFQIName.
</pre>
      DESIGN NOTE: This event cannot be delivered promptly in
      a single-threaded framework, because the event must
      happen after the return of the port result to the
      component calling getport. This requires one of three
      things:
      - the event be placed in a queue for the next time control
        passes to the framework.
      - the event be optional (some frameworks just don't have
        it, in which case components can't assume it, in which
        case it might as well not be in the specification.
      - the framework is required to be multithreaded and
        component developers are forced to handle multithreaded
        event delivery.
   */
  PortFetched = 18, 

  /** A port is about to be released from use with releasePort.
      The details are per PortFetchPending.
   */
  PortReleasePending = 19, 

  /** A port has been released with releasePort.
      The details are per PortFetched.
   */
  PortReleased = 20, 

  /** A factory is now available.
<pre>
      The details must have the following keys with defined values:
      factoryComponentName, portName.

      The details may additionally have keys with defined values:
      componentClass, componentFQIName,
      frameworkClass, frameworkToString, 
      containerToString, containerFQIName.
</pre>
   */
  FactoryOpened = 21, 

  /** A factory is no longer available for more creations.
      It may remain open for destruction of previously created
      items, however. ComponentDeleted is the final message in the
      lifecycle of the component, factory or not.
      The details are per FactoryOpened.
   */
  FactoryClosed = 22, 

  /** The context is shutting down, and any components
      added to the context by the event recipient should be
      be reclaimed.
</pre>
      The details must have the following keys with defined values:
      containerToString, containerFQIName.
      
      The details may additionally have keys with defined values:
      frameworkClass, frameworkToString, 
</pre>
   */
  ContextClosing = 23, 

} ; // end enum 


} ENDSEMI // end namespace type
} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/apis/ContextEventType.hh,v 1.1 2004/03/20 02:16:09 baallan Exp $ */

#endif // __ccafeopq__ContextEventType_H__
