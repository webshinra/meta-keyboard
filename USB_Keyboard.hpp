#pragma once

#include <SemanticKeyCode.hpp>

struct
USB_Keyboard
{
  void
  press (KeyId)
  {
    Keboard.press(KeyId);
  }
  
  void
  release (KeyId)
  {
    Keboard.release(KeyId);
  }
};
