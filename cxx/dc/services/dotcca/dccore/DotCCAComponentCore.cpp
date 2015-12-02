#include <cstring>
#include <vector>
#include <complex>
#include <boost/shared_ptr.hpp>
#include <dc/export/ccafeopq.hh>
#include "DotCCAComponentCore.hpp"
#include "dc/services/dotcca/treeReader/treeReaderPublic.hpp"
#include "dc/services/dotcca/treeReader/ComponentData.hpp"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#ifdef __GNUC__
#if __GNUC__ == 2
#include <string.h>
#define DOT_GCC_BROKEN_STRING 1
#else
#define DOT_GCC_BROKEN_STRING 0
#endif // gnuc2
#endif // gnuc

#define DCCC_DEBUG
#undef DCCC_DEBUG // quiet by default

#define PATHSEP "/"
#define PATHSEP_CHAR '/'


ccafe::DotCCAComponentCore::DotCCAComponentCore()
{
#ifdef DCCC_DEBUG
	std::cerr<< __FILE__ << ": CTOR" << std::endl;
#endif
}

ccafe::DotCCAComponentCore::~DotCCAComponentCore()
{
#ifdef DCCC_DEBUG
	std::cerr<< __FILE__ << ": DTOR" << std::endl;
#endif
}

std::vector< ::ccafeopq::ComponentClassDescription_shared >
ccafe::DotCCAComponentCore::parseDescriptions( const std::string & mypath)
       	throw ( std::invalid_argument)
{
	bool warned = false;
	if (mypath == "") {
		warned = true;
		fprintf(stderr,"%s:%d: dying 1...\n",__FILE__, __LINE__);
		throw std::invalid_argument("ccafe::DotCCAComponentCore::parseDescriptions: null input file given");
	}

	std::vector< ::ccafeopq::ComponentClassDescription_shared > ccdv;
	if (isSIDLFile(mypath) && !warned) {
#ifdef _NO_XML
		fprintf(stderr,"Ignoring SIDL file input.\n");
		fprintf(stderr,"%s:%d: XML support not built.\n",__FILE__, __LINE__);
		warned = true;
		return ccdv;
#else
		return parseSIDL(mypath);
#endif // _NO_XML
	}
	if (isOldFormat(mypath) && !warned) {
		extractOldDescriptions(mypath, ccdv);
		return ccdv;
	}
	if (isXMLCCAFormat(mypath) && !warned) {
#ifdef _NO_XML
		fprintf(stderr,"Ignoring CCA XML file input %s.\n",mypath.c_str());
		fprintf(stderr,"%s:%d: XML support not built.\n",__FILE__, __LINE__);
		warned = true;
#else
		extractXMLDescriptions(mypath, ccdv);
#endif // _NO_XML
		return ccdv;
	}

	if (! warned) {
		fprintf(stderr,"%s:%d: unreadable format...\n",__FILE__, __LINE__);
	}
	fprintf(stderr,"%s\n","ccafe::DotCCAComponentCore::parseDescriptions: input file has unrecognized data format");
	throw std::invalid_argument("ccafe::DotCCAComponentCore::parseDescriptions: input file has unrecognized data format");
}

bool
ccafe::DotCCAComponentCore::isSIDLFile(const std::string & filename)
{
#ifdef DCCC_DEBUG
	std::cout << "isSIDLFile(" << filename << ")" << std::endl;
#endif
	char dat[1024];
	const std::string l1 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	const std::string l2 = "<!DOCTYPE Symbol PUBLIC \"-//CCA//SIDL ";
	size_t len1 = l1.size();
	size_t len2 = l2.size();

	FILE * f = fopen(filename.c_str(),"r");
	if (f == 0) {
#ifdef DCCC_DEBUG
	std::cout << "isSIDLFile(" << filename << ") open failed." << std::endl;
#endif
		return false;
	}
	char *line;

	line = fgets( dat, 1023, f);
	if (line == 0) {
#ifdef DCCC_DEBUG
	std::cout << "isSIDLFile(" << filename << ") no line1." << std::endl;
#endif
		fclose(f);
		return false;
	}
	// bypass buggy string::compare, sigh
	if ( strncmp(l1.c_str(), line, len1 - 2) != 0 ) {
#ifdef DCCC_DEBUG
	std::cout << "isSIDLFile(" << filename << ") not xml." << std::endl;
	std::cout << "L1: " << l1 << std::endl;
	std::cout << "Lx: " << line << std::endl;
#endif
		fclose(f);
		return false;
	}

	line = fgets( dat, 1023, f);
	if (line == 0) {
#ifdef DCCC_DEBUG
	std::cout << "isSIDLFile(" << filename << ") no line2." << std::endl;
#endif
		fclose(f);
		return false;
	}
	if ( strncmp(l2.c_str(), line, len2 - 2) != 0 ) {
#ifdef DCCC_DEBUG
	std::cout << "isSIDLFile(" << filename << ") not sidl." << std::endl;
	std::cout << "L2: " << l2 << std::endl;
	std::cout << "Lx: " << line << std::endl;
#endif
		fclose(f);
		return false;
	}

	fclose(f);
	return true;
}

