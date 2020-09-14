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

  void RoutingMatrix::clear();

  int RoutingMatrix::getDestination(int address);

  void RoutingMatrix::setDestination(int address, int value);
  
  byte RoutingMatrix::increaseChannel(byte *input_midi_channel, byte *input_cc);

  byte RoutingMatrix::decreaseChannel(byte *input_midi_channel, byte *input_cc);

  byte RoutingMatrix::increaseCC(byte *input_midi_channel, byte *input_cc);

  byte RoutingMatrix::decreaseCC(byte *input_midi_channel, byte *input_cc);

};


#endif