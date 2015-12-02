#ifndef CmdActionCCARemove_h_seen
#define CmdActionCCARemove_h_seen

/** Deletes a single instance from the Arena, leaving
it in a very bad state if things were connected to it. */
class CmdActionCCARemove : public virtual CmdAction {
 private:
   char* namelist[1];
 public:
  CmdActionCCARemove();
  virtual ~CmdActionCCARemove();
  virtual char* argtype();
  virtual char** names(int& name_len);
  virtual char* help();
  virtual int doIt(CmdContext* cc, JCPN(Vector)* args);
};



#endif // CmdActionCCARemove_h_seen