bool 
ccafe::DotCCAComponentCore::isOldFormat(const std::string & filename)
{
	// open file. check for != <
#ifdef DCCC_DEBUG
	std::cout << "isOldFormat(" << filename << ")" << std::endl;
#endif
	FILE * f = fopen(filename.c_str(),"r");
	if (f == 0) {
		return false;
	}
	int c;
	c = fgetc(f);
	fclose(f);
	if (c == EOF) {
		return false;
	}
	if (c != '<' )
	{
		return true;
	}
	return false;
}

bool 
ccafe::DotCCAComponentCore::isXMLCCAFormat(const std::string & filename)
{
	// open file. check for <
#ifdef DCCC_DEBUG
	std::cout << "isXMLCCAFormat(" << filename << ")" << std::endl;
#endif
	FILE * f = fopen(filename.c_str(),"r");
	if (f == 0) {
		return false;
	}
	int c;
	c = fgetc(f);
	fclose(f);
	if (c == EOF) {
		return false;
	}
	if (c == '<' )
	{
		return true;
	}
	return false;
}

#ifndef IO_dn2
#ifdef DCCC_DEBUG
#define IO_dn2(x,y) fprintf(stderr,x,y)
#define IO_dn3(x,y,z) fprintf(stderr,x,y,z)
#else
#define IO_dn2(x,y) 
#define IO_dn3(x,y,z) 
#endif
#endif
#define eatspace(s) for (; s[0] != '\0' && isspace(s[0]); s = &(s[1]))
#define initspace(s,n) { int ns; for (ns = 0; ns < n; ns++ ) { s[ns] = '\0'; } }

