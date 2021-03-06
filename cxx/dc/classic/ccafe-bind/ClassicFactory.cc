#ifndef lint
static char id[] = 
"$Id: ClassicFactory.cc,v 1.3 2005/04/15 00:58:23 rob Exp $";
#endif



#include "jc++/jc++.h"
#include "jc++/lang/jc++lang.h"
#include "jc++/util/jc++util.h"
#include "parameters/parametersStar.h"
#include <cca.h>
#include "util/IO.h"


#ifdef CCAFE_NO_DL


#include "port/portInterfaces.h"
#include "port/supportInterfaces.h"
#include "dc/port/portStar.h"
#include "dc/component/componentStar.h"

#endif // CCAFE_NO_DL


#include <string.h>
#include <glob.h>
#include <ctype.h>

#include <AllCCA.hh>
#include "dc/babel/babel-cca/AllBabelCCA.hh"
#include "SIDL_Loader.hh"
#include "ClassicFactory.h"
#include "util/ascDynaLoad.h"
#include "util/freefree.h"
#include "dc/export/AllExport.hh"
#include "dc/classic/ccafe-bind/AllCcafeBind.hh"
#include "dc/babel/ccafe-bind/AllCcafeBind.hh"



/** If the line is lead off with match, copies the
    remainder of the line to the variable given.
    If str given isn't null, will free it before overwriting.
*/
static void 
munchKeyword(char *line, char *match, char *&str) {
  int matchLen;
  matchLen = strlen(match);
  if (strncmp(match,line,matchLen)==0) {
    if (str != 0) { free(str); }
    str = STRDUP(line+matchLen);
  }
}

/** Munch down the comment and meta-info lines.
    fills up the given buffers lb* with malloc'd strings if
    matching metalines found.
*/
static int 
checkMetaLine(char * line, 
	      char *&date, 
	      char *&builder, 
	      char *&lbl,
	      char *&cmptType
	      ) {
  eatspace(line);
  if (line[0] == '#') { return 1; }
  if (line[0] == '!') {
    if (line[1] == '\0') { return 1; }
    line++;
    eatspace(line);
    munchKeyword(line,(char *)"date=", date);
    munchKeyword(line,(char *)"builder=", builder);
    munchKeyword(line,(char *)"location=",lbl);
    munchKeyword(line,(char *)"componentType=",cmptType);
    return 1;
  }
  return 0; // not a comment or meta.
}

#define PATHSEP '/'

/** trim of *.cca from index and append lib name. */
static CFREE char *dlPathName(char *index, char *lib) {
  int ilen, llen;
  ilen = strlen(index);
  llen = strlen(lib);
  if (ilen == 0 || llen == 0) { return 0; }
  while (index[ilen] != PATHSEP && ilen > 0) { ilen--; }
  char *result;
  result = (char*)malloc(ilen+1+llen+1);
  result[ilen+llen+1] = '\0';
  strncpy(result,index,ilen+1);
  sprintf(&(result[ilen+1]),lib);
  return result;
}

