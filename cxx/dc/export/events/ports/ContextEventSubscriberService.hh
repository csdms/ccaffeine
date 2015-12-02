/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__Ports_ContextEventSubscriberService_H__
#define __ccafeopq__Ports_ContextEventSubscriberService_H__

namespace ccafeopq {
namespace ports {


/** A callback service to alert a component when peer component
    activities within CCA purview occur.
    This service is to be 
    immediately available during a setServices call. This service 
    interface is compatible with a direct-connected or proxy framework.
    After signing up, the subscriber will receive all container event
    notices. A filtering version of this interface is possible, but
    simply an ergonomic issue.
*/

class ContextEventSubscriberService  : public virtual ::ccafeopq::Port
{
public:
  /** obligatory virtual destructor */
  virtual ~ContextEventSubscriberService() {}


  ///////////////////////////////////////////////////////////////
  //// The listener callback registration functions.
  //// This is all most app-framework components will need.
  ///////////////////////////////////////////////////////////////

  /** Sign up to be told about events matching ceType.
      For those who wish to receive specific events that require no
      casting to dig out the information, see the other addXXXXEventListener
      functions in this interface.
      @param l  an object (this component or its delegate) that listens
             by implementing the ContextEventListener_shared callback.
      @param ceType ALL will cause all valid event types to be received,
             and any other type will cause that other to be received.
             Events will be delivered in generic form and the recipient
             may need to cast if they want more specific information.
   */
  virtual void addContextEventListener( ccafeopq::event::ContextEventListener_shared  l,  enum ccafeopq::event::type::ContextEventType ceType) = 0; 

  /** Ignore future Events.
      Removing a non-added listener is not an error. 
      @param l a previously added listener interface.
      @param ceType the same type that was given for addContextEventListener, usually.
             If you want to subscribe to all but one events for example, you could
             subscribe to ALL and then remove yourself from one type.
   */
  virtual void removeContextEventListener( ccafeopq::event::ContextEventListener_shared  l, enum ccafeopq::event::type::ContextEventType ceType) = 0; 


  /** Sign up to be told about events.
      @param l an object (this component or its delegate) that listens
           by implementing the ComponentFactoryEventListener_shared callback.
  */
  virtual void addComponentFactoryEventListener( ccafeopq::event::ComponentFactoryEventListener_shared  l) = 0;

  /** Sign up to be told about events.
      @param l an object (this component or its delegate) that listens
           by implementing the ComponentInstanceAddRequestEventListener_shared callback.
  */
  virtual void addComponentInstanceAddRequestEventListener( ccafeopq::event::ComponentInstanceAddRequestEventListener_shared  l) = 0;

  /** Sign up to be told about events.
      @param l an object (this component or its delegate) that listens
           by implementing the ComponentInstanceAddedEventListener_shared callback.
  */
  virtual void addComponentInstanceAddedEventListener( ccafeopq::event::ComponentInstanceAddedEventListener_shared  l) = 0;

  /** Sign up to be told about events.
      @param l an object (this component or its delegate) that listens
           by implementing the ComponentInstanceDeleteRequestEventListener_shared callback.
  */
  virtual void addComponentInstanceDeleteRequestEventListener( ccafeopq::event::ComponentInstanceDeleteRequestEventListener_shared  l) = 0;

  /** Sign up to be told about events.
      @param l an object (this component or its delegate) that listens
           by implementing the ComponentInstanceDeletedEventListener_shared callback.
  */
  virtual void addComponentInstanceDeletedEventListener( ccafeopq::event::ComponentInstanceDeletedEventListener_shared  l) = 0;

  /** Sign up to be told about events.
      @param l an object (this component or its delegate) that listens
           by implementing the ContextConnectionEventListener_shared callback.
  */
  virtual void addContextConnectionEventListener( ccafeopq::event::ContextConnectionEventListener_shared  l) = 0;

