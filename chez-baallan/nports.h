Everything here is in gov::cca::/gov.cca. namespace. Much, but not all
inherits from Port.
Originally there was a sequence scheme, but it turned into a brain dump.


Some design cases to accomodate:
#) Making recursively nestable containers possible simply
by introducing frame/component-scoped proxies that redirect calls
+ sufficient scoping information to the root-most container.
{user demand}

#) accomodate both the in and outside of the container having
ports portably. {rob}

#) separating component factory from repository mechanisms.
{ben}

#) allow multiple uses ports without requiring precompiler magic.
{carl, rob}

#) provide a global name and proc-count service. {jim/dave/craig}

#) Allow all (or all but one) service-provider components to be connected
(based on a policy interface) automatically without
showing up in the "component arena". This may show up as a
ConnectionFrameworkControlService interface or by some other mechanism.
In particular users need both automatic and manual connections-
Automatic:
- Many services where ports can only be satisfied by
  associating implementation instances 1:1 with the using component.
- Some services ports can be satisfied by one component
  instance providing to all using components.
- Some services which will be provided by the same
  implementation object as that behind the Services interface.
Manual:
- User specifies the connection.
Both:
- That is, in a nested container component specialized to some
  task (or functioning as a proxy gateway), the autoconnect policies
  may be different and so the container needs to be able to
  adjust the policies for the connection service in its scope.
- For those components with an instance 1:1 constraint, we may
  need to register the factory.

---------------------------------------------------------
#define abstract class
#define extends :
---------------------------------------------------------
abstract ComponentId {
  /** Returns the string unique to the frame we're in.
      If we're clever, the name is also globally unique, which is doable.
   */
  const char *toString();
};

abstract ComponentIdFactory extends Port {
  /** Creates component ids (with globally unique string id)
      by (in whatever way desired) grafting the ComponentInstanceInfo
      desired onto the frame's toString(). With nested containers,
      this allows for construction of dot-qualified names that would
      allow an end user to correctly refer to all instances wherever
      nested.
      If ComponentIdFactory is always a component itself, then
      frame could be omitted as an argument.
   */   
  ComponentId *createId(ComponentId *frame,
                        const ComponentInstanceInfo * info);

  /** return it to the factory. */
  void destroyId(ComponentId *id);
};

---------------------------------------------------------
abstract ComponentInstanceInfo {
  /** Return the name within the container, which is probably
      much shorter than the global string id.
   */
  const char *getName();

  /** Return the name within the container of the class
      for this instance.
   */
  const char *getComponentClass();

  /** This function may be out of place. */
  Services *getServices();
};

abstract ComponentInstanceInfoFactory extends Port {
  /** Create a component info. The Services may be out of place. 
    */
  ComponentInstanceInfo *createComponentInstanceInfo(const char *name,
                                                     const char *class,
                                                     const Services *services);

  /** return it to the factory. */
  void destroyComponentInstanceInfo();
};

---------------------------------------------------------
abstract ServicesFactory extends Port {
  Services *createServices();
  destroyServices(Services *s);
};

---------------------------------------------------------
/** c++ wrapper/object for a string array compatible with c-thinking.
   Yah, there's a c++ template for this interface, but it
   doesn't work cleanly through sidl and in any case we aren't
   going to force templates on anyone. The implementation under this
   could obviously be any number of c++ container templates
   instantiated to hold strings.
 */
abstract Argv (non-Port) {

  /** Get the number of strings in this argv.
    */
  const int getArgCount();

  /** Get the n-th element of this argv. 
    */
  const char *getArg(int i);

  /** Extend this argv by adding a copy of the arg passed here.
    */
  int appendArgv(const char *arg);

  /** Duplicate completely an argv. It */
  Argv *copyArgv();

  // convenience methods:
  /** Compute the number of strings in
      another well-formed (NULL-terminated) argv.
   */
  int sizeOfArgv(char **argv);
};