namespace /* anonymous, to hide local functions */ 
{

/** If the line is lead off with match, copies the
remainder of the line to str.
*/
void munchKeyword(char *line, char *match, std::string & str)
{
	int matchLen;
	matchLen = strlen(match); 
	if (strncmp(match,line,matchLen)==0) {
		str = (line+matchLen);
	}
}

/** Munch down the comment and meta-info lines.
fills up the given buffers if
matching metalines found.
*/
int checkMetaLine(char * line, std::string & date, 
 		std::string & builder, std::string & lbl,
	       	std::string & cmptType)
{
	eatspace(line);
	if (line[0] == '#') { return 1; }
	if (line[0] == '!') {
		if (line[1] == '\0') { return 1; }
		line++;
		eatspace(line);
		munchKeyword(line,(char *)"date=", date);
		munchKeyword(line,(char *)"builder=", builder);
		munchKeyword(line,(char *)"location=",lbl);
		munchKeyword(line,(char *)"componentType=",cmptType);
		return 1;
	}
	return 0; // not a comment or meta.
}


// strip crap after final / in index path name and
// append lib to obtain result.
std::string dlPathName(const char *index, const char *lib)
{
	int ilen, llen;
	ilen = strlen(index);
	llen = strlen(lib);
	if (ilen == 0 || llen == 0) { return ""; }
	while (index[ilen] != '/' && ilen > 0) { ilen--; } // PATHSEP winders different
	char *result;
	result = (char*)malloc(ilen+1+llen+1);
	result[ilen+llen+1] = '\0';
	strncpy(result,index,ilen+1);
	sprintf(&(result[ilen+1]),lib);
	std::string s = result;
	free(result);
	return s;
} 

// strip leading create_ if there and return rest.
std::string extractClassName(const char *name)
{
	const char *x;
	std::string result = name;
	if (strncmp(name,"create_",7) == 0)
	{
		x = name + 7;
		result = x;
	}
	return result;
}


// return false if can't find either last_lib or last_so_file
// return true if one exists and splits it into libDir,libName.
// prefers last_lib over last_so_file if both exist.
//
bool sanitize(const std::string last_lib, const std::string last_so_file, std::string & libDir, std::string & libName) 
{
	struct stat libPathStat;
	struct stat buildPathStat;
	const char *usePath;
	const char *libraryPath = last_lib.c_str();
	const char *buildLocation = last_so_file.c_str();
	int libOrBuild = 0;
	usePath = libraryPath;
	int badLibPath = 1;
	int badBuildPath = 1;
	badLibPath = stat(libraryPath,&libPathStat);
	if (badLibPath) {
		if (last_so_file != "") {
			badBuildPath = stat(buildLocation, &buildPathStat);
			if (badBuildPath) {
				fprintf(stderr,"Library build file %s appears bogus/missing'.\n", buildLocation);
				return false;
			}
			usePath = buildLocation;
			libOrBuild = 1;
		} else {
			fprintf(stderr,"Library file %s appears bogus/missing'.\n", libraryPath);
			return false;
		}
	}
	std::string filePath;
	filePath = usePath;
	size_t splitPos = filePath.rfind(PATHSEP_CHAR);
	if ( splitPos != filePath.npos) 
	{
		libDir = filePath.substr(0,splitPos);
		libName= filePath.substr(splitPos+1); // +1?
	// libName = leafname
	} else {
		libDir = "";
		libName = filePath;
	}
	return true;

}

} // end anonymous namespace

int
ccafe::DotCCAComponentCore::extractOldDescriptions( const std::string & mypath, std::vector< ::ccafeopq::ComponentClassDescription_shared > & ccdv )
{
#define CCAFE_LINESIZE 1024
	FILE *f;
	const char *fname = mypath.c_str();

	char linep[CCAFE_LINESIZE+1];
	char *line = linep; // char *line = &linep[0];
	std::string last_buildDate = "";
	std::string last_builder = "";
	std::string last_so_file = "";
	std::string last_buildLocation = "";
	std::string cmptType = "";
	std::string last_lib  = "";

	f = fopen(fname,"r");
	if ( f == 0 ) { return 1; }
	initspace(line,CCAFE_LINESIZE);
	IO_dn2("file = %s\n", fname);
	while (fgets(line,CCAFE_LINESIZE,f) != 0) {
		ccafe::ComponentData *cd = 0;
		eatspace(line);
		if (line[0] == '\0') { continue; }
		if (checkMetaLine(line, last_buildDate,
			last_builder,
			last_buildLocation,
			cmptType
		)) {
			initspace(line,CCAFE_LINESIZE);
			continue;
		}
		IO_dn2("cmptType = %s\n", cmptType.c_str());
		int numitems;
		char i1[CCAFE_LINESIZE], i2[CCAFE_LINESIZE];
		initspace(i1,CCAFE_LINESIZE);
		initspace(i2,CCAFE_LINESIZE);
		eatspace(line);
		numitems = sscanf(line,"%s%s",i1,i2);
		IO_dn2("numitems = %d\n", numitems);
		switch (numitems) {
		case 1:
		       	// compute name Foo/$i1 where Foo is fname less trailing *.cca
			last_lib = dlPathName(fname,i1);
			// compute name from location metadata key + i1
			last_so_file = dlPathName(last_buildLocation.c_str(),i1);
		break;
		case 2:
		{
		IO_dn3("items = %s, %s\n", i1, i2);
		IO_dn2("cmptType = %s\n", cmptType.c_str());
			if (last_lib == "")
			{
				IO_dn2("DotCCAComponentCore::extractOldDescriptions found class without library in %s.\n", fname);
				break;
			}
			
			cd = new ccafe::ComponentData();
#if DOT_GCC_BROKEN_STRING
			const char *ctypetmp = cmptType.c_str();
			if ( strncmp(ctypetmp,"babel",5) != 0 ) 
#else
			if ( cmptType.compare(0,5,"babel") != 0 ) 
#endif
			{
				std::string libDir;
				std::string libName;
				if ( sanitize(last_lib, last_so_file, libDir, libName) )
				{
					cd-> setLibraryLocation( libDir );
					cd-> setLibraryName( libName );
				} else {
					// if opq/classic fails, punt description.
					delete cd;
					cd = 0;
					break;
				}

				// rec->cFuncName = STRDUP(i1);
				cd-> setConstructorName(i1);
				// whack off create_ to get real class name
				// by convention.
				cd-> setComponentClassName( extractClassName(i1)  ); 
				cd-> setDeploymentClassAlias( i2 );
				// was rec->libraryClassName. Pallet alias 
				// is second element on line.
				IO_dn3("items = %s, %s\n", i1, i2);

			} else {

				// elsewise, babel loader has to deal with random pathness.
				cd-> setConstructorName( "" );
				cd-> setDeploymentClassAlias( i2 ); // babel classname is second element on line. no aliasing.
				cd-> setComponentClassName( i2  ); 
				// we're going to need these soon enough.
				cd-> setLibraryLocation( "" );
				cd-> setLibraryName( "" );
			}
			
			cd-> setIndexFile( mypath); 
			cd-> setLibraryLoading( "dynamic" );
			cd-> setExecScript("");
			
			if (cmptType == "" ) { cmptType = "classic"; }
			cd-> setCCASpecBinding( cmptType ); 

			::ccafeopq::ComponentClassDescription_shared ccd(cd);
			ccdv.push_back(ccd);
			cd = 0;
		}
		break;
		default:
			IO_dn3("DotCCAComponentCore::extractOldDescriptions bad line in %s (%s).\n", fname,line);
		break;
		}
		initspace(line,CCAFE_LINESIZE);

	}

	fclose(f);

	return 0;
#undef CCAFE_LINESIZE
}

