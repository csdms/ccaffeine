#ifndef CmdActionCCAPath_h_seen
#define CmdActionCCAPath_h_seen

/**
path sub commands:
init -- from env(CCA_COMPONENT_PATH)
append -- add a dir to the path
prepend -- insert dir at head of path
set -- replace path
show -- display current path
*/
class CmdActionCCAPath : public virtual CmdAction {

private:

  char *namelist[1];

  /** disassembles env string to argv */
  char **pathToArgv(const char *path, int &argc);

  /** destroys the result of a pathToArgv */
  void destroyP2A(char **&argv,int argc);
  
public:

  CmdActionCCAPath() ;

  virtual ~CmdActionCCAPath() ;


  virtual char * argtype() ;


  virtual char **names(int & len) ;


  virtual char * help() ;

  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;

};
#endif // CmdActionCCAPath_h_seen
