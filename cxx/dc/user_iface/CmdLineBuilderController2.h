#ifndef CmdLineBuilderController2_h_seen
#define CmdLineBuilderController2_h_seen

// requires
// #include "jc++/jc++.h"
// #include "dc/user_iface/BuilderController.h"
// #include "dc/user_iface/ccacmd/CmdActionCCA.h"

/** A command line controller of the Model-View-Controller pattern for
    the builder.  This reads from input and instructs the BuilderModel
    to perform actions and the BuilderView to printout information. 

    This implementation encapsulates all the globals into a command
    context cc.

    This implementation is also where we force CCAFFEINE to link
    various classes/functions/globals statically as a public service
    for components.
 */
class CmdLineBuilderController2 : public virtual BuilderController {

private:

  CmdParse *cp;
  char *rcFileName;
  DefaultBuilderModel *dbm;
 
  void setup() ;

public:
  /** input obtained from IO::in */
  CmdLineBuilderController2(CmdLineBuilderView *bv, DefaultBuilderModel* bm);

  CmdLineBuilderController2(FILE* in, CmdLineBuilderView *bv, DefaultBuilderModel* bm);

  //  CmdLineBuilderController2(FILE* in, FILE* out);

  ~CmdLineBuilderController2();


  /** Begin recieving input events from the user. */
  int parse();

   /** Add an action to the command stream of the controller.  Right
      now the Benware does not support removal. */
  virtual void addAction(CmdAction* action);

  /** returns 0 if ok, nonzero otherwise.
   * Used in this configuration, does not support mpi.
   */
  static int main(int argc, char **argv) ;

  /** This calls any functions necessary to prevent the link
    editor (ld) from stripping 'unused' functions that will be
    needed later by dynamically loaded components. */
  int forceLink();
};
#endif // CmdLineBuilderController2_h_seen
