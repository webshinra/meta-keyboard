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
    
    for (auto prob_i=0; prob_i < probes.size(); ++prob_i)      
      for (auto sensor_i=0; sensor_i < probes.size(); ++sensor_i) 
        {
          m_state[sensor_i][prob_i] = 0;
        }

    /// Light on the "on board" diode.
    /*    pinMode(6, OUTPUT);
          digitalWrite(6, 1);*/
  }

  std::list<HardwareKeyCode>
  update ()
  {
    return scan_matrix();
  }
  
private:
  etl::array<int8_t, sensors_num> const m_sensors;
  etl::array<int8_t, probes_num> const m_probes;
  etl::array<etl::array<int8_t, probes_num>,
             sensors_num> m_state;

  void
  scan_key (V3d adress)
  {
  }
  
  std::list<HardwareKeyCode>
  scan_matrix ()
  {
    std::list<HardwareKeyCode> l;
    
    for (int8_t prob_i=0; prob_i < m_probes.size(); ++prob_i) 
      {
        digitalWrite(m_probes[prob_i], LOW);
        
        for (int8_t sensor_i=0; sensor_i < m_sensors.size(); ++sensor_i) 
          {
            bool key_pressed = (digitalRead(m_sensors[sensor_i]) == LOW);

            Serial.print(digitalRead(m_sensors[sensor_i]));
            Serial.print(" ");
            delay(100);
            
            int8_t &current_state = m_state[sensor_i][prob_i];
            
            if(!key_pressed && current_state == -DEBOUNCE_AVERAGE)
                    { 
                
                      l.push_back(HardwareKeyCode{KeyEvent::key_released,
                                                  {sensor_i, prob_i}});
                    }
            else if(key_pressed && current_state == DEBOUNCE_AVERAGE)
              {
                l.push_back(HardwareKeyCode{KeyEvent::key_pressed,
                                            {sensor_i, prob_i}});
              }

            static_assert((DEBOUNCE_AVERAGE <= 100),
                          "Due to the switch matriprob_i debouncer"
                          " representation in memory, the debounce"
                          " average cannot be > 100.");
            
            if(key_pressed && (current_state <= 100) )
              ++ current_state;

            if(!key_pressed && (current_state >= -100) )
              -- current_state;
          }
        //Serial.println();
        digitalWrite(m_probes[prob_i], HIGH);
      }
    //Serial.println("");
    return l;
  }
};
