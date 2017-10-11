#pragma once

#include <KeyEvent.hpp>

//using KeyId = unsigned int;

union KeyId
{
  unsigned int code;
  unsigned char bytes[2];
}

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
