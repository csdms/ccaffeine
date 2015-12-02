// This is a generated file. Do not commit to CVS.
#include "dc/export/AllExport.hh"
#include "BabelFactoryService.hh"
#include <stdlib.h>
#include <stdio.h>

extern "C" {

ccafeopq::Component * create_BabelFactoryService() {
        ccafeopq::Component * c;
	BabelFactoryService * component;
	component = new BabelFactoryService();
	c = dynamic_cast< ccafeopq::Component * >(component); 
	if (!c) {
          ::fprintf(stderr,"dynamic_cast failed at %s:%d.\n",__FILE__,__LINE__);
          ::exit(2);
        }

	return c;
    }    

char **getComponentList() {
	static char *list[2];
	list[0] = "create_BabelFactoryService BabelFactoryService";
	list[1] = 0;
	return list;
}

}
static char id[]="$: genDLWrapperOpaque,v 1.1 2003/10/07 08:04:22 baallan Exp $";
