#include "test_script_babel.hh"
#include "dc/babel.new/babel-cca/AllBabelCCA.hh"
#include <iostream>

int test_script_babel_doit(int argc, char **argv) {


	test_script_babel::BabelMain myScript =
		test_script_babel::BabelMain::_create();
	ccaffeine::BabelMain cbm = myScript; // CAST

	ccaffeine::AbstractFramework caf = 
		ccaffeine::AbstractFramework::_create();

	try {
		caf.run( cbm );
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
	return	test_script_babel_doit(argc,argv);
}	
