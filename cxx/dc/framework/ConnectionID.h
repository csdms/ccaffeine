#ifndef dc_fwk_ConnectionID_h_seen
#define dc_fwk_ConnectionID_h_seen

#include <boost/shared_ptr.hpp>
#include <string>

class ConnectionID_impl;
class Gizzard;

typedef boost::shared_ptr< ConnectionID_impl > ConnectionID_ptr;

/**
Implementation of ccafeopq ConnectionID_Interface and
support for definition of ConnectionID_ptr.
*/
class ConnectionID_impl : public virtual ::ccafeopq::ConnectionID_Interface
{
private:
  bool dead;
  bool inUse;
  bool selfConnection;
  ::std::string pPortName;
  ::std::string uPortName;
  Gizzard *p;
  Gizzard *u;
  ::ccafeopq::TypeMap_shared tm;
  ::ccafeopq::Port *pp;

public:

  // set up a standard connection.
  ConnectionID_impl(Gizzard *provider, const ::std::string & providerPortName,
     Gizzard *user, const ::std::string & userPortName , ::ccafeopq::Port *pp_);

  // set up an internal connection.
  ConnectionID_impl(Gizzard *user, const ::std::string & userPortName,
     ::ccafeopq::Port *pp_);

  /** required destructor */
  virtual ~ConnectionID_impl();

  virtual ::ccafeopq::ComponentID_shared getProvider() throw ( ::ccafeopq::Exception );

  /** Recall that ComponentID is also a shared_ptr type.
     @throws a Exception if the underlying connection is no longer valid.
   */
  virtual ::ccafeopq::ComponentID_shared getUser() throw ( ::ccafeopq::Exception );

  virtual ::std::string getProviderPortName() throw ( ::ccafeopq::Exception );

  virtual ::std::string getUserPortName() throw ( ::ccafeopq::Exception );

  virtual bool isSameAs( ConnectionID_ptr cp);

  virtual bool isSameAs( ::ccafeopq::ConnectionID_shared & cp);

  /** Returns true if the connection is currently being used, i.e. the
      component has called getPort() but has not yet called
      releasePort(). */
  virtual int isActive();

  /** Is this connected to the framework internally? */
  virtual int isFrameworkConnection();

  virtual ::ccafeopq::TypeMap_shared getProperties();

  virtual void setProperties( ::ccafeopq::TypeMap_shared tm_);

  Gizzard *getProviderGizzard();

  Gizzard *getUserGizzard();

  ::ccafeopq::Port *getCachedPort();

  // return index of first in conns, or -1 if not found.
  static int indexOfConnection( const ::std::vector< ConnectionID_ptr > & conns,
                                   const ::std::string & upname,
                                   const ::std::string & ppname,
                                   Gizzard *userg, Gizzard * providerg);

  // return index of first in conns, or -1 if not found.
  static int indexOfConnection( const ::std::vector< ConnectionID_ptr > & conns,
                               ConnectionID_ptr c);

}; // end implementation of ComponentID_Interface

#endif // dc_fwk_ConnectionID_h_seen
