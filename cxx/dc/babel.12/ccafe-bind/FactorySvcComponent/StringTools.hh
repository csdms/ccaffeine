#ifndef __STRINGTOOLS_HH__
#define __STRINGTOOLS_HH__

class StringTools {
public:
  virtual ~StringTools(){}
  static std::string chomp(const std::string& toChomp);
  static std::vector<std::string> split(const std::string& s, const char c = ' ');
};


#endif // __STRINGTOOLS_HH__
