#ifndef dc_fwk_ComponentID_h_seen
#define dc_fwk_ComponentID_h_seen

#include <boost/shared_ptr.hpp>
#include <string>

class ComponentID_impl : public virtual ccafeopq::ComponentID_Interface
{
private:
  ::std::string instanceName;
  ::std::string serialization;
  bool dead;

public:
  ComponentID_impl(const ::std::string & instanceName, const ::std::string & serialized);

  /** required destructor */
  virtual ~ComponentID_impl();

  /** The ComponentID binding wrapper will receive the exception type
   * and message if an exception should be thrown. Status 0 on returns
   * means everything is ok and message will not have been changed.
   * The binding may do with this information what it pleases.
   */
  virtual const ::std::string getInstanceName() throw ( ::ccafeopq::Exception) ;


  virtual const ::std::string getSerialization() throw ( ::ccafeopq::Exception) ;

  /** ComponentID identity may not be testable
   * as a pointer comparison. All ids originate in the kernel, however. */
  virtual bool isSameAs( ::ccafeopq::ComponentID_shared & cid) ;

}; // end implementation of ComponentID_Interface

typedef boost::shared_ptr<ComponentID_impl> ComponentID; // FIXME

#endif // dc_fwk_ComponentID_h_seen