std::vector< ::ccafeopq::ComponentClassDescription_shared > 
ccafe::DotCCAComponentCore::parseSIDL( const std::string & path) throw ( std::invalid_argument)
{
#ifdef _NO_XML
	fprintf(stderr,"%s:%d: built without XML support.\n",__FILE__, __LINE__);
	throw std::invalid_argument("ccafe::DotCCAComponentCore::parseSIDL: built without XML support.");
#else
	ccafe::Parser parser;
	parser.parse(path); // return 1 if we have an error detectable here.
	std::vector< XMLNode_shared > depls = parser.findNodes("Symbol");
	std::vector< ::ccafeopq::ComponentClassDescription_shared > ccdv;

	// iterate list to create and append ccds on ccdv.
	std::string componentClassName;
	std::string ccaSpecBinding;
	std::string notConcrete;
	ccaSpecBinding = "babel";

	for ( size_t i =0; i < depls.size(); i++) {
		XMLNode_shared x = depls[i];

		// find class name <Symbol><SymbolName name="">
		std::vector< XMLNode_shared > specs = 
			x->matchChildren("SymbolName");
		if (specs.size() != 1) {
			continue; // whacked sidl
		}
		componentClassName = specs[0]->getAttribute("name","_BoGuS_");
		if (componentClassName == "_BoGuS_") {
			continue; // skip records w/out name.
		}

		// find class finished:
		// <Symbol><Class abstract="false">
		specs = x->matchChildren("Class");
		if (specs.size() != 1) {
			continue; // whacked sidl
		}
		notConcrete = specs[0]->getAttribute("abstract","true");
		if (notConcrete != "false") {
			continue; // skip records abstract
		}

		// <Symbol><Class><ImplementsBlock><SymbolName name="gcC">
		std::vector< XMLNode_shared > impls = 
			specs[0]->matchChildren("ImplementsBlock");
		if (impls.size() != 1) {
			continue; // skip records w/out IB
		}
		std::vector< XMLNode_shared > parents =
			impls[0]->matchChildren("SymbolName");
		if (impls.size() < 1) {
			continue; // skip records w/out parent interfaces.
		}
		bool isComponent = false;
		std::string gc = "gc";
		for (size_t k = 0; k < parents.size(); k++)
		{
			gc = parents[k]->getAttribute("name","gc");
			if (gc.compare("gov.cca.Component") == 0) {
				isComponent = true;
				break; // skip rest
			}
		}
		if (! isComponent) {
			continue; // skip rest
		}

		// create the class description instance.
		ccafe::ComponentData *cd = new ccafe::ComponentData();
		cd-> setComponentClassName( componentClassName );
		cd-> setDeploymentClassAlias( componentClassName );
		cd-> setCCASpecBinding( ccaSpecBinding ); 
		cd-> setLibraryLoading( "" );
		cd-> setLibraryLocation( "" );
		cd-> setLibraryName( "" );
		cd-> setExecScript( "" );
		cd-> setIndexFile( path );
		::ccafeopq::ComponentClassDescription_shared ccd(cd);
		ccdv.push_back(ccd);

	}

	return ccdv;
#endif // _NO_XML
}

