#ifndef __CLASSICFACTORY_HH__
#define __CLASSICFACTORY_HH__

#define BUFLEN 1024


// Stuff we don't want to put in the header if we can help it.
// we need to split the ccafe_factory_list uses into 
// per container and global so that the functions per container
// are correct. We want to avoid having multiple copies of
// dynamically loaded constructor function pointers around so
// we have a chance at unloading.

class classicComponentRecord : public virtual JCPN(Object) {
 public:
  char * className;        // className defined for user, possibly disambiguated
                           // or taken from .cca file for library.
  char * libraryClassName; // className found with library introspection.
  char * cFuncName;        // constructor function name for className
  char * libraryPath;      // .so file name where class+cfunc is found.
  char * buildDate;        // component data, if available.
  char * builder;          // component data, if available.
  char * buildLocation;    // component data, if available.
  char * componentType;    // classic, babel, etc.
  char * indexName;        // where we found out about this class.
  int inFactory;           // if 1, className will be found in ccafe_factory_list.

  ~classicComponentRecord() {
    free(className);
    free(libraryClassName);
    free(cFuncName);
    free(libraryPath);
    free(buildDate);
    free(builder);
    if(buildLocation) {
      free(buildLocation);
    }
    if(componentType) {
      free(componentType);
    }
    if(indexName) {
      free(indexName);
    }
    inFactory = -1;
    className = libraryClassName = libraryPath = 
      buildDate = builder = buildLocation = indexName = 0;
  } 

#define eatspace(s) for (; s[0] != '\0' && isspace(s[0]); s = &(s[1]))
#define initspace(s,n) { int ns; for (ns = 0; ns < n; ns++ ) { s[ns] = '\0'; } }

  /** It is likely that there is more than one component factory in a
      framework with containers.  That will allow "cca classname" conflicts
      to be resolved, but likely not c++ conflicts. The odds of "cca
      classnames", which are arbitrary strings often for management
      consumption, conflicting are good.

      This class should be better decomposed. Currently it is
      a combination of factory and wrappers for the DL stuff
      standing in lieu of a repository interface.
  */


  class ClassicFactory {
  private:
    bool debug;


    /** ccafe_factory_list: list of null constructors available to call
	now.  keyed by classname. */
    JCPN(StringHash) * ccafe_factory_list = 0;

    /** ccafe_repository: list of everything we know about loaded or loadable
	classes. elements are classicComponentRecord keyed by className. */
    JCPN(Vector) * ccafe_repository = 0;

    /** piecewise search path */
    JCPN(StringVector) * ccafe_componentPathEntries = 0;

    /** where we list libraries already opened, key = full path name, value =
	introspection function cast blindly to/from (Object *). */
    JCPN(StringHash) * ccafe_loadedLibraries = 0;

  public:

    ClassicFactory(){}

    void setDebug(bool tf){debug = tf;}

    /** Load any hard-coded types and set up pallet data structures.
	This method could be per-container and private.
	Must be called before any dynamic loading is attempted.
    */
    void initPallet();

    /** register a component constructor
	This method could be per-container and private.
    */
    int addClass(const char *className, classic::gov::cca::Component *(*create)());

    /** get the names of registered components.
	This method could be per-container.
    */
    CDELETE JCPN(StringVector) *getPallet();

    /** build a component named in results of getPallet. 
	This method could be per-container.
    */
    OpaqueComponent * instantiate(const char *className,
				  jcpp::StringHash** d);

    //============== repository ===============================================

    /** Set the component path. The array given is null terminated. 
	The path will be searched for dynamically loadable libraries.
	The memory you hand us in this call is not kept.

	The argv given may be empty and may contain unreal paths.
	It is anticipated that the array elements may include a url
	in the future. The framework makes no immediate commitment to
	loading from urls, we simply note that this is the hook, in
	the absence of a more complicated repository interface.

	This call is not required if you want to use only statically
	linked components hardwired into ComponentFactory.cxx.

	For those elements which are file system names:
	A component library is detectable if a file with a name ending
	in .cca is found. Each line of such a file is assumed to contain
	either an un-path-qualified library name or a comment. Comments
	start with # or !. The library is expected to follow the platform
	conventions for dynamic linking and to contain the function
        char **getComponentList(); 
	getComponentList returns an argv (null terminated) where each
	element is a string of the form
    	C-null-constructor-function Classname
	The C-null-constructor-function is a symbol the library can
	satisfy with a call to dlsym or equivalent. The Classname
	can be any string uniquely associated with the component. It
	is highly recommended, but not required, that Classname correspond
	to the C++ classname (with namespace elements). This is so
	that the faint of heart (or imagination) will have a clue
	when they go to use the component. For demo purposes, it is
	often politically correct to have Classnames mapped that 
	correspond to prior management sales pitches instead of
	actual C++ code.

	The advisability of loading and executing a component constructor
	(which may entail unresolved symbols if it requires other 
	components/libraries to be loaded first) is not addressed in 
	this interface. It is expected that the dependency issue will
	be addressed at a higher level where more pre-load introspection  
	is possible, before a load is required here.

	For those elements which are URLs, the semantics are still
	under-defined. A decent web trusted repository protocol is expected.

	This method could be per-container.
    */
    void setComponentPath(char  **pathDirArgv);

