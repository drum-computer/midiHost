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

  byte changeRouting(byte cursor_pos, byte midiChannel, byte cc)
  {
    int index = (midiChannel * Constants::NUM_CONTROLLERS) + cc;
    // read old value
    int value = matrix[index];
    byte display_val;
    switch (cursor_pos)
    {
    case 0: // means we are editing output channel
      value = (value + Constants::NUM_CONTROLLERS) >= Constants::MATRIX_SIZE 
                    ? value % Constants::NUM_CONTROLLERS
                    : value + Constants::NUM_CONTROLLERS;

      // add 1 for readability remap display value of channels from 0->15 to 1->16
      display_val = value / Constants::NUM_CONTROLLERS + 1;
      break;

    case 1: // means we are editing cc number
      // get channel number to which controller belongs
      byte channel_offset = value / Constants::NUM_CONTROLLERS;
      value = (value + 1) >= ((Constants::NUM_CONTROLLERS * channel_offset) 
                    + Constants::NUM_CONTROLLERS)
                      ? (Constants::NUM_CONTROLLERS * channel_offset)
                      : (value + 1);

      display_val = value % Constants::NUM_CONTROLLERS;
      break;
    }

    // write new value
    matrix[index] = value;
    return display_val;
  }

  void lookup(byte input_midi_channel, byte input_cc, 
              byte* output_midi_channel, byte* output_cc)
  {
    int index = (input_midi_channel * Constants::NUM_CONTROLLERS) + input_cc;
    *output_midi_channel = matrix[index] / Constants::NUM_CONTROLLERS;
    *output_cc = matrix[index] % Constants::NUM_CONTROLLERS;

  }
};


#endif