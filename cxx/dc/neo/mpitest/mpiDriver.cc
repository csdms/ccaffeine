#include "mpiTest_scr_NeoMain.hh"
#include <neosupport/MPISetup.hh>
#include "dc/neo/ccafe-bind/neoCcafePublic.hh"
#include <iostream>


/** in this example, we just use commworld everywhere without
 * partitioning. We don't check for exceptions other than
 * in the user code, myScript.
 */
int main(int argc, char **argv) {

	MPI_Init(&argc,&argv);

	int64_t fcomm = MPI_Comm_c2f(MPI_COMM_WORLD);
	NeoAbstractFramework naf(fcomm);
	neo::cca::AbstractFramework * af = &naf;

	// set up the mpi services 
	neo::support::MPISetup mpiServices;
	mpiServices.initialize(MPI_COMM_WORLD, MPI_COMM_WORLD, af);

	// do the script specific code
	mpiTest_scr_NeoMain myScript;

	try {
		naf.run( &myScript);
	}
	catch ( ::neo::cca::Exception &oe)
	{
		::std::cout << "mpiDriver caught fatal error:" << ::std::endl;
		::std::cout << oe.what() << ::std::endl;
		::std::cerr << "mpiDriver caught fatal error:" << ::std::endl;
		::std::cerr << oe.what() << ::std::endl;
		return -2;
	}
	catch ( ::std::exception &e)
	{
		::std::cout << "mpiDriver caught fatal error:" << ::std::endl;
		::std::cout << e.what() << ::std::endl;
		::std::cerr << "mpiDriver caught fatal error:" << ::std::endl;
		::std::cerr << e.what() << ::std::endl;
		return -2;
	}

	// tear down the mpi services 
	mpiServices.finalize(true);

	MPI_Finalize();
	return 0;
}
