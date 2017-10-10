#pragma once

#include <SemanticKeyCode.hpp>
int8_t key_interaction_buffer = -1;
int8_t key_char_buffer;

// horrible.
struct
I2C_Slave
{
  void
  press (KeyId id)
  {
    key_interaction_buffer = (int8_t)KeyEvent::key_pressed;
    key_char_buffer = 'i';
    Serial.println("pressed!");
  }
  
  void
  release (KeyId id)
  {
    key_interaction_buffer = KeyEvent::key_released;
    key_char_buffer = 'i';
    Serial.println("released!");
  }
};
