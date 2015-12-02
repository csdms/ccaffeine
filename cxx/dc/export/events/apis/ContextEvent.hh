/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__ContextEvent_H__
#define __ccafeopq__ContextEvent_H__

namespace ccafeopq {
namespace event {



/** Container event data mechanism. All the data accesible
    through this interface is relative to (interpretable only
    in the context of) the container in which the event belongs.
    The methods are named with ContextEvent
    so that implementors choosing to roll ContextEvent,
    ConnectionEvent, and generic std::string events ala Indiana
    into a single implementation
    will not have method naming conflicts.
    This interface is container-scoped while the ConnectionEvent
    interface is component-scoped, thus the two are not redundant.
*/

class ContextEvent
{
public:
  /** required destructor */
  virtual ~ContextEvent(){}


  /** Returns the integer standard type for the event. If the
      event is not one of the standard types, then this returns
      ContextEventType.NONE. 
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

  /** 
      The following additional info, if present, may make the event
      interpretable in the scope of the outermost framework. This
      is handy mainly as that's where the interactive user interface 
      will reside. 
<pre>
      containerFullyQualifiedInstanceName,
      componentFullyQualifiedInstanceName,
      callerComponentFullyQualifiedInstanceName,
      calleeComponentFullyQualifiedInstanceName,
</pre>
      These and others can be included in the std::string description.
      However, the sub-class of the event is what can be guaranteed
      machine interpretable. In some frameworks this function may
      return an XML or other SGML-style string.
   */
  virtual ::std::string getContextEventDescription() = 0; 

  /** Set or amend the description, as determined by the implementation.
   */
  virtual void setContextEventDescription(const ::std::string & description) = 0;

} ; // end interface ContextEvent

#define ccafeopq_event_ContextEvent_pvblock \
virtual enum ccafeopq::event::type::ContextEventType getContextEventType() = 0; \
virtual ::ccafeopq::ComponentID_shared  getContextEventSourceID() = 0; \
virtual int getContextEventSourceKey() = 0; \
virtual int64_t getContextEventSequenceNumber() = 0; \
virtual ::std::string getContextEventDescription() = 0; \
virtual void setContextEventDescription(const ::std::string & description) = 0


} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/apis/ContextEvent.hh,v 1.2 2004/04/02 02:17:52 baallan Exp $ */

#endif // __ccafeopq__ContextEvent_H__
