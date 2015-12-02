#include <neocca.hh>
#include <neosupport.hh>
#include "dc/export/AllExport.hh"
#include "dc/neo/ccafe-bind/NeoAbstractFramework.hh"
#include "dc/neo/ccafe-bind/NeoMacros.hh"
// #include "dc/framework/Frame.h"
#include "dc/framework/OpqAbstractFramework.h"
#include "dc/neo/ccafe-bind/ccafeTypeMap.hh"
#include "dc/neo/ccafe-bind/NeoOpaqueTypeMap.hh"
#include "dc/neo/ccafe-bind/NeoPortConverter.hh"
#include "dc/neo/ccafe-bind/NeoServices.hh"

/** causes oaf to be defined in the local scope, unwrapping it from
 * void * in the process. If opqFramework is null, causes death.
 */
#define OAF \
ccafe::AbstractFramework *oaf = static_cast< ccafe::AbstractFramework *>(opqFramework); \
if (opqFramework == 0 || oaf == 0) throw neo::cca::Exception("Ccaffeine AbstractFramework pointer is missing!")

NeoAbstractFramework::NeoAbstractFramework(int64_t fComm, bool useComm)
{
	ccafe::AbstractFramework * fwk = new ccafe::AbstractFramework(fComm,useComm);
	opqFramework = static_cast<void *>(fwk);
	if (useComm) {
		hasComm = true;
		fComm = fComm;
	} else {
		hasComm = false;
		fComm = -1;
	}
}

// ccafe extension
void 
NeoAbstractFramework::initialize( const ::std::string & args )
{
	OAF;
	oaf->initWithString( args);
}

void 
NeoAbstractFramework::run( NeoMain *driver )
{
	neo::cca::AbstractFramework * ncaf = this;
	driver->driverBody(ncaf);
}

// standard interface
NeoAbstractFramework::~NeoAbstractFramework()
{
	OAF;
	delete oaf;
	opqFramework = 0;
	if (hasComm) {
		fortranMPIComm = -2;
		hasComm = false;
	}
}

neo::cca::TypeMap_shared 
NeoAbstractFramework::createTypeMap()
{
	OAF;
	ccafeopq::TypeMap_shared otm = oaf->createTypeMap();
	neo::cca::TypeMap_shared ntm = ccafe::TypeMap::neoWrap(otm);
	return ntm;
}

neo::cca::Services *
NeoAbstractFramework::getServices(const std::string & selfInstanceName, const std::string & selfClassName, neo::cca::TypeMap_shared selfProperties)
{
	OAF;

	N2OMAP(selfProperties, otm);

	ccafeopq::Services * os = oaf->getServices(selfInstanceName, selfClassName, otm);

	NeoServices *ns = new NeoServices(os);

	return ns;
}

void 
NeoAbstractFramework::releaseServices( neo::cca::Services * svc)
{
	OAF;
	NeoServices *ns = dynamic_cast< NeoServices * >(svc);
	if (ns == 0) {
		return; // throw? not one of ours
	}
	ns->notifyReleaseListeners();
	ccafeopq::Services * os = ns->unwrapServices();
	oaf->releaseServices(os);
	delete svc;

}

void 
NeoAbstractFramework::shutdownFramework()
{
	OAF;
	oaf->shutdownFramework();
}

neo::cca::AbstractFramework * 
NeoAbstractFramework::createEmptyFramework()
{
	NeoAbstractFramework * nnf = new NeoAbstractFramework(fortranMPIComm,hasComm);
	neo::cca::AbstractFramework * nf = nnf;
	return nf;
}

void 
NeoAbstractFramework::destroyEmptyFramework( neo::cca::AbstractFramework * subframe)
{
	// make sure it came from us.
	NeoAbstractFramework *nnf = dynamic_cast< NeoAbstractFramework *>(subframe);
	delete nnf;
}
