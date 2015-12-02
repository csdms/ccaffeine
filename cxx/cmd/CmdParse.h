#ifndef CmdParse_h_seen
#define CmdParse_h_seen


// requires 
// #include "jc++/jc++.h"
// #include "jc++/util/jc++lang.h"
// #include "jc++/util/jc++util.h"
// #include "cmd/CmdContext.h"
// #include "cmd/CmdAction.h"
// #include "cmd/CmdActionExit.h"
// #include "cmd/CmdActionHelp.h"

/** Simple line parser skeleton and services. 
The main use is to create a particular parser piecewise
by adding CmdActions to it. Stateful parsers are supported by
specializing the CmdContext object. The Context is passed into
each CmdAction. */
class CmdParse : public virtual JCPN(Object) {

private:
  /** CmdActions added to this parser. */
  JCPN(Vector) *alist;
  /** this parser instance's data, functions, io and others */
  CmdContext *cc;
  /** Remove strings from an internally used structure. */
  void clearArgs(JCPN(Vector) * args);

public:

  /** Actions in the constructed parser will be called with icc as their context. */
  CDELETE CmdParse(CmdContext *icc) ;

  ~CmdParse() ;

  /** Adds a command to the parser. Presently does not check the sanity of 
      the command. 
   This function needs to do some insertion with checking for
   duplicates if we're paranoid. As it is, this comes out in
   the wash at getAction. Duplication will make commands useless.
  */
  void addAction(CmdAction *c) ;



  /** Returns the nearest match (by leading characters) of commands 
      stored in the list. */
  CmdAction *getAction(char *s) ;

  /** Returns the context given in the constructor, so the application
      destroying the parser can choose to destroy or reuse the context.
      If you destroy the context, destroy the parser, too.
   */
  CmdContext *getContext();

  // The following holds for all addXxxArg functions:
  // returns 0 if ok, -1 if error in next token, 1 if no next token.

  /** Converts the next token to a class (per app. definition) and adds to 
      arg list. */
  int addClassArg(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) ;


  /** Converts the next token to an instance (per app. definition) and adds 
      to arg list. */
  int addInstanceArg(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) ;


  /** Converts the remaining tokens to a string and adds to arg list. */
  int addLine(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) ;


  /** Adds the next token as a string to the arg list */
  int addStringArg(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) ;

  /** Adds the next token as a DoubleJC */
  int addDoubleArg(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) ;

  /** Adds the next token as a FloatJC */
  int addFloatArg(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) ;

  /** Adds the next token as a IntegerJC */
  int addIntegerArg(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) ;

  /** Adds the next token as a LongJC  (long long) */
  int addLongArg(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) ;

  /** Adds the next token as a BooleanJC  (int) */
  int addBooleanArg(JCPN(StringTokenizer) *st, JCPN(Vector) *args, JCPN(StringBuffer) *cb) ;


  /** Main command-line processing loop. 
      Returns 0 if the parser instance is willing to yield,
      and -1 if the parser instance thinks something fatal happened.
   */
  int parse();

  /** adjust the verbosity of the CmdContext inside. */
  void setContextVerbose(bool noisyHelp);
};
#endif //CmdParse_h_seen
