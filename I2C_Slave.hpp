#pragma once

#include <SemanticKeyCode.hpp>

// horrible.
struct
I2C_Slave
{
  void
  send_key(KeyId id,KeyEvent e)
  {
    if(g_key_buffer.size() < KEY_EVENT_BUFFER_LIMIT)
      g_key_buffer.push_back({e, id});
  }
  
  void
  press (KeyId id)
  {
    send_key(id, KeyEvent::key_pressed);
    if (SERIAL_DEBUG)
      Serial.println("pressed!");
  }
  
  void
  release (KeyId id)
  {
    send_key(id, KeyEvent::key_released);
    if (SERIAL_DEBUG)
      Serial.println("released!");
  }
};
