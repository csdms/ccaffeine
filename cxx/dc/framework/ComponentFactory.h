#ifndef __COMPONENTFACTORY_H__
#define __COMPONENTFACTORY_H__

#define BUFLEN 1024

namespace ccafe {
class ComponentRecord_Impl;
} ENDSEMI
typedef ::boost::shared_ptr< ccafe::ComponentRecord_Impl > ComponentRecord_shared;

/**
  There can sanely be only one instance of this per runtime.
  So there can be more than one Frame, but the dynamically
  opened libraries are the same across all frames -- that's
  life in unix. 

This class should be better decomposed. Currently it is
a combination of factory and wrappers for the DL stuff
standing in lieu of a repository interface.
One might want, for example, to show some component types
in the palette of one frame but not another. For now
we push that off to a UI to manage.
*/
class ComponentFactory : public virtual ccafeopq::ComponentFactory, public virtual KernelPort , public virtual ComponentRegistrar
{

private:

  static bool debug;

  /** dir names. */
  std::vector< std::string > componentPathEntries;
  /** file/uri that have been parsed. */
  std::vector< std::string > parsedFiles;
  /** metadata list */
  std::vector< ComponentRecord_shared > repository;
  /** dlopened file handles by name. */
  std::map< std::string, void *> loadedLibraries;

  /** register a classic component constructor */
  int addClass(const char *className, void * (*create)());

  int addClass(const char *className, void * (*create)(), bool required);

  /** register a babel class for dynamic loading. */
  int addClassBabel(const char *className);

  /** register a classic constructor that is static linked. */
  virtual int addStaticClass(const char *className, void *(*create)(), const char * classAlias);

  /** register a babel constructor that is static linked. */
  virtual int addStaticClassBabel(const char *className, void *(*create)(), const char * classAlias);

  /** internal use only. */
  int addStaticClassKind(const char *className, void *(*create)(), const char * classAlias, const char *classtype);

  /** 
     True if metadata file has already been parsed by the name fname
  */
  bool checkAlreadyLoaded(const char *fname);

  /** count the number of classes in the repository list
      that do not have constructors registered.
      This is approximate because all BABEL classes are
      considered loaded whether they have been dlopened or not
      (since babel hides dlopen from us).
  */
  int countUnloadedClasses();

  /** Look up a class description by UI alias. */
  ComponentRecord_shared getRecordByPaletteClassName( const char *cname);

  /** 
     Look up a class by babel class name or by classic create_ constructor?
     @param lib library pathname
     @param lcname real library class name.
  */
  ComponentRecord_shared getRecordByLibraryClassName( char *lib, char *lcname);

  /** Dump helpful Babel DL path info in case we fail to instantiate a class */
  void dump_babel_dl_info();

public:

  ComponentFactory();
  virtual ~ComponentFactory();
  /** Load any hard-coded types and set up palette data structures.
      Must be called before any loadPalette or
      instantiate is attempted.
  */
  void initPalette();

  /** print the repository */
  void dumpFactory();

  /** enables some additional spew */
  void setDebug(bool tf){debug = tf;}

  /** get the names of registered components.
      This method could be per-container.
  */
  std::vector< std::string > getPalette();

  /** build a component named in results of getPalette. 
  */
  ccafeopq::Component * instantiate(const char *deploymentClassAlias);

//============== old repository ===============================================

  /** Parse a file (or url when wget support is included)
      describing a component and attempt to add it to the
      runtime repository list.
   */ 
  void readComponentDescription( const std::string & uri);

  /** @param p a vector of path elements.
      Currently all elements must be names of directories
      searchable via glob(). An argv-style version of this
      function is also provided.
      When searchComponentPath is called,
      the directories given here are searched for metadata files
      matching the pattern *.cca and containing a class
      description. 
      The search results become the repository class list.
      This call is not cumulative--that
      is, all previously set paths are removed and replaced
      with the arguments to this one.

	Note for BABEL/SIDL: this call *is* cumulative for the babel
	class loader. The value passed here is *prepended* to the
	SIDL loader search path. If it is not cumulative, then
	the net effect is that SIDL_DLL_PATH is lost because
	SIDL Loader only consults env the first time to do an
	initial setSearchPath and thereafter ignores it.
	At least this is the apparent behavior october 2003.
   */
  void setComponentPath(const std::vector< std::string > & p);

