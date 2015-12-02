#include "dc/babel.12/component/ParameterDialogServiceTest/server/ccafe1_ParameterDialogServiceTest.hh"
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
static char id[]="$Id: ParameterDialogServiceTest_wrapper_Impl.cxx,v 1.2 2008/08/05 19:24:15 baallan Exp $";
