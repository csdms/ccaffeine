
#include <map>
#include <string>

#include "dc/export/config.hh"
#ifdef HAVE_CLASSIC
#include <cca.h>
#endif // HAVE_CLASSIC
#include "util/IO.h"


#ifdef CCAFE_NO_DL

#include "port/portInterfaces.h"
#include "port/supportInterfaces.h"
#include "dc/port/portStar.h"
#include "dc/component/componentStar.h"

#endif // CCAFE_NO_DL


#include <string.h>
#ifndef OS_CATAMOUNT
// no glob in catamount. no dynamic loading.
#include <glob.h>
#endif
#include <ctype.h>

#ifdef HAVE_BABEL
#include <AllCCA.hh>
#ifdef CXX_HEADER_SUFFIX_HXX
	#if BSUF == 100
	#include "dc/babel.new/babel-cca/AllBabelCCA.hxx"
	#endif
	#if BSUF == 120
	#include "dc/babel.12/babel-cca/AllBabelCCA.hxx"
	#endif
	#include "sidl_Loader.hxx"
	// arg FIXME
	#include "sidl_DLL.hxx"
# else
	#include "dc/babel/babel-cca/AllBabelCCA.hh"
	#include "sidl_Loader.hh"
	// arg FIXME
	#include "sidl_DLL.hh"
#endif // CXX_HEADER_SUFFIX_HXX
#endif // HAVE_BABEL

#if (defined(HAVE_NEO)||defined(HAVE_CLASSIC))
#include "util/ascDynaLoad.h"
#endif // neo or classic need dlopen wrapper.
#include "util/freefree.h"
#include "dc/export/AllExport.hh"
#include "dc/framework/KernelPort.h"
#include "dc/export/ccafeopq_support.hh"
#include "dc/services/dotcca/dccore/DotCCAComponentCore.hpp"
#ifdef HAVE_CLASSIC
#include "dc/classic/ccafe-bind/AllCcafeBind.hh"
#endif // HAVE_CLASSIC
#ifdef HAVE_BABEL
#ifdef CXX_HEADER_SUFFIX_HXX
	#if BSUF == 100
	#include "dc/babel.new/ccafe-bind/AllCcafeBind.hh"
	#endif
	#if BSUF == 120
	#include "dc/babel.12/ccafe-bind/AllCcafeBind.hh"
	#endif
#else
	#include "dc/babel/ccafe-bind/AllCcafeBind.hh"
#endif //CXX_HEADER_SUFFIX_HXX
#endif // HAVE_BABEL

#ifdef HAVE_NEO
#include <neocca.hh>
#include "dc/neo/ccafe-bind/AllNeoBind.hh"
#endif // HAVE_NEO

#include "ComponentRecord_Impl.h"
#include "KernelPort.h"
#include "ComponentRegistrar.h"
#include "ComponentFactory.h"

// for stat call
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef DSTRING
#define DSTRING "undated"
#endif

namespace {
  char id[]=
    "$Id: ComponentFactory.cxx,v 1.78 2008/11/20 18:57:46 baallan Exp $";
  char date[]=DSTRING;
} ENDSEMI

  // Must match component type in the ".cca" file
#define BABEL_TYPE "babel"
#define OPAQUE_TYPE "opaque"
#define CLASSIC_TYPE "classic"
#define NEO_TYPE "neo"


  // Stuff we don't want to put in the header if we can help it.
  // we need to split the ccafe_factory_list uses into 
  // per container and global so that the functions per container
  // are correct. We want to avoid having multiple copies of
  // dynamically loaded constructor function pointers around so
  // we have a chance at unloading.

  /** Print out debug info. */
#ifdef CCAFE_SPEW
#if CCAFE_SPEW
bool ComponentFactory::debug = true;
#else
bool ComponentFactory::debug = false;
#endif
#else
bool ComponentFactory::debug = false;
#endif

namespace {
  static bool cfl_init_done = false;

} ENDSEMI


#ifdef HAVE_CLASSIC
  // A dummy function that should never be called, if it is anyway, it
  // whines.

classic::gov::cca::Component * babelDummyLoader() {
  IO_en1(":-( The dummy loader for a babel component has been called.  "
	 "This cannot happen.  "
	 "Please  report this ccafe-help@z.ca.sandia.gov.");
  return 0;
}

#endif // HAVE_CLASSIC

#define eatspace(s) for (; s[0] != '\0' && isspace(s[0]); s = &(s[1]))
#define initspace(s,n) { int ns; for (ns = 0; ns < n; ns++ ) { s[ns] = '\0'; } }

#define PATHSEP '/'

#define CCAFE_LINESIZE 1024

ComponentFactory::ComponentFactory()
{
  initPalette();
  initKernel();
}

ComponentFactory::~ComponentFactory()
{
}