/** Factory for argvs.
*/
abstract ArgvFactory extends Port {
  Argv *createArgvFromCArgv(char **);
  Argv *createArgv();
  void destroyArgv();
};

---------------------------------------------------------
abstract ComponentFactory extends Port {
  /** Create a component instance, given the class name.
      A CreationService can be layered atop this factory
      interface.
  */
  Component *createComponentInstance(const char *className);

  /** Return the component to the factory. 
    */
  void destroyComponentInstance(Component *component);

  /** Add a constructor (C-wrapper of NULL constructor)
      to the factory along with xml data describing the
      component (which includes at minimum the class name).
   */
  const char *addClass(Component *(*create)(), const XMLDescription *xml);

};

--------------------------------------------------------
/** In a framework there is an arena where instantiated components
live (possibly the arena admits nested component structures).
This service interface lets one create instances and have them
placed appropriately in the arena with unique names and so forth
without knowing any details about how this is done.
@param className The type of instance we want to create. It's syntax
       does not include a URL. A separate repository
       service must first be accessed to suck the component
       definitions desired into the framework.
@param instanceName The instance name desired in the frame of
       the component using factory service. The service
       will attempt to use this name, but may change it if
       it is not unique. The final name selected can be fetched
       with the toString method of the ComponentId.
*/
abstract ComponentFactoryService extends Port {
  ComponentId *createComponent(const char *className, const char *instanceName);
  xmlinfolist getComponentClassList();
};

abstract RepositoryService extends Port {
  xmlinfolist getAvailableComponentClasses(const char *URL);
  int importClass(const char *XMLInfo, bool private, bool lazy);
 // ?? what else
};
--------------------------------------------------------
/** This is an interface entirely in terms of IDs and portinfos
and strings. It is designed to be useful for builders,
maximizing the use of strings and nearly opaque tokens. See
ContainerServices for additional functions that will be
needed by more sophisticated containers and for intermixing
different frameworks in the same binary.

This interface is supposed to make simple things easy.
*/
abstract ConnectionService extends Port {

  // makes the connection in the usual cca way.
  // Return:
  // 0 if succeeds, <0 if fails (because connect busy, port not there, etc).
  int connect(ComponentID *using, portname, ComponentID *providing, portname);
  int disconnect(ComponentID *using, portname, ComponentID *providing, portname);

  /** Takes a contained component and one of its provides ports
      and exports it to the "outside" of the container component,
      with the container-appropriate PortInfo (which under
      some rare circumstances might be the same as the original
      portinfo associated with ComponentID *providing).

      This function does not require that a getPort will
      succeed immediately or ahead of time (as provideTo did).
      The idea is to be similar to addProvidesPort, but
      hiding the Port* (since we can't get at it) behind
      the pair ComponentID and port name.

      The opposite of exportProvidesPort is removeProvidesPort.

      @param providing This cannot be the ComponentID of the container
             itself.
      @return 0 if ok, < 0 if arguments invalid or name in pi
              already taken.
   */
  int exportProvidesPort(ComponentID *providing, portname, PortInfo *pi);

  /** Takes a contained component's uses port and
      sets up a proxy for that uses port on the outside of the
      container.

      The idea is to extend the registerUsesPort argument
      list with the component/port pair of the contained component.

      The opposite of exportUsesPort is unregisterUsesPort.

      @param using This cannot be the ComponentID of the container
             itself.
      @return 0 if ok, < 0 if arguments invalid or name in pi
              already taken.
   */
  int exportUsesPort(PortInfo *pi, ComponentID *using, portname);

  /** Take a provides port and decorate the contained component
      with that port, thereby increasing the abilities of the
      decorated component.
      The opposite of this function is deleteProvidesPort.
      @param decorated This cannot be the ComponentID of the container
             itself.
      @return 0 if ok, < 0 if arguments invalid or name in pi
              already taken.
   */
  int insertProvidesPort(Port *p, PortInfo *pi, ComponentID *decorated);

  /** This is the analog for removeProvidesPort for those
      those ports created by decorating a contained
      component with insertProvidesPort.
      @param decorated This cannot be the ComponentID of the container
             itself.
      @return 0 if ok, < 0 if arguments invalid.
   */
  int deleteProvidesPort(const char *name, ComponentID *decorated);

};
--------------------------------------------------------
/** Here's an interface where we almost own up to an object
model. This one is complicated and used so that when/if
frameworks encounter each other they have a shot at
connecting. This interface is to complement the ConnectionService
and make hard things possible for components that want to
be really interesting containers.

Tis and excellent question whether this should be
combined with the ContainerInfoService.
*/
abstract ContainerServices extends Port {

// first some fairly routine functions.

  /** We want some contained things to connect to 
      Ports provided on the "inside" of the container wall.
      Naturally, this means we need to let the container
      add those Ports to its internal wall.
      These ports can only be accessed from components
      inside the container.
      @return 0 if ok, < 0 if arguments invalid.
   */
  int addInternalProvidesPort(Port *p, PortInfo *pi);

  /** opposite of addInternalProvidesPort, analogous to
      removeProvidesPort exactly.
   */
  int removeInternalProvidesPort(const char *name);

  /** We want some contained thing to be the one which
      provides the container with a service. We do
      care that the provider not be a peer or parent frame
      of the container.
   */
  int registerInternalUsesPort(PortInfo *pi);
   
  /** opposite of addInternalProvidesPort, analogous to
      removeProvidesPort exactly.
   */
  int unregisterInternalUsesPort(PortInfo *pi);

};
--------------------------------------------------------
/** This interface refers to a single connection between two
    ports. It 
abstract ConnectionInfo {

  ComponentID *getUsingComponent();

  const char *getUsingPortName();

  ComponentID *getProvidingComponent();

  const char *getProvidingPortName();

  /** returns true if there's a getPort of some sort
      outstanding on the connection.
   */
  bool connectionIsInUse();
};

