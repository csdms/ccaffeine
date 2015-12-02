#ifndef __GOTHREADCOMPONENT_HH__
#define __GOTHREADCOMPONENT_HH__


/**
 * Sets a date string on a StringConsumerPort.  It does this repeatedly
 * until the "Stop" button is pushed.
 */

class GoThreadComponent : public virtual classic::gov::cca::Component {

 private:


  classic::gov::cca::Services *svc;
  classic::gov::cca::StringConsumerPort *out;

  // thread management
  class GoPort_go : public virtual classic::gov::cca::GoPort {
  private:

    GoThreadComponent *  myGoThreadComponent;

  public:
    /*
     * We must access the state of the GoThreadComponent
     * to figure out whether the Go is running or not.
     */
    GoPort_go(GoThreadComponent * myGoThreadComponent);
    virtual ~GoPort_go(){}
    virtual int go();
  };

  class GoPort_stop : public virtual classic::gov::cca::GoPort {
  private:

    GoThreadComponent *  myGoThreadComponent;

  public:
    /**
     * In this component we must access the state of the GoThreadComponent
     * to tell the running go method to stop.
     */
    GoPort_stop(GoThreadComponent * myGoThreadComponent);
    virtual ~GoPort_stop(){}
    /**
     * Confusingly, the go button on this port will cause the other
     * GoPort to stop.  Kind of like pushing the "start" button in
     * Windows to shutdown.
     */
    virtual int go();
  };

  int isRunning;
  GoPort_go * go;
  GoPort_stop * stop;

 public:

  GoThreadComponent();
  virtual ~GoThreadComponent();


  virtual void setServices(classic::gov::cca::Services *cc);
#if (defined(__GNUC__)&&(__GNUC__<3))
  friend class GoPort_go ;
  friend class GoPort_stop ;
#endif
};


#endif 
