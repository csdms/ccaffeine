#ifndef CmdActionCCAShell_h_seen
#define CmdActionCCAShell_h_seen



/** Command to let one call out to linux from cxx commandline.
 Remove this if you put the framework on the web . */
class CmdActionCCAShell : public virtual CmdAction {

private:

  char * namelist[3];

public:

  CmdActionCCAShell() ;

  virtual ~CmdActionCCAShell() ;

  virtual char *argtype() ;

  virtual char **names(int & name_length) ;

  virtual char *help() ;

  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;

};
#endif // CmdActionCCAShell_h_seen
