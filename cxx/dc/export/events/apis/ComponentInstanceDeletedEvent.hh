/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__ComponentInstanceDeletedEvent_H__
#define __ccafeopq__ComponentInstanceDeletedEvent_H__

namespace ccafeopq {
namespace event {



/** 
   Advise others that a component is gone.
*/

class ComponentInstanceDeletedEvent : public virtual ContextEvent
{
public:
  /** required destructor */
  virtual ~ComponentInstanceDeletedEvent(){}

  // ccafeopq_event_ContextEvent_pvblock;
#if 0

  /** Returns the integer standard type for the event. If the
      event is not one of the standard types, then this returns
      ContextEventType.NONE. 
      For ComponentInstanceDeletedEvent, the type is
      ComponentDeleted.
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

  /** annotated, stringified event information.
      @return an arbitrary string.
   */
  virtual ::std::string getContextEventDescription() = 0;

  /** Set or amend the description, as determined by the implementation.
   */
  virtual void setContextEventDescription( ::std::string description) = 0;
#endif //0
  /////// ComponentInstanceDeletedEvent_sharedspecific functions
  /** @return class of deleted component. */
  virtual const ::std::string getDeadComponentClassName() = 0; /* throw? */

  /** @return name of deleted component. */
  virtual const ::std::string getDeadComponentInstanceName() = 0; /* throw? */
  
} ; // end interface ComponentInstanceDeletedEvent


} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/apis/ComponentInstanceDeletedEvent.hh,v 1.2 2004/04/02 02:17:52 baallan Exp $ */

#endif // __ccafeopq__ComponentInstanceDeletedEvent_H__