  /** Sign up to be told about events.
      @param l an object (this component or its delegate) that listens
           by implementing the PortActivityEventListener_shared callback.
  */
  virtual void addPortActivityEventListener( ccafeopq::event::PortActivityEventListener_shared  l) = 0;

  /** Sign up to be told about events.
      @param l an object (this component or its delegate) that listens
           by implementing the PortDefinitionEventListener_shared callback.
  */
  virtual void addPortDefinitionEventListener( ccafeopq::event::PortDefinitionEventListener_shared  l) = 0;

  /** Ignore future Events.
      Removing a non-added listener is not an error.
      @param l a previously added ComponentFactoryEventListener_shared listener interface.
   */
  virtual void removeComponentFactoryEventListener( ccafeopq::event::ComponentFactoryEventListener_shared  l) = 0;

  /** Ignore future Events.
      Removing a non-added listener is not an error.
      @param l a previously added ComponentInstanceAddRequestEventListener_shared listener interface.
   */
  virtual void removeComponentInstanceAddRequestEventListener( ccafeopq::event::ComponentInstanceAddRequestEventListener_shared  l) = 0;

  /** Ignore future Events.
      Removing a non-added listener is not an error.
      @param l a previously added ComponentInstanceAddedEventListener_shared listener interface.
   */
  virtual void removeComponentInstanceAddedEventListener( ccafeopq::event::ComponentInstanceAddedEventListener_shared  l) = 0;

  /** Ignore future Events.
      Removing a non-added listener is not an error.
      @param l a previously added ComponentInstanceDeleteRequestEventListener_shared listener interface.
   */
  virtual void removeComponentInstanceDeleteRequestEventListener( ccafeopq::event::ComponentInstanceDeleteRequestEventListener_shared  l) = 0;

  /** Ignore future Events.
      Removing a non-added listener is not an error.
      @param l a previously added ComponentInstanceDeletedEventListener_shared listener interface.
   */
  virtual void removeComponentInstanceDeletedEventListener( ccafeopq::event::ComponentInstanceDeletedEventListener_shared  l) = 0;

  /** Ignore future Events.
      Removing a non-added listener is not an error.
      @param l a previously added ContextConnectionEventListener_shared listener interface.
   */
  virtual void removeContextConnectionEventListener( ccafeopq::event::ContextConnectionEventListener_shared  l) = 0;

  /** Ignore future Events.
      Removing a non-added listener is not an error.
      @param l a previously added PortActivityEventListener_shared listener interface.
   */
  virtual void removePortActivityEventListener( ccafeopq::event::PortActivityEventListener_shared  l) = 0;

  /** Ignore future Events.
      Removing a non-added listener is not an error.
      @param l a previously added PortDefinitionEventListener_shared listener interface.
   */
  virtual void removePortDefinitionEventListener( ccafeopq::event::PortDefinitionEventListener_shared  l) = 0;

  ///////////////////////////////////////////////////////////////
  //// The enum to std::string and back mapping functions, 
  //// useful principally  generating UI strings.
  ///////////////////////////////////////////////////////////////

  /** Mapping function converting to standard std::string from the enumeration.
     The std::string result is identical to the enumerated names
     for events defined in this interface. E.g. FactoryClosed
     maps to  "FactoryClosed". Case is not significant but
     is provided for readability. 
  */
  virtual const std::string getStringFromEnum( enum ccafeopq::event::type::ContextEventType ceType) = 0; 

  /** Mapping function converting to standard int from a string.
      This function is *not* case sensitive, as we don't want
      standard events to be missed simply because of -key typos.
   */
  virtual enum ccafeopq::event::type::ContextEventType getEnumFromString(const  std::string & typeString) = 0; 

} ; // end interface ContextEventSubscriberService

} ENDSEMI // end namespace ports
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/ports/ContextEventSubscriberService.hh,v 1.2 2004/04/02 02:17:53 baallan Exp $ */

#endif // __ccafeopq__Ports_ContextEventSubscriberService_H__
