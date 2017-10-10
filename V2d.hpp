#pragma once

struct V2d
{
  int8_t probe;
  int8_t sensor;

  bool
  operator<(V2d const& o) const
  {
    if(probe == o.probe)
      return (sensor < o.sensor);
    else
      return (probe < o.probe);
  }
  
};
