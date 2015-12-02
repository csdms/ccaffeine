#ifndef __OPQConnectionEventListener_H__
#define __OPQConnectionEventListener_H__

namespace ccafeopq {
namespace connectionevents {

/**  The interface listeners must implement 
  to receive ConnectionEvents. */
class ConnectionEventListener {
 public:
  /** obligatory vdtor */
  virtual ~ConnectionEventListener() {}
  /** Connection event hook a component may supply.
      Any action by the component on its Services is
      allowed during the connection activity, including
      getting, using, releasing, and unregistering a uses port. */
  virtual void connectionActivity(ConnectionEvent_shared evt) = 0;
};


  } ENDSEMI // end namespace connectionevents
} ENDSEMI // end namespace ccafeopq

#endif // __OPQConnectionEventListener_H__
