#ifndef CmdActionCCARepository_h_seen
#define CmdActionCCARepository_h_seen

/** Surrogate for whatever real repository interface
becomes available from Foss. */
class CmdActionCCARepository : public virtual CmdAction {

private:

  char *namelist[1];

public:

  CmdActionCCARepository() ;

  virtual ~CmdActionCCARepository() ;


  virtual char * argtype() ;


  virtual char **names(int & len) ;


  virtual char * help() ;

  /** Currently supports repository get <class> and some other things */
  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;

};
#endif // CmdActionCCARepository_h_seen
