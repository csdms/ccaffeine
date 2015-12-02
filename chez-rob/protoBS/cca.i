
class Port {
};

class ComponentID {
  char* toString();
};

class PortInfo  {
public:
  virtual ~PortInfo();

  virtual char* getType();

  virtual char* getName();

  virtual char* getProperty(char* name);
};

class Services  {
public:
  virtual ~Services();

  virtual PortInfo *  createPortInfo( char *name,  
				      char *type,  
				      char** properties);

  virtual Port *getPort( char *name);

  virtual Port *getPortNonblocking(char* name);

  virtual void releasePort( char *name);

  virtual int registerUsesPort(PortInfo *name_and_type);

  virtual int unregisterUsesPort( char *name);

  virtual int addProvidesPort(Port *inPort, PortInfo *name);

  virtual void removeProvidesPort( char *name);

  virtual ComponentID* getComponentID();
};

class Component {
public:
  virtual ~Component();

  virtual void setServices(Services *cc);
};