  /** 
     argv style support for legacy codes.
   */
  void setComponentPath(const char  **pathDirArgv);


  /** Searches the componentPath for files ending in .cca and builds
      a repository index of the classes.
      Returns the number of classes dynamically loadable, but not
      yet loaded.

      This method could be per-container.
   */
  int searchComponentPath();

  /** Returns the list of tuples, library:component pairs, describing
      what is currently dynamically loaded and has a constructor
      registered. The list is hence of an
      even length since each pair is kept as successive elements, in
      {library, component} order. Due to possible syntax of urls
      and class names in namespaces, we do not try to combine these
      into a single string per component loaded, though this is
      surely doable by the thoughtful.

      This method, unfortunately, must be global in scope since
      we don't want to be redundantly loading libraries.
      This is probably a function useful only to the outermost
      framework/container. GetPalette is what users want to see.
  */
  std::vector< std::string > getLoadedComponents();

  /** Return the list of known but not loaded component classNames.
      Will be empty unless searchComponentPath has been called.
   */
  std::vector< std::string > getUnloadedComponents();

  /** list of the libraries which have been opened.
      Return may be empty but not null. 
      libraries listed do not include those opened
      by SIDL loader or by the C runtime itself.
   */
  std::vector< std::string > getLoadedLibraries();

  /** return the names of metadata files that were parsed. */
  std::vector< std::string > getParsedFiles();

  /** load a class to palette from the repository. className must be same
      as one returned from getUnloadedComponents. return is non-zero
      if there is an error.

    This method could be "apparently" per-container, but it affects
    the global runtime.
    Some OS runtime linkers may ignore global and lazy.
    In dlopen terms, lazy=true -> RTLD_LAZY, false->RTLD_NOW;
                     global=true ->RTLD_GLOBAL, false->RTLD_LOCAL.
   @param global if true, add symbols to global link table, else keep private.
   @param lazy if true, do not resolve undefined symbols in loaded component
                        until an attempt to use them is made.
  */
  int loadPalette(const std::string& className, bool global, bool lazy);

  /** legacy driver string support */
  int loadPalette(const char *className, bool global, bool lazy);

  ///////////////////////////////////////////
  // opq factory interface
  
  virtual std::vector< std::string> getComponentClassAliases();

  virtual std::vector< ccafeopq::ComponentClassDescription_shared > getComponentClasses();

  virtual ccafeopq::Component * createComponentInstance(const std::string & className);

  virtual ccafeopq::Component * createComponentInstance(const std::string & className, ccafeopq::TypeMap_shared & properties);

  virtual void destroyComponentInstance(const std::string & componentClassName, ccafeopq::Component * component);

  // virtual void setComponentPath(const std::vector< std::string > & paths);

  /** Get the current component path.
      If you wish to edit the path list, you just get the
      current path and copy the elements you want to keep into
      a new vector and call setComponentPath again.
  */
  virtual std::vector< std::string > getComponentPath();

  virtual void loadComponentDescription(const std::string & uri);

  virtual void indexComponentPath( );

  virtual void loadClass( const std::string paletteClassAlias , bool global, bool lazy);

  virtual int loadPorts(const std::string & libPathName);

  ///////////////////////////////////////////
  
private:


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
  int loadPalette(const char *libraryPath, const char *mapName, const char *cFuncName, bool global, bool lazy, const char * cmptType, const char * buildPath);



#if 0 //argv
//======================= argv class =======================================
  /** Duplicate a well-formed argv. */
  static /* CFREE */ char **copyArgv(char **argv); 

  /** Free well-formed argv members and argv. */
  static void destroyArgv(char **&argv); 

  /** Expand an argv, returning the pointer to it or to a new
      array sized 1 larger. Will accept a null argv input. */
  static char **appendArgv(char **&argv, char *string); 

  /** Get the argv length, excluding terminating null. */
  static int sizeofArgv(char **);
#endif // 0

};
#endif //__COMPONENTFACTORY_H__
