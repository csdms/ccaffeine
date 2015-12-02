#ifndef ccafeopq_events_seen
#define ccafeopq_events_seen
namespace ccafeopq {
namespace event {

class ContextEvent;
class ContextEventListener;
class ComponentFactoryEvent;
class ComponentFactoryEventListener;
class ComponentInstanceAddedEvent;
class ComponentInstanceAddedEventListener;
class ComponentInstanceAddRequestEvent;
class ComponentInstanceAddRequestEventListener;
class ComponentInstanceDeletedEvent;
class ComponentInstanceDeletedEventListener;
class ComponentInstanceDeleteRequestEvent;
class ComponentInstanceDeleteRequestEventListener;
class ContextConnectionEvent;
class ContextConnectionEventListener;
class PortActivityEvent;
class PortActivityEventListener;
class PortDefinitionEvent;
class PortDefinitionEventListener;

typedef boost::shared_ptr< ContextEvent > ContextEvent_shared;
typedef boost::shared_ptr< ContextEventListener > ContextEventListener_shared;
typedef boost::shared_ptr< ComponentFactoryEvent > ComponentFactoryEvent_shared;
typedef boost::shared_ptr< ComponentFactoryEventListener > ComponentFactoryEventListener_shared;
typedef boost::shared_ptr< ComponentInstanceAddedEvent > ComponentInstanceAddedEvent_shared;
typedef boost::shared_ptr< ComponentInstanceAddedEventListener > ComponentInstanceAddedEventListener_shared;
typedef boost::shared_ptr< ComponentInstanceAddRequestEvent > ComponentInstanceAddRequestEvent_shared;
typedef boost::shared_ptr< ComponentInstanceAddRequestEventListener > ComponentInstanceAddRequestEventListener_shared;
typedef boost::shared_ptr< ComponentInstanceDeletedEvent > ComponentInstanceDeletedEvent_shared;
typedef boost::shared_ptr< ComponentInstanceDeletedEventListener > ComponentInstanceDeletedEventListener_shared;
typedef boost::shared_ptr< ComponentInstanceDeleteRequestEvent > ComponentInstanceDeleteRequestEvent_shared;
typedef boost::shared_ptr< ComponentInstanceDeleteRequestEventListener > ComponentInstanceDeleteRequestEventListener_shared;
typedef boost::shared_ptr< ContextConnectionEvent > ContextConnectionEvent_shared;
typedef boost::shared_ptr< ContextConnectionEventListener > ContextConnectionEventListener_shared;
typedef boost::shared_ptr< PortActivityEvent > PortActivityEvent_shared;
typedef boost::shared_ptr< PortActivityEventListener > PortActivityEventListener_shared;
typedef boost::shared_ptr< PortDefinitionEvent > PortDefinitionEvent_shared;
typedef boost::shared_ptr< PortDefinitionEventListener > PortDefinitionEventListener_shared;

// listener lists
typedef std::vector <ComponentFactoryEventListener_shared > ComponentFactoryEventListenerList;

typedef std::vector <ComponentInstanceAddedEventListener_shared > ComponentInstanceAddedEventListenerList;

typedef std::vector <ComponentInstanceAddRequestEventListener_shared > ComponentInstanceAddRequestEventListenerList;

typedef std::vector <ComponentInstanceDeletedEventListener_shared > ComponentInstanceDeletedEventListenerList;

typedef std::vector <ComponentInstanceDeleteRequestEventListener_shared > ComponentInstanceDeleteRequestEventListenerList;

typedef std::vector <ContextConnectionEventListener_shared > ContextConnectionEventListenerList;

typedef std::vector <ContextEventListener_shared > ContextEventListenerList;

typedef std::vector <PortActivityEventListener_shared > PortActivityEventListenerList;

typedef std::vector <PortDefinitionEventListener_shared > PortDefinitionEventListenerList;


} ENDSEMI
} ENDSEMI

#include "dc/export/events/apis/ContextEventType.hh"
#include "dc/export/events/apis/ContextEvent.hh"

#include "dc/export/events/apis/ComponentFactoryEvent.hh"
#include "dc/export/events/apis/ComponentFactoryEventListener.hh"
#include "dc/export/events/apis/ComponentInstanceAddedEvent.hh"
#include "dc/export/events/apis/ComponentInstanceAddedEventListener.hh"
#include "dc/export/events/apis/ComponentInstanceAddRequestEvent.hh"
#include "dc/export/events/apis/ComponentInstanceAddRequestEventListener.hh"
#include "dc/export/events/apis/ComponentInstanceDeletedEvent.hh"
#include "dc/export/events/apis/ComponentInstanceDeletedEventListener.hh"
#include "dc/export/events/apis/ComponentInstanceDeleteRequestEvent.hh"
#include "dc/export/events/apis/ComponentInstanceDeleteRequestEventListener.hh"
#include "dc/export/events/apis/ContextConnectionEvent.hh"
#include "dc/export/events/apis/ContextConnectionEventListener.hh"
#include "dc/export/events/apis/ContextEventListener.hh"
#include "dc/export/events/apis/PortActivityEvent.hh"
#include "dc/export/events/apis/PortActivityEventListener.hh"
#include "dc/export/events/apis/PortDefinitionEvent.hh"
#include "dc/export/events/apis/PortDefinitionEventListener.hh"


#include "dc/export/events/ports/ContextEventPublisherService.hh"
#include "dc/export/events/ports/ContextEventSubscriberService.hh"

namespace ccafeopq {
namespace connectionevent {

} ENDSEMI
} ENDSEMI

#include "dc/export/connectionevents/AllConnectionEvent.hh"

#endif // ccafeopq_events_seen
