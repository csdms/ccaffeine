#ifndef CmdActionCCAPallet_h_seen
#define CmdActionCCAPallet_h_seen


/** List the contents of the pallet */
class CmdActionCCAPallet : public virtual CmdAction {

private:

  char *namelist[3];

public:

  CmdActionCCAPallet() ;

  virtual ~CmdActionCCAPallet() ;

  virtual char *argtype() ;

  virtual char **names(int& name_length) ;

  virtual char *help() ;

  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;

};
#endif // CmdActionCCAPallet_h_seen
