#ifndef __OpqConnectionEventService_H__
#define __OpqConnectionEventService_H__

#include <map>
#include <string>
#include <vector>

/** CCAFFEINE opq implementation of the connectionevent  spec */
class OpqConnectionEventService : 
                public virtual ccafeopq::ports::ConnectionEventService,
		public virtual KernelPort
{

	int serial;
	int nextSerial();

private:
	/** listeners signed up to hear after connections are made. */
	::std::vector< ::ccafeopq::connectionevents::ConnectionEventListener_shared > connectListeners;

	/** listeners signed up to hear before connections are broken. */
	::std::vector< ::ccafeopq::connectionevents::ConnectionEventListener_shared > disconnectListeners;

public:

	OpqConnectionEventService();
	virtual ~OpqConnectionEventService();

	virtual void addConnectEventListener(ccafeopq::connectionevents::ConnectionEventListener_shared l) ;

	virtual void addDisconnectEventListener(ccafeopq::connectionevents::ConnectionEventListener_shared l) ;

	virtual void removeConnectEventListener(ccafeopq::connectionevents::ConnectionEventListener_shared l);

	virtual void removeDisconnectEventListener(ccafeopq::connectionevents::ConnectionEventListener_shared l) ;

	virtual void fireConnectEvent(ccafeopq::connectionevents::ConnectionEvent_shared evt) ;

	virtual void fireDisconnectEvent(ccafeopq::connectionevents::ConnectionEvent_shared evt) ;

};

#endif //__OpqConnectionEventService_H__
