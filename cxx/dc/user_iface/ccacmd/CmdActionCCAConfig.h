#ifndef CmdActionCCAConfig_h_seen
#define CmdActionCCAConfig_h_seen


/** Handles the getting and setting of ParameterPorts 
parameter values. */
class CmdActionCCAConfig : public virtual CmdAction {

private:
  char * namelist[2];

public:
  CmdActionCCAConfig();

  virtual ~CmdActionCCAConfig();

  virtual char *argtype();

  virtual char **names(int &nlen);

  virtual char *help();

  virtual int doIt(CmdContext *cc, JCPN(Vector) *args);

};
#endif //CmdActionCCAConfig_h_seen
