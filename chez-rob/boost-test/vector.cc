#include <vector>
#include <string>
#include <stdio.h>

int main(int arg, char** argv) {
  std::vector< std::string > v;
  v.push_back("1");
  v.push_back("2");
  v.push_back("3");
  v.push_back("4");
  v.push_back("5");
  v.push_back("6");
  std::vector< std::string > w;
  w.push_back("7");
  w.push_back("8");
  w.push_back("9");
  w.push_back("10");
  v.insert(v.end(), w.begin(), w.end());
  for(int i = 0;i < v.size();i++) {
    printf("%s", v[i].c_str());
  }
  printf("\n");

  exit(0);
}
