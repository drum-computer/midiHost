#include "Arduino.h"
#include "Constants.h"
#include "RoutingMatrix.h"

RoutingMatrix::RoutingMatrix()
{ 
  // init default routing matrix
  for(int i = 0; i < Constants::MATRIX_SIZE; i++)
    matrix[i] = i;
}

int RoutingMatrix::getDestination(int address)
{
  return matrix[address];
}

void RoutingMatrix::setDestination(int address, int value)
{
  matrix[address] = value;
}
