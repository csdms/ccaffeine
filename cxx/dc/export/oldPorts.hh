#ifndef opaque_oldports_h_seen
#define opaque_oldports_h_seen

/** This is a file wherein we make opaque versions of
 * some services from old ccaffeine that are more
 * sane to babelify than babelifying the old stuff directly.
 *
 * To Wit:
 * 1
 * KeyValuePort (seldom used except by fwk+gui)
 * is not exported directly but instead we go ahead with
 * using: ComponentPropertiesService as as previously
 * negotiated on the forum mailing list.
 *
 * 2
 * ConfigurableParameterPortFactory/ParameterPort, etc.
 * become much more simple ParameterPortFactory
 *
 * 3
 * Components wishing to expose one or more property
 * sets directly to other components can do so by 
 * providing the ConfigurableComponentPort
 */
namespace ccafeopq {


/** This interface allows the component to get at its own
 * framework-manage properties. It's a simplification on
 * BuilderService.
 */
class ComponentPropertiesService : public virtual Port 
{

public:
    /** required destructor */
    virtual ~ComponentPropertiesService(){}

   
   /** @return the framework maintained properties of the
	component.
    */
   virtual TypeMap_shared getProperties() = 0;

   /** merge in the data from tm to the existing properties
	for the component. Attempts to change protected values
	are silently ignored.
    */
   virtual void mergeProperties( TypeMap_shared tm) throw (Exception ) = 0;

   /** cause the key/value pairs for the list of keys given
	to be removed from among the component properties.
	@throw If there is an attempt to remove protected properties.
    */ 
   virtual void removeProperties( ::std::vector< ::std::string > & keys) throw (Exception ) = 0;

} ; // end interface ComponentPropertiesService

} ENDSEMI // end namespace ccafeopq
#endif // opaque_oldports_h_seen