bool ComponentFactory::checkAlreadyLoaded(const char *fname) {
  std::vector< ComponentRecord_shared > & rep = repository;
  ComponentRecord_shared rec;
  std::string rgetindexfile;
  for (size_t i = 0; i < rep.size(); i++) {
    rec = rep[i];
    rgetindexfile = rec->getIndexFile();
    if ( strcmp(fname, rgetindexfile.c_str()) == 0) { return true; }
  }
  return false;
}

int ComponentFactory::countUnloadedClasses( ) {
  std::vector< ComponentRecord_shared > & rep = repository;
  ComponentRecord_shared rec;
  int result=0;
  for (size_t i = 0; i < rep.size(); i++) {
    rec = rep[i];
    if (rec->getInFactory() == 0) { result++; }
  }
  return result;
}

/** lookup by palette alias. */
ComponentRecord_shared ComponentFactory::getRecordByPaletteClassName( const char *cname) {
  std::vector< ComponentRecord_shared > & rep = repository;
  ComponentRecord_shared rec;
  for (size_t i = 0; i < rep.size(); i++) {
    rec = rep[i];
    if ( rec->getDeploymentClassAlias().compare(cname) == 0) { return rec; }
  }
  ComponentRecord_shared dummy;
  return dummy;
}

/** lookup by real class name  and library */
ComponentRecord_shared ComponentFactory::getRecordByLibraryClassName( char *lib, char *lcname) {
  std::vector< ComponentRecord_shared > & rep = repository;
  ComponentRecord_shared rec;
  for (size_t i = 0; i < rep.size(); i++) {
    rec = rep[i];
    if (rec->getComponentClassName().compare(lcname) == 0 &&
	rec->getLibraryLocation().compare(lib) == 0)
      { return rec; }
  }
  ComponentRecord_shared dummy;
  return dummy;
}

/*CDELETE*/ ccafeopq::Component * ComponentFactory::createComponentInstance(const std::string & className)
{
  return instantiate(className.c_str());
}

/*CDELETE*/ ccafeopq::Component * ComponentFactory::createComponentInstance(const std::string & className, ccafeopq::TypeMap_shared &tm)
{
  (void)tm; // fixme-feature tm not used in createComponentInstance
  return instantiate(className.c_str());
}

void ComponentFactory::destroyComponentInstance(const std::string & s, ccafeopq::Component *c)
{
  // fixme-feature not used yet.
}
/*
  
*/

