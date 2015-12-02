#ifndef CmdActionCCAProperties_h_seen
#define CmdActionCCAProperties_h_seen

/** The arena command lists the instance known in the 
associated BuilderModel from the CmdContextCCA. */
class CmdActionCCAProperties : public virtual CmdAction {

private:

   char * namelist[1];

public:

  CmdActionCCAProperties() ;

  virtual ~CmdActionCCAProperties() ;

  virtual char * argtype() ;

  virtual char ** names(int &len) ;

  virtual char * help() ;

  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;

};
#endif // CmdActionCCAProperties_h_seen
