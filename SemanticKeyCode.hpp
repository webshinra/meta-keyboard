#pragma once

#include <string>

#include <KeyEvent.hpp>

using KeyId = unsigned int;

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
