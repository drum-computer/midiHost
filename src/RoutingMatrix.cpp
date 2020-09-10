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


byte RoutingMatrix::increaseChannel(byte *input_midi_channel, byte *input_cc)
{
  int lookup_address = (*input_midi_channel * Constants::NUM_CONTROLLERS) 
                                                                    + *input_cc;
  int old_value = getDestination(lookup_address);
  int new_value;
  new_value = 
        (old_value + Constants::NUM_CONTROLLERS) >= Constants::MATRIX_SIZE 
                                  ? old_value % Constants::NUM_CONTROLLERS
                                  : old_value + Constants::NUM_CONTROLLERS;
  
  // put it back
  setDestination(lookup_address, new_value);

  // return display value
  return (new_value / Constants::NUM_CONTROLLERS) + 1;
}


byte RoutingMatrix::decreaseChannel(byte *input_midi_channel, byte *input_cc)
{
  int lookup_address = (*input_midi_channel * Constants::NUM_CONTROLLERS) 
                                                                    + *input_cc;
  int old_value = getDestination(lookup_address);
  int new_value;
  new_value = (old_value - Constants::NUM_CONTROLLERS) < 0 ? 
              Constants::MATRIX_SIZE - Constants::NUM_CONTROLLERS + old_value: 
                                      old_value - Constants::NUM_CONTROLLERS;
    
  // put it back
  setDestination(lookup_address, new_value);

  // update screen
  return (new_value / Constants::NUM_CONTROLLERS) + 1;
}