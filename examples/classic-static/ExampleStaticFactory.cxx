#include "dc/framework/dc_fwkPublic.h"
#include "ExampleStaticFactory.h"

#define MAPNAME(cxxName,cname)	\
  f->addStaticClass(cname, ( void*(*)() )(&create_##cxxName),cname); \
  ccount++; \
  fprintf(stderr,"# factory added %s\n",cname)

#define EXTERNDEF(cxxName) \
  extern classic::gov::cca::Component *create_##cxxName()

classic::gov::cca::Component *create_nullComponent()
{
	return 0;
}

/* Each component class must be declared EXTERNDEF
 * in the following block. This just declares the
 * constructors c wrapper -- it doesn't need to see
 * the actual component class header.
 */
extern "C" {

EXTERNDEF(StarterComponent) ;
EXTERNDEF(PrinterComponent) ;

// leftovers from last time jaideep did this
#if 0
  //Demo stuff
  //EXTERNDEF(Initialize) ;
  //EXTERNDEF(dpdt) ;
  //EXTERNDEF(problemModeler) ;

  //Module ReactingFlows
EXTERNDEF(reaction) ;
EXTERNDEF(ref) ;
EXTERNDEF(Driver) ;
EXTERNDEF(DiffComp_JR) ;
EXTERNDEF(DiffCoeff) ;
EXTERNDEF(DiffQuants) ;
EXTERNDEF(ICcomponent_JR) ;

  //Module Numerics
EXTERNDEF(CvodeComponent) ;
EXTERNDEF(Errest_JR) ;
EXTERNDEF(RKC2_Recursive) ;
EXTERNDEF(BicubicInterp) ;

  //Module Misc
EXTERNDEF(StatsComp) ;

  //Module Adaptors
EXTERNDEF(ChemistryIntegrator) ;

  //Module Meshes
EXTERNDEF(GraceComponent) ;
#endif

EXTERNDEF() ;
}

/* Each component class must be MAPNAMEd
 * in the following function. This pushes the
 * constructor function pointers into the classic factory
 * the framework comes with.
 */
void
ExampleStaticFactory::addClasses(ComponentRegistrar *f)
{
	int ccount = 0;
	MAPNAME(StarterComponent, "StarterComponent");
	MAPNAME(PrinterComponent, "PrinterComponent");
#if 0 
  // Demo stuff
  //  MAPNAME(Initialize, "Initialize");
  //  MAPNAME(dpdt, "dpdt");
  //  MAPNAME(problemModeler, "problemModeler");
	//
  //Module ReactingFlows
  MAPNAME(reaction, "reaction");
  MAPNAME(ref, "ref");
  MAPNAME(Driver, "Driver") ;
  MAPNAME(DiffComp_JR, "DiffComp_JR") ;
  MAPNAME(DiffCoeff, "DiffCoeff") ;
  MAPNAME(DiffQuants, "DiffQuants,") ;
  MAPNAME(ICcomponent_JR, "ICcomponent_JR") ;

  //Module Numerics
  MAPNAME(CvodeComponent, "CvodeComponent");
  MAPNAME(Errest_JR, "Errest_JR");
  MAPNAME(RKC2_Recursive, "RKC2_Recursive");
  MAPNAME(BicubicInterp, "BicubicInterp");

  //Module Misc
  MAPNAME(StatsComp, "StatsComp");

  //Module Adaptors
  MAPNAME(ChemistryIntegrator, "ChemistryIntegrator");

  //Module Meshes
  MAPNAME(GraceComponent, "GraceComponent");
#endif

  std::cerr << "ExampleStaticFactory registered " << ccount << " components." << std::endl;
  std::cout << "ExampleStaticFactory registered " << ccount << " components." << std::endl;
}
