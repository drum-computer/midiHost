#include "Arduino.h"
#include "Constants.h"
#include "RoutingMatrix.h"
#include "Mem.h"

RoutingMatrix::RoutingMatrix() : mem(Constants::MEM_CHIP_ADDR)
{ 
  // init default routing matrix
  clearBuffer();
}

void RoutingMatrix::clearBuffer()
{
  // init buffer with some nonsence value
  for (int i = 0; i < Constants::BUFFER_SIZE; i++)
  {
    buffer[0][i] = 9999;
    buffer[1][i] = 9999;
  }
}

byte RoutingMatrix::increaseChannelEXT(byte *input_midi_channel, byte *input_cc)
{
  int mem_address = 
          (*input_midi_channel * Constants::NUM_CONTROLLERS) + *input_cc;
  int old_value;
  byte buffer_index = 0;
  if(inBuffer(mem_address, &buffer_index))
    old_value = buffer[1][buffer_index];
  else
    old_value = mem.readCell(mem_address);
  int new_value = 
            (old_value + Constants::NUM_CONTROLLERS) >= Constants::MATRIX_SIZE 
                                      ? old_value % Constants::NUM_CONTROLLERS
                                      : old_value + Constants::NUM_CONTROLLERS;

  bufferStore(mem_address, new_value);

  return (new_value / Constants::NUM_CONTROLLERS) + 1;
}

byte RoutingMatrix::decreaseChannelEXT(byte *input_midi_channel, byte *input_cc)
{
  int mem_address = 
          (*input_midi_channel * Constants::NUM_CONTROLLERS) + *input_cc;
  int old_value;
  byte buffer_index = 0;
  if(inBuffer(mem_address, &buffer_index))
    old_value = buffer[1][buffer_index];
  else
    old_value = mem.readCell(mem_address);
  int new_value = (old_value - Constants::NUM_CONTROLLERS) < 0 ? 
              Constants::MATRIX_SIZE - Constants::NUM_CONTROLLERS + old_value: 
                                      old_value - Constants::NUM_CONTROLLERS;
    
  // put it back
  bufferStore(mem_address, new_value);

  // return display value
  return (new_value / Constants::NUM_CONTROLLERS) + 1;
}

byte RoutingMatrix::increaseCCEXT(byte *input_midi_channel, byte *input_cc)
{
  int mem_address = 
          (*input_midi_channel * Constants::NUM_CONTROLLERS) + *input_cc;
  int old_value;
  byte buffer_index = 0;
  if(inBuffer(mem_address, &buffer_index))
    old_value = buffer[1][buffer_index];
  else
    old_value = mem.readCell(mem_address);
  byte channel_offset = old_value / Constants::NUM_CONTROLLERS;
  int new_value = 
        (old_value + 1) >= ((Constants::NUM_CONTROLLERS * channel_offset) 
          + Constants::NUM_CONTROLLERS) ? 
            (Constants::NUM_CONTROLLERS * channel_offset) : (old_value + 1);

  // put it back
  bufferStore(mem_address, new_value);

  // return display value
  return new_value % Constants::NUM_CONTROLLERS;
}


byte RoutingMatrix::decreaseCCEXT(byte *input_midi_channel, byte *input_cc)
{
  int mem_address = 
          (*input_midi_channel * Constants::NUM_CONTROLLERS) + *input_cc;
  int old_value;
  byte buffer_index = 0;
  if(inBuffer(mem_address, &buffer_index))
    old_value = buffer[1][buffer_index];
  else
    old_value = mem.readCell(mem_address);
  byte channel_offset = old_value / Constants::NUM_CONTROLLERS;
  int new_value = 
        (old_value - 1) < (Constants::NUM_CONTROLLERS * channel_offset) ? 
                ((Constants::NUM_CONTROLLERS * (channel_offset + 1)) - 1) : 
                                                            (old_value - 1);

  // put it back
  bufferStore(mem_address, new_value);

  // return display value
  return new_value % Constants::NUM_CONTROLLERS;
}


int RoutingMatrix::getDestinationEXT(int address)
{
  byte buffer_index = 0;
  if(inBuffer(address, &buffer_index))
    return buffer[1][buffer_index];

  return mem.readCell(address);
}

void RoutingMatrix::bufferStore(int mem_address, int new_value)
{
  byte buffer_index = 0;
  if(inBuffer(mem_address, &buffer_index))
    buffer[1][buffer_index] = new_value;
  else
  {
    // check if buffer full, save all, flush buffer, init counter
    if(counter >= Constants::BUFFER_SIZE) // means buffer is full
    {
      saveBuffer();
    }
    
    buffer[0][counter] = mem_address;
    buffer[1][counter] = new_value;
    counter++;
  }
}


bool RoutingMatrix::inBuffer(int mem_address, byte *index)
{
  // bool inBuffer = false;
  for(byte i = 0; i < Constants::BUFFER_SIZE; i++)
  {
    if(buffer[0][i] == mem_address)
      {
        *index = i;
        return true;
      }
  }
  return false;
}

void RoutingMatrix::saveBuffer()
{
  // theoretically can't happen but just in case
  if(counter > Constants::BUFFER_SIZE)
    counter = Constants::BUFFER_SIZE;

  mem.storeBuffer(buffer, counter);
  clearBuffer();
  counter = 0;
}