
#ifndef staticfactory_h_seen
#define staticfactory_h_seen

/** StaticFactory stub for static linking classic
 * components into the legacy component factory stuff,
 * since classic doesn't include builderservice/componentRepository
 * features in its design.
 *
 * The framework may be handed an instance or instances of this 
 * to inform it of the component classes that were static linked
 * and their constructors.
 */
class StaticFactory {
public:
	virtual ~StaticFactory() {}
	/** The framework will invoke this function once
	 * giving the StaticFactory implementation the chance
	 * to call on the ComponentRegistrar interface.
	 * f should not be cached by the StaticFactory implementation.
	 */
	virtual void addClasses(ComponentRegistrar *f) = 0;

}; // end static factory

#endif // staticfactory_h_seen
