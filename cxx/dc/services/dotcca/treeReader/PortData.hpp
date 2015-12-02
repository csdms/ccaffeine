#ifndef __portData_hpp
#define __portData_hpp

#include <string>
#include <map>

namespace ccafe {
class PortData {
public:
  PortData() {}
  ~PortData() {}

  std::string summary; 
  std::string description;
  std::map<std::string, std::string> properties;

  int main(char **argv, int argc);

}; // end class portdata

} // end namespace ccafe
#endif
