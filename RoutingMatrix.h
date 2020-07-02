#ifndef RoutingMatrix_h
#define RoutingMatrix_h
#define NUM_CHANNELS 8
#define NUM_CONTROLLERS 128
#include "Arduino.h"


class RoutingMatrix
{
private:
  /* data */
public:
  byte matrix[NUM_CHANNELS][NUM_CONTROLLERS];
  RoutingMatrix()
  {
    // init default routing matrix
    for(int i = 0; i < NUM_CHANNELS; i++)
      for(int j = 0; j < NUM_CONTROLLERS; j++)
        matrix[i][j] = j;
  }
};


#endif