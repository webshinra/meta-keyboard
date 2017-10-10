#pragma once

#include <HardwareKeyCode.hpp>

// A key layer is the association between a physical switch
// (hardwarekeycode) and an std keycode (semantickeycode).
struct KeyLayer
{
  KeyLayer(KeyMap const& keymap):
    m_keymap(keymap)
  { }
  
  SemanticKeyCode
  map (HardwareKeyCode const& e) const
  { return {e.event_type, m_keymap[e.code.probe][e.code.sensor]}; }

private:
  KeyMap const& m_keymap;
};
