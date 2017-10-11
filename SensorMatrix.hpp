#pragma once
#include <deque.h>
#include <SemanticKeyCode.hpp>
#include <HardwareKeyCode.hpp>

using KeyQueue = etl::deque<SemanticKeyCode, KEY_EVENT_BUFFER_LIMIT>;
using HW_KeyQueue = etl::deque<HardwareKeyCode, KEY_EVENT_BUFFER_LIMIT>;

struct SensorMatrix
{
  virtual
  ~SensorMatrix ()
  { }

  virtual
  KeyQueue
  update () = 0;
};