    /** Get the current component path as a null-terminated array. 
	This may return empty but not null.
	If you wish to edit the path list, you just get the
	current path and copy the elements you want to keep into
	a new argv and call setComponentPath again.

	This method could be per-container.
    */
    char **getComponentPath();

    /** Searches the componentPath for files ending in .cca and builds
	a repository index of the classes.
	Returns the number of classes dynamically loadable, but not
	yet loaded.

	This method could be per-container.
    */
    int searchComponentPath();

    /** Returns the list of tuples, library:component pairs, describing
	what is currently dynamically loaded. The list is hence of an
	even length since each pair is kept as successive elements, in
	{library, component} order. Due to possible syntax of urls
	and class names in namespaces, we do not try to combine these
	into a single string per component loaded, though this is
	surely doable by the thoughtful.

	This method, unfortunately, must be global in scope since
	we don't want to be redundantly loading libraries.
	This is probably a function useful only to the outermost
	framework/container. GetPallet is what users want to see.
    */
    char ** getLoadedComponents();

    /** Return the list of known but not loaded component classNames.
	Will be empty unless searchComponentPath has been called.
    */
    char ** getUnloadedComponents();

    /** list of the libraries which have been introspected.
	return may be empty but not null.  */
    char ** getLoadedLibraries();

    /** load a class to pallet from the repository. className must be same
	as one returned from getUnloadedComponents. return is non-zero
	if there is an error.

	This method could be "apparently" per-container, but it
	affects the global runtime linker if global==true.  Some OS
	runtime linkers may ignore global and lazy.  In dlopen terms,
	lazy=true -> RTLD_LAZY, false->RTLD_NOW; global=true
	->RTLD_GLOBAL, false->RTLD_LOCAL.  @param global if true, add
	symbols to global link table, else keep private.  @param lazy
	if true, do not resolve undefined symbols in loaded component
	until an attempt to use them is made.
    */
    int loadPallet(char *className, bool global, bool lazy);

  private:
    char **loadedLibraries; // answer to getLoadedLibraries. global.
    char **loadedComponents; // answer to getLoadedComponents. global.
    char **unloadedLibraries; // list of libraries not opened. global.
    char **componentPath; // copied from caller. per container someday.
    char **unloadedComponents; // list of components in opened libraries
    // not yet added to pallet. per container someday.

    /** Return the classNames found in the library named.
	Currently an odd method.

	This method could be per-container.
    */
    char ** introspectLibrary(char *libraryPath, bool global, bool lazy);

    /** Handle the dlsym stuff.
	Return is non-zero if there is an error.
	This method could be "apparently" per-container, but it affects
	the global runtime linker if global==true.
	Some OS runtime linkers may ignore global and lazy.
	In dlopen terms, lazy=true -> RTLD_LAZY, false->RTLD_NOW;
	global=true ->RTLD_GLOBAL, false->RTLD_LOCAL.
	@param global if true, add symbols to global link table, else keep private.
	@param lazy if true, do not resolve undefined symbols in loaded component
	until an attempt to use them is made.
    */
    int loadPallet(char *libraryPath, char *mapName, char *cFuncName, bool global, bool lazy);


    /** Returns -1 if the component is unknown, 0 if the component is
	known but unloaded, and 1 if it is known and loaded. */
    int componentStatus(const char* className);


    //======================= argv class =======================================
    /** Duplicate a well-formed argv. */
    CFREE char **copyArgv(char **argv); 

    /** Free well-formed argv members and argv. */
    void destroyArgv(char **&argv); 

    /** Expand an argv, returning the pointer to it or to a new
	array sized 1 larger. Will accept a null argv input. */
    char **appendArgv(char **&argv, char *string); 

    /** Get the argv length, excluding terminating null. */
    int sizeofArgv(char **);

  };

  typedef boost::shared_ptr< ClassicFactory > ClassicFactory_ptr;

#endif //__CLASSICFACTORY_H__
