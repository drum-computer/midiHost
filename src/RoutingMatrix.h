#ifndef RoutingMatrix_h
#define RoutingMatrix_h
#include "Arduino.h"
#include "Constants.h"
#include "Mem.h"

class RoutingMatrix
{
private:
  byte counter = 0;
  Mem mem;
  void RoutingMatrix::bufferStore(int mem_address, int new_value);
  void RoutingMatrix::clearBuffer();

public:
  int matrix[2];  
  int buffer[2][Constants::BUFFER_SIZE]{0};
  RoutingMatrix();// : mem(Constants::MEM_CHIP_ADDR){};
  
  byte RoutingMatrix::increaseChannelEXT(byte *input_midi_channel, byte *input_cc);

  // void RoutingMatrix::bufferStore(int mem_address, int new_value);
  bool RoutingMatrix::inBuffer(int mem_address, byte *index);
  int RoutingMatrix::getDestinationEXT(int address);
  byte RoutingMatrix::decreaseChannelEXT(byte *input_midi_channel, byte *input_cc);
  byte RoutingMatrix::increaseCCEXT(byte *input_midi_channel, byte *input_cc);
  byte RoutingMatrix::decreaseCCEXT(byte *input_midi_channel, byte *input_cc);
  void RoutingMatrix::saveBuffer();
};


#endif