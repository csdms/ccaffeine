// 
// File:          ccafe6_MPIComponent_Impl.cc
// Symbol:        ccafe6.MPIComponent-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for ccafe6.MPIComponent
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccafe6_MPIComponent_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent._includes)

#include "util/noSeekMPI.h"
#include <mpi.h>
#include "dc/babel/babel-cca/server/ccaffeine_Services.hh"

// if FASCIST_PORT_TYPES  true (1) then register only as
// ccaffeine.ports.MPI*, not gov/cca names.
#define FASCIST_PORT_TYPES 1

namespace {

class CommHolder {
private:
	MPI_Comm com;
public:
	CommHolder(MPI_Comm c) : com(c) {}
	~CommHolder(){}
	MPI_Comm getComm() { return com; }
	void destroy() {
		MPI_Comm_free(&com);
	}
}; // end class commholder

} // end anon namespace

namespace ccafe6 {

class MPIService_Impl 
{

private:
	/** coms for recycle */
	std::vector< CommHolder *> rlist;
	/** coms in use */
	std::vector< CommHolder *> ulist;
	MPI_Comm prototype;

public:

	MPIService_Impl(MPI_Comm comm);
	virtual ~MPIService_Impl();
	virtual MPI_Comm getComm();
	virtual void releaseComm(MPI_Comm m);
	void reclaim();

}; // end class MPIService_Impl

class MPIBorrow_Impl
{

private:

	/** next available tag. */
	int maxTag;

	/** last issued key */
	int maxKey;

	MPI_Comm common;

public:

	MPIBorrow_Impl(MPI_Comm shareable);

	~MPIBorrow_Impl();

	/** Get a communicator and a set of available tags on it.
	* FIXME need to keep a key:tag lookup array to be fully safe.
	* FIXME need to keep a key comm lookup, if we manage more than one comm...
	* FIXME in neo/classic worlds, we may have conflicting tag lists
	* as they are not all around a central opaque mpi service.
	*/
	MPI_Comm borrowComm(int tagcount,  ::sidl::array<int32_t>& tagList, int&key);

	/** Return a communicator and release the tags on it. */
	void returnComm(MPI_Comm c, int tagcount,  ::sidl::array<int32_t> & tagList, int key);

};


//---------------------------------------------------------------
//---------------------------------------------------------------


MPIBorrow_Impl::MPIBorrow_Impl(MPI_Comm comm) {
	common = comm;
	maxTag = 0;
	maxKey = 0;
}

MPIBorrow_Impl::~MPIBorrow_Impl() {
	maxTag = -1;
	maxKey = -1;
}

MPI_Comm  
MPIBorrow_Impl::borrowComm(int tcount, ::sidl::array<int32_t>& tagList, int & key) {
	if (this == 0 || maxTag == -1) { return MPI_COMM_NULL; }
	maxKey++;
	key = maxKey;
	for (int i = 0; i < tcount; i++) {
		tagList.set( i , i + maxTag);
	}
	maxTag = tagList.get(tcount-1) + 1;
	return common;
}

void MPIBorrow_Impl::returnComm(MPI_Comm comm, int tcount, ::sidl::array<int32_t>& tags, int key) {
	if (this == 0 || maxTag == -1) { return; }
	// so if we get a use/return, we don't 
	if (key == maxKey-1) {
		maxKey--;
	} else {
		if (key < 0 || key > maxKey) { return; }
	}
	if (tcount < 0 || tcount > maxTag) { return; }
	for (int i = 0; i < tcount; i++) {
		tags.set(i , -1);
	}
}

//------------------------------------------------
//------------------------------------------------


MPIService_Impl::MPIService_Impl(MPI_Comm comm) {
	prototype = comm;
}

MPIService_Impl::~MPIService_Impl() {
	size_t i, cap;
	cap = rlist.size();
	for (i = 0; i < cap; i++) {
		CommHolder *c = rlist[i];
		c->destroy();	
		delete c;
		rlist[i] = 0;
	}
	rlist.clear();
	cap = ulist.size();
	for (i = 0; i < cap; i++) {
		// this shouldn't occur if user is correct.
		CommHolder *c2 = ulist[i];
		delete c2;
		ulist[i] = 0;
	}
	ulist.clear();
}

void
MPIService_Impl::reclaim() {
	size_t i, cap;
	cap = rlist.size();
	for (i = 0; i < cap; i++) {
		CommHolder *c = rlist[i];
		c->destroy();	
	}
	cap = ulist.size();
	for (i = 0; i < cap; i++) {
		CommHolder *c2 = ulist[i];
		c2->destroy();	
	}
	ulist.clear();
}

MPI_Comm
MPIService_Impl::getComm() {
	// check for one recyclable
	if (rlist.size() > 0) {
		CommHolder *c = rlist[(rlist.size()-1)];
		rlist.erase(rlist.end()-1);
		ulist.push_back(c);
		MPI_Comm result = c->getComm();
		return result;
	}
	// make a new duplicate. save it and return it.
	MPI_Comm tmp;
	MPI_Comm_dup(prototype, &tmp);
	CommHolder *c2 = new CommHolder(tmp);
        ulist.push_back(c2);	
	return tmp;
}

void 
MPIService_Impl::releaseComm(MPI_Comm m) {
  
	if (m == MPI_COMM_NULL) {
		return;
	}
	// if we don't find it, ignore it quietly.
	size_t i, cap;
	cap = ulist.size();
	for (i = 0; i < cap; i++) {
		int result;
		MPI_Comm tmp = ulist[i]->getComm();
		MPI_Comm_compare(m,tmp,&result);
		if (result == MPI_IDENT) {
			CommHolder *c = ulist[i];
			rlist.push_back(c);
			ulist.erase(ulist.begin()+i);
			return;
		}
	}
}

} // end namespace ccafe6

