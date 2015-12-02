#ifndef CmdActionCCAPortProperties_h_seen
#define CmdActionCCAPortProperties_h_seen

/** manipulates port properties. */
class CmdActionCCAPortProperties : public virtual CmdAction {

private:

   char * namelist[1];

public:

  CmdActionCCAPortProperties() ;

  virtual ~CmdActionCCAPortProperties() ;

  virtual char * argtype() ;

  virtual char ** names(int &len) ;

  virtual char * help() ;

  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;

};
#endif // CmdActionCCAPortProperties_h_seen
