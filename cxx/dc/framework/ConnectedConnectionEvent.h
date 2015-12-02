#ifndef __ConnectedConnectionEvent_h_seen__
#define __ConnectedConnectionEvent_h_seen__
/** Event delivered after a new connection has been made. */
class ConnectedConnectionEvent 
: public virtual ccafeopq::connectionevents::ConnectionEvent
{

private:
	// ::ccafeopq::PortInfo *pi;
	::ccafeopq::TypeMap_shared ctm;
	bool prechange;
	::std::string tpn;
	::std::string tpt;

public:
	ConnectedConnectionEvent( UserPortData & upd);
	ConnectedConnectionEvent( ProviderPortData & ppd);
	virtual ~ConnectedConnectionEvent();
  
	/** True if the event is before change. */
	virtual bool preChange();
	virtual void setpreChange(bool pc);
  
	/** True if the event informs a connection. (always) */
	virtual int connected();
  
	/** True if the event informs a disconnection (never) */
	virtual int disconnected();
  
	virtual std::string getName();
	
	virtual std::string getType();

	/** properties of port */
	virtual ccafeopq::TypeMap_shared getProperties();

	/** properties of port for babel passthrough*/
	virtual void * getOpqTypeMapSharedPtrAddress();
  
};
#endif // __ConnectedConnectionEvent_h_seen__

