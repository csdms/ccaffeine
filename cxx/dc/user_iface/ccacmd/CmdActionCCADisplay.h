#ifndef CmdActionCCADisplay_h_seen
#define CmdActionCCADisplay_h_seen

/** This is the original catchall command we inherited
from Rob. It is superceded by several separate commands.
@see CmdActionCCAArena
@see CmdActionCCAPallet
*/
class CmdActionCCADisplay : public virtual CmdAction {

private:

  // static 
  char *namelist[1];

public:

  CmdActionCCADisplay() ;
  virtual ~CmdActionCCADisplay() ;

  virtual char *argtype() ;

  virtual char **names(int &len) ;

  virtual char *help() ;

  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;

};
#endif // CmdActionCCADisplay_h_seen
