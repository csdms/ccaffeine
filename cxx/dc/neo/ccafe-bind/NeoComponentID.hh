#ifndef __NEOCOMPONENTID_HH__
#define __NEOCOMPONENTID_HH__

class NeoComponentID;

typedef boost::shared_ptr<NeoComponentID> NeoComponentID_shared;

/** Implementation of neo::cca::ComponentID. */

class NeoComponentID : public virtual neo::cca::ComponentID {

private:

  ::ccafeopq::ComponentID_shared cid;

public:

  virtual ~NeoComponentID(){}

  /** the real constructor */
  NeoComponentID( ccafeopq::ComponentID_shared cid_) ;

  /** test constructor only for qc */
  NeoComponentID( int bogon) {} ;

  /** return the name. */
  virtual ::std::string getInstanceName() throw (neo::cca::Exception ) ;

  /** return a framework specific serialization. */
  virtual ::std::string getSerialization() throw (neo::cca::Exception ) ;

  /** ComponentID identity may not be testable
    * as a pointer comparison. All ids originate in the framework, however.
    **/
  virtual bool isSameAs( neo::cca::ComponentID_shared cid_);


  /** the constructor we usually want. */
  static NeoComponentID_shared neoWrap( ccafeopq::ComponentID_shared cid_) ;

  /** convert vector of ids */
  static ::std::vector< neo::cca::ComponentID_shared >convertToVector( std::vector< ::ccafeopq::ComponentID_shared > & cids);

};

extern NeoComponentID NeoComponentID_test;

#endif // __NEOCOMPONENTID_HH__
