#pragma once

#include <SemanticKeyCode.hpp>

struct
USB_Keyboard
{
  void
  press (KeyId const& k)
  {
    Keyboard.press(k);
  }
  
  void
  release (KeyId const& k)
  {
    Keyboard.release(k);
  }
};
