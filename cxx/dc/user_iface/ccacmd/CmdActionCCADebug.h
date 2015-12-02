#ifndef CmdActionCCADebug_h_seen
#define CmdActionCCADebug_h_seen

/** this file is no longer in use. but may come handy later/elsewhere. */
class CmdActionCCADebug : public virtual CmdAction {

private:

  // static 
  char * namelist[2];

public:

  CmdActionCCADebug() ;

  virtual ~CmdActionCCADebug() ;

  virtual char *argtype() ;

  virtual char **names(int & name_length) ;

  virtual char *help() ;

  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;

};
#endif // CmdActionCCADebug_h_seen
