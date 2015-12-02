#ifndef CCAFE_OPQBS_H_SEEN
#define CCAFE_OPQBS_H_SEEN

class DefaultBuilderModel;
class ConnectionFramework;
class CmdLineBuilderView;

//===================================================================

/**
 * This is a very gross implementation of builderservice
 * internally, due to the messy confusion of buildermodel
 * and connectionfwk classes and builderview expectations.
 * But it works, and it doesn't surprise the gui user by
 * failing to print messages that make the gui work.
 *
 * It will throw exceptions liberally if it gets into a tight
 * spot, like destroying an instance that something else is
 * still connected to.
 *
 * This should be redone, but only when we have had the
 * time to make a full event model that the builderview
 * can subscribe to. Of course that exists in the new java
 * framework w/gcj, but will have to be back-ported
 * for non-gcj platforms.
 *
 */
class OpqBuilderService : public virtual ::ccafeopq::BuilderService, 
public virtual KernelPort
#ifdef HAVE_CLASSIC
, public virtual ::classic::gov::cca::Port
#endif // HAVE_CLASSIC
{

private:

  ::std::map<std::string, void *> * frame;

  // A null builderview
  CmdLineBuilderView * nullBV;

  // Utility methods to retrieve model, framework, and/or, view
  DefaultBuilderModel * getDefaultBuilderModel();
  CmdLineBuilderView * getCmdLineBuilderView();
  ConnectionFramework * getConnectionFramework();

public:
  OpqBuilderService();
  virtual ~OpqBuilderService();

  // opaque builderservice ness
  /** The ComponentID can be dropped on the floor if desired;
   * that won't cause the component instance to stop existing.
   */
  virtual ::ccafeopq::ComponentID_shared createInstance(const ::std::string & instanceName, const ::std::string & className, ::ccafeopq::TypeMap_shared & properties) throw ( ::ccafeopq::Exception ); 

  /** Memory lifecycle:
   * The vector is returned on the stack and when it goes out of scope,
   * all the ComponentID take care of themselves.
   */
  virtual ::std::vector< ::ccafeopq::ComponentID_shared > getComponentIDs() throw (::ccafeopq::Exception ); 

  /** 
   * Memory Lifecycle:
   * The info is returned on the stack and takes care of itself
   * per shared_ptr.
  */
  virtual ::ccafeopq::TypeMap_shared getComponentProperties( ::ccafeopq::ComponentID_shared & cid) throw (::ccafeopq::Exception );

  /**
   */
  virtual void setComponentProperties( ::ccafeopq::ComponentID_shared & cid,  ::ccafeopq::TypeMap_shared & map) throw (::ccafeopq::Exception );

  /** 
   * Memory Lifecycle:
   * The id is returned on the stack and takes care of itself
   * per shared_ptr.
  */
  virtual ::ccafeopq::ComponentID_shared getDeserialization( const ::std::string & s) throw (::ccafeopq::Exception );

  /**
   * Memory Lifecycle:
   * The id is returned on the stack and takes care of itself
   * per shared_ptr.
  */
  virtual ::ccafeopq::ComponentID_shared getComponentID( const ::std::string & componentInstanceName) throw (::ccafeopq::Exception );

   /** 
    */
  virtual void destroyInstance( ::ccafeopq::ComponentID_shared & toDie,  float timeout ) throw (::ccafeopq::Exception );

   /** 
    */
  virtual ::std::vector< ::std::string > getProvidedPortNames( ::ccafeopq::ComponentID_shared & cid) throw (::ccafeopq::Exception ); 

   /** 
    */
  virtual ::std::vector< ::std::string > getUsedPortNames( ::ccafeopq::ComponentID_shared & cid) throw (::ccafeopq::Exception ); 

  /**
   */
  virtual ::ccafeopq::TypeMap_shared getPortProperties( ::ccafeopq::ComponentID_shared & cid, const ::std::string & portname) throw (::ccafeopq::Exception );

  /**
  */
  virtual void setPortProperties( ::ccafeopq::ComponentID_shared & cid, const ::std::string & portname,  ::ccafeopq::TypeMap_shared & map) throw (::ccafeopq::Exception );

  /**
  */
  virtual ::ccafeopq::ConnectionID_shared connect( ::ccafeopq::ComponentID_shared & user, const ::std::string & usingPortName,  ::ccafeopq::ComponentID_shared & provider, const ::std::string & providingPortName) throw (::ccafeopq::Exception ); 

  /**
   */
  virtual ::std::vector < ::ccafeopq::ConnectionID_shared > getConnectionIDs( ::std::vector< ::ccafeopq::ComponentID_shared > & componentList) throw (::ccafeopq::Exception ); 

  virtual ::std::vector < ::ccafeopq::ConnectionID_shared > getConnectionIDs(  const ::std::string & userName, const ::std::string & usingPortName,  const ::std::string & providerName, const ::std::string & providingPortName) throw (::ccafeopq::Exception );

  /**
    */
  virtual ::ccafeopq::TypeMap_shared getConnectionProperties( ::ccafeopq::ConnectionID_shared & connID) throw (::ccafeopq::Exception );

  /**
  */
  virtual void setConnectionProperties( ::ccafeopq::ConnectionID_shared & connID,  ::ccafeopq::TypeMap_shared & map) throw (::ccafeopq::Exception );

  /** 
  */
  virtual void disconnect( ::ccafeopq::ConnectionID_shared & connID,  float timeout) throw (::ccafeopq::Exception ); 

  /**
  */
  virtual void disconnectAll( ::ccafeopq::ComponentID_shared & id1,  ::ccafeopq::ComponentID_shared & id2,  float timeout) throw (::ccafeopq::Exception ); 

  std::vector< ::ccafeopq::ComponentID_shared > 
    getComponentsThatUse(const std::string& portType);

  std::vector< ::ccafeopq::ComponentID_shared > 
    getComponentsThatProvide(const std::string& portType);

  virtual void appendRepositoryPath ( const ::std::string& dirPathElement );

  virtual void loadRepositoryClass (const ::std::string& className, bool loadGlobal, bool loadLazy );


  void setFrameData( std::map<std::string, void *> *v);
} ; // end interface BuilderService

#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr< OpqBuilderService * > OpqBuilderService_ptr;

#endif //CCAFE_OPQBS_H_SEEN
