#ifndef __DisconnectingConnectionEvent_h_seen__
#define __DisconnectingConnectionEvent_h_seen__

/** Event delivered to a connection listener before a connection is broken. */
class DisconnectingConnectionEvent 
: public virtual ccafeopq::connectionevents::ConnectionEvent
{

private:
	ccafeopq::PortInfo *pi; // delete me
	bool prechange;
	::ccafeopq::TypeMap_shared ctm;
	::std::string tpn;
	::std::string tpt;

public:
	DisconnectingConnectionEvent( UserPortData & upd);
	DisconnectingConnectionEvent( ProviderPortData & ppd);
	virtual ~DisconnectingConnectionEvent();
  
	/** True if the event is before change. */
	virtual bool preChange();
	virtual void setpreChange(bool pc);
  
	/** True if the event informs a connection. (never) */
	virtual int connected();

	/** True if the event informs a disconnection (always) */
	virtual int disconnected();
   
	virtual std::string getName();
	
	virtual std::string getType();

	/** properties of port */
	virtual ccafeopq::TypeMap_shared getProperties();

	/** properties of port for babel passthrough*/
	virtual void * getOpqTypeMapSharedPtrAddress();
  
};

#endif // __DisconnectingConnectionEvent_h_seen__
