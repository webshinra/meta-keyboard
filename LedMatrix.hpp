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
  {
    int i=0;
    randomSeed(42);
    for (auto& negs:m_state)
                 for (auto& pos:negs)
        pos = random(0,2);
  }

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
            if (m_state[neg_i][pos_i])
              {
                  
                pinMode(m_positives[pos_i], OUTPUT);
                digitalWrite(m_positives[pos_i], HIGH);
                pinMode(m_positives[pos_i], INPUT);
              }   
          }

        digitalWrite(m_negatives[neg_i], HIGH);
      }
    return  KeyQueue();
  }

  void
  step ()
  {
    
    etl::array<etl::array<bool, neg_num>, pos_num> new_state;
    
    for (uint8_t j=0; j < m_state.front().size(); ++j)
      for (uint8_t i=0; i < m_state.size(); ++i)
        {
          bool state[3];
          state[0] = m_state[(i > 0
                              ? i - 1
                              : m_state.size()-1)][j];
          state[1] = m_state[i][j];
          state[2] = m_state[(i < m_state.size()-2
                              ? i + 1
                              : 0)][j];

          if(
             (state[1] ^ state[2]))
            new_state[i][j] = false;
          else
            new_state[i][j] = true;
        }
    m_state = new_state;
  }
  
private:
  etl::array<int8_t, pos_num> m_positives;
  etl::array<int8_t, neg_num> m_negatives;
  etl::array<etl::array<bool, neg_num>, pos_num> m_state;
};
