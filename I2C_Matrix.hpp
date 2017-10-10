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
    //     if(!(subclock % DEBOUNCE_AVERAGE))
    // {
    Wire.requestFrom(t_slave_adress, 2);
    if(Wire.available() == 2)
      {
        uint8_t buffer[2];
        buffer[0] = Wire.read();
        buffer[1] = Wire.read();

        if(buffer[0] != (int)(KeyEvent::no_event))
          {
            l.push_back
              (SemanticKeyCode{static_cast<KeyEvent>(buffer[0]),
                               static_cast<KeyId>(buffer[1])});
          }
      }
    return l;
  }

private:
  unsigned subclock;
};
