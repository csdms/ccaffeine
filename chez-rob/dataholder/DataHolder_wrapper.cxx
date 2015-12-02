// Should be a generated file.
#include <cca.h>
#include <stdlib.h>
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "parameters/parametersStar.h"
#include "port/supportInterfaces.h"
#include "dc/port/CCA_Block.h"
#include "dc/port/BlockPort.h"
#include "BasicShape.h"
#include "util/IO.h"
#include "DataHolder.h"
#include "DataHolder_wrapper.h"

extern "C" {
  gov::cca::Component *create_DataHolder() {
    gov::cca::Component *wrapper = 
      dynamic_cast<gov::cca::Component *>(new DataHolder());
    return wrapper;
  }

// CCAFFEINE expects each .so file to have a getComponentList function.
// See dccafe/cxx/dc/framework/ComponentFactory.h for details.
// More sophisticated repository interfaces would supplant this.
char **getComponentList() {
	static char *list[2];
	list[0] = "create_DataHolder DataHolder";
	list[1] = 0;
	return list;
}

static char id[]="$Id: DataHolder_wrapper.cxx,v 1.1 2000/10/17 22:45:56 rob Exp $";
};

