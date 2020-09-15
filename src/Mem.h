#ifndef Mem_h
#define Mem_h
#include "Arduino.h"
#include "Wire.h"
#include "Constants.h"

class Mem
{
private:
  byte _chip_addr;
public:
  Mem(byte chip_addr);
  void Mem::storeAll(int data[]);
  void Mem::recallAll(int data[]);
  void Mem::cellWrite(unsigned int cell_addr, byte data);
  byte Mem::readCell(unsigned int eeaddress);
};

#endif
