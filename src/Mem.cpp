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
    int start_address = page * Constants::MEM_PAGE_SIZE;
    Wire.write((int)(start_address >> 8));   // MSB
    Wire.write((int)(start_address & 0xFF)); // LSB
    
    for(int index = 0; index < Constants::MEM_PAGE_SIZE; index++)
    {
      int mem_address = (page * Constants::MEM_PAGE_SIZE) + index;
      
      if((index % 2) == 0)  // on even cycle write data MSB
        Wire.write((int)(data[mem_address] >> 8));
      else                 //  on odd cycle write data LSB
        Wire.write((int)(data[mem_address] & 0xFF));
    }
      
    Wire.endTransmission();
    delay(5);
  }
}

void Mem::recallAll(int matrix[])
{
  byte rdata[2]{0x0, 0x0};

  // multiply matrix size by two since data is stored in MSB/LSB fashion
  for(int i = 0; i < (Constants::MATRIX_SIZE); i++)
  {
    for(int z = 0; z < 2; z++)
    {
      Wire.beginTransmission(_chip_addr);
      Wire.write((int)(i >> 8));   // MSB
      Wire.write((int)(i & 0xFF)); // LSB
      Wire.endTransmission();
    
      Wire.requestFrom(_chip_addr, 1);
      if((z % 2) == 0) // means we are reading MSB data byte
        rdata[0] = Wire.read();
      else             // means we are reading LSB data byte
        rdata[1] = Wire.read();
    }
    int data = ((rdata[0] & 0xff) << 8) | (rdata[1] & 0xff);
    matrix[i] = data;
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