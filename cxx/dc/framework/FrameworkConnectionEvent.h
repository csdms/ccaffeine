#ifndef __FrameworkConnectionEvent_H__
#define __FrameworkConnectionEvent_H__
#ifdef HAVE_CLASSIC
/** default implementation of ConnectionEvent.
 * needs to be redone with opaque context events anyway.
Inadequate in that it doesn't specify pre or post delivery. */
class FrameworkConnectionEvent 
: public virtual classic::gov::cca::ConnectionEvent
{
 private:

  bool tf;
  classic::gov::cca::PortInfo* pi;

 public:
  /** connected == true for a connection event, == false for
      disconnection; pi refers to the affected Port. */
  FrameworkConnectionEvent(bool connected_, classic::gov::cca::PortInfo* pi_) {
    tf = connected_;
    pi = pi_;
  }

  /** True if the event informs a connection. */
  virtual int connected() {
    return tf;
  }
  /** True if the event informs a disconnection */
  virtual int disconnected() {
    return !tf;
  }
  /** Get the PortInfo of the affected Port. */
  virtual classic::gov::cca::PortInfo* getPortInfo() {
    return pi;
  }
};

#endif // HAVE_CLASSIC
#endif // __FrameworkConnectionEvent_H__
