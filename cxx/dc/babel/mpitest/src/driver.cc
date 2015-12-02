#include "util/noSeekMPI.h"
#include <mpi.h>
#include "mpitest_script_babel.hh"
#include "dc/babel/babel-cca/AllBabelCCA.hh"
#include "dc/babel/component/MPIComponent/server/ccafe6.hh"
#include <iostream>

int mpitest_script_babel_doit(int argc, char **argv) {

	MPI_Init(&argc,&argv);

	int64_t borrowComm = MPI_Comm_c2f(MPI_COMM_WORLD);
	int64_t dupComm = MPI_Comm_c2f(MPI_COMM_WORLD);

	ccaffeine::AbstractFramework caf = 
		ccaffeine::AbstractFramework::_create();
	gov::cca::AbstractFramework af = caf; // CAST

	// now for the MPI setup. Obviously the communicator
	// could be split, and the separate sub-Comms set
	// on distinct frames if we made more than one instance
	// of ccaffeine::AbstractFramework.

	ccafe6::MPIComponent mpiProvider = ccafe6::MPIComponent::_create();
	mpiProvider.initialize( borrowComm, dupComm, af);


	// now for the user-specific code
	mpitest_script_babel::BabelMain myScript;
	myScript = mpitest_script_babel::BabelMain::_create();
	ccaffeine::BabelMain cbm = myScript; // CAST

	try {
		caf.run( cbm );
		mpiProvider.finalize(false); // false as we used commworld
	}
	catch ( ::gov::cca::CCAException oe)
	{
		::std::cout << "driver caught fatal error:" << ::std::endl;
		::std::cout << oe.getNote() << ::std::endl;
		::std::cerr << "driver caught fatal error:" << ::std::endl;
		::std::cerr << oe.getNote() << ::std::endl;
		return -2;
	}
	catch ( ::std::exception &e)
	{
		::std::cout << "driver caught fatal error:" << ::std::endl;
		::std::cout << e.what() << ::std::endl;
		::std::cerr << "driver caught fatal error:" << ::std::endl;
		::std::cerr << e.what() << ::std::endl;
		return -2;
	}

	return 0;
}

int main(int argc, char **argv) {
	return	mpitest_script_babel_doit(argc,argv);
}	
