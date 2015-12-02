#ifndef lint
static char id[]=
"$Id: DefaultBuilderModel.cxx,v 1.42 2006/07/31 23:48:37 baallan Exp $";
#endif

#include <vector>
#include <string>

#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "parameters/parametersStar.h"

#include "dc/framework/dc_fwkPublic.h"
#include "port/portInterfaces.h"

#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/DefaultBuilderModel.h"
#include "dc/user_iface/InitScript.h"
#include "dc/user_iface/ProgramSuffix.h"

#include "util/IO.h"
#include "util/freefree.h"

namespace {
	/** find a string in a list of strings, or return -1 if not there. */
	// just vector.find operation. duh, unless stl broken.
int indexOf( ::std::vector< ::std::string > &v, ::std::string & sbuf)
{
  for (size_t j = 0 ; j < v.size(); j++)
  {
    if (v[j] == sbuf) {
      return int(j);
    }
  }
  return -1;
}
};

/** Create a unique instance name wrt namesTaken list. */
std::string DefaultBuilderModel::createInstanceName(const std::string & cName) 
{
  int c = 0;
  char buf[2048];
  const char *className = cName.c_str();
  // trim off the absolute path
  int i = JString::lastIndexOf(const_cast<char *>(className),'.');
  if (i == (int)strlen(className)) {
    return "";
  }
  sprintf(buf,"%s%d",&(className[i+1]),c);
  std::string sbuf = buf;
  std::vector< std::string > namesTaken = getInstanceNames();
  while(indexOf(namesTaken, sbuf) != -1) {
    c++;
    sprintf(buf,"%s%d",&(className[i+1]),c);
    sbuf = buf;
  }
  std::string instName;
  instName = buf;
  namesTaken.push_back(instName);
  return instName;
}



DefaultBuilderModel::DefaultBuilderModel(int & notfound, StaticFactory *sf, int64_t fComm, bool useComm){

  notfound = 0;
  IO_dn3("DefaultBuilderModel::DefaultBuilderModel(nf,sf,%d,%s)",(int)fComm,(useComm?"TRUE":"FALSE"));
  int err;
  /* CDELETE */ fwk_data = new ConnectionFramework(fComm,useComm,err);
  if (sf != 0) {
	  fwk_data->initStaticFactory(sf);
  }

  if (err != 0) {
    notfound = 1;
    return;
  }
  fwk_data->addComponentChangedListener(this);

  void * bmv = static_cast<void *>(this);
  fwk_data->putFrameItem("DefaultBuilderModel", bmv);

  IO_dn3("DefaultBuilderModel::DefaultBuilderModel(nf,sf,%d,%s)",(int)fComm,(useComm?"TRUE":"FALSE"));

#ifndef HAVE_BABEL
  fprintf(stderr,"\nCCAFFEINE configured WITHOUT babel and babel components.\n");
#else
  fprintf(stderr,"\nCCAFFEINE configured with spec (%s) and babel (%s).\n",CCASPEC_VERSION, CCASPEC_BABEL_VERSION);
#endif

#ifdef HAVE_CLASSIC
  fprintf(stderr,"\nCCAFFEINE configured with classic (%s).\n",CLASSIC_VERSION);
#else
  fprintf(stderr,"\nCCAFFEINE configured without classic and classic components.\n");
#endif

#ifdef HAVE_NEO
  fprintf(stderr,"\nCCAFFEINE configured with neo (%s).\n",NEOCCA_VERSION);
#else
  fprintf(stderr,"\nCCAFFEINE configured without neo and neo components.\n");
#endif

}

DefaultBuilderModel::~DefaultBuilderModel() {
  size_t i = cmptChgLsnrs.size() ;
  for ( ; i > 0; i--) { cmptChgLsnrs[i-1] = 0; } // erase the list.
  cmptChgLsnrs.clear();
  delete fwk_data;
}

