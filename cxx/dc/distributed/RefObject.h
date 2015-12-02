#ifndef RefObject_seen
#define RefObject_seen

class SafeRef;

class RefCountedObject : public virtual JCPN(Object) {
 private:
  CCAFEMutex mut; // BUGBUG - how lightweight are mutexes???
  int refCount;
 protected:
  friend SafeRef;
  int addRef() { 
    CCAFEMutexLock lock(&mut);
    return refCount++;
  };
  // BUGBUG - throw when decremented too far?
  int deleteRef() {
    CCAFEMutexLock lock(&mut);
    return refCount--; 
  };
 public:
  RefCountedObject() {
    refCount = 0;
  };
  ~RefCountedObject() {
  };
};

class SafeRef :public virtual JCPN(Object) {
 private:
  RefCountedObject* obj;
 public:
  SafeRef(RefCountedObject* obj) {
    this->obj = obj;
    if (obj)
      obj->addRef();
  };
  ~SafeRef() {
    int count = obj->deleteRef();
    if (count <= 0)
      {
	delete obj;
	obj = null;
      }
  };
  RefCountedObject* getObject() {
    return obj;
  };
};


class ExceptionSafeFileDescriptor {
 private:
  FILE* fileid;
 public:
  ExceptionSafeFileDescriptor() { fileid = NULL; };
  ExceptionSafeFileDescriptor(FILE* fileid)
    {
      this->fileid = fileid;
    };
  FILE* getFileId () { return fileid; };
  void setFileId (FILE* fileid) { this->fileid = fileid; };

  ~ExceptionSafeFileDescriptor() 
    {
      ::fclose(fileid);
    };
};

#endif // RefObject_seen
