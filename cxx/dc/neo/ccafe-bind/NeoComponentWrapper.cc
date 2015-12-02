#include <neocca.hh>
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include "dc/neo/ccafe-bind/NeoPortConverter.hh"
#include "dc/neo/ccafe-bind/NeoServices.hh"
#include "dc/neo/ccafe-bind/NeoServicesHelper.hh"
#include "dc/neo/ccafe-bind/NeoComponentWrapper.hh"

NeoComponentWrapper::~NeoComponentWrapper()
{
 	delete cptr;
	cptr = 0;
	cs = 0;
}

neo::cca::Component *
NeoComponentWrapper::getWrapped() 
{ return cptr; }

void NeoComponentWrapper::setServices( ccafeopq::Services * svc) throw (ccafeopq::Exception)
{
	IO_dn1("NeoComponentWrapper::setServices enter");
	if ( svc != 0) {
		int64_t fComm;
                if (svc -> hasMPIComm(fComm) ) {
                        csh.initComm(fComm);
                } else {
                        csh.initComm(0);
                }
		NeoServicesHelper *cshp;
		cshp = &csh;
		ccafeopq::ServicesHelper *oshp;
		oshp = cshp;
		svc->addServicesHelper(oshp);
		cshp->addBindingDelegates(svc);
		cs = new NeoServices(svc);
		cptr->setServices(cs);
	} else {
		cs->notifyReleaseListeners();
		delete cs;
		cs = 0;
	}
	IO_dn1("NeoComponentWrapper::setServices leave");
}
