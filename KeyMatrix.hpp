#pragma once

#include <SwitchMatrix.hpp>

// A key matrix is the association between an active Layer and an
// HardwareKeycode.
template <int8_t columns_size,
          int8_t rows_size,
          bool rows_write>
struct KeyMatrix:
  public SensorMatrix
{
  KeyMatrix (int8_t const columns[columns_size],
             int8_t const rows[rows_size]):
    m_switchs (columns, rows)
  { }
  
  std::list<SemanticKeyCode>
  update ()
  {
    std::list<HardwareKeyCode> state = m_switchs.update();
    std::list<SemanticKeyCode> l;
    for(auto &event:state)
      {
        // ici j'applique la keymap
        l.push_back({event.event_type,
                     keymap_bepo_l[event.code.col][event.code.row]});
      }
    return l;
  }

private:
  SwitchMatrix<columns_size, rows_size, rows_write> m_switchs;
  };