//==============================================================
/*CDELETE*/ ccafeopq::Component * ComponentFactory::instantiate(const char *className) {
  IO_dn1("entry");
  if (!cfl_init_done) {
    IO::en("ComponentFactory function called before ComponentFactory::initPalette");
    return (ccafeopq::Component*)0;
  }

#ifdef HAVE_CLASSIC
  classic::gov::cca::Component * (*create)();
  create = 0;
#endif
#ifdef HAVE_NEO
  neo::cca::Component * (*creatNeo)();
  creatNeo = 0;
#endif

  ComponentRecord_shared r = getRecordByPaletteClassName((char*)className);
  if (r == 0) {
    IO::en("ComponentFactory::instantiate called with unknown className %s\n",className);
    return static_cast< ccafeopq::Component* >(0);
  }
  std::string libraryClassName = r->getComponentClassName();
  std::string ct = r->getCCASpecBinding();
  if(ComponentFactory::debug && (ct != "")) {
    fprintf(stderr, "%s: componentType = %s for className = %s\n", 
            __FILE__, ct.c_str(), className);
  }
  std::string rtmpstring;
  IO_dn2("paletteClassAlias = %s", className);
  IO_dn2("libraryClassName = %s", libraryClassName.c_str());
  rtmpstring =  r->getConstructorName();
  IO_dn2("r->cFuncName = %s", rtmpstring.c_str());
  rtmpstring =  r->getLibraryLocation();
  IO_dn2("r->buildLocation = %s", rtmpstring.c_str());
  IO_dn2("r->componentType = %s", ct.c_str());

  IO_dn2("componentType = %s", ct.c_str());
  if(ct != "") {
    IO_dn2("strncmp(ct.c_str(), BABEL_TYPE, strlen(BABEL_TYPE)) = %d", 
           strncmp(ct.c_str(), BABEL_TYPE, strlen(BABEL_TYPE)));
  }
  if((ct != "") && 
     (strncmp(ct.c_str(), BABEL_TYPE, strlen(BABEL_TYPE)) == 0)) {
    // each choice inside this #if must return.
    
#ifndef HAVE_BABEL
    IO_en2("dccafe was configured and built without cca-spec-babel:%s",
	   "\nTry reconfiguring and rebuilding --with-cca-babel. See ./configure --help.");
    return static_cast< ccafeopq::Component* >(0);
#else // HAVE_BABEL defined
    IO_dn2("Babel Component: %s to be instantiated", libraryClassName.c_str());
    // the metadata xml format now allows babel classes to be palette
    // aliased. so we have to look up the real babel class name.
    // normally this is identical to the babel class name.
    if (r->getConstructorFunc() == 0) {
      gov::cca::Component babelCmpt;
      sidl::BaseClass bc;
      sidl::DLL dll = sidl::Loader::findLibrary(libraryClassName, "ior/impl", sidl::Scope_SCLSCOPE, sidl::Resolve_SCLRESOLVE);
      if (dll._is_nil()) {
        IO_en2(":-( Could not load Babel component using "
	       "sidl::Loader::findLibrary for library: %s", 
	       libraryClassName.c_str());
        IO_en2("Seeking Component class: %s", className);
        dump_babel_dl_info();
        return static_cast< ccafeopq::Component* >(0);
      }
      bc = dll.createClass(libraryClassName);
      if(bc._is_nil()) {
        IO_en2(":-( For some reason, even though we loaded the component "
	       "successfully, the component could not be instantiated.\n"
	       "Is Ccaffeine and your component compiled with compatible "
	       "compilers?  Just a guess but you might want to try "
	       "recompiling *everything*.\n Could not instantiate "
	       "component class named: %s\n",className);
        dump_babel_dl_info();
        return static_cast< ccafeopq::Component* >(0);
      }
  
      babelCmpt = ::babel_cast<gov::cca::Component> (bc);  // CAST

      if ( babelCmpt._is_nil() ) {
        IO_en2(":-( Could not cast to gov.cca.Component, are you sure your " 
	       "component subclasses gov.cca.Component?\n"
               " classname: %s", className);
        dump_babel_dl_info();
        return static_cast< ccafeopq::Component* >(0);
      }

      BabelComponentWrapper * bcw = new BabelComponentWrapper(babelCmpt);
      return bcw;
    } else {
      // static babel hack link path
      ccafeopq::Component * (*createBabel)();
      createBabel = (ccafeopq::Component * (*)())(r->getConstructorFunc());
      if(createBabel != 0) {
        ::ccafeopq::Component * boc = createBabel();
        return boc;
      } 
      return static_cast< ccafeopq::Component* >(0);
    }
#endif // HAVE_BABEL defined

  }
  // This applies to classic since we are in charge of loading the
  // component.  In fact it is a bad idea to load Babel code, better
  // to leave that to Babel.
  if ( ! r->getInFactory() ) {
    IO::en("ComponentFactory::instantiate called name of class not loaded %s\n",className);
    IO::en("ComponentFactory::instantiate try repository get-global %s first\n",className);
    IO::en("ComponentFactory::instantiate or repository get %s first\n",className);
    return static_cast< ccafeopq::Component* >(0);
  }
  if( (ct != "") && 
      (strncmp(ct.c_str(), OPAQUE_TYPE, strlen(OPAQUE_TYPE)) == 0)) {
    // each choice inside this if must return.
    // Component of pure type opaque
    ccafeopq::Component * (*creat)();
    creat = (ccafeopq::Component * (*)())(r->getConstructorFunc());
    if(creat != 0) {
      return creat();
    } else {
      IO_en1("ccafeopq::Component creation wrapper is null.");
      return static_cast< ccafeopq::Component* >(0);
    }
  }
  if( (ct != "") && 
      (strncmp(ct.c_str(), NEO_TYPE, strlen(NEO_TYPE)) == 0)) {
#ifdef HAVE_NEO
    // each choice inside this if must return.
    // Component of type neo
    neo::cca::Component * (*creatNeo)();
    creatNeo = (neo::cca::Component * (*)())(r->getConstructorFunc());
    if(creatNeo != 0) {
      ::neo::cca::Component *nc = creatNeo();
      ::ccafeopq::Component * oc = new NeoComponentWrapper(nc);
      return oc;
    } else {
      IO_en1("ccafeopq::Component creation wrapper is null for neo component.");
      return static_cast< ccafeopq::Component* >(0);
    }
#else
    IO_en1("neo component support not configured into framework. Can't do neo components.");
    return static_cast< ccafeopq::Component* >(0);
#endif // HAVE_NEO
  }
#ifdef HAVE_CLASSIC
  // always default to classic
  create = (classic::gov::cca::Component * (*)())(r->getConstructorFunc());
  if (create != 0) {
    ::classic::gov::cca::Component *cc = create();
    ::ccafeopq::Component * oc = new ClassicComponentWrapper(cc);
    return oc;
  }
  if (create == 0) {
    fprintf(stderr, ":-( Attempt to call a null ptr in %s:%d\n", 
	    __FILE__, 
	    __LINE__);
  }
#else
    IO_en1("classic component support not configured into framework. Can't do classic components.");
    return static_cast< ccafeopq::Component* >(0);
#endif // HAVE_CLASSIC
  
  IO_en1("Undefined component or dynamic loading not configured in/working.");
  return static_cast< ccafeopq::Component* >(0);
}

std::vector<std::string> ComponentFactory::getComponentClassAliases() {
  return getPalette();
}

