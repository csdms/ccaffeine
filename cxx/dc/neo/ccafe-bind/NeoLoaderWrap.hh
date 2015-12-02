#ifndef NeoLoaderWrap_h_seen
#define NeoLoaderWrap_h_seen

/**
 * Wrapper around the gorey details of the ccafeopq stuff
 * so it looks more babellike in a vague sort of way 
 * but also handles c++ virtualness correctly.
 */
class NeoLoaderWrap : public virtual neo::cca::ports::Loader
{

private:
	::ccafeopq::ComponentFactory *ocf;
	int serial;
	static int nextNum() { genSerial++; return genSerial; }
	static int genSerial;
	void checkthrow(const char *funcName);


public:
	NeoLoaderWrap( ccafeopq::ComponentFactory *f);

	// never use this constructor. testing only.
	NeoLoaderWrap(int bogon);

	virtual ~NeoLoaderWrap();


	/** replace current path with new paths. each vector element is one
	* directory name. Path is searched for .cca and possibly .scl elements.
	*/
	virtual void setPath(const std::vector< std::string > & paths);

	/** return the list of directories searched for .cca files. */
	virtual std::vector< std::string > getPath();

	/**
	* Cause the named port interface library to be dynamically loaded.
	* The port class will be loaded globally, as interfaces
	* between components must be globally defined.
	*/
	virtual int loadPortLibrary( const std::string & portLibraryName);

	/**
	* Cause the named class to become instantiable by a subsequent
	* call to BuilderSErvice.createComponentInstance(). This activity
	* may require side effects with dlopen.
	*   In dlopen terms, lazy=true -> RTLD_LAZY, false->RTLD_NOW;
	*                  global=true ->RTLD_GLOBAL, false->RTLD_LOCAL.
	*/
	virtual void loadComponent( const std::string & paletteClassAlias , bool global, bool lazy);


}; // end class NeoLoaderWrap

extern NeoLoaderWrap NeoLoaderWrap_test;

#endif // NeoLoaderWrap_h_seen
