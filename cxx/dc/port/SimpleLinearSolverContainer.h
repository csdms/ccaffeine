#ifdef HAVE_CLASSIC
#ifndef SimpleLinearSolverContainer_h_seen
#define SimpleLinearSolverContainer_h_seen
/** Simplistic interface to linear equation solvers
in several precisions, possibly complex. 
We can derive reliably by typedef
SimpleLinearSolverContainer_R8I4 for the common double/int case.
*/
template<class Scalar, class Ordinal>
class SimpleLinearSolverContainer : public virtual classic::gov::cca::Port {

public:

  virtual ~SimpleLinearSolverContainer() {}

  /** Local: define an equation in terms of variable Id's and
             paired coefficients and a single right hand side.
      @param equationId must be unique of some integer type, so if setEquation is called
             twice with the same id, the last definition wins.
      @param variableLen is the number of variables in the equation, and hence the
             length of variableIds and variableCoefs.
      @param variableIds array must be unique in a given equation, and is variableLen
             long.
      @param variableCoefs array is variableLen long.
      @param rhs must be set at the same time, per Rob Armstrong. Bug.
  */
  virtual void setEquation(Ordinal equationId, Ordinal variableLen, Ordinal *variableIds, Scalar *variableCoefs, Scalar rhs) = 0;

  /** Collective: tells container there are no more equations coming, allowing
      it to setup any internal structures for solving.
      @return 0 if system is successfully built. "Success" 
      is defined by the implementation. Some implementations may allow non-square
      systems. 1 otherwise.
  */
  virtual int buildSystem() = 0;

  /** Collective: run the solver, after the buildSystem is done. 
     @return -2: system never solved.
     -1: permanent failure of solution algorithm.
     0: possible to continue iterating.
     1: solution reached.
  */
  virtual int solve() = 0;

  /** Collective: get the computed residuals, after the solve is done. 
     @return -2: some equationId requested is unknown or other extreme bogosity.
      -1 system unsolved.  0 successful call.
  */
  virtual int getResidual(Ordinal equationLen, Ordinal *equationIds, Scalar *residual) = 0;

  /** Collective: get the computed solution, after the solve is done. 
   @return -2: some variableId requested is unknown or other extreme bogosity.
    -1 system unsolved.  0 successful call.
  */
  virtual int getSolution(Ordinal variableLen, Ordinal *variableIds, Scalar *solution) = 0;

};
#endif //SimpleLinearSolverContainer_h_seen
#endif // HAVE_CLASSIC