#define CCAFE_LINESIZE 1024
/** doesn't tolerate whitespace in library names. */
static void 
scanIndexFile(JCPN(Vector) *rep, char *fname) {
  FILE *f;
  classicComponentRecord *rec;
  char linep[CCAFE_LINESIZE+1];
  char *line = linep;// char *line = &linep[0];
  char *last_buildDate = 0; 
  char *last_builder = 0;
  char *last_buildLocation = 0;
  char *cmptType = 0;
  char *last_lib  = 0;
  JCPN(Object) *obj = 0;

  f = fopen(fname,"r");
  if ( f == 0 ) { return; }
  initspace(line,CCAFE_LINESIZE);
  while (fgets(line,CCAFE_LINESIZE,f) != 0) {
    eatspace(line);
    if (line[0] == '\0') { continue; }
    if (checkMetaLine(line, last_buildDate, 
		      last_builder, 
		      last_buildLocation,
		      cmptType
		      )) {
      initspace(line,CCAFE_LINESIZE);
      continue;
    }
    int numitems;
    char i1[CCAFE_LINESIZE], i2[CCAFE_LINESIZE];
    initspace(i1,CCAFE_LINESIZE);
    initspace(i2,CCAFE_LINESIZE);
    eatspace(line);
    numitems = sscanf(line,"%s%s",i1,i2);
    switch (numitems) {
    case 1:
      if (last_lib != 0) { free(last_lib); }
      last_lib = dlPathName(fname,i1); 
      break;
    case 2:
      if (last_lib == 0) {
	IO::en("ClassicFactory::scanIndexFile found class without library in %s.",
	       fname);
	break;
      }  
      rec = new classicComponentRecord();
      rec->cFuncName = STRDUP(i1);
      rec->libraryClassName = STRDUP(i2); // may get updated from actual library.
      rec->libraryPath = STRDUP(last_lib); 
      rec->buildDate = (last_buildDate==0)?0:STRDUP(last_buildDate);
      rec->builder = (last_builder==0)?0:STRDUP(last_builder);
      rec->buildLocation = (last_buildLocation==0)?0:STRDUP(last_buildLocation);
      rec->componentType = (cmptType==0)?0:STRDUP(cmptType);
      rec->inFactory = 0;
      rec->indexName = STRDUP(fname);
      rec->className = getUniqueClass(rep,i2);
      obj = dynamic_cast<JCPN(Object) *>(rec); CHECKDC(obj);
      rep->add(obj);
      break;
    default:
      IO::en("ClassicFactory::scanIndexFile bad line in %s (%s).",
	     fname,line);
      break;
    }
    initspace(line,CCAFE_LINESIZE);
    
  }
    
  fclose(f);
  if (last_buildDate) { free(last_buildDate); }
  if (last_builder) { free(last_builder); }
  if (last_buildLocation) { free(last_buildLocation); }
  if (last_lib) { free(last_lib); }
}

/** assumes input is CCAFE_LINESIZE long in size, and shorter in content.
    If cname is duplicated by an element of rep, changes cname. */
CFREE static char *getUniqueClass(JCPN(Vector) *rep,char *cname) {
  classicComponentRecord *rec;
  JCPN(Object) *obj;
  int changed = 1, extended = 0;
  while (changed) {
    changed = 0;
    // see if the current name is in the names.
    for (int i = 0; i < rep->size(); i++) { // iterate over list of class records.
      obj = rep->get(i);
      if (obj == 0) { 
	IO::en("ClassicFactory::getUniqueClass found bad data at %d",i);
      }
      rec = dynamic_cast<classicComponentRecord *>(obj); CHECKDC(rec);
      if (strcmp(cname,rec->className)==0) { changed = 1; }
    }
    if (changed) {
      // it is.
      if (extended) { // extended is overloaded to be boolean and len.
	(cname[extended])++; // just increment the already appended letter.
      } else {
	// first trip.
	extended = strlen(cname); // find where to put the new letters.
	cname[extended] = '_'; // append _
	extended++;
	cname[extended] = 'A'; // append A
	cname[extended+1] = '\0';  // reterminate string.
	//printf("ClassicFactory::getUniqueClass renamed %s.", cname);
	IO::en("ClassicFactory::getUniqueClass renamed %s.", cname);
      }
    }
  }
  return STRDUP(cname);
}

int static checkAlreadyLoaded(JCPN(Vector) *rep, char *fname) {
  classicComponentRecord *rec;
  JCPN(Object) *obj;
  for (int i = 0; i < rep->size(); i++) {
    obj = rep->get(i); 
    if (obj == 0) { 
      IO::en("ClassicFactory::checkAlreadyLoaded found bad data at %d",i);
    }
    rec = dynamic_cast<classicComponentRecord *>(obj); CHECKDC(rec);
    if (strcmp(fname,rec->indexName)==0) { return 1; }
  }
  return 0;
}

