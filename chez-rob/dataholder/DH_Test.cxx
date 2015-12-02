#include <cca.h>
#include "DataHolder_wrapper.h"
#include "mpi.h"


int main(int argc, char** argv) {

  gov::cca::Component *c;

  MPI_Init(&argc, &argv);

  c = create_DataHolder();

  //  c->setServices(0);

  delete c;

  return 0;
}
