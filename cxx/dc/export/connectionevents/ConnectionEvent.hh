#ifndef __OPQConnectionEvent_H__
#define __OPQConnectionEvent_H__

namespace ccafeopq {
namespace connectionevents {

/**  ConnectionEvent event interface at the component instance scope. */
class ConnectionEvent {
 public:
  /** obligatory vdtor */
  virtual ~ConnectionEvent() {}

  /** True if event is posted about something about to happen, false if already happened. */
  virtual bool preChange() = 0;

  /** True if the event informs a connection. */
  virtual int connected() = 0;
  /** True if the event informs a disconnection */
  virtual int disconnected() = 0;

  /** name of port on instance. */
  virtual std::string getName() = 0;
  /** type/class of port on instance. */
  virtual std::string getType() = 0;
  /** properties of port */
  virtual ccafeopq::TypeMap_shared getProperties() = 0;

  virtual void * getOpqTypeMapSharedPtrAddress() = 0;
};

 } ENDSEMI // end namespace connectionevents
 } ENDSEMI // end namespace  ccafeopq
#endif // __OPQConnectionEvent_H__
