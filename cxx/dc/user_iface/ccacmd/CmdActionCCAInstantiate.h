#ifndef CmdActionCCAInstantiate_h_seen
#define CmdActionCCAInstantiate_h_seen

/** Find a class in the palette and create an instance of it.
*/
class CmdActionCCAInstantiate : public virtual CmdAction {

private:

  // static 
  char *namelist[3];

public:

  CmdActionCCAInstantiate() ;

  virtual ~CmdActionCCAInstantiate() ;


  virtual char * argtype() ;


  virtual char **names(int & len) ;


  virtual char * help() ;

  /** Create instance of class given with optional instance name.
  Without a name, a unique instance name will be generated. */
  virtual int doIt(CmdContext *cc, JCPN(Vector) *args) ;

};
#endif // CmdActionCCAInstantiate_h_seen