namespace {

void whine(std::string s)
{
	ccaffeine::CCAException ex = ::ccaffeine::CCAException::_create();
	ex.setNote(s);
	throw ex;
}
// fixme-feature traceback
#define WHINE(s) whine(s)

}; // end namespace anon

#include <iostream>

// DO-NOT-DELETE splicer.end(ccafe6.MPIComponent._includes)

// user defined constructor
void ccafe6::MPIComponent_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent._ctor)
	m1 = 0;
	m2 = 0;
	initialized = false;
	finalized = false;
	isExternal = true;
	IO_dn1("MPIComponent is now constructed\n");
  // DO-NOT-DELETE splicer.end(ccafe6.MPIComponent._ctor)
}

// user defined destructor
void ccafe6::MPIComponent_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent._dtor)
  // add destruction details here
	delete m1;
	delete m2;
	m2 = 0;
	m1 = 0;
  // DO-NOT-DELETE splicer.end(ccafe6.MPIComponent._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Create and add to the framework MPIService and MPIBorrow
 * support services. This will appear in the frame as an
 * MPISetup component. MPI_Init must have been called before
 * this is called.
 * @param borrowComm  the shared communicator 
 *   for those using MPIBorrow. In Fortran format.
 * @param dupComm  the communicator to duplicate 
 *   for those using MPIService. In Fortran format.
 * @param af The frame into which the services will be added.
 */
void
ccafe6::MPIComponent_impl::initialize (
  /*in*/ int64_t borrowComm,
  /*in*/ int64_t dupComm,
  /*inout*/ ::gov::cca::AbstractFramework& af ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent.initialize)

	if (initialized) {
		WHINE("ccafe6::MPIComponent::initialize called redundantly.");
	}
	if (af._is_nil()) {
		std::cerr << "Ugh! no framework. dying..." << std::endl;
		WHINE("ccafe6::MPIComponent::initialize got af==0");
	}
	naf = af;
	isExternal = true;
	gov::cca::TypeMap mstm;
	ms = naf.getServices("MPISetup","ccafe6.MPIComponent", mstm);
	initPrivate(borrowComm, dupComm);

  // DO-NOT-DELETE splicer.end(ccafe6.MPIComponent.initialize)
}