int
ccafe::DotCCAComponentCore::extractXMLDescriptions(const std::string & path, std::vector< ::ccafeopq::ComponentClassDescription_shared > & ccdv)
{
#ifdef _NO_XML
	fprintf(stderr,"%s:%d: built without XML support.\n",__FILE__, __LINE__);
	throw std::invalid_argument("ccafe::DotCCAComponentCore: built without XML support.");
#else
	ccafe::Parser parser;
	parser.parse(path); // return 1 if we have an error detectable here.
	std::vector< XMLNode_shared > depls = parser.findNodes("componentDeployment");
	
	// iterate list to create and append ccds on ccdv.
	std::string componentClassName;
	std::string deploymentClassAlias;
	std::string ccaSpecBinding;
	std::string libraryLoading;
	std::string libraryLocation; // this is a directory name, not full pathname. ends in /
	std::string libraryName; // this is a leaf filename ...
	// unless it's a libtool archive (then it's a full pathname)
	// see hack below for disambiguation of libraryName when dlopening.
	std::string execScript;
	std::string cctor;
	std::string libtoolArchive;
	std::string staticArchive;
	std::string sharedArchive;

	for ( size_t i =0; i < depls.size(); i++) {
		XMLNode_shared x = depls[i];
		componentClassName = 
			x->getAttribute("name","_BoGuS_");
		if (componentClassName == "_BoGuS_") {
			continue; // skip records w/out name.
		}
		deploymentClassAlias = 
			x->getAttribute("palletClassAlias","_BoGuS_");
		if (deploymentClassAlias == "_BoGuS_") {
			deploymentClassAlias = 
				x->getAttribute("paletteClassAlias","_BoGuS_");
		}
		if (deploymentClassAlias == "_BoGuS_") {
			deploymentClassAlias = componentClassName;
		}
		std::vector< XMLNode_shared > envs = 
			x->matchChildren("environment");
		if (envs.size() != 1) {
			continue; // skip records w/out env or w/multiple.
		}
		std::vector< XMLNode_shared > specs =
			envs[0]->matchChildren("ccaSpec");
		if (specs.size() > 1) {
			continue; // skip records w/out env or w/multiple.
		}
		if (specs.size() == 0) {
			ccaSpecBinding = "babel";
		} else {
			ccaSpecBinding = specs[0]->getAttribute("binding","babel");
		}
		std::vector< XMLNode_shared > libs =
			envs[0]->matchChildren("library");
		if (libs.size() != 1) {
			continue; // skip records w/out env or w/multiple.
		}
		XMLNode_shared lib = libs[0];
		libraryLoading = lib->getAttribute("loading","_BoGuS_");
		libraryLocation = lib->getAttribute("location","_BoGuS_");
		libraryName = lib->getAttribute("name", "_BoGuS_");
		staticArchive = lib->getAttribute("static-archive", "_BoGuS_");
		sharedArchive = lib->getAttribute("shared-archive", "_BoGuS_");
		libtoolArchive = lib->getAttribute("libtool-archive", "_BoGuS_");
		cctor = lib->getAttribute("constructor", "_BoGuS_");

		if (	libraryLoading == "_BoGuS_" ||
			(ccaSpecBinding != "babel" &&
				( libraryLocation == "_BoGuS_"  || libraryName == "_BoGuS_") 
			)
		   ) {
			continue; // skip records w/out complete location.
		}
		// create the class description instance.
		ccafe::ComponentData *cd = new ccafe::ComponentData();
		if (cctor != "_BoGuS_") {
			cd->setConstructorName(cctor);
		}
		cd-> setComponentClassName( componentClassName );
		cd-> setDeploymentClassAlias( deploymentClassAlias );
		cd-> setCCASpecBinding( ccaSpecBinding ); 
		cd-> setLibraryLoading( libraryLoading );
// we need a better class description interface
// the next bit is a hack-around.
		cd-> setLibraryLocation( libraryLocation );
		if (libraryLoading != "libtool") {
			cd-> setLibraryLocation( libraryLocation );
			cd-> setLibraryName( libraryName );
		} else {
			// temporary policy that needs better CCD interface to fix:
			cd-> setLibraryLocation( "" );
			if (libtoolArchive != "_BoGuS_") {
				cd-> setLibraryName( libtoolArchive );
			}
			if (staticArchive != "_BoGuS_") {
				cd-> setLibraryName( staticArchive );
			}
			if (sharedArchive != "_BoGuS_") {
				cd-> setLibraryName( sharedArchive );
			}
			
		}

		cd-> setExecScript("");
		cd-> setIndexFile( path ); // rec->indexName = STRDUP(fname);
		::ccafeopq::ComponentClassDescription_shared ccd(cd);
		ccdv.push_back(ccd);

	}
#endif // no xml
	return 0;
}

