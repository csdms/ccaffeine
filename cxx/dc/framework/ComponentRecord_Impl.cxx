
#include <map>
#include <string>

#include "util/IO.h"

#include "dc/export/AllExport.hh"
#include "dc/services/dotcca/dccore/DotCCAComponentCore.hpp"
#include "ComponentRecord_Impl.h"

#define CRI_DEBUG 0

namespace {
char id[]=
"$Id: ComponentRecord_Impl.cxx,v 1.3 2004/11/05 00:42:55 baallan Exp $";
} ENDSEMI


::std::string
ccafe::ComponentRecord_Impl::getComponentClassName() throw (ccafeopq::Exception )
{ return ccd->getComponentClassName(); }

::std::string 
ccafe::ComponentRecord_Impl::getCCASpecBinding() throw (ccafeopq::Exception ) 
{ return ccd->getCCASpecBinding(); }

::std::string 
ccafe::ComponentRecord_Impl::getIndexFile() throw (ccafeopq::Exception ) 
{ return ccd->getIndexFile(); }
  
::std::string 
ccafe::ComponentRecord_Impl::getDeploymentClassAlias() throw (ccafeopq::Exception ) 
{ return ccd->getDeploymentClassAlias(); }

::std::string 
ccafe::ComponentRecord_Impl::getConstructorName() throw (ccafeopq::Exception )
{ return ccd->getConstructorName(); }

::std::string 
ccafe::ComponentRecord_Impl::getLibraryLoading() throw (ccafeopq::Exception)
{ return ccd->getLibraryLoading(); }

::std::string 
ccafe::ComponentRecord_Impl::getLibraryName() throw (ccafeopq::Exception )
{ return ccd->getLibraryName(); }

::std::string 
ccafe::ComponentRecord_Impl::getLibraryLocation() throw (ccafeopq::Exception )
{ return ccd->getLibraryLocation(); }

::std::string 
ccafe::ComponentRecord_Impl::getExecScript() throw (ccafeopq::Exception )
{ return ccd->getExecScript(); }

void 
ccafe::ComponentRecord_Impl::getDOMTree() throw (ccafeopq::Exception )
{ return ccd->getDOMTree(); }

bool 
ccafe::ComponentRecord_Impl::getInFactory()
{
  if (inFactory < 0 ) {
#if CRI_DEBUG
    std::cerr << __FILE__ << ": getInFactory " << getDeploymentClassAlias() << std::endl;
#endif
	throw ccafeopq::Exception("dead Factory record!");
  } else { 
	  return inFactory; 
  }
}

void 
ccafe::ComponentRecord_Impl::setInFactory(int i)
{ inFactory = i; }

void *
ccafe::ComponentRecord_Impl::getConstructorFunc()
{
	return (void *)create;
}

void 
ccafe::ComponentRecord_Impl::setConstructorFunc( void *create_)
{
#if CRI_DEBUG
    std::cerr << __FILE__ << " setConstructorFunc " << create_ << std::endl;
#endif
	create = ( void * (*)()) create_;
	setInFactory(1);
#if 0
	if (create == 0) {
		setInFactory(0);
	}
#endif
}

void 
ccafe::ComponentRecord_Impl::setCCD( ccafeopq::ComponentClassDescription_shared ccd_)
{
#if CRI_DEBUG
    std::cerr << __FILE__ << " setCCD " << ccd_->getDeploymentClassAlias() << std::endl;
#endif
	ccd = ccd_;
}

void
ccafe::ComponentRecord_Impl::setFoundInPath(bool tf)
{
#if CRI_DEBUG
    std::cerr << __FILE__ << " setFoundInPath " << tf << std::endl;
#endif
	foundInPath = tf;
}

bool ccafe::ComponentRecord_Impl::getFoundInPath()
{
	return foundInPath;
}

ccafe::ComponentRecord_Impl::ComponentRecord_Impl()
{
    create = 0;
    inFactory = 0;
#if CRI_DEBUG
    std::cerr << __FILE__ << ": CTOR" << std::endl;
#endif
}

ccafe::ComponentRecord_Impl::~ComponentRecord_Impl()
{
#if CRI_DEBUG
    std::cerr << __FILE__ << ": DTOR in" << std::endl;
#endif
    create = 0;
    inFactory = -1;
    ccd.reset();
#if CRI_DEBUG
    std::cerr << __FILE__ << ": DTOR out" << std::endl;
#endif
}

std::string
ccafe::ComponentRecord_Impl::toString()
{
	std::string s = "";
	s += "{";
	s += getComponentClassName();
	s += "} ";
	s += "{";
	s += getCCASpecBinding();
	s += "} ";
	s += "{";
	s += getIndexFile();
	s += "} ";
	s += "{";
	s += getDeploymentClassAlias();
	s += "} ";
	s += "{";
	s += getConstructorName();
	s += "} ";
	s += "{";
	s += getLibraryLoading();
	s += "} ";
	s += "{";
	s += getLibraryName();
	s += "} ";
	s += "{";
	s += getLibraryLocation();
	s += "} ";
	s += "{";
	s += getExecScript();
	s += "} ";
	s += "{";
	s += (getFoundInPath() ? "inPath" : "notInPath");
	s += "} ";
	s += "{";
	s += (getConstructorFunc() != 0)?"inFactory" : "notInFactory";
	s += "} ";
	return s;
}

