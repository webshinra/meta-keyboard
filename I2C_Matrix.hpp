#pragma once

// Class Reading from I2C slaves on t_adress.
#include <Wire.h>

template <int8_t t_slave_adress,
          int8_t t_this_adress>
struct I2C_Matrix:
  public SensorMatrix
{
  I2C_Matrix(bool do_init=true)
  {
    if (do_init)
      {
        Serial.begin(9600);
      }
    
  }
  
  virtual
  KeyQueue
  update () override
  {
    KeyQueue l;
    if(Serial1.available() == 3)
      {
        digitalWrite(6, 1);
        uint8_t buffer[3];
        buffer[0] = Serial1.read();
        buffer[1] = Serial1.read();
        buffer[2] = Serial1.read();
        
        if(buffer[0] != (int)(KeyEvent::no_event))
          {
            l.push_back
              (SemanticKeyCode
                  {static_cast<KeyEvent>(buffer[0]),
                   static_cast<KeyId>(((KeyId)buffer[2] << 8))});
          }
      }
         
    return l;
  }
};