static int countUnloadedClasses(JCPN(Vector) *rep) {
  classicComponentRecord *rec;
  int result=0;
  JCPN(Object) *obj;
  for (int i = 0; i < rep->size(); i++) {
    obj = rep->get(i); 
    if (obj == 0) { 
      IO::en("ClassicFactory::countUnloadedClasses found bad data at %d",i);
    }
    rec = dynamic_cast<classicComponentRecord *>(obj); CHECKDC(rec);
    if (rec->inFactory == 0) { result++; }
  }
  return result;
}

static classicComponentRecord *getRecordByClassName(JCPN(Vector) *rep, char *cname) {
  ccafeClassicRecord *rec;
  JCPN(Object) *obj;
  for (int i = 0; i < rep->size(); i++) {
    obj = rep->get(i); 
    if (obj == 0) { 
      IO::en("ClassicFactory::getRecordByClassName found bad data at %d",i);
    }
    rec = dynamic_cast<classicComponentRecord *>(obj); CHECKDC(rec);
    if (strcmp(rec->className,cname) == 0) { return rec; }
  }
  return 0;
}

static classicComponentRecord *getRecordByLibraryClassName(JCPN(Vector) *rep, char *lib, char *lcname) {
  classicComponentRecord *rec;
  JCPN(Object) *obj;
  for (int i = 0; i < rep->size(); i++) {
    obj = rep->get(i); 
    if (obj == 0) { 
      IO::en("ClassicFactory::getRecordByClassName found bad data at %d",i);
    }
    rec = dynamic_cast<classicComponentRecord *>(obj); CHECKDC(rec);
    if (strcmp(rec->libraryClassName,lcname) == 0 &&
	strcmp(rec->libraryPath,lib)==0) { return rec; }
  }
  return 0;
}

CDELETE OpaqueComponent * 
ClassicFactory::instantiate(const char *className, 
			    jcpp::StringHash** instances) {
  if (ccafe_factory_list == 0) {
    IO::en("ClassicFactory function called before ClassicFactory::initPallet");
    return (OpaqueComponent*)NULL;
  }

  classic::gov::cca::Component * (*create)();
  create = 0;

  classicComponentRecord *r = classicComponentRecord::getRecordByClassName(ccafe_repository, (char*)className);
  char* ct = r->componentType;
  if(ClassicFactory::debug && (ct != NULL)) {
    fprintf(stderr, "%s: componentType = %s for className = %s\n", 
	    __FILE__, r->componentType, className);
  }
  create = (classic::gov::cca::Component * (*)())((void *)ccafe_factory_list->get((char *)className));
  if (create != 0) {
    if(create == 0) {
      fprintf(stderr, ":-( Attempt to call a null ptr in %s:%d\n", 
	      __FILE__, 
	      __LINE__);
      return (OpaqueComponent*)(NULL);
    }
    return (OpaqueComponent*)(new ClassicComponentWrapper(create()));
  }

  
  return (OpaqueComponent*)(0);
}

//==============================================================
CDELETE JCPN(StringVector) *ClassicFactory::getPallet() {

  // a curious function, because we know on the back side
  // of most getpallet calls the first thing people do
  // is get the JCPN(StringEnumeration) from the vector...

  if (ccafe_factory_list == 0) { 
    IO::en("ClassicFactory::getPallet called before ClassicFactory::initPallet");
    return 0;
  }

  JCPN(StringEnumeration) *keys = ccafe_factory_list->keys();
  if (!keys) { 
    IO::en("ClassicFactory::getPallet no keys found");
    return 0; 
  }
  JCPN(StringVector) *v = new JCPN(StringVector)();
  if (v == 0) { 
    IO::en("ClassicFactory::getPallet 'new StringVector' failed");
    delete keys;
    return v; 
  }
  while (keys->hasMoreElements()) {
    v->addElement(keys->nextElement());
  }
  //  delete keys;
  v->sort();
  return v;
}

