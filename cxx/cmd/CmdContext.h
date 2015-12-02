#ifndef CmdContext_h_seen
#define CmdContext_h_seen


// $Id: CmdContext.h,v 1.8 2005/02/01 00:14:33 baallan Exp $

// requires
// #include "jc++/jc++.h"
// #include "jc++/util/jc++util.h"

/** The actions for any useful command-line interface ultimately depend
    on some context information.
    Each specific interpreter will subclass CmdContext differently,
    and write CmdActions that use interpreter specific data or methods.
  */
class CmdContext : public virtual JCPN(Object) {

private:

  /** every interpreter has a debug switch, which may or may not do much. */
  boolean debug_;

  /** every interpreter has a verbose switch for error message style. */
  boolean verbose_;

public:

  CDELETE CmdContext();
  virtual ~CmdContext(){}

  /** change debugging flag */
  boolean setDebug(boolean d);

  /** return the current debug flag value. */
  boolean debug();

  /** change verbose messages */
  boolean setVerbose(boolean v);

  /** return verbosity message */
  boolean verbose();

  /** Writing a line */
  virtual void pn(char * s)=0;
  /** Writing a character c \n */
  virtual void pn(char c)=0;

  /** Write a string w/out adding \n */
  virtual void p(char * s)=0;
  /** Write a character w/out adding \n */
  virtual void p(char c)=0;

  /** prompt string. not yours to delete or cache except by copy. */
  virtual char * prompt()=0;

  /** Interpreter has to get input from somewhere, line at a time.
   Dearly wish this could support command and name completions.
   If 0 is returned, the value of readError is returned to the caller
   of CmdParse::parse() for the parser instance containing this cc.
  */
  virtual char * readLine(int & readError)=0;

  /** Interpreter can define a restricted set of classes as qualified
   for command-line use. May return null.
   This takes care of changing approximate class names to exact,
   in some parsers.
   If a string is returned, it will be exactly defined in the
   CmdContext, but the partial-matching is not guaranteed unique.
   The returned string is owned by the context and the caller need
   not free/delete it.
  */
  virtual char * getClass(char * className)=0;

  /** Interpreter can define a restricted set of instances as qualified
   for command-line use. May return null.
   This takes care of changing approximate instance names to exact,
   in some parsers.
   If a string is returned, it will be exactly defined in the
   CmdContext, but the partial-matching is not guaranteed unique.
   The returned string is owned by the context and the caller need
   not free/delete it.
  */
  virtual char * getInstance(char * instanceName)=0;


};
#endif // CmdContext_h_seen
