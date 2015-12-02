#ifndef __NEOConnectionID_HH__
#define __NEOConnectionID_HH__

class NeoConnectionID;

typedef boost::shared_ptr<NeoConnectionID> NeoConnectionID_shared;

/** Implementation of neo::cca::ConnectionID. */

class NeoConnectionID : public virtual neo::cca::ConnectionID {

private:

  ::ccafeopq::ConnectionID_shared cid;

public:

  virtual ~NeoConnectionID(){}

  /** the real constructor. */
  NeoConnectionID( ccafeopq::ConnectionID_shared cid_) ;

  /** dummy constructor for testing only. */
  NeoConnectionID( int bogon );

  /** the constructor we usually want. */
  static NeoConnectionID_shared neoWrap( ccafeopq::ConnectionID_shared cid_) ;

  static ::std::vector< neo::cca::ConnectionID_shared >convertToVector( std::vector< ::ccafeopq::ConnectionID_shared > & cids);



  /** Recall that ComponentID is also a shared_ptr type.
   */
  virtual neo::cca::ComponentID_shared getProvider() throw (neo::cca::Exception );

  /** Recall that ComponentID_shared is also a shared_ptr type.
     @throws a Exception if the underlying connection is no longer valid.
     */
  virtual neo::cca::ComponentID_shared getUser() throw (neo::cca::Exception ); 

  virtual std::string getProviderPortName() throw (neo::cca::Exception ); 

  virtual std::string getUserPortName() throw (neo::cca::Exception ); 


};

extern NeoConnectionID NeoConnectionID_test;

#endif // __NEOConnectionID_HH__
