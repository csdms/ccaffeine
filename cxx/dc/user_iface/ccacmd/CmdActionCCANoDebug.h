#ifndef CmdActionCCANoDebug_h_seen
#define CmdActionCCANoDebug_h_seen


/** this file is no longer in use, tho may come handy later/elsewhere. */
class CmdActionCCANoDebug : public virtual CmdAction {

private:

  char * namelist[2];

public:

  CmdActionCCANoDebug() ;

  virtual ~CmdActionCCANoDebug() ;

  virtual char *argtype() ;

  virtual char **names(int & name_length) ;

  virtual char *help() ;

  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;

};
#endif // CmdActionCCANoDebug_h_seen
