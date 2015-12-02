// this file disappears if there is no mpi.
#ifdef _CCAMPI
#include <mpi.h>
#include "util/noSeekMPI.h"
#include "util/IO.h"

// The ifdef below needed for Leopard (issue494)
#ifdef OS_MACOSX
#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif
#ifndef SEEK_END
#define SEEK_END 2
#endif
#endif // OS_MACOSX

#include "dc/export/config.hh"
#ifdef HAVE_CLASSIC
#include <cca.h>
#include <ports/MPIService.h>
#endif // HAVE_CLASSIC
#ifdef HAVE_NEO
#include <neocca.hh>
#include <neoports.hh>
#endif // HAVE_NEO
#include "dc/port/DefaultMPIService.h"

const int DefaultMPIService::cap; // small enough for debugging demos. must match header

DefaultMPIService::DefaultMPIService(int64_t fComm) {
	int i;
  IO_dn2("DefaultMPIService::DefaultMPIService(%d)",(int)fComm);
  fortranMPIComm = fComm;
  for (i = 0; i < cap; i++) {
    comm[i] = MPI_COMM_NULL;
    inuse[i] = false;
  }
}

DefaultMPIService::~DefaultMPIService() {
	int i;
  for (i = 0; i < cap; i++) {
    // maybe should use commcompare...
    if (comm[i] != MPI_COMM_NULL) {
      MPI_Comm_free(&(comm[i]));
      comm[i] = MPI_COMM_NULL;
      if (inuse[i]) {
        // oh well, too bad.
        inuse[i] = false;
      }
    }
  }
}

MPI_Comm DefaultMPIService::getComm() {
	int i;
  // check for one recyclable
  for (i = 0; i < cap; i++) {
    // maybe should use commcompare...
    if (comm[i] != MPI_COMM_NULL) {
      if (!inuse[i]) {
        inuse[i] = true;
        return comm[i];
      }
    }
  }
  // find someplace to put a new duplicate.
  for (i = 0; i < cap; i++) {
    // maybe should use commcompare...
    if (comm[i] == MPI_COMM_NULL) {
      MPI_Fint cfcomm = (MPI_Fint)fortranMPIComm;
      MPI_Comm urcomm = MPI_Comm_f2c(cfcomm);
      MPI_Comm_dup(urcomm, &(comm[i]));
      inuse[i] = true;
      return comm[i];
    }
  }
  // too bad, we're toast. hate those hardcoded cap limits.
  return MPI_COMM_NULL;
}

void DefaultMPIService::releaseComm(MPI_Comm m) {
  
  if (m == MPI_COMM_NULL) {
    return;
  }
  // if we don't find it, ignore it quietly.
	int i;
  for (i = 0; i < cap; i++) {
    int result;
    MPI_Comm_compare(m,comm[i],&result);
    if (result == MPI_IDENT && inuse[i] == true) {
      inuse[i] = false;
      break;
    }
  }
}

#endif // _CCAMPI
