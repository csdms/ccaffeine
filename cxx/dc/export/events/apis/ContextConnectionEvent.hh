/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__ContextConnectionEvent_H__
#define __ccafeopq__ContextConnectionEvent_H__

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

class ContextConnectionEvent : public virtual ContextEvent
{
public:
  /** required destructor */
  virtual ~ContextConnectionEvent(){}

  // ccafeopq_event_ContextEvent_pvblock;
#if 0

  /** Returns the integer standard type for the event. If the
      event is not one of the standard types, then this returns
      ContextEventType.NONE. 
      For ContextConnectionEvent, the type is one of
      ConnectPending, Connected, DisconnectPending, Disconnected.
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
  /////// ContextConnectionEvent_sharedspecific functions
  /** @return the providing component id. */
  virtual ::ccafeopq::ComponentID_shared getProvider() = 0; 

  /** @return the using component id. */
  virtual ::ccafeopq::ComponentID_shared getUser() = 0; 

  /** Properties from the provided port, when event is
      Connected, Disconnected. May return null for 
      ConnectPending DisconnectPending, when port is not known
      with certainty to exist.
      @return the properties of the providing port.
  */
  virtual ccafeopq::TypeMap_shared getProviderPortProperties() = 0;

  /** Properties from the using port, when event is
      Connected, Disconnected. May return null for 
      ConnectPending DisconnectPending, when port is not known
      with certainty to exist.
      @return the properties of the using port.
   */
  virtual ccafeopq::TypeMap_shared getUserPortProperties() = 0;

  /** Provider port instance.
      @return provider port name.
   */
  virtual const ::std::string getProviderPortName() = 0; 
  
  /** User port instance.
      @return user port name.
   */
  virtual const ::std::string getUserPortName() = 0; 
  
} ; // end interface ContextConnectionEvent


} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/apis/ContextConnectionEvent.hh,v 1.2 2004/04/02 02:17:52 baallan Exp $ */

#endif // __ccafeopq__ContextConnectionEvent_H__
