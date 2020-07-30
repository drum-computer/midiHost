#ifndef RoutingMatrix_h
#define RoutingMatrix_h
#include "Arduino.h"
#include "Constants.h"

class RoutingMatrix
{
private:
  /* data */
public:
  int matrix[Constants::MATRIX_SIZE];
  RoutingMatrix()
  {
    // init default routing matrix
    for(int i = 0; i < Constants::MATRIX_SIZE; i++)
      matrix[i] = i;
  }

  int getDestination(int address)
  {
    return matrix[address];
  }

  void setDestination(int address, int value)
  {
    matrix[address] = value;
  }

};


#endif