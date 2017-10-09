#pragma once

#include <string>
#include <vector>

#include <KeyEvent.hpp>

using KeyId = unsigned int;
using KeyMap =  std::vector<std::vector<KeyId>>;

struct
SemanticKeyCode
{
  KeyEvent event_type;
  KeyId code;

  bool
  operator!= (SemanticKeyCode c)
  {
    return (this->code != c.code
            or
            this->event_type != c.event_type);
  }
};
