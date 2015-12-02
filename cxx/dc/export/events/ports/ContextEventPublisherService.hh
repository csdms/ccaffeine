/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__Ports_ContextEventPublisherService_H__
#define __ccafeopq__Ports_ContextEventPublisherService_H__

namespace ccafeopq {
namespace ports {


/** A message service to alert listeners when peer component
    activities within CCA purview occur. Used to generate and
    publish events.
    This service is to be 
    immediately available during a setServices call. This service 
    interface is compatible with a direct-connected or proxy framework.
*/

class ContextEventPublisherService  : public virtual ::ccafeopq::Port
{
public:
  /** obligatory virtual destructor */
  virtual ~ContextEventPublisherService() {}


  /** The event notice deliver function.
      @return 0 if ok, -1 if
              eData alleges to be a standard event type but carries
              insufficient information to actually be that type.
   */
  virtual int fireEvent( ccafeopq::event::ContextEvent_shared  eData) = 0; 

  /** Create a non-specific event object. This is as close as we get
      to extensible.
      @param ceType int value from ContextEventType interface.
      @param source The componentid of the component firing the event, or
             null if the generator is the framework itself.
      @param sourceKey user-defined key per ContextEvent_sharedinterface.
      @return an ContextEvent_sharedthat must then be destroyed by caller
              when finished.
   */
  virtual ccafeopq::event::ContextEvent_shared createContextEvent( enum ccafeopq::event::type::ContextEventType ceType,  ::ccafeopq::ComponentID_shared  source,  int sourceKey) = 0; 

   //// creation of context event instances.

  /** Make factory events. Factories are not themselves responsible for generating
      these events, though they may if they wish to.
      @param factoryID the factory component.
      @param factoryPortProperties the new factory port being announced.
      @param cet is one of FactoryPortAdded, FactoryPortRemovePending.
      @param source the component making the announcement.
      @param sourceKey emitter id within the component making the announcement.
    */
  virtual ccafeopq::event::ComponentFactoryEvent_shared createComponentFactoryEvent( ::ccafeopq::ComponentID_shared factoryID,  ::ccafeopq::TypeMap_shared factoryPortProperties,  enum ccafeopq::event::type::ContextEventType cet,  ::ccafeopq::ComponentID_shared source,  int sourceKey) = 0;

  /** Make instance request notice.  Note: event type is only: ComponentAddPending.
      @param componentClassName fully qualified class name of the component type desired.
             There is no requirement that this name match to a loaded class anywhere.
      @param componentInstanceName instance name of the component desired.
             There is no requirement that this name be 'available'.
      @param source the component making the announcement.
      @param sourceKey emitter id within the component making the announcement.
   */
  virtual ccafeopq::event::ComponentInstanceAddRequestEvent_shared createComponentInstanceAddRequestEvent( std::string & componentClassName,  std::string & componentInstanceName,  ::ccafeopq::ComponentID_shared source,  int sourceKey) = 0;

  /** Make instance added notice.  NOTE- event type is only ComponentAdded.
      @param componentClassName fully qualified class name of the component created.
      @param cid the instance added.
      @param source the component making the announcement.
      @param sourceKey emitter id within the component making the announcement.
   */
  virtual ccafeopq::event::ComponentInstanceAddedEvent_shared createComponentInstanceAddedEvent( std::string & componentClassName,  ::ccafeopq::ComponentID_shared cid,  ::ccafeopq::ComponentID_shared source,  int sourceKey) = 0;

  /** Make instance going away soon notice.
      Note: event type is only: ComponentDeletePending.
      @param componentClassName fully qualified class name of the component 
             to be deleted.
      @param cid the instance to be deleted.
      @param source the component making the announcement.
      @param sourceKey emitter id within the component making the announcement.
   */
  virtual ccafeopq::event::ComponentInstanceDeleteRequestEvent_shared createComponentInstanceDeleteRequestEvent( std::string & componentClassName,  ::ccafeopq::ComponentID_shared cid,  ::ccafeopq::ComponentID_shared source,  int sourceKey) = 0;

