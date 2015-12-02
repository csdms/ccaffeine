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
#include "ColorHolder.h"
#include "ColorHolder_wrapper.h"

extern "C" {
  gov::cca::Component *create_DataHolder() {
    gov::cca::Component *wrapper = 
      dynamic_cast<gov::cca::Component *>(new ColorHolder());
    return wrapper;
  }

// CCAFFEINE expects each .so file to have a getComponentList function.
// See dccafe/cxx/dc/framework/ComponentFactory.h for details.
// More sophisticated repository interfaces would supplant this.
char **getComponentList() {
	static char *list[2];
	list[0] = "create_ColorHolder ColorHolder";
	list[1] = 0;
	return list;
}

static char id[]="$Id: ColorHolder_wrapper.cxx,v 1.1 2000/12/11 15:24:45 rob Exp $";
};

