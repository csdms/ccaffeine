#ifndef CmdActionCCAGo_h_seen
#define CmdActionCCAGo_h_seen

// requires
// #include "jc++/jc++.h"
// #include "jc++/util/jc++util.h"
// #include "cmd/CmdContext.h"
// #include "cmd/CmdAction.h"
/** Fire all the go ports or a named go port on a named instance. 
*/
class CmdActionCCAGo : public virtual CmdAction {

private:

  char *namelist[2];

public:

  CmdActionCCAGo();
  virtual ~CmdActionCCAGo();

  virtual char *argtype() ;

  virtual char **names(int& names_len) ;

  virtual char *help() ;

  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;

};
#endif  //CmdActionCCAGo_h_seen
