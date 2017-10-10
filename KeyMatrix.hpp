#pragma once

#include <SwitchMatrix.hpp>

// A key matrix is the association between an active Layer and an
// HardwareKeycode.
template <int8_t sensors_num,
          int8_t probes_num>
struct KeyMatrix:
  public SensorMatrix
{
  KeyMatrix (etl::array<int8_t, sensors_num> const& sensors,
             etl::array<int8_t, probes_num> const& probes):
    m_switchs (sensors, probes)
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
  SwitchMatrix<sensors_num, probes_num> m_switchs;
  std::vector<KeyLayer*> m_layers;
};
