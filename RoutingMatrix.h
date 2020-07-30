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

  void route(byte input_midi_channel, byte input_cc, 
              byte* output_midi_channel, byte* output_cc)
  {
    int index = (input_midi_channel * Constants::NUM_CONTROLLERS) + input_cc;
    *output_midi_channel = matrix[index] / Constants::NUM_CONTROLLERS;
    *output_cc = matrix[index] % Constants::NUM_CONTROLLERS;

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