--------------------------------------------------------
abstract ComponentInfo {
  const char *getClassName();
  Services *getServices();
  PortInfo **getProvidesPorts();
  PortInfo **getUsesPorts();
  Port *getProvidesPort(const char *portname);
};
--------------------------------------------------------

/** Functions we need for introspecting what the user may
 have done in the container manually before calling on the container.
*/
abstract ContainerInfoService extends Port {
  /** Returns an array of connection information for
      all connections in the container, including connections
      to the "inside" of the container. In this array,
      each connection on a multiply connected port (uses or provides)
      shows up individually.
   */
  ConnectionInfo **getConnectionList(int & nConnections);
  ComponentInfo **getChildList(int &nChildren);
};

--------------------------------------------------------
--------------------------------------------------------
/** here's an interface for dealing with the outstanding
      "how does one multiplex a uses port"
    question. It's simply a matter of taste that this
    is not part of the main Services. 
    This interface allows a component to use 0 or more
    provided Ports in an array connected to a single
    uses port slot (name).

    The semantics of "multiplex" are left entirely to the
    using component, as is the iteration ordering,
    the handling of returns from functions contained in
    the provided ports, etc. These are all things CCA
    knows nothing about.

    A framework may choose not to support multiplexing,
    in which case it does not implement this service.
 */
abstract ArrayUsesService extends Port {
  /** defines a uses port that will allow multiple connects.
      The opposite of this call is unregisterUsesPort.
   */
  int registerArrayUsesPort(PortInfo *pi);

  /** Gets the number of connections and the array of providers.
      Since there is no definition in this interface for the "right
      number of connections", this call is non-blocking.
      This cannot be called again (for a given uses port name)
      until the corresponding releaseArrayUsesPort occurs.
   */
  Port ** getArrayUsesPort(const char *name, int & nConnections);

  /** Returns the array of connections when done with it.
      Must be called after getArrayUsesPort is.
   */   
  void releaseArrayUsesPort(Port ** array, char *name);

};
--------------------------------------------------------
