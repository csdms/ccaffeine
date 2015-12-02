
#ifndef babelstaticfactory_h_seen
#define babelstaticfactory_h_seen

/** BabelStaticFactory stub for static linking classic
 * components into the legacy component factory stuff,
 * since classic doesn't include builderservice/componentRepository
 * features in its design.
 *
 * The framework may be handed an instance or instances of this 
 * to inform it of the component classes that were static linked
 * and their constructors.
 */
class BabelStaticFactory : public virtual StaticFactory {
public:
	BabelStaticFactory() {}
	virtual ~BabelStaticFactory() {}
	/** The framework will invoke this function once
	 * giving the BabelStaticFactory implementation the chance
	 * to call on the ComponentRegistrar interface.
	 * f should not be cached by the BabelStaticFactory implementation.
	 */
	virtual void addClasses(ComponentRegistrar *f);

}; // end babelstatic factory

#endif // babelstaticfactory_h_seen
