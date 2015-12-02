#ifndef CmdActionCCALinks_h_seen
#define CmdActionCCALinks_h_seen

/** The links command lists the connections known in the 
associated BuilderModel from the CmdContextCCA. */
class CmdActionCCALinks : public virtual CmdAction {

private:

   char * namelist[2];

public:

  CmdActionCCALinks() ;

  virtual ~CmdActionCCALinks() ;

  virtual char * argtype() ;

  virtual char ** names(int &len) ;

  virtual char * help() ;

  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;

};
#endif // CmdActionCCALinks_h_seen
