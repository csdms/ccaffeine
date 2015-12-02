// this file disappears if there is no mpi.
#ifdef _CCAMPI
#include <mpi.h>
#include "util/noSeekMPI.h"
#include "util/IO.h"
#include "dc/export/config.hh"
#ifdef HAVE_CLASSIC
#include <cca.h>
#include <ports/MPIBorrow.h>
#endif // HAVE_CLASSIC
#ifdef HAVE_NEO
#include <neocca.hh>
#include <neoports.hh>
#endif // HAVE_NEO
#include "dc/port/DefaultMPIBorrow.h"

DefaultMPIBorrow::DefaultMPIBorrow(int64_t fComm) {
  IO_dn2("DefaultMPIBorrow::DefaultMPIBorrow(%d)",(int)fComm);
  maxTag = 0;
  maxKey = 0;
  fortranMPIComm = fComm;
}

DefaultMPIBorrow::~DefaultMPIBorrow() {
	maxTag = -1;
	maxKey = -1;
}

MPI_Comm DefaultMPIBorrow::borrowComm(int tcount, int *tags, int &key) {
	if (this == 0 || maxTag == -1) { return MPI_COMM_NULL; }
	maxKey++;
  key = maxKey;
	for (int i = 0; i < tcount; i++) {
		tags[i] = i+ maxTag;
	}
	maxTag = tags[tcount-1] + 1;
      MPI_Fint cfcomm = (MPI_Fint)fortranMPIComm;
      MPI_Comm urcomm = MPI_Comm_f2c(cfcomm);
  return urcomm;
}

void DefaultMPIBorrow::returnComm(MPI_Comm comm, int tcount, int *tags, int key) {
	if (this == 0 || maxTag == -1) { return; }
  if (key == maxKey-1) {
		maxKey--;
	} else {
		if (key < 0 || key > maxKey) { return; }
	}
	if (tcount < 0 || tcount > maxTag) { return; }
	for (int i = 0; i < tcount; i++) {
		tags[i] = -1;
	}
}

#endif // _CCAMPI
