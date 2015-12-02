#ifndef CmdActionCCADisconnect_h_seen
#define CmdActionCCADisconnect_h_seen

/** Disconnects using instance port to providing instance port,
using the instance known in the CmdContext BuilderModel */
class CmdActionCCADisconnect :  public virtual CmdAction {

private:

  // static 
  char *namelist[1];

public:

  CmdActionCCADisconnect() ;

  virtual ~CmdActionCCADisconnect() ;

  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;

  virtual char * help() ;

  virtual char *argtype() ;

  virtual char **names(int &len) ;

};
#endif // CmdActionCCADisconnect_h_seen
