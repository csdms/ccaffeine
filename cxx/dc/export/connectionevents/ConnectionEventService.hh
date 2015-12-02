#ifndef __OPQConnectionEventService_H__
#define __OPQConnectionEventService_H__


namespace ccafeopq {
namespace ports {

/** ConnectionEvent Service Interface. Should be
 * able to get and use one of these from the Services implementation
 * during a setServices call. 
 * <p>The CCAT Event Bus model could conceivably be used to implement
 * this, but this interface and its subsidiaries place much smaller
 * burden on the framework writer. Further, with an asynchronous
 * bus delivery mechanism it may be harder to guarantee the
 * event order condition on the DisconnectingConnectionEvent.
 * </p>
 * <p>From the CCAT event page:
 *  A publisher can send events directly to listeners
 *  without an intervening event channel.  The ports can
 *  simply be connected together. This is an instance
 *  of a 1-to-n uses-to-provides connection, which is
 *  permitted by the CCA specification.  Connecting multiple
 *  providers is also possible. The CCA specification
 *  allows general m-to-n connections between m uses ports
 *  and n provides ports.</p>
 * <p>We note that while possibly allowing it, the specification
 * does not require or (presently, 8/2000) provide a standard way to
 * allow MxN Port connections.</p>
 *
 * Extended to support ConnectPending and Disconnected per cca.sidl, 3/2009.
 */
class ConnectionEventService : public virtual ccafeopq::Port 
{
 private:
 public:
  /** obligatory vdtor */
  virtual ~ConnectionEventService() {}

  /** Register l as interested in post-notification of connections */
  virtual void addConnectEventListener(ccafeopq::connectionevents::ConnectionEventListener_shared l) = 0;

  /** Register l as interested in pre-notification of disconnections.
   * @see www.extreme.indiana.edu/ccat/event_service.html
   */
  virtual void addDisconnectEventListener(ccafeopq::connectionevents::ConnectionEventListener_shared  l) = 0;

  /** Remove l as interested in post-notification of connections */
  virtual void removeConnectEventListener(ccafeopq::connectionevents::ConnectionEventListener_shared l) = 0;

  /** Remove l as interested in pre-notification of disconnections */
  virtual void removeDisconnectEventListener(ccafeopq::connectionevents::ConnectionEventListener_shared l) = 0;
};

  } ENDSEMI // end namespace ports
} ENDSEMI // end namespace ccafeopq

#endif // __OPQConnectionEventService_H__
