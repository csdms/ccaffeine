#include "dc/babel/component/ParameterDialogServiceTest/server/ccafe1_ParameterDialogServiceTest.hh"
#include "gov_cca_Component.hh"

extern "C" {

gov::cca::Component create_ParameterDialogServiceTest() {
	::gov::cca::Component ex = ccafe1::ParameterDialogServiceTest();
	return ex;
}    

char **getComponentList() {
	static char *list[2];
	list[0] = "create_ParameterDialogServiceTest ccafe1.ParameterDialogServiceTest";
	list[1] = 0;
	return list;
}

}
static char id[]="$Id: ParameterDialogServiceTest_wrapper_Impl.cc,v 1.1 2003/04/08 20:33:24 baallan Exp $";
