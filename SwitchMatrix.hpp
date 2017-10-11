#pragma once

// A switch matrix is the association form sample and sensor input
// combinaison and a harware keycode.

#include <V3d.hpp>
#include <KeyLayer.hpp>
#include <HardwareKeyCode.hpp>
#include <HardwareKeyCode.hpp>

#include <array.h>

template <int8_t sensors_num,
          int8_t probes_num>
struct SwitchMatrix
{
  SwitchMatrix (etl::array<int8_t, sensors_num> const& sensors,
                etl::array<int8_t, probes_num> const& probes):
    m_sensors(sensors),
    m_probes(probes)
  {
    for (auto &p:probes) 
      {
        pinMode(p, OUTPUT);
        digitalWrite(p, HIGH);
      }

    for (auto &s:sensors) 
      {
        pinMode(s, INPUT_PULLUP);
      }
    
    for (uint8_t prob_i=0; prob_i < probes.size(); ++prob_i)      
      for (uint8_t sensor_i=0; sensor_i < sensors.size(); ++sensor_i) 
        {
          // Initialising the state matrix with a «key released»
          // state, to avoid massive release on boot.
          m_state[sensor_i][prob_i] = -(DEBOUNCE_AVERAGE*2);
        }
  }

  HW_KeyQueue
  update ()
  {
    return scan_matrix();
  }
  
private:
  etl::array<int8_t, sensors_num> const m_sensors;
  etl::array<int8_t, probes_num> const m_probes;
  etl::array<etl::array<int8_t, probes_num>,
             sensors_num> m_state;
  
  HW_KeyQueue
  scan_matrix ()
  {
    HW_KeyQueue l;
    
    for (uint8_t prob_i=0;
         prob_i < m_probes.size();
         ++ prob_i) 
      {
        digitalWrite(m_probes[prob_i], LOW);
        
        for (uint8_t sensor_i=0;
             sensor_i < m_sensors.size();
             ++ sensor_i) 
          {
            bool key_pressed = (digitalRead(m_sensors[sensor_i]) == LOW);
            
            int8_t &current_state = m_state[sensor_i][prob_i];

            if (SERIAL_DEBUG)
              {
                Serial.print(current_state);
                Serial.print("\t");
              }
            
            if(!key_pressed && current_state == -DEBOUNCE_AVERAGE)
              { 
                if(l.size() < KEY_EVENT_BUFFER_LIMIT)
                  l.push_back(HardwareKeyCode{KeyEvent::key_released,
                                              {sensor_i, prob_i}});
              }
            else if(key_pressed && current_state == DEBOUNCE_AVERAGE)
              {
                if(l.size() < KEY_EVENT_BUFFER_LIMIT)
                  l.push_back(HardwareKeyCode{KeyEvent::key_pressed,
                                              {sensor_i, prob_i}});
              }

            static_assert((DEBOUNCE_AVERAGE <= 60),
                          "Due to the switch matrix debouncer"
                          " representation in memory, the debounce"
                          " average cannot be > 60.");
            
            if(key_pressed && (current_state <= (DEBOUNCE_AVERAGE * 2)) )
              ++ current_state;

            if(!key_pressed && (current_state >= -(DEBOUNCE_AVERAGE * 2)) )
              -- current_state;
          }
        if (SERIAL_DEBUG)
          {
            Serial.println();
          }
        
        digitalWrite(m_probes[prob_i], HIGH);
      }
    if (SERIAL_DEBUG)
      {
        Serial.println("");
        //oodelay(100);
      }
    
    return l;
  }
};
