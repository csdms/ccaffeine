#ifndef AllConnectionEvent_hh_seen
#define AllConnectionEvent_hh_seen

namespace ccafeopq {
	namespace ports {
		class ConnectionEventService;
	} ENDSEMI
	namespace connectionevents {

		class ConnectionEvent;
		class ConnectionEventListener;

		typedef boost::shared_ptr< ConnectionEvent > ConnectionEvent_shared;
		typedef boost::shared_ptr< ConnectionEventListener > ConnectionEventListener_shared;

		typedef std::vector <ConnectionEvent > ConnectionEventList;
		typedef std::vector <ConnectionEventListener > ConnectionEventListenerList;

	} ENDSEMI
} ENDSEMI

#include "dc/export/connectionevents/ConnectionEvent.hh"
#include "dc/export/connectionevents/ConnectionEventListener.hh"
#include "dc/export/connectionevents/ConnectionEventService.hh"
#endif // AllConnectionEvent_hh_seen