void DefaultBuilderModel::initScript() {
	// we skip dealing with the parser as the parser is
	// wrapped around us anyway.
#ifdef _CCAMPI

#ifdef HAVE_BABEL
	// boot the babel mpi component if it's around.
	std::vector< std::string > paths = fwk_data->getRepositoryPath();
	std::string mpipath = MPICOMPONENT_INDEX_INSTALLED;
	paths.insert(paths.begin(), mpipath);
	setRepositoryPath(paths);
	loadRepositoryClass("ccafe6.MPIComponent", true, false);
#define HIDEMPI 1
#if HIDEMPI 
	::ccafeopq::TypeMap_shared tm = Gizzard::createTypeMapStatic();
	tm->putBool(::ccafeopq::Keys::CCAFE_VISIBLE, false);
	pullDownFromPallet("ccafe6.MPIComponent","MPISetup", tm);
#else
	pullDownFromPallet("ccafe6.MPIComponent","MPISetup");
#endif // HIDEMPI

#endif // HAVE_BABEL

#endif // _CCAMPI
}

void DefaultBuilderModel::componentChanged(ComponentChangedEvent* evt) {
  size_t i = cmptChgLsnrs.size() ;
  for ( ; i > 0; i--) {
    ComponentChangedListener* l = cmptChgLsnrs[i-1];
    CHECKDC(l);
    l->componentChanged(evt);
  }
}

ConnectionFramework *DefaultBuilderModel::getFramework()
{
	return fwk_data;
}

void DefaultBuilderModel::addComponentChangedListener(ComponentChangedListener* l) {
  cmptChgLsnrs.push_back(l);
}

std::string DefaultBuilderModel:: pullDownFromPallet(const std::string & className, const std::string & instanceName, ::ccafeopq::TypeMap_shared cprops)
{
  ComponentInfo_shared ci;
  ci = fwk_data->instantiate(className, instanceName, cprops);
  if (!ci) { return ""; }
  return ci->getInstanceName();
}

/** Instantiate a component that presently exists on the pallet and
place it in the arena giving it an instanceName.  

    @returns A string that is the instantiated components unique
    instance name. */
std::string DefaultBuilderModel::pullDownFromPallet(const std::string & className, const std::string & instanceName) 
{
  ::ccafeopq::TypeMap_shared cprops;
  ::std::string rname = pullDownFromPallet(className,instanceName,cprops);
  return rname;
}

/** Instantiate a component that presently exists on the pallet and
place it in the arena.  

    @returns A string that is the instantiated components unique
    instance name. */

std::string DefaultBuilderModel::pullDownFromPallet(const std::string & className) {
  ::std::string s;
  ::ccafeopq::TypeMap_shared cprops;

  s = createInstanceName(className);
  if (s.size() == 0) {
    return s;
  }
  return pullDownFromPallet(className, s, cprops);
}


int DefaultBuilderModel::disconnect(const char *fromInstance,
                                 const char *providesPortInstance, 
                                 const char *toInstance,
                                 const char *usesPortInstance) {

  return fwk_data->disconnect(fromInstance, providesPortInstance, toInstance, usesPortInstance);
}



/** Connect the instance of an already "pulled down" (instantiated)
    component, already residing in the arena, to another component
    in the arena.  Note that the order here honors the port flow.
    Port's flow from "fromInstance" to toInstance in the argument
    list.  Data flow moves in the opposite direction of port flow.
*/
int DefaultBuilderModel::connect(const char *fromInstance,
                                 const char *providesPortInstance, 
                                 const char *toInstance,
                                 const char *usesPortInstance)
{
  return fwk_data->connect(fromInstance, providesPortInstance, toInstance, usesPortInstance);
}

/** The arena is where instantiated components live and can be
    subsequently connected together. The component information is
    stored in a ComponentInfo stored in a map.
    The key to each instance is the
    String-valued instance name of the instantiated component.

*/
::std::map< ::std::string, ComponentInfo_shared >
DefaultBuilderModel::getArena()
{
  std::map< ::std::string, ccafe::CmpBox_shared > cbm = fwk_data->getInstances();
  return ComponentInfo::wrapCmpBoxMap( cbm );
}

/** The pallet is an array of String's that are the class names
    (types) of components that can be instantiated by the connection
    framework. 
    Do not delete the pointer returned. */
std::vector< std::string > 
DefaultBuilderModel::getPallet() {
  return fwk_data->getComponentClasses();
}

int DefaultBuilderModel::goOne(const char * instanceName, const char * portInstanceName) {
  return fwk_data->goOne(instanceName,portInstanceName);
}

void DefaultBuilderModel::setDebug(bool tf) {
  fwk_data->setDebug(tf);
}

void DefaultBuilderModel::removeInstantiatedComponent(const std::string & instanceName) {
  if (instanceName == "MPISetup") {
	return; // no killing our mpi world this way. that's our job.
  }
  fwk_data->removeInstantiatedComponent(instanceName);
}

