/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__ComponentFactoryEvent_H__
#define __ccafeopq__ComponentFactoryEvent_H__

namespace ccafeopq {
namespace event {



/** 
   Notify interested parties that a new component factory 
   is in play or an old one is going away.
*/

class ComponentFactoryEvent : public virtual ContextEvent
{
public:
  /** required destructor */
  virtual ~ComponentFactoryEvent(){}

 // ccafeopq_event_ContextEvent_pvblock;

#if 0
  /** Returns the integer standard type for the event. If the
      event is not one of the standard types, then this returns
      ContextEventType.NONE. 
      For ComponentFactoryEvent, the type is
      FactoryPortAdded
      FactoryPortRemovePending
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
  virtual void setContextEventDescription(const ::std::string & description) = 0;
#endif


  /////// ComponentFactoryEvent_sharedspecific functions
  /** @return the componentid of the factory being mentioned. */
  virtual ::ccafeopq::ComponentID_shared getFactoryID() = 0; /* throw? */

  /** @return the properties of the port that provides the factory function */
  virtual ccafeopq::TypeMap_shared getFactoryPortProperties() = 0; /* throw? */
  
} ; // end interface ComponentFactoryEvent


} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/apis/ComponentFactoryEvent.hh,v 1.2 2004/04/02 02:17:52 baallan Exp $ */

#endif // __ccafeopq__ComponentFactoryEvent_H__
