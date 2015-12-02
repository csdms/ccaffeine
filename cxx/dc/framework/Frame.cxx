
#include <vector>
#include <map>
#include <string>
#include <unistd.h>
#include "dc/export/config.hh"
#ifdef HAVE_CLASSIC
#include <cca.h>
#include <stdPorts.h>
#endif // HAVE_CLASSIC
#ifdef HAVE_NEO
#include <neocca.hh>
#endif // HAVE_NEO

#include "dc/export/ccafeopq.hh"
#include "dc/framework/dc_fwkStar.h"
#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/BuilderView.h"
#include "dc/user_iface/DefaultBuilderModel.h"
#include "dc/user_iface/CmdLineBuilderView.h"
  
#include "dc/framework/KernelPort.h"
#include "util/IO.h"
#include "util/StringTools.hh"

namespace {
char id[]=
"$Id: Frame.cxx,v 1.9 2006/07/31 23:48:36 baallan Exp $";
} ENDSEMI

#ifdef HAVE_BABEL
#include "babel_compat.hh"
#endif

#define CCAFE_FRAME_PRIVATE_OK

#include "dc/framework/Frame.h"

#define DECLDBM \
	DefaultBuilderModel * dbm; \
	dbm = (DefaultBuilderModel *)bm

#define CHECKDBM(s) \
	if (dbm == 0) { \
		::std::cerr << "ccafe::Frame::" << s << \
			" null DefaultBuilderModel" << ::std::endl; \
       	} \
	assert(dbm!=0)

// -------------------------------------------------------

ccafe::Frame::Frame(int64_t fComm, bool useComm)
{
	int err = 0;
	DECLDBM;
	dbm = new DefaultBuilderModel(err,0,fComm, useComm);
	CHECKDBM("Frame");
	bm = (void *)dbm;
}

ccafe::Frame::~Frame()
{
	DECLDBM;
	CHECKDBM("~Frame");
	delete dbm;
	dbm = 0;
	bm = 0;
}

void ccafe::Frame::initialize( const ::std::string & args ) 
{
	DECLDBM;
	CHECKDBM("initialize");

	ComponentFactory_shared factory;
	ConnectionFramework *cf;
	cf = dbm->getFramework();
	factory = cf->getBaseComponentFactory();
// BUG BUG BUG FIXME
  std::vector< std::string > v = StringTools::split(args);
  //  const char ** loadCmpt = 0;
  for(unsigned int i = 0;i < v.size();i++) {
    if(v[i] == "--path") {
      std::string path = v[++i];
      std::vector< std::string > p = StringTools::split(path,':');
      IO_dn1("Component search path being set to:");
      for(unsigned int i = 0;i < p.size();i++) {
        IO_dn2("Component path element: %s", p[i].c_str());
      }
      IO_dn1("into ComponentFactory");
	// this logic, and where it derived from, is buggy.
	// probably want append path
      factory->setComponentPath(p);
      IO_dn1("into ComponentFactory");
      factory->indexComponentPath();
      IO_dn1("returned from ComponentFactory");
      continue;
    }
    if(v[i] == "--load") {
      std::string c = v[++i];
      std::vector< std::string > cmpts = StringTools::split(c, ':');
      for(unsigned int i = 0;i < cmpts.size();i++) {
        factory->loadClass(cmpts[i], true, true);
        IO_dn2("Loaded %s into pallet", cmpts[i].c_str());
      }
      continue;
    }

  }

}

ccafeopq::TypeMap_shared 
ccafe::Frame::createTypeMap()
{
	::ccafeopq::TypeMap_shared tm = Gizzard::createTypeMapStatic();
	return tm;
}

ccafeopq::Services * 
ccafe::Frame::getServices ( const ::std::string& selfInstanceName, const ::std::string& selfClassName, ::ccafeopq::TypeMap_shared selfProperties)
{

	DECLDBM;
	CHECKDBM("getServices");
	ConnectionFramework *cf;
	cf = dbm->getFramework();
	cf->addExternalComponent(selfInstanceName, selfClassName, selfProperties);
	Gizzard *g = cf->getGizzard(selfInstanceName);
	if (! g) {
		// whine
		// FIXME
	}
	return g;

}

void 
ccafe::Frame::releaseServices ( ::ccafeopq::Services *svc)
{
	// Before we get here, a binding should have called
	// the appropriate shutdown ComponentRelease interfaces.
	DECLDBM;
	CHECKDBM("releaseServices");
	ConnectionFramework *cf;
	cf = dbm->getFramework();
	ccafeopq::ComponentID_shared cid = svc->getComponentID();
	std::string selfInstanceName = cid->getInstanceName();
	cf->removeExternalComponent(selfInstanceName);
}

void 
ccafe::Frame::shutdownFramework()
{
	DECLDBM;
	CHECKDBM("shutdownFramework");
	// need bm->shutdown
	// FIXME
}
