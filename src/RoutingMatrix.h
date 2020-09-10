#ifndef RoutingMatrix_h
#define RoutingMatrix_h
#include "Arduino.h"
#include "Constants.h"

class RoutingMatrix
{
private:
  int matrix[Constants::MATRIX_SIZE];  
public:
  RoutingMatrix();

  int RoutingMatrix::getDestination(int address);

  void RoutingMatrix::setDestination(int address, int value);
  
  void RoutingMatrix::increaseChannel(byte *input_midi_channel, byte *input_cc);
};


#endif