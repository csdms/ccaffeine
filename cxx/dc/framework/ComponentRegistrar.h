#ifndef ComponentRegistrar_h_seen
#define ComponentRegistrar_h_seen
/** virtual interface to hide componentfactory idiocy from the
 * classic static linking world.
 */
class ComponentRegistrar {
public:
	virtual ~ComponentRegistrar() {}
  /** register a classic constructor that is static linked. */
  virtual int addStaticClass(const char *className, void *(*create)(), const char * classAlias) = 0;
  /** register a babel constructor that is static linked outside the blessed factory pattern. */
  virtual int addStaticClassBabel(const char *className, void *(*create)(), const char * classAlias) = 0;

};

#endif //  ComponentRegistrar_h_seen
