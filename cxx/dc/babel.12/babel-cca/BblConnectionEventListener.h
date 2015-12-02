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
#ifdef CCAFE_AUDIT
  IO_dn2("BblConnectionEventListener::CTOR %d", (int)type_);
#endif
  }
  virtual ~BblConnectionEventListener(){
#ifdef CCAFE_AUDIT
  IO_dn2("BblConnectionEventListener::DTOR %d", (int)type);
#endif
  }

  virtual void connectionActivity( ccafeopq::connectionevents::ConnectionEvent_shared evt) {
    ::gov::cca::ports::EventType typ = gov::cca::ports::EventType_Error;
    if(evt->connected()) {
      if (evt->preChange()) {
        typ = gov::cca::ports::EventType_ConnectPending;
      } else {
        typ = gov::cca::ports::EventType_Connected;
      }
    } else if(evt->disconnected()) {
      if (evt->preChange()) {
        typ = gov::cca::ports::EventType_DisconnectPending;
      } else {
        typ = gov::cca::ports::EventType_Disconnected;
      }
    }
    if (type != gov::cca::ports::EventType_ALL && typ != type) {
      return;
    }
    
    // yes, this is the only way to tunnel shared pointers through babel
    // but it is possible.
    void * vp = 0;
    vp = evt->getOpqTypeMapSharedPtrAddress(); // fixme
    ::ccaffeine::TypeMap ctm = ccaffeine::TypeMap::_create();
    ctm.initialize(vp);

#ifdef CCAFE_AUDIT
    IO_dn2("BblConnectionEventListener::activity %d", (int)typ);
#endif
    ccaffeine::ports::ConnectionEvent bblEvt = ccaffeine::ports::ConnectionEvent::_create();
    bblEvt.initialize(typ, ctm);
    l.connectionActivity(bblEvt);
  }

};

#endif // __BBLCONNECTIONEVENTLISTENER_H__
