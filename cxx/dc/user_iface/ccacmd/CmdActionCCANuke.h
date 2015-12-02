#ifndef CmdActionCCANuke_h_seen
#define CmdActionCCANuke_h_seen


/** Supposed to remove everything in the Arena. The underlying
BuilderModel code is broken in this regard. */
class CmdActionCCANuke : public virtual CmdAction {
 private:
   char* namelist[1];
 public:
  CmdActionCCANuke();
  virtual ~CmdActionCCANuke();
  virtual char* argtype();
  virtual char** names(int& name_len);
  virtual char* help();
  virtual int doIt(CmdContext* cc, JCPN(Vector)* args);
};



#endif // CmdActionCCANuke_h_seen
