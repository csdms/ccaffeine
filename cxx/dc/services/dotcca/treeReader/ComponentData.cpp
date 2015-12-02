#include "dc/services/dotcca/treeReader/ComponentData.hpp"

#define CD_DEBUG 0

ccafe::ComponentData::ComponentData()
{
#if CD_DEBUG
	std::cerr << __FILE__ << ": ctor" << std::endl;
#endif
	initDummy();
	dead = 0;
}

ccafe::ComponentData::~ComponentData()
{
#if CD_DEBUG
	std::cerr << __FILE__ << ": dtor" << std::endl;
#endif
	std::string s = "dead_";
	s += componentClassName;
	initDummy();
	componentClassName = s;
	dead = 0xFEEDF00D;
}

std::string ccafe::ComponentData::getComponentClassName () throw(ccafeopq::Exception)
{
	if (dead != 0xFEEDF00D) {
#if CD_DEBUG
	std::cerr << __FILE__ << ":getComponentClassName " << componentClassName << std::endl;
#endif
		return componentClassName;
	}
#if CD_DEBUG
	std::cerr << __FILE__ << ":getComponentClassName " << "DEAD_!! "<< std::endl;
#endif
	throw ccafeopq::Exception("ccafe::ComponentData::getComponentClassName called on deallocated ComponentData reference");
}

std::string ccafe::ComponentData::getLibraryName ()throw (ccafeopq::Exception)
{
	if (dead != 0xFEEDF00D) {
		return libraryName;
	}
	throw ccafeopq::Exception("ccafe::ComponentData::getLibraryName called on deallocated ComponentData reference");
}

std::string ccafe::ComponentData::getDeploymentClassAlias() throw (ccafeopq::Exception)
{
	if (dead != 0xFEEDF00D) {
#if CD_DEBUG
	std::cerr << __FILE__ << ":getDeploymentClassAlias " << componentClassName << std::endl;
#endif
		return deploymentClassAlias;
	}
#if CD_DEBUG
	std::cerr << __FILE__ << ":getDeploymentClassAlias " << "DEAD_!!"<< std::endl;
#endif
	throw ccafeopq::Exception("ccafe::ComponentData::getDeploymentClassAlias called on deallocated ComponentData reference");
}

std::string ccafe::ComponentData::getCCASpecBinding() throw (ccafeopq::Exception)
{
	if (dead != 0xFEEDF00D) {
		return ccaSpecBinding;
	}
	throw ccafeopq::Exception("ccafe::ComponentData::getCCASpecBinding called on deallocated ComponentData reference");
}

std::string ccafe::ComponentData::getLibraryLoading() throw (ccafeopq::Exception)
{
	if (dead != 0xFEEDF00D) {
		return libraryLoading;
	}
	throw ccafeopq::Exception("ccafe::ComponentData::getLibraryLoading called on deallocated ComponentData reference");
}

std::string ccafe::ComponentData::getConstructorName() throw (ccafeopq::Exception)
{
	if (dead != 0xFEEDF00D) {
		return ctorName;
	}
	throw ccafeopq::Exception("ccafe::ComponentData::getConstructorName called on deallocated ComponentData reference");
}

std::string ccafe::ComponentData::getIndexFile() throw (ccafeopq::Exception)
{
	if (dead != 0xFEEDF00D) {
		return indexFile;
	}
	throw ccafeopq::Exception("ccafe::ComponentData::getIndexFile called on deallocated ComponentData reference");
}

std::string ccafe::ComponentData::getLibraryLocation() throw (ccafeopq::Exception)
{
	if (dead != 0xFEEDF00D) {
		return libraryLocation;
	}
	throw ccafeopq::Exception("ccafe::ComponentData::getLibraryLocation called on deallocated ComponentData reference");
}

std::string ccafe::ComponentData::getExecScript () throw (ccafeopq::Exception)
{
	if (dead != 0xFEEDF00D) {
		return execScript;
	}
	throw ccafeopq::Exception("ccafe::ComponentData::getExecScript called on deallocated ComponentData reference");
}

