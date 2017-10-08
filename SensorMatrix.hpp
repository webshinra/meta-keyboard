#pragma once
#include <SemanticKeyCode.hpp>

struct SensorMatrix
{
  virtual
  std::list<SemanticKeyCode>
  update () = 0;
};
