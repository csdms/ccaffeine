
#ifndef examplestaticfactory_h_seen
#define examplestaticfactory_h_seen

/** This implements a static factory assuming combustion components.
 */
class ExampleStaticFactory : public virtual StaticFactory {
public:
	ExampleStaticFactory() {}
	virtual ~ExampleStaticFactory() {}
	/** The framework will invoke this function once
	 * giving the StaticFactory implementation the chance
	 * to call on the ComponentFactory interface.
	 */
	virtual void addClasses(ComponentRegistrar *f);

}; // end examplestatic factory

#endif // examplestaticfactory_h_seen
