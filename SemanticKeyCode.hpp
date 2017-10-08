#pragma once

#include <string>

#include <KeyEvent.hpp>

struct
SemanticKeyCode
{
  KeyEvent event_type;
  int code;

  bool
  operator!= (SemanticKeyCode c)
  {
    return (this->code != c.code
            or
            this->event_type != c.event_type);
  }
};
