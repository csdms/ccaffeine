#ifndef __CCAFFEINEABSTRACTFRAMEWORK_H__
#define __CCAFFEINEABSTRACTFRAMEWORK_H__


/** Creates a single instance of Ccaffeine and returns that instance
    in calls to clone().  Each time getBootstrapServices() is called
    there is an attempt to create a new component instance within
    Ccaffeine.  If getBootstrapServices() is called with an identical
    instance name as a previous call, a CCAException will be
    thrown. All gov::cca::BuilderService interfaces retrieved from a
    bootstrapped gov::cca::Services will be tied to the same framework
    underneath its AbstractFramework antecedent. */
class CcaffeineAbstractFramework : public virtual gov::cca::AbstractFramework {

private:

  DefaultBuilderModel* bm;
  gov::cca::BuilderService* builder;
  jcpp::StringHash* exteriorComponents;
  int shutdown;
  int count;
  boolean optionDebug; // debug options
  boolean debug;  // general debug
  boolean withMPI; // Are we to initiate MPI?
  int initArgc;
  char** initArgv;

  void parseArgs(int argc, char** argv);
  void initComponentFactory();

public:

  /* Arguments indicate the environment that the Framework will find
   *       itself in: e.g. how many processors, whether MPI/PVM has
   *       already been initiated, etc.  */

  CcaffeineAbstractFramework(int argc, char** argv);

  CcaffeineAbstractFramework(gov::cca::StringList* list);

  virtual ~CcaffeineAbstractFramework();

  /** Obtain Services handle, which noone can set on us as there
      is no "main()" "this" pointer in some languages and this scope
      is "higher" than the framework instance. Cannot be called 
      twice on the same fwk instance without an intervening 
      releaseBootstrapServices. (Is there a real threaded counterexample of this?)
      @param selfInstanceName The name of the component instance the 
      calling code wishes to appear as in the framework. 
      If there is a name collision with an already
      existing component, the name will be appended to be made
      unambiguous. This should be checked by examining the
      result of getComponentID.getLocalName() from the returned
      Services.
      @param selfClassName The name of the component instance the 
      calling code wishes to appear as in the framework. 
      This may, but is not required, to correspond to any
      actual class name.
      @param selfProperties An array of strings that is arranged
      key, value, key, value  for as many keys as needed.

      @return  A normal Services object of the sort normally passed
      in Component.setServices(). 
  */

  gov::cca::Services* getBootstrapServices(char* selfInstanceName, 
					   char* selfClassName, 
					   char** selfProperties) 
    throw (gov::cca::CCAException);

  /** Release Services obtained earlier. This will have the
      side effect of disconnecting any remaining connections that have
      been made between the 'main' component and others in the
      framework.
      @param svc The result of getBootstrapServices earlier obtained.
  */
  void releaseBootstrapServices(gov::cca::Services* svc) 
    throw (gov::cca::CCAException);

  /** Creates a new framework instance based on the
      same underlying framework implementation. This way, a main()
      building several containers (possibly nesting them) can
      pick the implementation class of the framework once and then
      everywhere else clone new instances without hard-coding the framework type.
      The clone is shallow, i.e. it does not create
      copies of any components within the original framework.
  */
  gov::cca::AbstractFramework* createFramework() 
    throw (gov::cca::CCAException);

  /** After releaseBootstrapServices, attempt an orderly shutdown.
      This constitutes setting Services null on all the components.
      Well written components will-
      <pre>
      possibly checkpoint themselves, and
      drop connections, and 
      unregister or remove ports in an orderly fashion, and 
      release any other system resources
      during the setServices(null) call on them.
      </pre>
      In languages supporting a delete call, it is reasonable to call 
      delete on the framework instance after this is called.
  */  
  void shutdownFramework();
};

#endif // __CCAFFEINEABSTRACTFRAMEWORK_H__