//==============================================================
// register a component constructor
// returns -1 if duplicate class, -2 if factory is still closed.
// return 0 if ok.
int ClassicFactory::addClass(const char *className, 
			     classic::gov::cca::Component * (*create)()) {

  if (ccafe_factory_list) {
    if (ccafe_factory_list->containsKey((char *)className)) {
      IO::en("ClassicFactory::addClass called with duplicate className %s",
	     className);
      return -1;
    }
    ccafe_factory_list->put((char *)className,(JCPN(Object) *)((void*)create));
  } else {
    IO::en("ClassicFactory::addClass called before ClassicFactory::initPallet");
    return -2;
  }
  return 0;
}
 
//==============================================================
#define CREATEDEF(cxxName) \
static classic::gov::cca::Component *create_##cxxName() { return new cxxName(); }

#define MAPNAME(cname,cxxName) \
  addClass(cname, create_##cxxName); fprintf(stderr,"# factory added %s\n",cname)

//==============================================================
// define the simple constructor function pointers.

#ifdef CCAFE_NO_DL
#ifdef _CCAMPI 
#ifdef _ISIS
// see component/DataHolder.h
// CREATEDEF(DataHolder);
#endif // _ISIS
#endif // _CCAMPI

#endif // CCAFE_NO_DL

//==============================================================
// Define the mapping of string names to C++ classes by adding
// hard-coded types to the pallet or check the env(CCA_COMPONENT_PATH) for
// loadable components.
void ClassicFactory::initPallet() {
  if (ccafe_factory_list !=  0) {
    IO::en("ClassicFactory::initPallet called twice!");
    return;
  }
  ccafe_repository = new JCPN(Vector)(20);
  ccafe_componentPathEntries = new JCPN(StringVector)();
  ccafe_loadedLibraries = new JCPN(StringHash)();
  loadedLibraries = 0;
  loadedComponents = 0;
  unloadedLibraries = 0;
  componentPath = 0;
  unloadedComponents = 0; 

  ccafe_factory_list = new JCPN(StringHash)();

#ifdef CCAFE_NO_DL // defined in a config header if dl not available

  // #ifdef _CCAMPI 
  // #ifdef _ISIS
  //   // see component/DataHolder.h
  //   MAPNAME("DataHolder",         DataHolder);
  // #endif // _ISIS
  // #endif // _CCAMPI

  // #ifdef _ISIS
  //   MAPNAME("SNL_Map",            SNL_Map_Component);
  //   MAPNAME("ISIS_JCPN(Vector)",        ISIS_JCPN(Vector)_Component);
  //   MAPNAME("ISIS_DCSR_Matrix",   ISIS_DCSR_Matrix_Component);
  //   MAPNAME("Identity_PC",        Identity_PC_Component);
  //   MAPNAME("ISIS_GMRES",         ISIS_GMRES_Component);
  //   MAPNAME("Integrator",         Integrator2);
  //   MAPNAME("Diffusion",         Diffusion);
  //   MAPNAME("Diffusion2",         Diffusion2);
  // #endif // _ISIS

  // #ifdef _OLD_ESI
  //   MAPNAME("PlateA",             Plate1);
  //   MAPNAME("PlateB",             Plate2);
  //   MAPNAME("SimpleMath",         DiagonalModel);
  // #endif //_OLD_ESI

  // #ifdef STV_ROOT
  //   MAPNAME("CUMULVS",		Eyes);
  // #endif // STV_ROOT

  // #ifdef EYES2_ROOT
  //   MAPNAME("TextView",		Eyes2);
  // #endif // EYES2_ROOT

  //   MAPNAME("TimeStamper",        TimeStamper);
  //   MAPNAME("RevalidateTest",     RevalidateTest);
  //   MAPNAME("Timer",              Timer);
  //   MAPNAME("StarterComponent",   StarterComponent);
  //   MAPNAME("PrinterComponent",   PrinterComponent);

#endif // CCAFE_NO_DL

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

void ClassicFactory::setComponentPath(char **pathDirArgv) {
  if (ccafe_factory_list == 0) {
    IO::en("ClassicFactory function called before ClassicFactory::initPallet");
    return;
  }

  JCPN(StringIteratedFree) sif;
  ccafe_componentPathEntries->doAll(sif);
  //ccafe_componentPathEntries->doAll((void (*)(char *))free);
  delete ccafe_componentPathEntries;
  ccafe_componentPathEntries = new JCPN(StringVector)();
  if (pathDirArgv == 0) { return; }
  for (int i = 0; pathDirArgv[i] != 0;  i++) {
    ccafe_componentPathEntries->add(STRDUP(pathDirArgv[i]));
  }
  
}

/** Get the current component path as a null-terminated array. 
    This may return empty but not null.
    If you wish to edit the path list, you just get the
    current path and copy the elements you want to keep into
    a new argv and call setComponentPath again.

    This method could be per-container.
*/
char **ClassicFactory::getComponentPath() {
  if (ccafe_factory_list == 0) {
    IO::en("ClassicFactory function called before ClassicFactory::initPallet");
    return 0;
  }
  destroyArgv(componentPath);
  componentPath = appendArgv(componentPath,0);
  for (int i = 0 ; i < ccafe_componentPathEntries->size(); i++) {
    componentPath = appendArgv(componentPath,STRDUP(ccafe_componentPathEntries->get(i)));
  }
  return componentPath;
}

extern "C" {
  static int ComponentFactory_glob_whine(const char *epath, int eerrno) {
    IO::en("ComponentFactory::searchComponentPath: open failed for %s -- %s.",
	   epath, strerror(eerrno));
    return 0;
  }
}

int ClassicFactory::searchComponentPath() {

  if (ccafe_factory_list == 0) {
    IO::en("ClassicFactory function called before ClassicFactory::initPallet");
    return 0;
  }

  if (ccafe_componentPathEntries->size() < 1) {
    return 0;
  }
  destroyArgv(unloadedLibraries);
  unloadedLibraries = appendArgv(unloadedLibraries,0);

#define INDEX_PAT "/*.cca"
  glob_t globbuf;
  globbuf.gl_offs = 0;

  char *entry;
  unsigned i;
  for (i = 0; i < (unsigned)(ccafe_componentPathEntries->size()) ; i++) {
    entry = ccafe_componentPathEntries->get(i);
    char *pat;
    pat = (char *)malloc(strlen(INDEX_PAT) + strlen(entry) + 1);
    if (pat == 0) {
      IO::en("ClassicFactory::searchClassicPath: malloc fail.");
      break;
    }
    sprintf(pat,"%s%s", entry, INDEX_PAT);
    int err = glob(pat, ((!i)?GLOB_MARK:(GLOB_MARK|GLOB_APPEND)), ComponentFactory_glob_whine , &globbuf);
    switch (err) {
    case GLOB_NOSPACE:
      IO::en("ClassicFactory::searchComponentPath: malloc fail in glob.");
      break;
#ifndef OS_MACOSX
    case GLOB_ABORTED:
      IO::en("ClassicFactory::searchComponentPath: glob aborted unexpectedly.");
      break;
    case GLOB_NOMATCH:
      IO::en("ClassicFactory::searchComponentPath: Empty list -- %s.", pat);
      break;
#else
    case GLOB_ERR:
      IO::en("ClassicFactory::searchComponentPath: unexpected error from glob.");
      break;
#endif // OS_MACOSX
    default:
      break;
    }
    free(pat);
  }

  for (i = 0 ; i < globbuf.gl_pathc ; i++) {
    char *p = globbuf.gl_pathv[i];
    // here's our policy not to reread an index file once read or read dirs.
    if (p[strlen(p)-1] != PATHSEP &&
	!classicComponentRecord::checkAlreadyLoaded(ccafe_repository, p)) {
      // printf("scanning %d = %s\n", i, p);
      classicComponentRecord::scanIndexFile(ccafe_repository, p); 
    }
  }

  globfree(&globbuf);

  int result = classicComponentRecord::countUnloadedClasses(ccafe_repository);
  return result; 
}

char ** ClassicFactory::getLoadedLibraries() {
  if (ccafe_factory_list == 0) {
    IO::en("ClassicFactory function called before ClassicFactory::initPallet");
    return 0;
  }

  loadedLibraries = appendArgv(loadedLibraries,0);
  JCPN(StringEnumeration) *keys = ccafe_loadedLibraries->keys();
  while (keys->hasMoreElements()) {
    char *lib = keys->nextElement();
    loadedLibraries = appendArgv(loadedLibraries,STRDUP(lib));
  }
  delete keys;
  return loadedLibraries;
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
    framework/container. GetPallet is what users want to see.
*/
char ** ClassicFactory::getLoadedComponents() {
  if (ccafe_factory_list == 0) {
    IO::en("ClassicFactory function called before ClassicFactory::initPallet");
    return 0;
  }

  destroyArgv(loadedComponents);
  loadedComponents = appendArgv(loadedComponents,0);
  classicComponentRecord *rec;
  JCPN(Vector) *rep;
  rep = ccafe_repository;
  JCPN(Object) *obj;
  for (int i = 0; i < rep->size(); i++) {
    obj = rep->get(i);
    if (obj == 0) { 
      IO::en("ClassicFactory::getLoadedClassics found bad data at %d",i);
    }
    rec = dynamic_cast<classicComponentRecord *>(obj); CHECKDC(rec);
    if (rec->inFactory) {
      loadedComponents = appendArgv(loadedComponents,STRDUP(rec->libraryPath));
      loadedComponents = appendArgv(loadedComponents,STRDUP(rec->className));
    }
  }
  return loadedComponents;
}

char ** ClassicFactory::getUnloadedComponents() {
  if (ccafe_factory_list == 0) {
    IO::en("ClassicFactory function called before ClassicFactory::initPallet");
    return 0;
  }

  destroyArgv(unloadedComponents);
  unloadedComponents = appendArgv(unloadedComponents,0);
  classicComponentRecord *rec;
  JCPN(Vector) *rep;
  rep = ccafe_repository;
  for (int i = 0; i < rep->size(); i++) {
    rec = dynamic_cast<classicComponentRecord *>(rep->get(i));
    if (!rec->inFactory) {
      unloadedComponents = appendArgv(unloadedComponents,STRDUP(rec->libraryPath));
      unloadedComponents = appendArgv(unloadedComponents,STRDUP(rec->className));
    }
  }
  return unloadedComponents;
}

/** Return the classNames found in the library named.
    libraryPath must be one from searchComponentPath().
    Return may be null.

    This method could be per-container.
*/
char ** ClassicFactory::introspectLibrary(char *libraryPath, bool global, bool lazy) {
  if (ccafe_factory_list == 0) {
    IO::en("ClassicFactory function called before ClassicFactory::initPallet");
    return 0;
  }

  if (libraryPath == 0) { 
    fprintf(stderr,"ClassicFactory::introspectLibrary: no path given\n");
    return 0;
  }
  char **(*peek)() = 0;
  peek = (char **(*)())CCA_IntrospectLibrary(libraryPath,(char *)"getComponentList",
					     (global ? 0 : 1), 
					     (global ? 1 : 0), 
					     (lazy ? 1 : 0), 
					     (lazy ? 0 : 1), 
					     1 );
  if (peek == 0) { 
    fprintf(stderr,"Library %s failed to load or has no 'getComponentList'.\n",libraryPath);
    if (!global || lazy) {
      fprintf(stderr,"If there are unresolved symbols, loading this component LAZY\n"
	      "or loading some other component GLOBAL may help.\n");
    }
    return 0;
  }
  ccafe_loadedLibraries->put(libraryPath,(JCPN(Object) *)((void*)peek));
  return peek();
}

// do dl stuff, privately.
int ClassicFactory::loadPallet(char *libraryPath, char *mapName, char *cFuncName, bool global, bool lazy) {

  if (ccafe_factory_list == 0) {
    IO::en("ClassicFactory function called before ClassicFactory::initPallet");
    return 0;
  }

  char **lindex;
  lindex = introspectLibrary(libraryPath, global, lazy);
  if (!lindex) { 
    return -1;  
  }
  char *li;
  char *constructorMatch = 0;
  for (int i = 0; lindex[i] != 0; i++) {
    li = lindex[i];
    if (strncmp(li,cFuncName,strlen(cFuncName))==0) {
      constructorMatch = cFuncName;
      break;
    }
  }
  if (constructorMatch == 0) {
    IO::en("Library index file entry %s does not match library %s",
	   cFuncName, libraryPath);
    return -1;
  }
  if (strcmp(&(li[strlen(cFuncName)+1]),mapName)!=0) {
    IO::en("Pallet class %s maps to different %s",mapName,
	   &(li[strlen(cFuncName)+1]));
  }
   
  // update classname, assuming coherence of cfuncname
  classic::gov::cca::Component * (*create)();
  create = (classic::gov::cca::Component * (*)())CCA_DynamicSymbol(libraryPath,
								   cFuncName);
  int err;
  err = addClass(mapName, create);
  if (err) {
    IO::en("# factory bounced(%d) {%s}:{%s} as %s\n",
	   err,libraryPath,li,mapName);
    return err;
  }
  IO::en("# factory added {%s}:{%s} as %s\n",
	 libraryPath,li,mapName);
  return 0;
}

// by unique class name
int ClassicFactory::loadPallet(char *className, bool global, bool lazy) { 
  if (ccafe_factory_list == 0) {
    IO::en("ClassicFactory function called before ClassicFactory::initPallet");
    return 0;
  }

  classicComponentRecord *rec;
  rec = classicComponentRecord::getRecordByClassName(ccafe_repository,className);
  if (rec == 0) {
    IO::en("ComponentFactory::loadPallet(%s) failed (unknown component).",
	   className);
    return -1;
  }
  if (!rec->inFactory) {
    return loadPallet(rec->libraryPath, className, rec->cFuncName, global, lazy);
  }
  IO::en("ClassicFactory::loadPallet(%s) failed (already loaded).",
	 className);
  return -1;
}

int componentStatus(const char* className) {
  if (ccafe_factory_list == 0) {
    IO::en("ClassicFactory function called before ClassicFactory::initPallet");
    return 0;
  }

  classicComponentRecord *rec;
  rec = classicComponentRecord::getRecordByClassName(ccafe_repository,
						     className);
  if (rec == 0) {
    return -1;
  }
  if (!rec->inFactory) {
    return 0;
  }
  return 1;
}




//==============================================================================

void ClassicFactory::destroyArgv(char **&argv) {
  if (argv == 0) { return; }
  for (int i = 0; argv[i] != 0; i++) {
    free(argv[i]);
    argv[i] = 0;
  }
  free(argv);
  argv = 0;
}

int ClassicFactory::sizeofArgv(char **argv) {
  if (argv==0) { return -1; }
  int i = 0;
  while (argv[i] !=0) {
    i++;
  }
  return i;
}

CFREE char ** ClassicFactory::copyArgv(char **argv) {
  int argc;
  char **newArgv;

  argc = sizeofArgv(argv);
  newArgv = (char **)malloc(sizeof(char *)*(argc+1));

  for (int i = 0; i <= argc; i++) { 
    newArgv[i] = argv[i]; 
  }

  return newArgv;
 
}

char **ClassicFactory::appendArgv(char **&argv, char *string) {

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
