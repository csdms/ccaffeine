#ifndef dc_fwk_UserPortData_h_seen
#define dc_fwk_UserPortData_h_seen

#include <vector>
#include <string>

/** a cpp logical to control whether we use
 * hand-coded copy constructor or the default.
 * this class is designed for the default to work,
 * but sometimes we want debugging code.
 */
#define UserPortData_USEEXPLICIT_COPYCTOR 0

/** container of provided port and all its related data.
 These should only exist inside the lists inside the gizzard,
 but they must follow stl copy semantics.
*/

class UserPortData 
{

private:
  // ::ccafeopq::Port *pp; on connectionid, not here.
  ::ccafeopq::TypeMap_shared tm;
  ::std::string name;
  ::std::string type;
  int serial;
  bool isActive;
  bool isSelfConnected;
  void shutdown();
  ::std::vector< ConnectionID_ptr >conns;

  friend class Gizzard;

public:

  UserPortData();
#if UserPortData_USEEXPLICIT_COPYCTOR
  UserPortData(const UserPortData & src);
#endif

  /** create a provides port record. the typemap pushed in
      must be already created, not just an empty shared ptr.
      serial must be a unique int.
   */
  UserPortData(const ::std::string & name_, const ::std::string & type_, ::ccafeopq::TypeMap_shared & tm_, int serial); 

  virtual ~UserPortData();

  /** return a *copy* of the typemap. */
  ::ccafeopq::TypeMap_shared getUserPortProperties();

  void setUserPortProperties( ::ccafeopq::TypeMap_shared tm_);

  ::std::string getPortName() const;
  ::std::string getPortType() const;
  bool getIsActive();
  bool getIsConnected();

  const ::std::vector< ConnectionID_ptr > & getConnectionIDs() const;

  ConnectionID_ptr addConnection(Gizzard *user, const ::std::string & uname, Gizzard *provider, const ::std::string & pname, ::ccafeopq::Port *p);

  ConnectionID_ptr addSelfConnection(Gizzard *user, const ::std::string & uname, ::ccafeopq::Port *p);

  /** return number of active connections broken in process */
  int removeConnection(ConnectionID_ptr & cp);
  /** return number of active connections broken in process */
  int removeConnections();

  int getNumberOfConnections();
  int getMaxConnections();
  int getMinConnections();

 // convenience methods...

  // updates isActive.
  ::ccafeopq::Port *getProvided();
  void releaseProvided();

  ::std::vector< ::ccafeopq::Port * > getAllProvided();
  void releaseAllProvided();

  ::std::string toString() const;

  static void initDefaultProperties( ::ccafeopq::TypeMap_shared t,
		 const std::string &name, const std::string & type );

};

#endif // dc_fwk_UserPortData_h_seen
