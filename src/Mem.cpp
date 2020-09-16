#include "Arduino.h"
#include "Wire.h"
#include "Mem.h"
#include "Constants.h"

Mem::Mem(byte chip_addr)
{
  Wire.begin();
  _chip_addr = chip_addr;
}

void Mem::storeAll(int data[])
{
  // multiply matrix size by 2 since each int in it is 2 bytes long
  byte num_pages = (Constants::MATRIX_SIZE * 2) / Constants::MEM_PAGE_SIZE;
  for(int page = 0; page < num_pages; page++)
  {
    Wire.beginTransmission(_chip_addr);
    Wire.write((int)(page * Constants::MEM_PAGE_SIZE) >> 8); // mem address MSB
    Wire.write((int)(page * Constants::MEM_PAGE_SIZE) & 0xFF); // mem address LSB
    
    for(int index = 0; index < Constants::MEM_PAGE_SIZE; index++)
    {  
      if((index % 2) == 0)  // on even cycle write data MSB
        Wire.write(data[(((page * Constants::MEM_PAGE_SIZE) + index) / 2)] >> 8);
      else                 //  on odd cycle write data LSB
        Wire.write(data[(((page * Constants::MEM_PAGE_SIZE) + index) / 2)] & 0xFF);
    }
      
    Wire.endTransmission();
    delay(5);
  }
}

void Mem::recallAll(int matrix[])
{
  byte rdata[2]{0x0, 0x0};

  // multiply matrix size by two since data is stored in MSB/LSB fashion
  for(int i = 0; i < Constants::MATRIX_SIZE; i++)
  {
    byte mem_addr = i * 2;
    Wire.beginTransmission(_chip_addr);
    Wire.write((int)(mem_addr >> 8));   // MSB
    Wire.write((int)(mem_addr & 0xFF)); // LSB
    Wire.endTransmission();
  
    Wire.requestFrom(_chip_addr, 2);
    while(Wire.available())
    {
      rdata[0] = Wire.read();
      rdata[1] = Wire.read();
      unsigned int data = ((rdata[0] & 0xff) << 8) | (rdata[1] & 0xff);
      matrix[i] = data;
    }
  }
}

void Mem::cellWrite(unsigned int cell_addr, byte data)
{
  Wire.beginTransmission(_chip_addr);
  Wire.write((int)(cell_addr >> 8));   // MSB
  Wire.write((int)(cell_addr & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();
 
  delay(5);
}

byte Mem::readCell(unsigned int eeaddress) 
{
  byte rdata = 0xFF;
 
  Wire.beginTransmission(_chip_addr);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
 
  Wire.requestFrom(_chip_addr, 1);
 
  rdata = Wire.read();
 
  return rdata;
}