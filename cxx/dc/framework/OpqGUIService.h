#ifndef dc_framework_OpqGUIService_h_seen
#define dc_framework_OpqGUIService_h_seen
class OpqGUIService : 
public virtual ::ccafeopq::GUIService,
public virtual KernelPort
#ifdef HAVE_NEO
, public virtual neo::cca::Port
#endif // HAVE_NEO
#ifdef HAVE_CLASSIC
, public virtual classic::gov::cca::Port
#endif // HAVE_CLASSIC
{

public:

  OpqGUIService();
  virtual ~OpqGUIService();

  virtual void load(const  ::std::string & arguments);

  void setFrameData(std::map<std::string, void *> *fd);

private:
  std::map<std::string, void *> *frame;
};

#endif // dc_framework_OpqGUIService_h_seen
