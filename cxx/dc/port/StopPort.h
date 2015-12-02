#ifdef HAVE_CLASSIC
/** StopPort for use in interrupting loops gracefully.
    @author Ben Allan, 9/30/1999, Sandia National Laboratories.
    @version $Id: StopPort.h,v 1.7 2004/10/16 05:53:21 baallan Exp $
 */
class StopPort : public virtual classic::gov::cca::Port {
public:
  /** Returns 0 if no interrupt is set, OTHERWISE returns interrupt value. */
  virtual int get() =0;
  /** Set 0 to clear interrupt. */
  virtual void setInterrupt(int interrupt) =0;
};
#endif // HAVE_CLASSIC