void DefaultBuilderModel::removeAllInstantiatedComponents() {
  ::std::vector< ::std::string >keys = getInstanceNames();
  for (size_t i = 0; i < keys.size(); i++) {
    removeInstantiatedComponent(keys[i]);
  }
}


/** Get the parameter data from a component, if it has any,
    or the empty string if it doesn't. */
CFREE char *  DefaultBuilderModel::getConfiguration(const char * instanceName, const char * portInstanceName) { 
  char * s;
  s = fwk_data->getConfiguration(instanceName,portInstanceName);
  if (s == 0) { // should *never* happen
    IO::en("fwk->getConfiguration(\"%s\",\"%s\") failed badly"); 
    s = strdup("");
  }
  return s;
}

/** Get the parameter data from a component, if it has any,
    or the empty string if it doesn't. */
CFREE char *  DefaultBuilderModel::getConfiguration(const char * instanceName, const char * portInstanceName, const char *fieldName) { 
  char * s;
  s = fwk_data->getConfiguration(instanceName,portInstanceName,fieldName);
  if (s == 0) { // should *never* happen
    IO::en("fwk->getConfiguration(\"%s\",\"%s\",\"%s\") failed badly"); 
    s = strdup("");
  }
  return s;
}

/** Set the parameter data from a component, if it has any.
    Return the parameters if it takes any, or the empty
    string if it doesn't. */
char *  DefaultBuilderModel::setConfiguration(const char * instanceName,const  char * portInstanceName,const  char *fieldName,const  char * configuration) {
  return fwk_data->setConfiguration(instanceName,portInstanceName,fieldName,configuration);
}

std::vector< std::string > DefaultBuilderModel::getComponentProperties(::std::string & instanceName) {
  return fwk_data->getComponentProperties(instanceName);
}
const std::string DefaultBuilderModel::getComponentProperty(const char * instanceName, const char * key) {
  return fwk_data->getComponentProperty(instanceName, key);
}

std::vector< std::string > 
DefaultBuilderModel::getComponentProperties(const std::string & instanceName) {
  return fwk_data->getComponentProperties(instanceName);
}

void DefaultBuilderModel::setComponentProperty(const char * instanceName, const char * key, const char * value) {
  return fwk_data->setComponentProperty(instanceName, key, value);
}

ccafeopq::TypeMap_shared DefaultBuilderModel::getPortProperties( const ::std::string & instanceName, const std::string & portName)
{
	return fwk_data->getPortProperties(instanceName,  portName);	
}

int DefaultBuilderModel::setPortProperty( const ::std::string & instanceName, const std::string & portName,
	         	const std::string & key, const std::string & valueType, const std::string & value)
{
	return fwk_data->setPortProperty(instanceName, portName, key, valueType, value);
}



/** Set current module path from an argv. Input will only be read
    until argc or a null element is reached. Normal return is 0. */
int DefaultBuilderModel::setRepositoryPath(char **argv, int argc)
{
  return fwk_data->setRepositoryPath(argv,argc);
}
int DefaultBuilderModel::setRepositoryPath(const std::vector< std::string > & p)
{
  return fwk_data->setRepositoryPath(p);
}

/** Get current componenent path as an argv. Path returned
    is null-terminated and has argc elements. Not yours
    to mess with the content. */
std::vector< std::string >DefaultBuilderModel::getRepositoryPath() {
  return fwk_data->getRepositoryPath();
}

/** Return the list of unloaded classes and where
    they come from. argc is an even number, as you
    get the library location following each class entry.
    Class names will be unique, whether or not component
    writers worried about that.
*/
std::vector< std::string> DefaultBuilderModel::getRepositoryClasses() {
  return fwk_data->getRepositoryClasses();
}

/** Move a class from the repository to the
  factory. Probably involves a dynamic load.
  returns 0 if transferred successfully.
*/
int DefaultBuilderModel::loadRepositoryClass(const char *className, bool global, bool lazy) {
  int result;
  result = fwk_data->loadRepositoryClass(className, global, lazy);
  return result;
}

int DefaultBuilderModel::loadPorts(const std::string & libPathName)
{
  int result;
  result = fwk_data->loadPorts(libPathName);
  return result;
}

::std::vector< std::string > DefaultBuilderModel::getInstanceNames()
{
	return fwk_data->instanceNames();
}

