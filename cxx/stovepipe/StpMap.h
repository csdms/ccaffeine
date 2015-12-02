#ifndef __STPMAP_H__
#define __STPMAP_H__


class StpMap {
private:
  StringHash* hash;
public:
  StpMap(){  
    hash = new StringHash();
  }
  virtual ~StpMap(){ 
    delete hash;
  }
  
private:

  /** Check this pointer for NULL-ness, if it is print out the two
      strings catenated. */
  int chkptr(void* ptr, char* prefix0, char* prefix1);

  /** Insert a particular key and value. */
  void insert(const char* key, const char* value);

  /** Remove the entry given by "key" from the Map. */
  void remove(const char *key);

public:

  /** Initialize with C-style command line arguments.*/
  void init(int argc, char** argv);

/** Return the value keyed to the commandline argument name, or return
    NULL if no such argument was given.  Note that if the argument
    name was given without a value an empty string will be
    returned. */
  const char* get(const char* key);

  /** Put a value into stovepipe. */
  void put(const char* key, const char* value);


/** By convention, namespaces for arguments are designated with a
    selected prefix in front of the argument name separated by a dash.
    For example: myprog --myNamespace-myArgName argValue.  stp_getn is
    a convenience function that enforces that convention.  This call
    is equivalent to stp_get(strcat(strcat(namespace, "-"),argName)). */
  const char* getn(const char* namespc, const char* key);
  
  /** Put a value into stovepipe. */
  void putn(const char* namespc, const char* key, const char* value);
};

class AString : public virtual Object {
 public:
  char* str;
  void put(const char* s) {
    str = STRDUP(s);
  }
  AString() {}
  AString(const char* strg) {
    str = STRDUP(strg);
  }
  virtual ~AString() {
    free(str);
    str = 0;
  }
};
#endif // __STPMAP_H__