//==============================================================
std::vector<std::string> ComponentFactory::getPalette() {

  // a curious function, because we know on the back side
  // of most getpalette calls the first thing people do
  // is get the JCPN(StringEnumeration) from the vector...

  std::vector< std::string > v;
  if (!cfl_init_done) { 
    IO::en("ComponentFactory::getPalette called before ComponentFactory::initPalette");
    return v;
  }

  ComponentRecord_shared rec;

  for (size_t i = 0; i < repository.size(); i++ )
    {
      rec = repository[i];
      if (rec->getInFactory()) {
	v.push_back(rec->getDeploymentClassAlias());
      }
    }
#if 0 // debug io
  for (size_t j = 0; j < v.size(); j++) 
  {
	  IO_en2("# getPalette: %s",v[j].c_str() );
  }
#endif
  return v;
}

int ComponentFactory::addClass(const char *className, void * (*create)() )
{
	return addClass(className, create, true);
}

int ComponentFactory::addClassBabel(const char *className)
{
	return addClass(className, 0, false);
}

int ComponentFactory::addStaticClassBabel( const char *className, 
                               void * (*create)(),
			       const char * classAlias) {
	return addStaticClassKind(className, create, classAlias, BABEL_TYPE);
}

int ComponentFactory::addStaticClass( const char *className, 
                               void * (*create)(),
			       const char * classAlias) {
	return addStaticClassKind(className, create, classAlias, CLASSIC_TYPE);
}

int ComponentFactory::addStaticClassKind( const char *className, 
                               void * (*create)(),
			       const char * classAlias,
				const char *classtype) 
{
  size_t i;
	  // bounce duplicates
	  ComponentRecord_shared oldrec;
	  std::vector< ComponentRecord_shared > & rep = repository;
	  bool duplicate = false;
	  for ( i = 0; i < rep.size(); i++) {
	    oldrec = rep[i];
	    if (oldrec->getDeploymentClassAlias() == classAlias ||
		oldrec->getComponentClassName() == className )
	      {
		duplicate = true;
		break;
	      }
	  }
	  if (duplicate)
	    {
	      IO::en("ComponentFactory::addStaticClass: class name or alias (%s alias %s) duplicates one already found. It is ignored.",
		     className,
		     classAlias);
	      return -1;
	    }

	  ccafe::ComponentRecord_Impl *cri = new ccafe::ComponentRecord_Impl();
	  assert(cri != 0);
	  ComponentRecord_shared rec(cri);
	  rec->setFoundInPath(false);
          ccafe::DotCCAComponentCore dccc;
         ::ccafeopq::ComponentClassDescription_shared ccd = dccc.createStaticDescription( classtype, className, classAlias );
	  rec->setCCD(ccd);
	  repository.push_back(rec);
	  rec.reset();
	  return addClass(className, create);
}
//==============================================================
// register a classic component constructor.
// returns -1 if duplicate class, -2 if factory is still closed.
// return 0 if ok.
int ComponentFactory::addClass(const char *className, 
                               void * (*create)(), bool createRequired)
{

  ComponentRecord_shared rec;
  if (cfl_init_done) {

    if (createRequired && create == 0) {
      IO::en("ComponentFactory::addClass(%s,0) called with null constructor pointer",
             className);
      return -1;
    }
    for (size_t i = 0; i < repository.size(); i++)
      {
	rec = repository[i];
	if ( rec->getDeploymentClassAlias() == className ) {
	  break;
	}
      }
    if (rec == 0) {
      IO::en("ComponentFactory::addClass called with palette name %s not recorded in metadata", className);
      return -1;
    }
    if ( rec->getInFactory() ) {
      IO::en("ComponentFactory::addClass called with duplicate className %s", className);
      return -1;
    }
    rec->setConstructorFunc((void*)create);
    //rec->setInFactory(1);

  } else {
    IO::en("ComponentFactory::addClass called before ComponentFactory::initPalette");
    return -2;
  }
  return 0;
}
 
//==============================================================
#define CREATEDEF(cxxName)						\
  static classic::gov::cca::Component *create_##cxxName() { return new cxxName(); }

