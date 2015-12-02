#ifndef HashKey_seen
#define HashKey_seen

namespace jcpp {

class HashKey :public virtual Object {
 private:
  static const long magic = 1103515245;
 public:
  virtual ~HashKey() {}
  virtual int hashValue() { return (((long) (this))*magic); };
  virtual boolean equals(Object* obj) {return obj == this; };

};

} ENDSEMI //jcpp

#endif
