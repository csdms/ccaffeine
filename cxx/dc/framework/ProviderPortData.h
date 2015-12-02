#ifndef dc_fwk_ProviderPortData_h_seen
#define dc_fwk_ProviderPortData_h_seen

#include <vector>
#include <string>

/** a cpp logical to control whether we use
 * hand-coded copy constructor or the default.
 * this class is designed for the default to work,
 * but sometimes we want debugging code.
 */
#define ProviderPortData_USEEXPLICIT_COPYCTOR 0



/** container of provided port and all its related data.
 These should only exist inside the lists inside the gizzard,
 but they must follow stl copy semantics.
 */

class ProviderPortData 
{

private:
  ::ccafeopq::Port *pp;
  ::ccafeopq::TypeMap_shared tm;
  ::std::string name;
  ::std::string type;
  int serial;
  int numberOfUsers;


friend class Gizzard;

  ::ccafeopq::Port *getPortInterface();
  void releasePortInterface();
  void shutdown();

public:

  /** do not use, except for empty placeholder values in containers. */
  ProviderPortData(); 
#if ProviderPortData_USEEXPLICIT_COPYCTOR
  ProviderPortData(const ProviderPortData &src); 
#endif


  /** create a provides port record. the typemap pushed in
      must be already created, (and passed through
      initDefaultProperties) not just be an empty shared ptr.
      serial must be a unique int. tm_ is kept internally.
   */
  ProviderPortData( ::ccafeopq::Port *p, const ::std::string & name_, const ::std::string & type_, ::ccafeopq::TypeMap_shared & tm_, int serial); 
  virtual ~ProviderPortData();

  ::ccafeopq::TypeMap_shared getProviderPortProperties();
  void setProviderPortProperties( ::ccafeopq::TypeMap_shared tm_);

  ::std::string getPortName() const;
  ::std::string getPortType() const;
  int getMaxConnections();
  int getMinConnections();
  int getNumberOfUsers();

  static void initDefaultProperties( ::ccafeopq::TypeMap_shared t,
                   const std::string &name, const std::string & type );


  ::std::string toString() const;

};

#endif // dc_fwk_ProviderPortData_h_seen
