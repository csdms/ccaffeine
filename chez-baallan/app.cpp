// this is a function we expect apps/container writers to be able to cope with
// for gluing components together.
  
// do your own inits elsewhere.
// setServices will query for the required fwk services.
// someone else is going to use this component, or something like it,
// in one of two ways:
// 1) they call on an interface where they hand us A,X,B linear items
// as ESI_ objects.
// 2) we'll get the matrix and vector as ports.
//
// Since we're handling everything opaquely, we'll assume 2.
// This component will connect to something that provides a,x,b.



/** This function instantiates and wires the configured 
    selection of solution components together. We want enough info
    to pass that the framework being called on can distinguish
    between components it owns and the ones it is managing
    but are contained in a narrower scope.
 */
  ComponentFactoryService * componentFactoryService;
  ConnectionService *connector;
  ComponentId * LinearSystemID;
  ComponentId * PCID;
  ComponentId * SolverID;
  ComponentId * myID = services->getComponentID();
  ESI_Matrix *A;
  ESI_Vector *X, *B;

int doMarshal_and_solve_ISIS_CGNR_PolySPAI() {

//// create some components inside us: LinearSystemID, PCID, SolverID
  componentFactory = services->getPort("componentFactory");
  
  PCID = componentFactoryService->createComponentInstance("PC","ISIS_PolySPAI_PC");
  // resulting PCID toString result will be something like
  // myID->toString() + "PC". The framework reserves the right to
  // modify "PC" (the requested component name) to manage uniqueness
  // issues at the user-interface level, therefore checking the 
  // componentID is the only way to know what name you really have.

  SolverID = componentFactoryService->createComponentInstance("Solver","ISIS_CGNR");

  LinearSystemID = componentFactoryService->createComponentInstance("LinSys","ISIS_LinearSystem");

//// hook the solver and pc to the linear system.
  connector = services->getPort("connector");
  int err;
  err = connector->connect(LinearSystemID, "solver", SolverID, "solver");
  assert(err==0);
  err = connector->connect(LinearSystemID, "preconditioner", PCID, "apply");
  assert(err==0);
  
//// Hook the ports we're using to LinearSystemID.
//// Each provideTo amounts to:
//// connect(LinearSystemID,"fooToBeUsedByLSName",myId,"barBeingUsedByMeName");
//// where connect now has not only fetch and make connections
//// internally but also needs to notice the cases where one of the
//// componentID is the self id of the caller.
  A = services->getPort("Amatrix");
  assert(A!=0);
  err = connector->provideTo(LinearSystemID, "a", A);
  assert(err==0);

  X = services->getPort("Xvector");
  assert(X!=0);
  err = connector->provideTo(LinearSystemID, "x", X);
  assert(err==0);

  B = services->getPort("Bvector");
  assert(B!=0);
  err = connector->provideTo(LinearSystemID, "b", B);
  assert(err==0);

//// Solve the damn thing, but we have to be twisty, unfortunately,
//// unless we have a call dispatch service (which isn't generic).
  // first we provide the port
  err = connector->exportAs(LinearSystemID,"scaleAndSolve",
                            "goCG");
  assert(err==0);

  // Then we get the port we provide, since this is required by the
  // deliberately vague mess that is defines getPort.
  GoPort *system;
  system = services->getPort("goCG");
  system->go();

  // then we find out how we did.
  err = connector->exportAs(SolverID, "solverParameterAccess",
                            "solverOutput");
  ESI_Solver *solver;
  solver = services->getPort("solverOutput");
  double resid = solver->computeResidual();

  //
  services->releasePort("solverOutput");
  services->releasePort("goCG");

  //