#define MAPNAME(cname,cxxName)						\
  addClass(cname, create_##cxxName); fprintf(stderr,"# factory added %s\n",cname)

//==============================================================
// define the simple constructor function pointers.

#ifdef CCAFE_NO_DL
#ifdef HAVE_CLASSIC
CREATEDEF(TimeStamper);
// CREATEDEF(RevalidateTest); fixme events
CREATEDEF(Timer);
CREATEDEF(StarterComponent);
CREATEDEF(PrinterComponent);
#endif // HAVE_CLASSIC

#endif // CCAFE_NO_DL

//==============================================================
// Define the mapping of string names to C++ classes by adding
// hard-coded types to the palette or check the env(CCA_COMPONENT_PATH) for
// loadable components.
void ComponentFactory::initPalette() {
  if (cfl_init_done) {
    IO::en("ComponentFactory::initPalette called twice!");
    return;
  }

#ifdef CCAFE_NO_DL // defined in a config header if dl not available

  MAPNAME("TimeStamper",        TimeStamper);
  //   MAPNAME("RevalidateTest",     RevalidateTest); fixme events
  MAPNAME("Timer",              Timer);
  MAPNAME("StarterComponent",   StarterComponent);
  MAPNAME("PrinterComponent",   PrinterComponent);

#endif // CCAFE_NO_DL

  cfl_init_done = true;
}

void 
ComponentFactory::setComponentPath(const std::vector< std::string > & p) {
  componentPathEntries.clear();
#ifdef HAVE_BABEL
  // save the old sidl path
  std::string bpath = sidl::Loader::getSearchPath();
  IO_dn2("was sidl::Loader::getSearchPath=%s",bpath.c_str());
  sidl::Loader::setSearchPath("");
#endif
  for (size_t i = 0; i < p.size();  i++) {
    componentPathEntries.push_back(p[i]);
    IO_dn2("Path = %s", p[i].c_str());
#ifdef HAVE_BABEL
    // sidl::Loader::addSearchPath(p[i]); to support arbitrary file suffix,
    // we must add this call.
#endif
  }
#ifdef HAVE_BABEL
  // append old sidl path last so that new path
  // has effect in event of conflict.
  sidl::Loader::addSearchPath(bpath);
  bpath = sidl::Loader::getSearchPath();
  IO_dn2("now sidl::Loader::getSearchPath=%s",bpath.c_str());
#endif
}

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
    start with # or !. Additional details of the file format
    will be found in the documentation.

    The advisability of loading and executing a component constructor
    (which may entail unresolved symbols if it requires other 
    components/libraries to be loaded first) is not addressed in 
    this interface. It is expected that the dependency issue will
    be addressed at a higher level where more pre-load introspection
    is possible, before a load is required here.

    For those elements which are URLs, the semantics are still
    under-defined. A decent web trusted repository protocol is expected.

*/
void 
ComponentFactory::setComponentPath(const char **pathDirArgv)
{
  if (!cfl_init_done) {
    IO::en("ComponentFactory function called before ComponentFactory::initPalette");
    return;
  }
  std::vector< std::string > vals;
  if (pathDirArgv == 0) { return; }
  for (int i = 0; pathDirArgv[i] != 0;  i++) {
    vals.push_back(pathDirArgv[i]);
  }
  setComponentPath(vals);
}

std::vector< std::string> ComponentFactory::getComponentPath() {
  if (!cfl_init_done) {
    IO::en("ComponentFactory function called before ComponentFactory::initPalette");
  }
  return componentPathEntries;
}


std::vector< std::string> ComponentFactory::getParsedFiles()
{
  if (!cfl_init_done) {
    IO::en("ComponentFactory function called before ComponentFactory::initPalette");
  }
  
  IO_en2("ComponentFactory::getParsedFiles: %d files",(int)parsedFiles.size());
  return parsedFiles;
}


extern "C" {
  static int ComponentFactory_glob_whine(const char *epath, int eerrno)
  {
    IO::en("ComponentFactory::searchComponentPath: open failed for %s -- %s.",
	   epath, strerror(eerrno));
    return 0;
  }
} // end C

// cast to get around incomplete ibm prototype for glob errfunc
// under aix /usr/include has a broken glob header, in the protoized part,
// omits the args to glob errfunc argument.
#ifndef OS_AIX
#define FIX_BROKEN_IBM(f) f
#else
#if defined(_AIX50) || defined(_AIX51)
#define FIX_BROKEN_IBM(f) f
#else
#define FIX_BROKEN_IBM(f) ( (int (*)())(f) )
#endif // _AIX50 _AIX51
#endif // OS_AIX

void ComponentFactory::indexComponentPath()
{
  searchComponentPath();
}

int ComponentFactory::searchComponentPath()
{

  if (!cfl_init_done) {
    IO::en("ComponentFactory function called before ComponentFactory::initPalette");
    return 0;
  }

  if (componentPathEntries.size() < 1) {
    return 0;
  }

#ifndef OS_CATAMOUNT
#define INDEX_PAT "/*.cca"
  glob_t globbuf;
  globbuf.gl_offs = 0;

  std::string entry;
  size_t i;
  for (i = 0; i < componentPathEntries.size() ; i++) {
    entry = componentPathEntries[i];
    entry += INDEX_PAT;
    const char *pat;
    pat = entry.c_str();
    int err = glob(pat, ((!i)?GLOB_MARK:(GLOB_MARK|GLOB_APPEND)),
                   FIX_BROKEN_IBM(ComponentFactory_glob_whine) , &globbuf);

    switch (err) {
    case GLOB_NOSPACE:
      IO::en("ComponentFactory::searchComponentPath: malloc fail in glob.");
      break;
#if defined(MACOSX) || defined(OS_MACOSX)
    case GLOB_ERR:
      IO::en("ComponentFactory::searchComponentPath: unexpected error from glob.");
      break;
#else
    case GLOB_ABORTED:
      IO::en("ComponentFactory::searchComponentPath: glob aborted unexpectedly.");
      break;
    case GLOB_NOMATCH:
      IO::en("ComponentFactory::searchComponentPath: Empty list -- %s.", pat);
      break;
#endif // OS_MACOSX
    default:
      break;
    }
  }

  size_t pathc = globbuf.gl_pathc;
  for (i = 0 ; i < pathc ; i++) {
    char *p = globbuf.gl_pathv[i];
    // here's our policy not to reread an index file once read or read dirs.
    if (p[strlen(p)-1] != PATHSEP && !checkAlreadyLoaded( p)) {
      ccafe::DotCCAComponentCore dccc;
      std::string fpath = p;
      std::vector< ::ccafeopq::ComponentClassDescription_shared > ccdv = dccc.parseDescriptions( fpath );
      parsedFiles.push_back(fpath);
#ifdef HAVE_BABEL
      sidl::Loader::addSearchPath( fpath );
#endif // HAVE_BABEL
      // ccafe_repository
      for (size_t j = 0 ; j < ccdv.size(); j++)
	{
	  // bounce duplicates
	  ComponentRecord_shared oldrec;
	  std::vector< ComponentRecord_shared > & rep = repository;
	  bool duplicate = false;
	  for (size_t i = 0; i < rep.size(); i++) {
	    oldrec = rep[i];
	    if (oldrec->getDeploymentClassAlias() == ccdv[j]->getDeploymentClassAlias() ||
		oldrec->getComponentClassName() == ccdv[j]->getComponentClassName() )
	      {
		duplicate = true;
		break;
	      }
	  }
	  if (duplicate)
	    {
              std::string gccn =  ccdv[j]->getComponentClassName();
              std::string gdca =  ccdv[j]->getDeploymentClassAlias();
	      IO::en("ComponentFactory::searchComponentPath: class name or alias (%s alias %s) duplicates one already found. It is ignored.",
		     gccn.c_str(),
		     gdca.c_str());
	      continue;
	    }

	  ccafe::ComponentRecord_Impl *cri = new ccafe::ComponentRecord_Impl();
	  assert(cri != 0);
	  ComponentRecord_shared rec(cri);
	  rec->setFoundInPath(true);
	  rec->setCCD(ccdv[j]);
	  repository.push_back(rec);
	  rec.reset();
	}
    }
  }

  globfree(&globbuf);
#endif // OS_CATAMOUNT
  int result = countUnloadedClasses();
  return result; 
}

std::vector< std::string > ComponentFactory::getLoadedLibraries() {
  if (!cfl_init_done) {
    IO::en("ComponentFactory function called before ComponentFactory::initPalette");
  }
  ::std::map< ::std::string, void * >::iterator pos;
  std::vector< std::string > result;
  pos = loadedLibraries.begin();
  while (pos != loadedLibraries.end())
    {
      result.push_back(pos->first);
    }
  return result; // iterate over map loadedLibraries?
}


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
    framework/container. GetPalette is what users want to see.
*/
std::vector< std::string > ComponentFactory::getLoadedComponents() {
  std::vector< std::string > dummy;
  if (!cfl_init_done) {
    IO::en("ComponentFactory function called before ComponentFactory::initPalette");
    return dummy;
  }

  ComponentRecord_shared rec;
  std::vector< ComponentRecord_shared > & rep = repository;
  for (size_t i = 0; i < rep.size(); i++) {
    rec = rep[i];
    if (rec->getInFactory()) {
      dummy.push_back(rec->getLibraryName());
      dummy.push_back(rec->getComponentClassName());
    }
  }
  return dummy;
}

std::vector< std::string > ComponentFactory::getUnloadedComponents() {
  std::vector< std::string > dummy;
  if (!cfl_init_done) {
    IO::en("ComponentFactory function called before ComponentFactory::initPalette");
    return dummy;
  }

  ComponentRecord_shared rec;
  std::vector< ComponentRecord_shared > & rep = repository;
  for (size_t i = 0; i < rep.size(); i++) {
    rec = rep[i];
    if ( ! rec->getInFactory()) {
      dummy.push_back(rec->getLibraryName());
      dummy.push_back(rec->getComponentClassName());
    }
  }
  return dummy;
}

std::vector< ccafeopq::ComponentClassDescription_shared > ComponentFactory::getComponentClasses() {
  std::vector< ccafeopq::ComponentClassDescription_shared > dummy;
  if (!cfl_init_done) {
    IO::en("ComponentFactory function called before ComponentFactory::initPalette");
    return dummy;
  }

  ComponentRecord_shared rec;
  std::vector< ComponentRecord_shared > & rep = repository;
  for (size_t i = 0; i < rep.size(); i++) {
    rec = rep[i];
    dummy.push_back(rec);
  }
  return dummy;
}

//
int ComponentFactory::loadPorts(const std::string & libPathName) {

  if (! cfl_init_done) {
    IO::en("ComponentFactory function called before ComponentFactory::initPalette");
    return 0;
  }
#if (defined(HAVE_CLASSIC)||defined(HAVE_NEO))
  int err = CCA_LoadPorts(const_cast<char *>(libPathName.c_str()),1);
  return err;
#else
    IO::en("ComponentFactory::loadPorts failed. neo and classic disabled.");
    return 1;
#endif
}

// do dl stuff, privately.
int ComponentFactory::loadPalette(const char *soName, const char *mapName, const char *cFuncName, bool global, bool lazy, const char * cmptType, const char * soDir) {

  if (! cfl_init_done) {
    IO::en("ComponentFactory function called before ComponentFactory::initPalette");
    return 0;
  }
  std::string sfilename = soDir;
  sfilename += "/";
  sfilename += soName;
  IO_dn3("mapName = %s, cmptType = %s", mapName, cmptType);

  // We want to leave the babel components alone.
  // For the pure-virtual based components (opq,neo,classic,
  // we cheat and c-cast all types for purposes of addClass
  // to classic.
  // probably would have been better off keeping void* explicitly.
  if((cmptType == 0) || 
     (strncmp(cmptType, OPAQUE_TYPE, strlen(OPAQUE_TYPE)) == 0)
#ifdef HAVE_NEO
     || (strncmp(cmptType, NEO_TYPE, strlen(NEO_TYPE)) == 0)
#endif // HAVE_NEO
#ifdef HAVE_CLASSIC
     || (strncmp(cmptType, CLASSIC_TYPE, strlen(CLASSIC_TYPE)) == 0)
#endif // HAVE_CLASSIC
     )
    {

      int err = 1;
#if (defined(HAVE_NEO)||defined(HAVE_CLASSIC))
      // update classname, assuming coherence of cfuncname
      void * (*create)();
      create = (void * (*)())CCA_IntrospectLibrary(
								    sfilename.c_str(), cFuncName,
								    (global ? 0 : 1), 
								    (global ? 1 : 0), 
								    (lazy ? 1 : 0), 
								    (lazy ? 0 : 1), 
								    1);
      err = addClass(mapName, create, true);
      if (err) {
	IO::en("# factory bounced(%d) {%s}:{%s} as %s\n",
	       err,(sfilename.c_str()), cFuncName, mapName);
	return err;
      }
      loadedLibraries[sfilename] = (void*)8; // dummy entry
      IO::en("# factory added {%s}:{%s} as %s\n",
	     (sfilename.c_str()), cFuncName, mapName);
      return 0;
#else
	IO::en("# neo and classic not configure in. factory bounced(%d) {%s}:{%s} as %s\n",
	       err,(sfilename.c_str()), cFuncName, mapName);
	return 1;
#endif // neo || classic

  } else {

    if(strncmp(cmptType, BABEL_TYPE, strlen(BABEL_TYPE)) == 0) 
      {
#ifndef HAVE_BABEL
	fprintf(stderr,"CCAFFEINE configured WITHOUT babel and babel components.\n"
		"I hope you're not trying to load a babel component.\n"
		"Reconfigure with --with-cca-babel=/something and remake if you need babel.\n");
	return -1;
#else

	// It is a babel component
	int err = 0;
	IO_dn2("mapName = %s", mapName);

	// Dummy function for Babel components
	err = addClassBabel(mapName);

	IO_dn2("err = %d", err);
	return err;
#endif
      }
    IO_en2("Unrecognized componentType option (%s) in \".cca\" file",cmptType);
    return -1;
  }
}

void ComponentFactory::dumpFactory()
{
  std::cout << "------- repository dump  ------" << std::endl;
  for (size_t i = 0; i < repository.size(); i++)
    {
      std::cout << "--------" << repository[i]->getDeploymentClassAlias() << "----------" << std::endl;
      std::cout << repository[i]->toString() << std::endl;
    }
  std::cout << "------- done ------" << std::endl;
}
void ComponentFactory::loadComponentDescription(const std::string & uri)
{
  readComponentDescription(uri);
}

void ComponentFactory::readComponentDescription(const std::string & uri)
{
  // FIXME -- needs to be refactored so search and read have
  // mostly common implementation.
  // parse uri file, // add description, // set 'notglobd' flag in description
  if (uri == std::string("")) {
    return;
  }
  const char *p = uri.c_str();
  // here's our policy not to reread an index file once read or read dirs.
  if (p[strlen(p)-1] != PATHSEP && !checkAlreadyLoaded( p)) {
    ccafe::DotCCAComponentCore dccc;
    std::string fpath = p;
    std::vector< ::ccafeopq::ComponentClassDescription_shared > ccdv = dccc.parseDescriptions( fpath );
    parsedFiles.push_back(fpath);
    for (size_t j = 0 ; j < ccdv.size(); j++)
      {
	// bounce duplicates
	ComponentRecord_shared oldrec;
	std::vector< ComponentRecord_shared > & rep = repository;
	bool duplicate = false;
	for (size_t i = 0; i < rep.size(); i++) {
	  oldrec = rep[i];
	  if (oldrec->getDeploymentClassAlias() == ccdv[j]->getDeploymentClassAlias() ||
	      oldrec->getComponentClassName() == ccdv[j]->getComponentClassName() )
	    {
	      duplicate = true;
	      break;
	    }
	}
	if (duplicate)
	  {
            std::string gccn =  ccdv[j]->getComponentClassName();
            std::string gdca =  ccdv[j]->getDeploymentClassAlias();
	    IO::en("ComponentFactory::readComponentDescription: class name or alias (%s alias %s) duplicates one already found. It is ignored.",
		   gccn.c_str(),
		   gdca.c_str());
	    continue;
	  }

	ccafe::ComponentRecord_Impl *cri = new ccafe::ComponentRecord_Impl();
	assert(cri != 0);
	ComponentRecord_shared rec(cri);
	rec->setFoundInPath(false);
	rec->setCCD(ccdv[j]);
	repository.push_back(rec);
	rec.reset();
      }
  }
}

void 
ComponentFactory::loadClass(const std::string className, bool global, bool lazy) {
  loadPalette(className,global,lazy);
}

int 
ComponentFactory::loadPalette(const std::string& className, 
			      bool global, 
			      bool lazy) { 
  return loadPalette(className.c_str(), global, lazy);
}

// by unique class name
int ComponentFactory::loadPalette(const char *className, bool global, bool lazy) { 
  if (!cfl_init_done) {
    IO::en("ComponentFactory function called before ComponentFactory::initPalette");
    return 0;
  }

  ComponentRecord_shared rec;
  rec = getRecordByPaletteClassName(className);
  if (rec == 0) {
    IO::en("ComponentFactory::loadPalette(%s) failed (unknown component).",
           className);
    return -1;
  }
  if (!rec->getInFactory()) {
    std::string gln = rec->getLibraryName();
    std::string gcn = rec->getConstructorName();
    std::string gcsb = rec->getCCASpecBinding();
    std::string gll = rec->getLibraryLocation();
    return loadPalette(gln.c_str(), className, 
		       gcn.c_str(), 
		       global, 
		       lazy,
		       gcsb.c_str(), gll.c_str());
  }
  IO::en("ComponentFactory::loadPalette(%s) failed (already loaded).",
         className);
  return -1;
}

void
ComponentFactory::dump_babel_dl_info() {
#ifndef HAVE_BABEL
#else
  std::string bpath = sidl::Loader::getSearchPath();
  IO_en2("sidl::Loader::getSearchPath=%s",bpath.c_str());
  const char *sdbg = getenv("SIDL_DEBUG_DLOPEN");
  if (sdbg != 0) { IO_en2("SIDL_DEBUG_DLOPEN=%s",sdbg); }
  else { IO_en2("SIDL_DEBUG_DLOPEN %s","not set."); }
  const char *sdbg2 = getenv("sidl_DEBUG_DLOPEN");
  if (sdbg2 != 0) { IO_en2("sidl_DEBUG_DLOPEN=%s",sdbg2); }
  else { IO_en2("sidl_DEBUG_DLOPEN %s","not set."); }
  const char *spath = getenv("SIDL_DLL_PATH");
  if (spath != 0) { IO_en2("SIDL_DLL_PATH=%s",spath); }
#endif    
  const char *lpath = getenv("LD_LIBRARY_PATH");
  if (lpath != 0) { IO_en2("LD_LIBRARY_PATH=%s",lpath); }
  if (ComponentFactory::debug) {
    dumpFactory();
  }
}

//==============================================================================
#if 0 // argv

void ComponentFactory::destroyArgv(char **&argv) {
  if (argv == 0) { return; }
  for (int i = 0; argv[i] != 0; i++) {
    free(argv[i]);
    argv[i] = 0;
  }
  free(argv);
  argv = 0;
}

int ComponentFactory::sizeofArgv(char **argv) {
  if (argv==0) { return -1; }
  int i = 0;
  while (argv[i] !=0) {
    i++;
  }
  return i;
}

/* CFREE */ char ** ComponentFactory::copyArgv(char **argv) {
  int argc;
  char **newArgv;

  argc = sizeofArgv(argv);
  newArgv = (char **)malloc(sizeof(char *)*(argc+1));

  for (int i = 0; i <= argc; i++) { 
    newArgv[i] = argv[i]; 
  }

  return newArgv;
 
}

char **ComponentFactory::appendArgv(char **&argv, char *string) {

  char **newArgv;
  // new case
  if (argv==0) {
    // malloc argv and add string
    newArgv = (char **)malloc(sizeof(char *)*(2));
    newArgv[0] = newArgv[1] = 0;
    if (string !=0) {
      newArgv[0] = string;
    }
    return newArgv;
  }
  // noop case
  if (string == 0) { 
    return argv;
  }
  // expand/replace case
  int argc;
  argc = sizeofArgv(argv);
  newArgv = (char **)malloc(sizeof(char *)*(argc+2));
  for (int i = 0; i < argc; i++) { 
    newArgv[i] = argv[i]; 
    argv[i] = 0; 
  }
  newArgv[argc] = string;
  newArgv[argc+1] = 0;
  free(argv);
  return newArgv;
}

#endif // 0 dump argv
