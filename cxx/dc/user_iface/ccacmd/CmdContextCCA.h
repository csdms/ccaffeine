#ifndef CmdContextCCA_h_seen
#define CmdContextCCA_h_seen


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
To bootstrap ourselves further, we parse an rcFile once. 
 CmdContextCCA is the serial/non-mpi version of the parser;
 it allows interactive and rc-only parsing by default. */
class CmdContextCCA : public virtual CmdContext {

 private:

  char * tmpString;

public:

  // Specific interpreters define different globals like so.
  /** Where all the real goop is hidden, including the framework. we create this. */
  DefaultBuilderModel *bm;

  /** Where we send stuff and get stuff. We extract bm from it. */
  CmdLineBuilderView *bv;

  /** instantiation of interpreters has specific details.
    In this cca parser, we need a builderview. */
  CmdContextCCA(CmdLineBuilderView *bv_, DefaultBuilderModel* bm) ;

  /** instantiation of interpreters has specific details.
    In this cca parser, we need a builderview and an output channel. */
  CmdContextCCA(FILE* out, CmdLineBuilderView *bv_, DefaultBuilderModel* bm) ;

  virtual ~CmdContextCCA();

  /** Write a line from a null-terminated string. */
  virtual void pn(char *s) ;

  /** Write a line fraction from a null-terminated string. */
  virtual void p(char *s) ;

  /** Write a character and a carriage return. */
  virtual void pn(char s) ;

  /** Write a character. */
  virtual void p(char s) ;

  /** cca> */
  virtual char *prompt() ;

  /** Read lines using _readLine. If the line ends in \, read another
      line and append it before returning the combined line. */
  CFREE virtual char *readLine(int &err);

  /** Checks the name given against the arena list in the buildermodel.
      Uses an ugly fuzzy match algorithm. */
  virtual char *getInstance(char *instanceName) ;

  /** Checks the name given against the class list in the buildermodel.
      Uses an ugly fuzzy match algorithm. */
  virtual char *getClass(char *className) ;

  /** Returns the rcfile name and lines read statistics. If
    none returns will be null/0 */
  char *getRCInfo(int & linesRead, int & lineErr);

protected:
  /** Found from bv or given in constructor. */
  FILE* in;

  /** constructor args independent initializations. */
  void setup();

  /** remove trailing blanks from strings. */
  void trim_blanks(char *str);

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

  /**
    Returns 1 if rcfile apparently found and 0 if not.
    rcFile is set up for reading if 1 returned.
  */
  virtual int initRC();

  /** Reads a line from the rcfile into buf. status out is 0 if ok, 1 if no more lines
      or other fatal error. rcFile is closed before a return of 1. */
  int rcLine(char *buf, int bufSize);

  /** Checks for magic word at start of rc file. avoids accidentally parsing dumb files.
    returns 0 if ok, 1 if bad magic.  The magic word is #!ccaffeine. */
  int badMagic(FILE *file, const char *fname);

  /** checks for #!eof marker to interrupt file read before end of file. 
   * use is to turn off every thing in a .ccaferc after the
   * #!eof if you're using the gui and want only to go as far in
   * your usual .ccaferc as loading classes.
   */
  bool isFakeEOF(char *line);

  /** The rc filename we found and read. */
  char *rcFileName;

  /** File pointer of rcfile, or 0 if none. */
  FILE *rc;

  /** Number of rc lines read so far. */
  int lineCount;

  /** Most recent rc error, possibly nothing, eof, or something exotic. */
  int lastErr;

  /** Flag for whether or not we've tried opening the rc file. */
  int rcUnknown;
};
#endif //CmdContextCCA_h_seen
