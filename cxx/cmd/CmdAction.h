#ifndef CmdAction_h_seen
#define CmdAction_h_seen

// $Id: CmdAction.h,v 1.6 2005/02/01 00:14:33 baallan Exp $


// requires
// #include "jc++/jc++.h"
// #include "jc++/util/jc++util.h"
// #include "cmd/CmdContext.h"

/** CmdAction is the interface specification for adding a
command to a CmdParse parser. */
class CmdAction : public virtual JCPN(Object) {

public:

  virtual ~CmdAction(){}

  /** Does the action, called with the CmdContext of the interpreter
   and with a vector that matches the signature given by argtype().
   The exit command returns 1; others return 0. */
  virtual int doIt(CmdContext *cc, JCPN(Vector) *args)=0;

  /** Returns a string containing the description of this command. */
  virtual char *help()=0;

  /** Describes the args Vector wanted by this Command.
   * <pre>
   * This is our hack to get around stupid varargs-lessness in java.
   * Each character indicates a separate user argument and its type.
   * Type checked user input:
   *   C --> class named by user.
   *   c --> optional class named by user.
   *   I --> instance named by user.
   *   i --> optional instance named by user.
   *   S --> string token from user.
   *   s --> optional string token from user.
   *   K --> long token from user.
   *   k --> optional long token from user.
   *   D --> int token from user.
   *   d --> optional int token from user.
   *   B --> bool token from user.
   *   b --> optional bool token from user.
   *   G --> double token from user.
   *   g --> optional double token from user.
   *   * --> repeat previous character ad infinitum. can only appear last. 
   * Special (cannot be followed directly by *):
   *   A --> all of the line after the command name token as a single string.
   *   a --> all of the line after the command name token as optional string.
   *   L --> the list of known CmdActions.
   *   P --> the command parser itself. 
   * </pre>
  */
  virtual char *argtype()=0;

  /** name(s) of the function. Do not free them. on exit len is number of names. */
  virtual char ** names(int& len)=0;

};
#endif // CmdAction_h_seen