/**
 * Create and add to the framework MPIService and MPIBorrow
 * support services. This will appear in the frame as an
 * MPISetup component. MPI_Init must have been called before
 * this is called.
 * @param borrowComm  the shared communicator 
 *   for those using MPIBorrow. In Fortran format.
 * @param dupComm  the communicator to duplicate 
 *   for those using MPIService. In Fortran format.
 * @param af The frame into which the services will be added.
 */
void
ccafe6::MPIComponent_impl::initializeCcafe (
  /*inout*/ ::gov::cca::AbstractFramework& af ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent.initializeCcafe)
	if (initialized) {
		WHINE("ccafe6::MPIComponent::initializeCcafe called redundantly.");
	}
	if (af._is_nil()) {
		std::cerr << "Ugh! no framework. dying..." << std::endl;
		WHINE("ccafe6::MPIComponent::initialize got af==0");
	}
	isExternal = true;
	naf = af;
	gov::cca::TypeMap mstm;
	ms = naf.getServices("MPISetup","MPISetup", mstm);

        int64_t comm = 0;
	ccaffeine::Services us = ::babel_cast<ccaffeine::Services> (ms); // CAST
	if (us._is_nil()) {
		std::cerr << "MPIComponent.initializeCcafe called outside ccaffeine..." << std::endl;
		WHINE("ccafe6::MPIComponent::initializeCcafe called in non-ccaffeine framework.");
	}
	if (! us.hasMPIComm(comm) ) {
#if 0 // here is what we must not do
		std::cerr << "MPIComponent.initializeCcafe called without mpi in build." << std::endl;
		WHINE("ccafe6::MPIComponent::initializeCcafe called in non-MPI framework.");
#endif
		initialized = finalized = true;
		// we're done. no mpi to be had. so we just be quiet.
		return;
	}

	initPrivate(comm,comm);
	return;


  // DO-NOT-DELETE splicer.end(ccafe6.MPIComponent.initializeCcafe)
}

/**
 * Shutdown the previous mpi-related services.
 * @param reclaim if reclaim true, try to release communicator
 * resources allocated in MPIService support.
 * Otherwise, lose them.
 */
void
ccafe6::MPIComponent_impl::finalize (
  /*in*/ bool reclaim ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent.finalize)
	if (! initialized) {
		WHINE("ccafe6::MPIComponent::finalize called before init or setServices.");
	}
	if (! finalized) {
		finalized = true;
		sr.removeService("ccaffeine.ports.MPIService");
		sr.removeService("ccaffeine.ports.MPIBorrow");
#if FASCIST_PORT_TYPES
// no alii
#else
		sr.removeService("gov.cca.ports.MPIService");
		sr.removeService("gov::cca::ports::MPIService");
		sr.removeService("::gov::cca::ports::MPIService");
		sr.removeService("gov.cca.ports.MPIBorrow");
		sr.removeService("gov::cca::ports::MPIBorrow");
		sr.removeService("::gov::cca::ports::MPIBorrow");
#endif // FASCIST_PORT_TYPES
		ms.releasePort("serviceRegistry");
		ms.unregisterUsesPort("serviceRegistry");
		sr = 0;
	}
	if (isExternal) {
		naf.releaseServices(ms);
		naf = 0;
	}
	ms = 0;
	mpis = 0;
	mpib = 0;

	if (reclaim) { // fixme
		m1->reclaim();
	}

  // DO-NOT-DELETE splicer.end(ccafe6.MPIComponent.finalize)
}

/**
 * Get an mpi communicator with the same scope as the component instance.
 * Won't be mpi_comm_null. The communicator returned will be
 * private to the recipient, which implies an mpicommdup.
 * @return The comm produced, in FORTRAN form. C callers use comm_f2c
 * method defined by their mpi implementation, usually MPI_Comm_f2c,
 * to convert result to MPI_Comm.
 * @throw CCAException if the service cannot be implemented because MPI is
 * not present.
 */
