#ifndef dc_port_DefaultGUIService_h_seen
#define dc_port_DefaultGUIService_h_seen
class DefaultGUIService : 
public virtual GUIService
#ifdef HAVE_NEO
, public virtual neo::cca::Port
#endif // HAVE_NEO
#ifdef HAVE_CLASSIC
, public virtual classic::gov::cca::Port
#endif // HAVE_CLASSIC
{

public:

  DefaultGUIService();
  virtual ~DefaultGUIService();

  virtual void load( ::std::string & arguments);

  void setFrameData(std::map<std::string, void *> *fd);

private:
  std::map<std::string, void *> *frame;
};

#endif // dc_port_DefaultGUIService_h_seen
