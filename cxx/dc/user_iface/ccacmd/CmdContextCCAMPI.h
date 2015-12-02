#ifndef CmdContextCCAMPI_h_seen
#define CmdContextCCAMPI_h_seen


// #include "util/IO.h"
// #include "jc++/jc++.h"
// #include "jc++/util/jc++util.h"

// #include "cmd/CmdContext.h"
// #include "cmd/CmdAction.h"
// #include "dc/user_iface/DefaultBuilderModel.h"
// #include "dc/user_iface/CmdLineBuilderView.h"

/** PATHSEP_STRING should come from a top level config, as it's
    different under win. The only other place so far needing it
    is  ./dc/framework/ComponentFactory.cxx.
*/
#define PATHSEP_STRING "/"

/** another taste may make this name different, so we put it here */
#define CCAFE_RC_NAME ".ccaferc"

/** The CCA demo command-line interpreter has some messy data,
which is as it should be in useful programs. We are constructed
with a builderview and we in turn create the buildermodel.
To bootstrap ourselves further, we parse an rcFile once.  */
class CmdContextCCAMPI : public virtual CmdContextCCA {

public:

  /** Where we send stuff and get stuff. We extract bm from it. */
  CmdLineBuilderView *bv;

  /** instantiation of interpreters has specific details.
    In this cca parser, we need a builderview. */
  CmdContextCCAMPI(CmdLineBuilderView *bv_, DefaultBuilderModel* bm, bool batch_=true);

  /** instantiation of interpreters has specific details.
    In this cca parser, we need a builderview and an output channel. */
  CmdContextCCAMPI(FILE* out, CmdLineBuilderView *bv_, DefaultBuilderModel* bm, bool batch_=true);

  virtual ~CmdContextCCAMPI();

protected:

  /**
    Returns 1 if rcfile apparently found and 0 if not.
    rcFile is set up for reading if 1 returned.
  */
  int initRC();

  /** 
    In our version of _readLine, we have overloaded to handle an rc file.
    We look for lines in files env(CCAFE_RC_FILE), env(HOME)/.ccaferc, and
    a compiled in path $(CCAFE_INSTALL_ROOT)/cxx/dc/user_iface/CcaffeineRC
    to return before we start parsing the regular input obtained from bv.
    The advisability of this on a global file system is not investigated here.
    GFS Hint: if it's a problem, have each node run with a different 
    env(CCAFE_RC_FILE) value.
  */
  CFREE virtual char *_readLine(int &readerr);

  bool batch;

};
#endif //CmdContextCCAMPI_h_seen
