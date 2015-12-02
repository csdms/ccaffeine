#include "TestScriptBabel.hxx"
#include "dc/babel.new/babel-cca/AllBabelCCA.hxx"
#include <iostream>

int TestScriptBabel_doit(int argc, char **argv) {


	TestScriptBabel::BabelMain myScript =
		TestScriptBabel::BabelMain::_create();
	ccaffeine::BabelMain cbm = myScript; // CAST

	ccaffeine::AbstractFramework caf = 
		ccaffeine::AbstractFramework::_create();
	caf.initialize("",0,0);

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
	return	TestScriptBabel_doit(argc,argv);
}	
