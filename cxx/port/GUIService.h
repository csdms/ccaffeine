#ifndef port_GUIService_h_seen
#define port_GUIService_h_seen
/** Use scenario:
    registerUsesPort("GUIService",...);
    GUIService* GUIPort = dynamic_cast<GUIService*>(getPort("GUIService"));
    GUIPort->load("gov.sandia.sophia.PlottingBean http://x.sandia.gov/plotData.txt");
    // Put in code that deals with the plotting here
    // ...
*/
#include <string>

/** "GUIService" is the string port type to request in both classic and neo.
 * The type to then dynamic_cast to once retrieved as a port of some
 * flavor is GUIService.
 *
 * Component's eye view of the ccaffeine GUI world. 
 * */
class GUIService
#if (defined(HAVE_CLASSIC) || defined(HAVE_NEO))
: 
#endif // neo or classic
#ifdef HAVE_CLASSIC
	public virtual classic::gov::cca::Port
#endif // HAVE_CLASSIC
#ifdef HAVE_NEO
#ifdef HAVE_CLASSIC
,
#endif
       	public virtual neo::cca::Port
#endif // HAVE_NEO
{
 public:
  virtual ~GUIService() {}

  virtual void load( ::std::string & arguments) = 0;

};

#endif // port_GUIService_h_seen
