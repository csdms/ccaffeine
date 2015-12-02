#ifndef CmdActionHelp_h_seen
#define CmdActionHelp_h_seen


// requires 
// #include "jc++/jc++.h"
// #include "jc++/util/jc++util.h"
// #include "cmd/CmdContext.h"
// #include "cmd/CmdAction.h"

/** The standard help implementation for a Cmd parser.  */
class CmdActionHelp : public virtual CmdAction {

private:

  char *namelist[2];
    
  /** lists the names of the CmdAction given */
  void writeCmdNames(CmdContext *cc, CmdAction *c);
  /** lists the syntax, as defined by the argtype given. */
  void writeArgDesc(CmdContext *cc, char *argtype);

public:

  CDELETE CmdActionHelp();
  virtual ~CmdActionHelp();

  /** list help on a specific command or print the dictionary */
  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;
  
  virtual char * help();

  virtual char * argtype();

  virtual char **names(int& len);

};
#endif //CmdActionHelp_h_seen
