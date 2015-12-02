#ifndef ConfigurableParameterPort_h_seen
#define ConfigurableParameterPort_h_seen


/**
  The idea is for the component to create and hand to us a bunch
  of parameter objects that it has its own references to. We
  use them long enough to negotiate with the user interface and
  then forget them.

  This is the interface specification. The implementation
  is hidden from the component, other than knowledge of the
  BaseParameter interface.
*/
class ConfigurableParameterPort :  public virtual ParameterPort {

public:

  virtual ~ConfigurableParameterPort() {}

/** ParameterPort interface */

  /** Sets value and returns 0 if fieldName is known.
   After the value is set but before a 0 return, any 
   ParameterSetListeners associated with the Port are called.
   The value given is *assumed* to be valid. We expect that
   the various input UIs  rejected invalid inputs.
   */
  virtual int setConfigurationString(char * fieldName, char *value) =0;

  /** Return stringified form of all known requests, with
      embedded title/tab information. Calls any ParameterGetListeners
      registered. */
  /*CFREE*/ virtual char *getConfigurationString(char *infix) =0;

  /** Return the stringified form of a specific field in the parameter page.
      Does not call ParameterGetListeners. */
  /*CFREE*/ virtual char *getConfigurationString(char *infix, char *fieldName) =0;

  /** return the named parameter object if it exists. */
  virtual BaseParameter *getParameter(char *name)=0;


/** Methods used to configure a parameter port */
  /** Clear all previously added requests, titles, groups. After
      this call, it is as if the ConfigurableParameterPort has
      never been configured. */
  virtual void clearRequests() =0;

  /** A batch of requests may have a title/banner String.
    A typical use of the title is at the top of a gui window.
    A framework is likely to prefix the title with a component name.*/
  virtual void setBatchTitle(char *title_) =0;

  /** The requests in a batch may be grouped with this call, the
     name attaching to all requests made after this call until
     another of these calls is made.
     The name is typically used as the key on a tabbed dialog
     or a text screen region. */
  virtual void setGroupName(char *name) =0;

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
    The Configurable value must be supplied. Out of range Configurables
    will be mapped to the first/lowest value allowed. 
     p may be any of the parameters from the parameters package.
     e.g.
     StringParameter sp = new StringParameter("foo","bar","loser");
        sp->addChoice("winner");
        sp->addChoice("village idiot");
     pp->addRequest(sp);
     pp->addRequest(new IntParameter("foo","bar",0,-10,10));
  */
  virtual void addRequest(BaseParameter *p) =0;


/** Methods used primarily by the component that owns
    the ConfigurableParameterPort instance to handle events. */

  /** 
      Returns TRUE if current set of requests has been
      explicitly blessed by the user. FALSE otherwise.
      Since all parameters come with a default, use of
      this is just a policy option.
  */
  virtual bool isFullyConfigured() =0;

  /** Give the creator of a parameter port a chance to 
      update its contents. Is called in getConfigurationString()
      before the response is generated.
  */
  virtual void setUpdater(ParameterGetListener *powner)=0;

  /** Register listeners who care that an parameter is set. 
      Listeners are called after values are set. */
  virtual void setUpdatedListener(ParameterSetListener *powner)=0;

};



#endif //ConfigurableParameterPort_h_seen
