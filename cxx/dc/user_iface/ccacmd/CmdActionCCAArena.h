#ifndef CmdActionCCAArena_h_seen
#define CmdActionCCAArena_h_seen

/** The arena command lists the instance known in the 
associated BuilderModel from the CmdContextCCA. */
class CmdActionCCAArena : public virtual CmdAction {

private:

  // static 
   char * namelist[2];

public:

  CmdActionCCAArena() ;

  virtual ~CmdActionCCAArena() ;

  virtual char * argtype() ;

  virtual char ** names(int &len) ;

  virtual char * help() ;

  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;

};
#endif // CmdActionCCAArena_h_seen
