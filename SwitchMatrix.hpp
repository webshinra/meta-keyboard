#pragma once

// A switch matrix is the association form sample and sensor input
// combinaison and a harware keycode.

#include <V3d.hpp>
#include <KeyLayer.hpp>
#include <HardwareKeyCode.hpp>
#include <HardwareKeyCode.hpp>

constexpr bool ROW_AS_SENSOR = false;
constexpr bool COL_AS_SENSOR = true;

template <int8_t columns_size,
          int8_t rows_size,
          bool rows_write>
struct SwitchMatrix
{
  SwitchMatrix (int8_t const columns[columns_size],
                int8_t const rows[rows_size])
  {
    for (auto i=0; i < rows_size; ++i) 
      {
        pinMode(rows[i],
                (rows_write ? OUTPUT : INPUT_PULLUP));
        digitalWrite(rows[i], LOW);
      }

    for (auto i=0; i < columns_size; ++i) 
      {
        pinMode(columns[i],
                (rows_write ? INPUT_PULLUP : OUTPUT));
      }
    for (auto x=0; x < rows_size; ++x)      
      for (auto y=0; y < columns_size; ++y) 
        {
          m_state[y][x] = 0;
        }

    /// Light on the "on board" diode.
    pinMode(6, OUTPUT);
    digitalWrite(6, 1);
  }

  std::list<HardwareKeyCode>
  update ()
  {
    return scan_matrix();
  }
  
private:
  void
  scan_key (V3d adress)
  {
  }
  
  std::list<HardwareKeyCode>
  scan_matrix ()
  {
    std::list<HardwareKeyCode> l;
    
    for (int8_t x=0; x < rows_size; ++x) 
      {
        digitalWrite(rows[x], LOW);
        
        for (int8_t y=0; y < columns_size; ++y) 
          {
            bool key_pressed = (digitalRead(columns[y]) == LOW);

            int8_t &current_state = m_state[y][x];
            
            if(!key_pressed && current_state == -DEBOUNCE_AVERAGE)
              { 
                l.push_back(HardwareKeyCode{KeyEvent::key_released,
                                            {y, x}});
              }
            else if(key_pressed && current_state == DEBOUNCE_AVERAGE)
              {
                l.push_back(HardwareKeyCode{KeyEvent::key_pressed,
                                            {y,x}});
              }

            static_assert((DEBOUNCE_AVERAGE <= 100),
                          "Due to the switch matrix debouncer"
                          " representation in memory, the debounce"
                          " average cannot be > 100.");
            
            if(key_pressed && (current_state <= 100) )
              ++ current_state;

            if(!key_pressed && (current_state >= -100) )
              -- current_state;
          }

        digitalWrite(rows[x], HIGH);
      }
    return l;
  }

  int8_t m_state[columns_size][rows_size];
};
