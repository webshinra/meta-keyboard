#pragma once

struct V2d
{
  int8_t col;
  int8_t row;

  bool
  operator<(V2d const& o) const
  {
    if(col == o.col)
      return (row < o.row);
    else
      return (col < o.col);
  }
  
};
