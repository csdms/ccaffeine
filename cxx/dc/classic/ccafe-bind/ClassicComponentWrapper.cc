#include <cca.h>
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include "dc/classic/ccafe-bind/ClassicPortConverter.hh"
#include "dc/classic/ccafe-bind/ClassicServices.hh"
#include "dc/classic/ccafe-bind/ClassicServicesHelper.hh"
#include "dc/classic/ccafe-bind/ClassicComponentWrapper.hh"

ClassicComponentWrapper::~ClassicComponentWrapper()
{
 	delete cptr;
	delete csh_ptr;
	delete cs;
	cs = 0;
	csh_ptr = 0;
	cptr = 0;
}

ClassicComponentWrapper::ClassicComponentWrapper(classic::gov::cca::Component* cmpt) : cptr(cmpt)
{
	csh_ptr = new ClassicServicesHelper();
	cs = 0; // will be created in setServices.
}

void ClassicComponentWrapper::setServices( ccafeopq::Services * svc) throw (ccafeopq::Exception)
{
	IO_dn1("ClassicComponentWrapper::setServices enter");
	if ( svc != 0) {
		int64_t fComm;
		if (svc -> hasMPIComm(fComm) ) {
			csh_ptr->initComm(fComm);
		} else {
			csh_ptr->initComm(0);
		}
		ccafeopq::ServicesHelper *oshp;
		oshp = csh_ptr;
		svc->addServicesHelper(oshp);
		csh_ptr->addBindingDelegates(svc);
		cs = new ClassicServices(svc);
		cptr->setServices(cs);
	} else {
		cptr->setServices(0);
	}
	IO_dn1("ClassicComponentWrapper::setServices leave");
}
