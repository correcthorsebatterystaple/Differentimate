#ifndef DIFFUNIT
#define DIFFUNIT

#include <string>
class DiffUnit {
private:
  std::string unit;
public:
  DiffUnit(std::string exp);
  std::string getUnit();
};

#endif