int64_t
ccafe6::MPIComponent_impl::getComm () 
throw ( 
  ::gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent.getComm)
  MPI_Comm ccomm = m1->getComm();
  int64_t fcomm = MPI_Comm_c2f(ccomm);
  return fcomm;
  // DO-NOT-DELETE splicer.end(ccafe6.MPIComponent.getComm)
}

/**
 * Let go the communicator. previously fetched with getComm.
 *  @throw CCAException if an error is detected.
 */
void
ccafe6::MPIComponent_impl::releaseComm (
  /*in*/ int64_t comm ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent.releaseComm)
  MPI_Comm ccomm = MPI_Comm_f2c(comm);
  m1->releaseComm(ccomm);
  // DO-NOT-DELETE splicer.end(ccafe6.MPIComponent.releaseComm)
}

void
ccafe6::MPIComponent_impl::setServices (
  /* in */ ::gov::cca::Services services )
throw (
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent.setServices)
	if (initialized) {
		WHINE("ccafe6.MPIComponent.setServices called after external initializer used.");
	}
	isExternal = false;
	ms = services;
        int64_t comm = 0;
	ccaffeine::Services us = ::babel_cast<ccaffeine::Services> (ms); // CAST
	if (us._is_nil()) {
		std::cerr << "MPIComponent.setServices called outside ccaffeine..." << std::endl;
		WHINE("ccafe6::MPIComponent::setServices called in non-ccaffeine framework.");
	}
	if (! us.hasMPIComm(comm) ) {
		std::cerr << "MPIComponent.setServices called without mpi in build." << std::endl;
#if 0 // here is what we must not do
		WHINE("ccafe6::MPIComponent::setServices called in non-MPI ccaffeine.");
#endif
		initialized = finalized = true;
		// we're done. no mpi to be had. so we just be quiet.
		return;
	}

	initPrivate(comm,comm);
  // DO-NOT-DELETE splicer.end(ccafe6.MPIComponent.setServices)
}
                                                                               
void
ccafe6::MPIComponent_impl::releaseServices (
  /* in */ ::gov::cca::Services Svc )
throw (
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent.releaseServices)
	if (isExternal) {
		WHINE("ccafe6.MPIComponent.releaseServices called incorrectly");
	}
	self.finalize(true);
  // DO-NOT-DELETE splicer.end(ccafe6.MPIComponent.releaseServices)
}
        
/**
 * Get a communicator of the port provider (in FORTRAN form).
 * This communicator will be the same instance as the comm of the
 * port provider, with all the message collision potential that implies.
 * Instances which have a comm covering only a subset of themselves
 * will return FORTRAN MPI_COMM_NULL on their "un-covered" processes.
 * 
 * @param tagCount: The number of tags the borrower wishes to use
 * all to itself.
 * @param tagList: Array to be filled with tags available. The
 * array given as input is at least tagCount long.
 * @param key: key to be returned when the tags and comm are done with.
 * @return The comm being borrowed, in FORTRAN form. C callers use comm_f2c
 * method defined by their mpi implementation, usually MPI_Comm_f2c,
 * to convert result to MPI_Comm.
 * @throw CCAException if the service cannot be implemented because MPI is
 * not present.
 */
int64_t
ccafe6::MPIComponent_impl::borrowComm (
  /*in*/ int32_t tagsRequested,
  /*inout*/ ::sidl::array<int32_t>& tagList,
  /*inout*/ int32_t& key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent.borrowComm)
	MPI_Comm ccomm = m2->borrowComm(tagsRequested, tagList, key);
	int64_t fcomm = MPI_Comm_c2f(ccomm);
	return fcomm;
  // DO-NOT-DELETE splicer.end(ccafe6.MPIComponent.borrowComm)
}

/**
 * Return a previously borrowed communicator and tag list.
 *  @param tagCount: The length of tagList.
 *  @param tagList: The tags being returned, tagCount long.
 *  @param key: The key obtained with borrowComm. It is
 *         an error to attempt to return tags that you didn't receive.
 *  @throw CCAException if an error is detected.
 */
