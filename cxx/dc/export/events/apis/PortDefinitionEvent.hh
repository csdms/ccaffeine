/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__PortDefinitionEvent_H__
#define __ccafeopq__PortDefinitionEvent_H__

namespace ccafeopq {
namespace event {



/** 
   This interface lets components be notified about ports
   coming and going on other components.
   Special notes:
   PortAddPending events do not guarantee that a PortAdded
   event will follow. The port addition may fail if there
   is a port naming conflict yet to be discovered.
*/

class PortDefinitionEvent : public virtual ContextEvent
{
public:
  /** required destructor */
  virtual ~PortDefinitionEvent(){}

 // ccafeopq_event_ContextEvent_pvblock;
#if 0

  /** Returns the integer standard type for the event. If the
      event is not one of the standard types, then this returns
      ContextEventType.NONE. 
      For PortDefinitionEvent, the type is one of subset
      PortAddPending,
      PortAdded,
      PortRemovePending,
      PortRemoved,
      PortRegisterPending,
      PortRegistered,
      PortUnregisterPending,
      PortUnregistered.

   */
  virtual enum ccafeopq::event::type::ContextEventType getContextEventType() = 0; 

  /** 
    Fetch the component generating the event.
    @return the componentID of the component generating the event,
     or null if the container itself generated the event.
   */
  virtual ::ccafeopq::ComponentID_shared  getContextEventSourceID() = 0; 

  /** Within a source component, there may be more than one emitter. Key
      is the self-proclaimed serial number of the emitter, unique
      within the scope of the result from getSourceID.
   */
  virtual int getContextEventSourceKey() = 0; 

  /** For each source:key pair events are emitted in a monotonically
      increasing sequence. It is hoped 64 bits is enough to handle
      long runs.
   */
  virtual int64_t getContextEventSequenceNumber() = 0; 

  /** Annotated, stringified event information.
      @return an arbitrary string.
   */
  virtual ::std::string getContextEventDescription() = 0;

  /** Set or amend the description, as determined by the implementation.
   */
  virtual void setContextEventDescription( ::std::string description) = 0;
#endif  // 0

  ///// PortDefinitionEvent_sharedspecific functions
  /** @return id of component now providing or registering a port. */
  virtual ::ccafeopq::ComponentID_shared getComponent() = 0; 

  /** @return properties supplied to the provide or register call. */
  virtual ccafeopq::TypeMap_shared getPortProperties() = 0; 

  /** Fetch instance name of port.
      @return port instance name supplied to the provide or register call.
   */
  virtual const ::std::string getPortName() = 0;

  /** Fetch class name of port.
     @return port instance type supplied to the provide or register call.
   */
  virtual const ::std::string getPortType() = 0;
  
} ; // end interface PortDefinitionEvent


} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/apis/PortDefinitionEvent.hh,v 1.2 2004/04/02 02:17:52 baallan Exp $ */

#endif // __ccafeopq__PortDefinitionEvent_H__
