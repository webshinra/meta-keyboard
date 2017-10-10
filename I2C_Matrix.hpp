#pragma once

// Class Reading from I2C slaves on t_adress.
#include <Wire.h>

template <int8_t t_slave_adress,
          int8_t t_this_adress>
struct I2C_Matrix:
  public SensorMatrix
{
  I2C_Matrix(bool do_init=true):
    subclock(0)
  {
    if (do_init)
      Wire.begin(t_this_adress);
  }
  
  virtual
  std::list<SemanticKeyCode>
  update () override
  {
    std::list<SemanticKeyCode> l;
    if(!(subclock % DEBOUNCE_AVERAGE))
      {
        Wire.requestFrom(t_slave_adress, 2);
        if(Wire.available() == 2)
          {
            bool key_pressed = Wire.read(); // What kind?
            char keystroke = Wire.read(); // Which key?
    
            l.push_back(SemanticKeyCode{ (key_pressed
                                          ? KeyEvent::key_pressed
                                          : KeyEvent::key_released),
                                         keystroke });
          }
      }
    subclock++;
    return l;
  }

private:
  unsigned subclock;
};
