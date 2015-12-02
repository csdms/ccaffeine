#include "Test_Script_Ccafe_scr_NeoMain.hh"
#include "dc/neo/ccafe-bind/neoCcafePublic.hh"
#include <iostream>

int main(int argc, char **argv) {
	Test_Script_Ccafe_scr_NeoMain myScript;
	NeoAbstractFramework naf(0);
	try {
		naf.run( &myScript);
	}
	catch ( ::neo::cca::Exception &oe)
	{
		::std::cout << "driver caught fatal error:" << ::std::endl;
		::std::cout << oe.what() << ::std::endl;
		::std::cerr << "driver caught fatal error:" << ::std::endl;
		::std::cerr << oe.what() << ::std::endl;
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
