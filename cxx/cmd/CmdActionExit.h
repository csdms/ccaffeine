#ifndef CmdActionExit_h_seen
#define CmdActionExit_h_seen

// $Id: CmdActionExit.h,v 1.6 2005/02/01 00:14:33 baallan Exp $


// requires 
// #include "jc++/jc++.h"
// #include "jc++/util/Vector.h"
// #include "cmd/CmdContext.h"
// #include "cmd/CmdAction.h"

/** standard exit command for all Cmd parsers. */
class CmdActionExit : public virtual CmdAction {

public:

  CDELETE CmdActionExit();
  virtual ~CmdActionExit();

  /** Always returns -1. */
  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;
  
  virtual char * help();

  virtual char * argtype();

  virtual char ** names(int& len);

private:

  /** we have 4 names */
  char *namelist[4];
    
};
#endif // CmdActionExit_h_seen
