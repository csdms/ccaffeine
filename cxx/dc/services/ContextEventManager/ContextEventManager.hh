#ifndef ccafe_ContextEventManager
#define ccafe_ContextEventManager

namespace ccafeopq {
namespace event {

class EventProcessor;

/**
  This component manages event firing and subscription requests.

  <p>Provides Ports (name,type)</p>
  <ul>
    <li>"ContextEventPublisherService", "gov.ccafe.ports.ContextEventPublisherService" </li>
    <li>"ContextEventSubscriberService", "gov.ccafe.ports.ContextEventSubscriberService"</li>
  </ul>

*/
class ContextEventManager :
//public virtual ccafeopq::Component, 
public virtual ccafeopq::ports::ContextEventPublisherService,
public virtual ccafeopq::ports::ContextEventSubscriberService,
public virtual ::ccafeopq::support::Port
{

private:
	int64_t seqNumGenerator; 
	bool debug;

#if 0
  private ContextExceptionService ces = null;
  Services *svc;
#endif

  /** Generate a sequence number.
      fixme-feature: this is used for all source:key pairs;
      the generator would last longer if it ran a table
      of seqNumGenerator keyed by source:key pairs.
   */
	int64_t nextNum();

	/** whine if debug true. */
	void log(std::string s);

	std::vector< ccafeopq::event::EventProcessor * > processors;

	ComponentFactoryEventProcessor cfep;
	ComponentInstanceAddRequestEventProcessor ciarep;
	ComponentInstanceAddedEventProcessor ciaep;
	ComponentInstanceDeleteRequestEventProcessor cidrep;
	ComponentInstanceDeletedEventProcessor cidep;
	ContextConnectionEventProcessor ccep;
	PortActivityEventProcessor paep;
	PortDefinitionEventProcessor pdep;
  
	ContextEventListenerList cell;
	ComponentFactoryEventListenerList theComponentFactoryEventListeners;
	ComponentInstanceAddRequestEventListenerList theComponentInstanceAddRequestEventListeners;
	ComponentInstanceAddedEventListenerList theComponentInstanceAddedEventListeners;
	ComponentInstanceDeleteRequestEventListenerList theComponentInstanceDeleteRequestEventListeners;
	ComponentInstanceDeletedEventListenerList theComponentInstanceDeletedEventListeners;
	ContextConnectionEventListenerList theContextConnectionEventListeners;
	PortActivityEventListenerList thePortActivityEventListeners;
	PortDefinitionEventListenerList thePortDefinitionEventListeners;

#if 0
	/** pairwise listing of the ports we use.
	// use componentProperties service?
	*/
	std::vector< std::string > usesPorts;

	/** pairwise listing of ports we provide directly. */
	std::vector< std::string > providesPorts;

	void tearDownPorts() throw(ccafeopq::Exception);
	void setUpPorts() throw(ccafeopq::Exception);
#endif
	bool initDone;
	void initProcessorList();



public:
	void addProcessor(EventProcessor *ep);

	ComponentFactoryEventListenerList getComponentFactoryEventListeners();
	ComponentInstanceAddRequestEventListenerList getComponentInstanceAddRequestEventListeners();
	ComponentInstanceAddedEventListenerList getComponentInstanceAddedEventListeners();
	ComponentInstanceDeleteRequestEventListenerList getComponentInstanceDeleteRequestEventListeners();
	ComponentInstanceDeletedEventListenerList getComponentInstanceDeletedEventListeners();
	ContextConnectionEventListenerList getContextConnectionEventListeners();
	PortActivityEventListenerList getPortActivityEventListeners();
	PortDefinitionEventListenerList getPortDefinitionEventListeners();


	/** A new eventmanager component */
	ContextEventManager() ;
	~ContextEventManager() ;


#if 0
  /** cca componentness */
  public void setServices(Services s);
#endif


#if 0
	virtual int CCAFE_start();

	virtual void CCAFE_finish()
#endif

  //////////////////////////////////////////////////////////////
  // ContextEventPublisherService multi-client port interface
  //////////////////////////////////////////////////////////////
  
  /** The event notice delivery function.
      @return 0 if ok, -1 if 
              eData alleges to be a standard event type but carries
              insufficient information to actually be that type.
   */
  int fireEvent( ContextEvent_shared eData);

  /** Create a non-specific event object. This is as close as we get
      to extensible.
      @param ceType enum value from ContextEventType interface.
      @param source The componentid of the component firing the event, or
             null if the generator is the framework itself.
      @param sourceKey user-defined key per ContextEvent interface.
      @return an ContextEvent that must then be destroyed by caller
              when finished.
   */
  ContextEvent_shared createContextEvent( enum ccafeopq::event::type::ContextEventType ceType, ccafeopq::ComponentID_shared source, int sourceKey) ;

   //// creation of context event instances.

  /** Make factory events. Factories are not themselves responsible for generating
      these events, though they may if they wish to.
      @param factoryID the factory component.
      @param factoryPortProperties the new factory port being announced.
      @param cet is one of FactoryPortAdded, FactoryPortRemovePending.
      @param source the component making the announcement.
      @param sourceKey emitter id within the component making the announcement.
    */
  ComponentFactoryEvent_shared createComponentFactoryEvent( ccafeopq::ComponentID_shared factoryID, ccafeopq::TypeMap_shared factoryPortProperties, enum ccafeopq::event::type::ContextEventType cet, ccafeopq::ComponentID_shared source, int sourceKey);

  /** Make instance request notice.  Note: event type is only: ComponentAddPending.
      @param componentClassName fully qualified class name of the component type desired.
             There is no requirement that this name match to a loaded class anywhere.
      @param componentInstanceName instance name of the component desired.
             There is no requirement that this name be 'available'.
      @param source the component making the announcement.
      @param sourceKey emitter id within the component making the announcement.
   */
  ComponentInstanceAddRequestEvent_shared createComponentInstanceAddRequestEvent( std::string & componentClassName, std::string & componentInstanceName, ccafeopq::ComponentID_shared source, int sourceKey);

  /** Make instance added notice.  Note: event type is only: ComponentAdded.
      @param componentClassName fully qualified class name of the component created.
      @param cid the instance added.
      @param source the component making the announcement.
      @param sourceKey emitter id within the component making the announcement.
   */
  ComponentInstanceAddedEvent_shared createComponentInstanceAddedEvent( std::string & componentClassName, ccafeopq::ComponentID_shared cid, ccafeopq::ComponentID_shared source, int sourceKey);

  /** Make instance going away soon notice.
      Note: event type is only: ComponentDeletePending.
      @param componentClassName fully qualified class name of the 
             component to be deleted.
      @param cid the instance to be deleted.
      @param source the component making the announcement.
      @param sourceKey emitter id within the component making the announcement.
   */
  ComponentInstanceDeleteRequestEvent_shared createComponentInstanceDeleteRequestEvent( std::string & componentClassName, ccafeopq::ComponentID_shared cid, ccafeopq::ComponentID_shared source, int sourceKey);

  /** Make instance gone away notice.  Note: event type is only: ComponentDeleted.
      @param deadComponentClassName fully qualified class name of the component deleted.
      @param deadComponentInstanceName the name of the instance deleted.
      @param source the component making the announcement.
      @param sourceKey emitter id within the component making the announcement.
   */
  ComponentInstanceDeletedEvent_shared createComponentInstanceDeletedEvent( std::string & deadComponentClassName, std::string & deadComponentInstanceName, ccafeopq::ComponentID_shared source, int sourceKey);

  /** Make ConnectionEvent in context notice.
      @param user the caller component.
      @param userPortName the caller port instance.
      @param userPortProperties the callers view of the port properties.
      @param provider the callee component.
      @param providerPortName the callee port instance.
      @param providerPortProperties the callees view of the port properties.
      @param cet is one of ConnectPending, Connected, DisconnectPending, Disconnected.
      @param source the component making the announcement.
      @param sourceKey emitter id within the component making the announcement.
   */
  ContextConnectionEvent_shared createContextConnectionEvent( ccafeopq::ComponentID_shared user, std::string & userPortName, ccafeopq::TypeMap_shared userPortProperties, ccafeopq::ComponentID_shared provider, std::string & providerPortName, ccafeopq::TypeMap_shared providerPortProperties, enum ccafeopq::event::type::ContextEventType cet, ccafeopq::ComponentID_shared source, int sourceKey);

  /** Make Port use activity notice from connid.
      @param connID the connection on which the activity is occuring.
      @param cet is one of PortFetchPending, PortFetched, PortReleasePending, PortReleased.
      @param source the component making the announcement.
      @param sourceKey emitter id within the component making the announcement.
   */
  PortActivityEvent_shared createPortActivityEvent( ccafeopq::ConnectionID_shared connID, std::string & portType, enum ccafeopq::event::type::ContextEventType cet, ccafeopq::ComponentID_shared source, int sourceKey);

  /** Make Port use activity notice with no connections.
      @param portName port being fetched.
      @param portType kind of port being fetched.
      @param cet is one of PortFetchPending, PortFetched, PortReleasePending, PortReleased.
      @param source the component making the announcement.  assumed to be user.
      @param sourceKey emitter id within the component making the announcement.
   */
  PortActivityEvent_shared createPortActivityEvent( std::string & portName, std::string & portType, enum ccafeopq::event::type::ContextEventType cet, ccafeopq::ComponentID_shared source, int sourceKey);

   /** Make Port definition event notice.
      @param component the component where the affected port (will)exist(ed).
      @param name the port instance name alleged.
      @param type the port type alleged.
      @param portProperties the user-supplied properties of the port, 
             which exist a little while before and after the port itself does
             (or maybe are null).
      @param cet is one of PortAddPending, PortAdded, PortRemovePending, PortRemoved,
             PortRegisterPending, PortRegistered, PortUnregisterPending, PortUnregistered.
      @param source the component making the announcement.
      @param sourceKey emitter id within the component making the announcement.
   */
  PortDefinitionEvent_shared createPortDefinitionEvent( ccafeopq::ComponentID_shared component, std::string & name, std::string & type, ccafeopq::TypeMap_shared portProperties, enum ccafeopq::event::type::ContextEventType cet, ccafeopq::ComponentID_shared source, int sourceKey);

  //////////////////////////////////////////////////////////////
  // end ContextEventPublisherService multi-client port interface
  //////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////
  // ContextEventSubscriberService multi-client port interface
  //////////////////////////////////////////////////////////////

  /** Sign up to be told about events matching ceType.
      For those who wish to receive specific events that require no
      casting to dig out the information, see the other addXXXXEventListener
      functions in this interface.
      @param l an object (this component or its delegate) that listens
             by implementing the ContextEventListener callback.
      @param ceType ALL will cause all valid event types to be received,
             and any other type will cause that other to be received.
             Events will be delivered in generic form and the recipient
             may need to cast if they want more specific information.
   */
  void addContextEventListener(ContextEventListener_shared l, enum ccafeopq::event::type::ContextEventType ceType);

  /** Ignore future Events.
      Removing a non-added listener is not an error. 
      @param l a previously added listener interface.
      @param ceType the same type that was given for addContextEventListener, usually.
             If you want to subscribe to all but one events for example, you could
             subscribe to ALL and then remove yourself from one type.
   */
  void removeContextEventListener( ContextEventListener_shared l, enum ccafeopq::event::type::ContextEventType ceType) ;

  /** Sign up to be told about events.
      @param l an object (this component or its delegate) that listens.
  */
  void addComponentFactoryEventListener( ComponentFactoryEventListener_shared l);

  /** Sign up to be told about events.
      @param l an object (this component or its delegate) that listens.
  */
  void addComponentInstanceAddRequestEventListener( ComponentInstanceAddRequestEventListener_shared l);

  /** Sign up to be told about events.
      @param l an object (this component or its delegate) that listens.
  */
  void addComponentInstanceAddedEventListener( ComponentInstanceAddedEventListener_shared l);

  /** Sign up to be told about events.
      @param l an object (this component or its delegate) that listens.
  */
  void addComponentInstanceDeleteRequestEventListener( ComponentInstanceDeleteRequestEventListener_shared l);

  /** Sign up to be told about events.
      @param l an object (this component or its delegate) that listens.
  */
  void addComponentInstanceDeletedEventListener( ComponentInstanceDeletedEventListener_shared l);

  /** Sign up to be told about events.
      @param l an object (this component or its delegate) that listens.
  */
  void addContextConnectionEventListener( ContextConnectionEventListener_shared l);

  /** Sign up to be told about events.
      @param l an object (this component or its delegate) that listens.
  */
  void addPortActivityEventListener( PortActivityEventListener_shared l);

  /** Sign up to be told about events.
      @param l an object (this component or its delegate) that listens.
  */
  void addPortDefinitionEventListener( PortDefinitionEventListener_shared l);

  /** Ignore future Events.
      Removing a non-added listener is not an error.
      @param l a previously added ComponentFactoryEventListener listener interface.
   */
  void removeComponentFactoryEventListener( ComponentFactoryEventListener_shared l);

  /** Ignore future Events.
      Removing a non-added listener is not an error.
      @param l a previously added ComponentInstanceAddRequestEventListener listener interface.
   */
  void removeComponentInstanceAddRequestEventListener( ComponentInstanceAddRequestEventListener_shared l);

  /** Ignore future Events.
      Removing a non-added listener is not an error.
      @param l a previously added ComponentInstanceAddedEventListener listener interface.
   */
  void removeComponentInstanceAddedEventListener( ComponentInstanceAddedEventListener_shared l);

  /** Ignore future Events.
      Removing a non-added listener is not an error.
      @param l a previously added ComponentInstanceDeleteRequestEventListener listener interface.
   */
  void removeComponentInstanceDeleteRequestEventListener( ComponentInstanceDeleteRequestEventListener_shared l);

  /** Ignore future Events.
      Removing a non-added listener is not an error.
      @param l a previously added ComponentInstanceDeletedEventListener listener interface.
   */
  void removeComponentInstanceDeletedEventListener( ComponentInstanceDeletedEventListener_shared l);

  /** Ignore future Events.
      Removing a non-added listener is not an error.
      @param l a previously added ContextConnectionEventListener listener interface.
   */
  void removeContextConnectionEventListener( ContextConnectionEventListener_shared l);

  /** Ignore future Events.
      Removing a non-added listener is not an error.
      @param l a previously added PortActivityEventListener listener interface.
   */
  void removePortActivityEventListener( PortActivityEventListener_shared l);

  /** Ignore future Events.
      Removing a non-added listener is not an error.
      @param l a previously added PortDefinitionEventListener listener interface.
   */
  void removePortDefinitionEventListener( PortDefinitionEventListener_shared l);

  /** Mapping function converting to standard string from the enumeration.
     The string result is identical to the enumerated names
     for events defined in this interface. E.g. FactoryClosed
     maps to  "FactoryClosed". Case is not significant but
     is provided for readability. 
  */
  const std::string getStringFromEnum( enum ccafeopq::event::type::ContextEventType ceType) ;

  /** Mapping function converting to enum from a string.
      This function is *not* case ContextEventType.sensitive, as we don't want
      standard events to be missed simply because of -key typos.
   */
  enum ccafeopq::event::type::ContextEventType getEnumFromString( const std::string & typeString) ;

  //////////////////////////////////////////////////////////////
  // end ContextEventSubscriberService multi-client port interface
  //////////////////////////////////////////////////////////////
  /** convert enum to string, or NONE if unknown. */
  static enum ccafeopq::event::type::ContextEventType enumFromString( const std::string & t);

  /** convert string to enum, or NONE if unknown. */
  static const std::string stringFromEnum( enum ccafeopq::event::type::ContextEventType ceType) ;

  //////////////////////////////////////////////////////////////////////
  //  CCAFE standard methods
  //////////////////////////////////////////////////////////////////////
#if 0 
  static void main(String[] args) {
    // test null-constructor and tostring methods.
    printMainClassTest(args); 
  }
#endif

}; // end class ContextEventManager


} ENDSEMI // namespace event
} ENDSEMI // namespace ccafeopq


#endif // ccafe_ContextEventManager
