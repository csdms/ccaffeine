#ifndef JavaWriter_seen
#define JavaWriter_seen

namespace jcpp {
class Writer {
 public:
  virtual void close() = 0;
  virtual void flush() = 0;
  virtual void write(char* string)=0;
};

} ENDSEMI //jcpp

#endif
