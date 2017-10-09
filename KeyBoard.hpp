#pragma once

#include <list>
#include <SensorMatrix.hpp>
#include <SemanticKeyCode.hpp>

struct KeyBoard:
  SemanticKeyCode
{
  void
  update ()
  {
    for (auto &m:m_matrix)
      for (auto &event:m->update())
        m_buffer.push_back(event);
  }

  void
  send_changes ()
  {
    for (auto &key:m_buffer)
      switch (key.event_type)
        {
        case KeyEvent::key_pressed:
          //Keyboard.press(key.code);
          break;
        case KeyEvent::key_released:
          //Keyboard.release(key.code);
          break;
        };
    
    m_buffer.clear();
  }

  void
  add_matrix (SensorMatrix* sensors)
  {
    m_matrix.push_back(sensors);
  }
  
  std::list<SemanticKeyCode> m_buffer;
  std::list<SensorMatrix*> m_matrix;
};
