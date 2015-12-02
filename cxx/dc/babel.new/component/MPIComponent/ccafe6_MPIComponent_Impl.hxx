// 
// File:          ccafe6_MPIComponent_Impl.hh
// Symbol:        ccafe6.MPIComponent-v0.0
// Symbol Type:   class
// Description:   Server-side implementation for ccafe6.MPIComponent
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccafe6_MPIComponent_Impl_hh
#define included_ccafe6_MPIComponent_Impl_hh

#ifndef included_sidl_cxx_hh
#include "sidl_cxx.hh"
#endif
#ifndef included_ccafe6_MPIComponent_IOR_h
#include "ccafe6_MPIComponent_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_ccafe6_MPIComponent_hh
#include "ccafe6_MPIComponent.hh"
#endif
#ifndef included_gov_cca_AbstractFramework_hh
#include "gov_cca_AbstractFramework.hh"
#endif
#ifndef included_gov_cca_CCAException_hh
#include "gov_cca_CCAException.hh"
#endif
#ifndef included_gov_cca_Services_hh
#include "gov_cca_Services.hh"
#endif
#ifndef included_sidl_BaseInterface_hh
#include "sidl_BaseInterface.hh"
#endif
#ifndef included_sidl_ClassInfo_hh
#include "sidl_ClassInfo.hh"
#endif


// DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent._includes)

#include "util/IO.h"
#include "dc/babel.new/babel-cca/server/ccaffeine_ports_MPIService.hxx"
#include "dc/babel.new/babel-cca/server/ccaffeine_ports_MPIBorrow.hxx"
#include "dc/babel.new/babel-cca/server/ccaffeine_CCAException.hxx"
#include "gov_cca_ports.hxx"
namespace ccafe6 {
	class MPIBorrow_Impl;
	class MPIService_Impl;
}

// DO-NOT-DELETE splicer.end(ccafe6.MPIComponent._includes)

namespace ccafe6 { 

  /**
   * Symbol "ccafe6.MPIComponent" (version 0.0)
   * 
   * mpi component 
   */
  class MPIComponent_impl
  // DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccafe6.MPIComponent._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    MPIComponent self;

    // DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent._implementation)

	gov::cca::Services ms;
	gov::cca::AbstractFramework naf;
	gov::cca::ports::ServiceRegistry sr;
	ccaffeine::ports::MPIService mpis;
	ccaffeine::ports::MPIBorrow mpib;
	MPIService_Impl *m1;
	MPIBorrow_Impl *m2;
	/** true if component has been started already. */
	bool initialized;
	/** true if component has been shut down already. */
	bool finalized;
	/** true if component is initialized rather than loaded as a normal component. */
	bool isExternal;

	/* ms must already be defined when this is called
	 * and after its done mpis, mpib, m1,m2 will have their
	 * best available values.
	 */
	void initPrivate(int64_t borrowComm, int64_t dupComm)
	throw ( 
		::gov::cca::CCAException
	);

    // DO-NOT-DELETE splicer.end(ccafe6.MPIComponent._implementation)

  private:
    // private default constructor (required)
    MPIComponent_impl() {} 

  public:
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    MPIComponent_impl( struct ccafe6_MPIComponent__object * s ) : self(s,
      true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~MPIComponent_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:


    /**
     * Create and add to the framework MPIService and MPIBorrow
     * support services. This will appear in the frame as an
     * MPISetup component. MPI_Init must have been called before
     * this is called.
     * @param borrowComm  the shared communicator 
     *   for those using MPIBorrow.
     * @param dupComm  the communicator to duplicate 
     *   for those using MPIService.
     * @param af The frame into which the services will be added.
     */
    void
    initialize (
      /*in*/ int64_t borrowComm,
      /*in*/ int64_t dupComm,
      /*inout*/ ::gov::cca::AbstractFramework& af
    )
    throw ( 
      ::gov::cca::CCAException
    );


    /**
     * Shutdown the previous mpi-related services.
     * @param reclaim if reclaim true, try to release communicator
     * resources allocated in MPIService support.
     * Otherwise, lose them.
     */
    void
    finalize (
      /*in*/ bool reclaim
    )
    throw ( 
      ::gov::cca::CCAException
    );


    /**
     * Starts up a component presence in the calling framework.
     * @param Svc the component instance's handle on the framework world.
     * Contracts concerning Svc and setServices:
     * 
     * The component interaction with the CCA framework
     * and Ports begins on the call to setServices by the framework.
     * 
     * This function is called exactly once for each instance created
     * by the framework.
     * 
     * The argument Svc will never be nil/null.
     * 
     * Those uses ports which are automatically connected by the framework
     * (so-called service-ports) may be obtained via getPort during
     * setServices.
     */
    void
    setServices (
      /*in*/ ::gov::cca::Services services
    )
    throw ( 
      ::gov::cca::CCAException
    );


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
    getComm() throw ( 
      ::gov::cca::CCAException
    );

    /**
     * Let go the communicator. previously fetched with getComm.
     *  @throw CCAException if an error is detected.
     */
    void
    releaseComm (
      /*in*/ int64_t comm
    )
    throw ( 
      ::gov::cca::CCAException
    );


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
    borrowComm (
      /*in*/ int32_t tagsRequested,
      /*inout*/ ::sidl::array<int32_t>& tagList,
      /*inout*/ int32_t& key
    )
    throw ( 
      ::gov::cca::CCAException
    );


    /**
     * Return a previously borrowed communicator and tag list.
     *  @param tagCount: The length of tagList.
     *  @param tagList: The tags being returned, tagCount long.
     *  @param key: The key obtained with borrowComm. It is
     *         an error to attempt to return tags that you didn't receive.
     *  @throw CCAException if an error is detected.
     */
    void
    returnComm (
      /*in*/ int64_t comm,
      /*in*/ ::sidl::array<int32_t> tagList,
      /*in*/ int32_t key
    )
    throw ( 
      ::gov::cca::CCAException
    );

  };  // end class MPIComponent_impl

} // end namespace ccafe6

// DO-NOT-DELETE splicer.begin(ccafe6.MPIComponent._misc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccafe6.MPIComponent._misc)

#endif