void ccafe::ComponentData::getDOMTree () throw (ccafeopq::Exception)
{
}

void ccafe::ComponentData::setComponentClassName( std::string s)
{
	componentClassName = s;
#if CD_DEBUG
	std::cerr << __FILE__ << ":setComponentClassName " << s << std::endl;
#endif
}

void ccafe::ComponentData::setIndexFile( std::string s)
{
	indexFile = s;
#if CD_DEBUG
	std::cerr << __FILE__ << ":setIndexFile " << s << std::endl;
#endif
}

void ccafe::ComponentData::setDeploymentClassAlias( std::string s)
{
#if CD_DEBUG
	std::cerr << __FILE__ << ":setDeploymentClassAlias " << s << std::endl;
#endif
	deploymentClassAlias = s;
}

void ccafe::ComponentData::setCCASpecBinding( std::string s)
{
#if CD_DEBUG
	std::cerr << __FILE__ << ":setCCASpecBinding " << s << std::endl;
#endif
	ccaSpecBinding = s;
}

void ccafe::ComponentData::setLibraryLoading( std::string s)
{
	libraryLoading = s;
}

void ccafe::ComponentData::setLibraryLocation( std::string s)
{
	libraryLocation = s;
}

void ccafe::ComponentData::setLibraryName( std::string s)
{
	libraryName = s;
}

void ccafe::ComponentData::setConstructorName( std::string s)
{
	ctorName = s;
}

void ccafe::ComponentData::setExecScript( std::string s)
{
	execScript = s;
}

void ccafe::ComponentData::initDummy()
{
	componentClassName = "uninit_componentClassName";
	deploymentClassAlias = "uninit_deploymentClassAlias";
	ccaSpecBinding = "uninit_ccaSpecBinding";
	libraryLoading = "uninit_libraryLoading";
	libraryLocation = "uninit_libraryLocation";
	libraryName = "uninit_libraryName";
	execScript = "uninit_execScript";
}

#include <iostream>

int ccafe::ComponentData::main(int argc, char **argv)
{
	ComponentData c;

	std::string s = c.getComponentClassName();
	std::cout << "class= " << s << std::endl;

	s = c.getDeploymentClassAlias();
	std::cout << "alias= " << s << std::endl;

	s = c.getCCASpecBinding();
	std::cout << "binding= " << s << std::endl;

	s = c.getLibraryLoading();
	std::cout << "loading= " << s << std::endl;

	s = c.getLibraryLocation();
	std::cout << "location= " << s << std::endl;

	s = c.getLibraryName ();
	std::cout << "name= " << s << std::endl;

	s = c.getExecScript ();
	std::cout << "script= " << s << std::endl;

	c.setComponentClassName( "myclass");
	c.setDeploymentClassAlias( "myalias");
	c.setConstructorName( "myclassicCTOR");
	c.setCCASpecBinding( "mybinding");
	c.setLibraryLoading( "myload");
	c.setLibraryLocation( "mydir");
	c.setLibraryName( "mylib");
	c.setExecScript( "myscript");

	s = c.getComponentClassName();
	std::cout << "class= " << s << std::endl;

	s = c.getDeploymentClassAlias();
	std::cout << "alias= " << s << std::endl;

	s = c.getCCASpecBinding();
	std::cout << "binding= " << s << std::endl;

	s = c.getLibraryLoading();
	std::cout << "loading= " << s << std::endl;

	s = c.getConstructorName();
	std::cout << "ctorname= " << s << std::endl;

	s = c.getLibraryLocation();
	std::cout << "location= " << s << std::endl;

	s = c.getLibraryName ();
	std::cout << "name= " << s << std::endl;

	s = c.getExecScript ();
	std::cout << "script= " << s << std::endl;

	return 0;

}

#ifdef ComponentData_MAIN
int main(int argc, char *argv[])
{
	return ::ccafe::ComponentData::main(argc, argv);
}
#endif
