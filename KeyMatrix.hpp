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

  ~KeyMatrix ()
  {
    for(auto &layer:m_layers)
      delete layer;
  }
  
  std::list<SemanticKeyCode>
  update ()
  {
    std::list<HardwareKeyCode> state = m_switchs.update();
    std::list<SemanticKeyCode> l;
    for(auto &event:state)
      {
        // ici j'applique la keymap en 0, on fera mieux plus tard.
        l.push_back(m_layers[0]->map(event));
      }
    return l;
             }

  void
  add_layer (KeyLayer *layer)
  { m_layers.push_back(layer); }
  
private:
  SwitchMatrix<columns_size, rows_size, rows_write> m_switchs;
  std::vector<KeyLayer*> m_layers;
};
