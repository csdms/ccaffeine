#ifndef __BBLCONNECTIONEVENTLISTENER_H__
#define __BBLCONNECTIONEVENTLISTENER_H__

class BblConnectionEventListener
: public virtual ccafeopq::connectionevents::ConnectionEventListener
{
  
private:

  gov::cca::ports::EventType type;
  gov::cca::ports::ConnectionEventListener l;

public:
  BblConnectionEventListener(gov::cca::ports::EventType type_,
			       gov::cca::ports::ConnectionEventListener l_) {
    type = type_;
    l = l_;
  }
  virtual ~BblConnectionEventListener(){}

  virtual void connectionActivity( ccafeopq::connectionevents::ConnectionEvent_shared evt) {
    ::gov::cca::ports::EventType typ = gov::cca::ports::EventType_Error;
    if(evt->connected()) {
      typ = gov::cca::ports::EventType_Connected;
    } else if(evt->disconnected()) {
      typ = gov::cca::ports::EventType_Disconnected;
    }
    if(typ != type) {
      return;
    }
    
    // yes, this is the only way to tunnel shared pointers through babel
    // but it is possible.
    void * vp = 0;
    vp = evt->getOpqTypeMapSharedPtrAddress(); // fixme
    ::ccaffeine::TypeMap ctm = ccaffeine::TypeMap::_create();
    ctm.initialize(vp);

    ccaffeine::ports::ConnectionEvent bblEvt;
    bblEvt.initialize(typ, ctm);
    l.connectionActivity(bblEvt);
  }

};

#endif // __BBLCONNECTIONEVENTLISTENER_H__
