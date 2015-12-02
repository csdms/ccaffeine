#ifndef CmdActionCCAConnect_h_seen
#define CmdActionCCAConnect_h_seen

/** Connects using instance port to providing instance port,
using the instance known in the CmdContext BuilderModel.
*/
class CmdActionCCAConnect :  public virtual CmdAction {

private:

  // static 
  char *namelist[1];

public:

  CmdActionCCAConnect() ;

  virtual ~CmdActionCCAConnect() ;

  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;

  virtual char * help() ;

  virtual char *argtype() ;

  virtual char **names(int &len) ;

};
#endif // CmdActionCCAConnect_h_seen
