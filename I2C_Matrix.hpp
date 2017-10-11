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
        uint8_t event = Serial1.read();

        KeyId k;
        k.bytes[0] = Serial1.read();
        k.bytes[1] = Serial1.read();
        
        if(event != (int)(KeyEvent::no_event))
          {
            l.push_back
              (SemanticKeyCode
                  {static_cast<KeyEvent>(event),
                   k.code});
          }
          }
         
    return l;
  }
};
