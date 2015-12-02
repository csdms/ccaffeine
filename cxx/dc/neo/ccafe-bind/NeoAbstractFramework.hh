#ifndef NeoAbstractFramework_hh_seen
#define NeoAbstractFramework_hh_seen

 /* The abstract framework neo users see.
 */
class NeoAbstractFramework  : public virtual neo::cca::AbstractFramework
{

private:
	void *opqFramework;
	int64_t fortranMPIComm;
	bool hasComm;

public:
  NeoAbstractFramework(int64_t fComm, bool useComm);

  // ccafe extension. doesn't actually do anything we
  // can think of right now.
  virtual void initialize( const ::std::string & args );

  /** take an object implementing driverBody and use it once. */
  virtual void run( NeoMain *driver );

  // standard interface
  virtual ~NeoAbstractFramework();

  virtual neo::cca::TypeMap_shared createTypeMap();

  virtual neo::cca::Services *getServices(const std::string & selfInstanceName, const std::string & selfClassName, neo::cca::TypeMap_shared selfProperties);

  virtual void releaseServices( neo::cca::Services * svc);

  /** Tell the framework to close up shop, but the framework
   * instance still needs to be deallocated by falling off the stack
   * or by being deleted or by being passed back to
   * destroyEmptyFramework() in the case that it was
   * created with createEmptyFramework.
   */
  virtual void shutdownFramework();

  /** Constructor of a sub-framework instance -- a separate
   * container from this one with the same implementation,
   * but probably little or no common content.
   */
  virtual neo::cca::AbstractFramework * createEmptyFramework();

  /** Destructor of a framework instance obtained from
   *  createEmptyFramework. 
   *  subframe->shutdown() will be called if it has not
   *  already been.
   */
  virtual void destroyEmptyFramework( neo::cca::AbstractFramework * subframe);

};

#endif // NeoAbstractFramework_hh_seen