void
ccafe6::MPIComponent_impl::returnComm (
  /*in*/ int64_t comm,
  /*in*/ int32_t tagsRequested,
  /*in*/ ::sidl::array<int32_t> tagList,
  /*in*/ int32_t key ) 
throw ( 
  ::gov::cca::CCAException
){
  // DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent.returnComm)
	MPI_Comm ccomm = MPI_Comm_f2c(comm);
	m2->returnComm(ccomm, tagsRequested, tagList, key);
  // DO-NOT-DELETE splicer.end(ccafe6.MPIComponent.returnComm)
}


// DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent._misc)
// Put miscellaneous code here

void ccafe6::MPIComponent_impl::initPrivate(int64_t borrowComm, int64_t dupComm)
throw ( ::gov::cca::CCAException)
{
	if (initialized) {
		WHINE("ccafe6::MPIComponent_impl::initPrivate called redundantly.");
	}
	MPI_Fint bc = borrowComm; // CAST
	MPI_Fint dc = dupComm; // CAST
	mpis = self;
	mpib = self;
	MPI_Comm bComm = MPI_Comm_f2c(bc);
	MPI_Comm dComm = MPI_Comm_f2c(dc);
	m1 = new MPIService_Impl(dComm);
	m2 = new MPIBorrow_Impl(bComm);

	gov::cca::TypeMap mstm;
	ms.registerUsesPort("serviceRegistry", "gov.cca.ports.ServiceRegistry", mstm);
	gov::cca::Port p = ms.getPort("serviceRegistry");
	sr = p;
	if (sr._is_nil())
	{
		WHINE("no ServiceRegistry available.");
	}

        // We can add the same service under multiple types so that
        // the users of mpi ports don't have to be perfect within
        // the ambiguities of c++.
        // support 3:
        //      gov::cca::ports::MPIBorrow/Service
        //      ::gov::cca::ports::MPIBorrow/Service
        //      gov.cca.ports.MPIBorrow/Service
	// This is of course pointless if we strictly enforce port
	// type naming as the sidl naming, per recent additions of tom.
        if (!sr.addSingletonService("ccaffeine.ports.MPIBorrow", mpib))
        {
                WHINE("ServiceRegistry rejected ccaffeine.ports.MPIBorrow.");
        }
        if (!sr.addSingletonService("ccaffeine.ports.MPIService", mpis))
        {
                WHINE("ServiceRegistry rejected ccaffeine.ports.MPIService." );
        }
#if FASCIST_PORT_TYPES
// no extras
#else
        if (!sr.addSingletonService("gov::cca::ports::MPIBorrow", mpib))
        {
                WHINE("ServiceRegistry rejected gov::cca::ports::MPIBorrow.");
        }
        if (!sr.addSingletonService("::gov::cca::ports::MPIBorrow", mpib))
        {
                WHINE("ServiceRegistry rejected ::gov::cca::ports::MPIBorrow." );
        }
        if (!sr.addSingletonService("gov.cca.ports.MPIBorrow", mpib))
        {
                WHINE("ServiceRegistry rejected gov.cca.ports.MPIBorrow." );
        }
        if (!sr.addSingletonService("gov::cca::ports::MPIService", mpis))
        {
                WHINE("ServiceRegistry rejected gov::cca::ports::MPIService." );
        }
        if (!sr.addSingletonService("::gov::cca::ports::MPIService", mpis))
        {
                WHINE("ServiceRegistry rejected ::gov::cca::ports::MPIService." );
        }
        if (!sr.addSingletonService("gov.cca.ports.MPIService", mpis))
        {
                WHINE("ServiceRegistry rejected gov.cca.ports.MPIService." );
        }
#endif // FASCIST_PORT_TYPES
	initialized = true;
}

// DO-NOT-DELETE splicer.end(ccafe6.MPIComponent._misc)

