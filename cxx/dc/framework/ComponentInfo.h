#ifndef __COMPONENTINFO_H__
#define __COMPONENTINFO_H__
#include <string>
// class Gizzard;
//
namespace ccafe {
	class CmpBox;
} // end namespace ccafe fwd decl of cmpbox

class ComponentInfo;

typedef boost::shared_ptr< ComponentInfo > ComponentInfo_shared;

/** Miscellaneous component INSTANCE interfaces data container 
 * wrapper for legacy ui. 
 * The uis no longer have to deal with memory managing these,
 * as they are only available in shared form.
 */
class ComponentInfo {
 private:

  boost::shared_ptr< ::ccafe::CmpBox > box;

 public:

  ComponentInfo( boost::shared_ptr< ::ccafe::CmpBox > b);


  /** The class name from which this component was instantiated. */
  const std::string getClassName();

  virtual ~ComponentInfo();

  /** The instance name for the component.*/
  const std::string getInstanceName();

  /** Get the UsesPort information registry that this component would
      like to use. A vector of data. */
  const ::std::vector< UserPortData > & getUsesPortRegister();

  /** Get the ProvidesPort information that this component provides. 
      A vector of data. */
  const ::std::vector< ProviderPortData > & getProvidesPorts();

  ::std::vector< ConnectionID_ptr > getUsesConnections();


  /** Properties for this component */
  ::ccafeopq::TypeMap_shared getComponentPropertyTypeMap();

  /** Properties for this component */
  void setComponentPropertyTypeMap(::ccafeopq::TypeMap_shared tm);

  /** Properties for this component */
::ccafeopq::TypeMap_shared 
    getPortPropertyTypeMap(const std::string & portname);
  
  /** Properties for this component */
void setPortPropertyTypeMap(const std::string & portname, 
					   ::ccafeopq::TypeMap_shared tm);

  std::string toString();

  static ComponentInfo_shared wrapCmpBox( boost::shared_ptr< ::ccafe::CmpBox > b);

  static std::vector < ComponentInfo_shared > wrapCmpBoxVector( std::vector< ccafe::CmpBox_shared > & bvec);

  static std::map < std::string, ComponentInfo_shared > wrapCmpBoxMap( std::map< std::string, ccafe::CmpBox_shared > & bmap);

};

typedef boost::shared_ptr< ComponentInfo > ComponentInfo_shared;
#endif // __COMPONENTINFO_H__
