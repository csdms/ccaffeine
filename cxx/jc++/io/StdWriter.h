#ifndef JavaStdWriter_seen
#define JavaStdWriter_seen

namespace jcpp {

class StdWriter : public Writer {
private:
  FILE* fd;
public:
  StdWriter(int fd_) { fd = ::fdopen(fd_, "w"); };
  virtual void close() { ::close(fileno(fd)); };
  virtual void flush() { ::fflush(fd);};
  virtual void write(char* string) { ::fprintf(fd, string); };
};

} ENDSEMI //jcpp

#endif
