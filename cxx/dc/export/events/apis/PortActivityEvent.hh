/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__PortActivityEvent_H__
#define __ccafeopq__PortActivityEvent_H__

namespace ccafeopq {
namespace event {



/** 
    This interface is container-scoped while the ConnectionEvent
    interface is component-scoped, thus the two are not redundant.
    Special notes:
    The ConnectPending means a request with the data
    available in this interface was made; it does not
    guarantee that the data is consistent or that the
    connection process will succeed.
*/

class PortActivityEvent : public virtual ContextEvent
{
public:
  /** required destructor */
  virtual ~PortActivityEvent(){}

  // ccafeopq_event_ContextEvent_pvblock;
#if 0

  /** Returns the integer standard type for the event. If the
      event is not one of the standard types, then this returns
      ContextEventType.NONE. 
      For PortActivityEvent, the type is one of subset
      PortFetchPending,
      PortFetched,
      PortReleasePending,
      PortReleased.
      Special notes:
      PortFetchPending does not guarantee a PortFetched event, as
      the defined connection may prove bogus. 
      For ArrayUses ports, a separate event occurs for connection.
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
#endif // 0
  ///// PortActivityEvent_sharedspecific functions
  /** @return connection changing, it it exists yet, or null. */
  virtual ::ccafeopq::ConnectionID_shared getConnection() = 0;
  
  /** @return the component getting/releasing one of its port. */
  virtual ::ccafeopq::ComponentID_shared getComponent() = 0; 
  
  /** @return name of port user component is getting/releasing. */
  virtual const ::std::string getPortName() = 0;
  
  /** @return type of port being affected. */
  virtual const ::std::string getPortType() = 0;
  
} ; // end interface PortActivityEvent


} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/apis/PortActivityEvent.hh,v 1.2 2004/04/02 02:17:52 baallan Exp $ */

#endif // __ccafeopq__PortActivityEvent_H__
