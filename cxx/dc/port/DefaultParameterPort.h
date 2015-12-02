#ifndef DefaultParameterPort_h_seen
#define DefaultParameterPort_h_seen

#include <string>
#include <vector>
#include <stdexcept>
/** auxiliary class of dubious distinction.
 * each instance is a container of a string or a pointer.
 */
namespace dpp {

class tvElement {
private:
	std::string tabName;
	BaseParameter *bp;
	bool isString;
public:
	~tvElement() {
		tabName = "deleted";
		bp = 0;
	}
	tvElement(std::string & s)
		: tabName(s), bp(0), isString(true) {}
	tvElement(BaseParameter *p)
		: tabName(""), bp(p), isString(false) {}
	std::string getN() { 
		if (!isString) { 
			throw std::logic_error("not tabname element");
		}
		return tabName; 
	}
	BaseParameter *getP() {
		if (isString) { 
			throw std::logic_error("not parameter element");
		}
	       	return bp;
       	}
}; // end tvElement class

} ENDSEMI // end namespace dpp

/**
  So the idea is for the component to create and hand to us a bunch
  of parameter objects that it has its own references to. 

  At such time as isConfigured returns true, the component can use 
  these objects as user-blessed input. Each parameter.value has been
  initialized.

  This is our default implementation of the ConfigurableParameterPort
  interface.
*/
class DefaultParameterPort :  public virtual ConfigurableParameterPort {

private:
  /** The tabVector is a list of other vectors.
      For each of these othervectors, the first entry is the groupName String.
      The pVector is a flat list of all the parameters, in the order added.
  */
  ::std::vector< ::std::vector< ::dpp::tvElement > > tabVector;
  ::std::vector< BaseParameter *> pVector;
  char *title; // assume to live in user space
  bool configured;
  int requestCount;
  ::std::vector< ParameterGetListener * > getListeners;
  ::std::vector< ParameterSetListener * > setListeners;

public:

  DefaultParameterPort() ;
  virtual ~DefaultParameterPort() ;

  /** Returns 0 if success, -1 if error. */
  virtual int setConfigurationString(char * fieldName, char *value);


  /** Return stringified form of all known requests, with
      embedded title/tab information. */
  /*CFREE*/ virtual char *getConfigurationString(char *infix) ;
  /*CFREE*/ virtual char *getConfigurationString(char *infix, char *fieldName) ;

  /** Methods used by the component that is putting user in charge of
      the tunable parameters.
      Returns TRUE if current set of requests has been
      explicitly blessed by the user. FALSE otherwise.
      Since all parameters come with a default, use of
      this is just a policy option.
  */
  bool isFullyConfigured() ;

  /** Clear all previously added requests, titles, groups. */
  void clearRequests() ;

  /** give the creator of a parameter port a chance to 
      update its contents. Is called in getConfigurationString();
  */
  void setUpdater(ParameterGetListener *po);

  void setUpdatedListener(ParameterSetListener *po);

  /** A batch of requests may have a title/banner String.
    A typical use of the title is at the top of a gui window.
    A framework is likely to prefix the title with a component name.*/
  void setBatchTitle(char *title_) ;

  /** The requests in a batch may be grouped with this call, the
     name attaching to all requests made after this call until
     another of these calls is made.
     The name is typically used as the key on a tabbed dialog
     or a text screen region. */
  void setGroupName(char *name) ;

  /** The following characters in strings associated with this
    interface may make for misbehavior of certain Views
    of this port : "\n\r\t"

    The prompt string to display
    (if not NULL) will be presented to the human and an appropriate
    response will be returned. 

    If the help string is not NULL, and the user asks for help,
    then the help string will be presented to the human.

    Appropriate responses are those which fall in the range (or CHOICE)
    given by the caller. (specific semantics per parameter type.)

    The user input is the value in each function.
    The Default value must be supplied. Out of range Defaults
    will be mapped to the first/lowest value allowed. 
     p may be any of the parameters from the parameters package.
     e.g.
     StringParameter sp = new StringParameter("foo","bar","loser");
        sp->addChoice("winner");
        sp->addChoice("village idiot");
     pp->addRequest(sp);
     pp->addRequest(new IntParameter("foo","bar",0,-10,10));
  */
  void addRequest(BaseParameter *p) ;

  BaseParameter *getParameter(char  *name);
};
#endif //DefaultParameterPort_h_seen
