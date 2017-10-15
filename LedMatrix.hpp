#pragma once

#include <array.h>
#include <SemanticKeyCode.hpp>
#include <HardwareKeyCode.hpp>

template <int8_t pos_num,
          int8_t neg_num>
struct LedMatrix:
  SensorMatrix
{
  LedMatrix (etl::array<int8_t, pos_num> const& positives,
             etl::array<int8_t, neg_num> const& negatives):
    m_positives(positives),
    m_negatives(negatives)
  { }

  virtual
  KeyQueue
  update () override
  {
    for (uint8_t neg_i=0;
         neg_i < m_negatives.size();
         ++ neg_i) 
        {
          digitalWrite(m_negatives[neg_i], LOW);
          for (uint8_t pos_i=0;
               pos_i < m_positives.size();
               ++ pos_i) 
            {
              pinMode(m_positives[pos_i], OUTPUT);
              digitalWrite(m_positives[pos_i], HIGH);
              pinMode(m_positives[pos_i], INPUT);
            }

          digitalWrite(m_negatives[neg_i], HIGH);
        }
    
    //delay(10);
    //digitalWrite(13, 1);
    //  digitalWrite(23, 0);
    /*    pinMode(13, OUTPUT);
          digitalWrite(13, 0);

    
          delay(1);

          digitalWrite(23, 0);
          pinMode(23, INPUT);
    
          digitalWrite(13, 1);
    */
    return  KeyQueue();
  }

private:
  etl::array<int8_t, pos_num> m_positives;
  etl::array<int8_t, neg_num> m_negatives;
};