  /** Make instance gone away notice.  Note: event type is only: ComponentDeleted.
      @param deadComponentClassName fully qualified class name of the component deleted.
      @param deadComponentInstanceName the name of the instance deleted.
      @param source the component making the announcement.
      @param sourceKey emitter id within the component making the announcement.
   */
  virtual ccafeopq::event::ComponentInstanceDeletedEvent_shared createComponentInstanceDeletedEvent( std::string & deadComponentClassName,  std::string & deadComponentInstanceName,  ::ccafeopq::ComponentID_shared source,  int sourceKey) = 0;

  /** Make ConnectionEvent_sharedin context notice.
      @param user the caller component.
      @param userPortName the caller port.
      @param userPortProperties the callers view of the port properties,
             possibly null.
      @param provider the callee component.
      @param providerPortName the callee port.
      @param providerPortProperties the callees view of the port properties,
             possibly null.
      @param cet is one of ConnectPending, Connected, DisconnectPending, Disconnected.
      @param source the component making the announcement.
      @param sourceKey emitter id within the component making the announcement.
   */
  virtual ccafeopq::event::ContextConnectionEvent_shared createContextConnectionEvent( ::ccafeopq::ComponentID_shared user,  std::string & userPortName,  ::ccafeopq::TypeMap_shared userPortProperties,  ::ccafeopq::ComponentID_shared provider,  std::string & providerPortName,  ::ccafeopq::TypeMap_shared providerPortProperties,  enum ccafeopq::event::type::ContextEventType cet,  ::ccafeopq::ComponentID_shared source,  int sourceKey) = 0;

  /** Make Port use activity notice for connected port.
      @param connID the connection on which the activity is occuring.
      @param portType the port class name.
      @param cet is one of PortFetchPending, PortFetched, PortReleasePending, PortReleased.
      @param source the component making the announcement.
      @param sourceKey emitter id within the component making the announcement.
   */
  virtual ccafeopq::event::PortActivityEvent_shared createPortActivityEvent( ccafeopq::ConnectionID_shared connID,  std::string & portType,  enum ccafeopq::event::type::ContextEventType cet,  ::ccafeopq::ComponentID_shared source,  int sourceKey) = 0;

  /** Make Port use activity notice where no connection is available.
      @param portName port being fetched.
      @param portType kind of port being fetched.
      @param cet is one of PortFetchPending, PortFetched, PortReleasePending, PortReleased.
      @param source the component making the announcement. assumed to be user.
      @param sourceKey emitter id within the component making the announcement.
   */
  virtual ccafeopq::event::PortActivityEvent_shared createPortActivityEvent( std::string & portName,  std::string & portType,  enum ccafeopq::event::type::ContextEventType cet,  ::ccafeopq::ComponentID_shared source,  int sourceKey) = 0;

   /** Make Port definition event notice.
      @param component the component where the affected port (will)exist(ed).
      @param portName port instance name in component scope.
      @param portType port class name in component scope.
      @param portProperties the user-supplied properties of the port,
             which exist a little while before and after the port itself 
             does (and may be null).
      @param cet is one of PortAddPending, PortAdded,
             PortRemovePending, PortRemoved,
             PortRegisterPending, PortRegistered,
             PortUnregisterPending, PortUnregistered.
      @param source the component making the announcement.
      @param sourceKey emitter id within the component making the announcement.
   */
  virtual ccafeopq::event::PortDefinitionEvent_shared createPortDefinitionEvent( ::ccafeopq::ComponentID_shared component,  std::string & portName,  std::string & portType,  ::ccafeopq::TypeMap_shared portProperties,  enum ccafeopq::event::type::ContextEventType cet,  ::ccafeopq::ComponentID_shared source,  int sourceKey) = 0;


} ; // end interface ContextEventPublisherService

} ENDSEMI // end ports namespace
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/ports/ContextEventPublisherService.hh,v 1.3 2004/04/25 00:52:48 baallan Exp $ */

#endif // __ccafeopq__Ports_ContextEventPublisherService_H__
