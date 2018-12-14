#include <iostream>
#include <string>
#include "DiffUnit.h"

DiffUnit::DiffUnit(std::string exp) {
  this->unit = exp;
}

std::string DiffUnit::getUnit() {
  return unit;
}