::ccafeopq::ComponentClassDescription_shared 
ccafe::DotCCAComponentCore::createStaticDescription(
		const ::std::string specBinding,
		const ::std::string componentClassName, 
		const ::std::string deploymentClassAlias)
{
		ccafe::ComponentData *cd;
		cd = new ccafe::ComponentData();
		cd-> setConstructorName("_static_");
		cd-> setComponentClassName( componentClassName );
		cd-> setDeploymentClassAlias( deploymentClassAlias );
		cd-> setCCASpecBinding( specBinding ); 
		cd-> setLibraryLoading( "_static_");
		cd-> setLibraryLocation( "_static_");
		cd-> setLibraryName( "_static_");
		cd-> setExecScript("");
		cd-> setIndexFile( "_static_" ); 
		::ccafeopq::ComponentClassDescription_shared ccd(cd);
		return ccd;
}

int
ccafe::DotCCAComponentCore::main(int argc, char *argv[])
{
	ccafe::DotCCAComponentCore dcc;
       	// dcc not used. decoy to catch missing virtual function implementations.
	
	// actual test code
	if (argc != 3) {
		std::cerr << argv[0] << ": " << "<path> <file> required" << std::endl;
		return 1;
	}

	std::string path = argv[1];
	std::string file = argv[2];
	path += PATHSEP;
	path += file;
	std::vector< ::ccafeopq::ComponentClassDescription_shared > ccdv =
		dcc.parseDescriptions(path);
	std::cout << "Found " << ccdv.size() << " descriptions in " << file << std::endl;
	for (size_t i = 0; i < ccdv.size(); i++) 
	{
		::ccafeopq::ComponentClassDescription_shared ccd = ccdv[i];
		std::cout << "indexFile=" << ccd->getIndexFile()  << std::endl;
		std::cout << "CLASS= " << ccd->getComponentClassName() << std::endl;
		std::cout << "alias= " << ccd->getDeploymentClassAlias() << std::endl;
		std::cout << "binding= " << ccd->getCCASpecBinding() << std::endl;
		std::cout << "libLoading= " << ccd->getLibraryLoading() << std::endl;
		std::cout << "libLocation= " << ccd->getLibraryLocation() << std::endl;
		std::cout << "libName= " << ccd->getLibraryName() << std::endl;
		std::cout << "exec= " << ccd->getExecScript() << std::endl ;
		std::cout << "ctor=" << ccd->getConstructorName ()  << std::endl;
		std::cout << std::endl;

	}
	return 0;
}

#ifdef DotCCAComponentCore_MAIN
int main(int argc, char *argv[])
{
	ccafe::DotCCAComponentCore dcc;
	return dcc.main(argc,argv);
}
#endif // DotCCAComponentCore_MAIN
