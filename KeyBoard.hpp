#pragma once

#include <set>
#include <list>
#include <SensorMatrix.hpp>
#include <SemanticKeyCode.hpp>

template <typename KeyboardType>
struct KeyBoard
{
  KeyBoard()
  {
    
    m_exclusion.insert({KEY_MENU});
    m_exclusion.insert({MODIFIERKEY_GUI});
    m_exclusion.insert({KEY_RIGHT_ALT});
    m_exclusion.insert({KEY_LEFT_SHIFT});
    m_exclusion.insert({KEY_RIGHT_ARROW});
    m_exclusion.insert({KEY_LEFT_ARROW});


    
    m_exclusion.insert({KEY_LEFT_ALT});
    m_exclusion.insert({KEY_LEFT_CTRL});
    m_exclusion.insert({KEY_UP_ARROW});
    m_exclusion.insert({KEY_DOWN_ARROW});
    m_exclusion.insert({KEY_ESC});
  }
  
  virtual
  ~KeyBoard ()
  {
    for (auto &matrix:m_matrix)
      delete matrix;
  }
  
  void
  update ()
  {
    for (auto &m:m_matrix)
      for (auto &event:m->update())
        if(m_buffer.size() < KEY_EVENT_BUFFER_LIMIT)
          m_buffer.push_back(event);
  }

  void
  send_changes ()
  {
    for (auto &key:m_buffer)
      switch (key.event_type)
        {
        case KeyEvent::key_pressed:
          m_kb.press(key.code);
          break;
        case KeyEvent::key_released:
          m_kb.release(key.code);
          break;
        case KeyEvent::no_event:
          break;
        };
    
    m_buffer.clear();
  }

  void
  add_matrix (SensorMatrix* sensors)
  { m_matrix.push_back(sensors); }

  uint8_t
  nb_press ()
  {
    uint8_t count = 0;

    for (auto const &buff:m_buffer)
      if ((buff.event_type == KeyEvent::key_pressed)
          and
          (!m_exclusion.count(buff.code)))
        ++ count;
    
    return count;
  }
  
  KeyboardType m_kb;
  
  KeyQueue m_buffer;
  
  std::set<KeyId> m_exclusion;
  etl::deque<SensorMatrix*, SENSOR_MATRIX_LIMIT> m_matrix;
};
