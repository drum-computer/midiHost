#include "Arduino.h"
#include "LiquidCrystal.h"
#include "LCD.h"


void LCD::printLeadingZeroes(int val, byte max_digits)
{
  int max_value = 1;
  for(byte i = 0; i < max_digits - 1; i++)
  {
    if (val == 0)
      LiquidCrystal::print(F("0"));
    else
      max_value *= 10; 
  }

  max_value--;
  if (val != 0)
    while (val < max_value)
    {
      LiquidCrystal::print(F("0"));
      val *= 10;
    }
}

void LCD::updateCursorPosition(byte cursor_position)
{
  switch (cursor_position)
  {
  case 0:
    LiquidCrystal::setCursor(4, 1);
    break;
  case 1:
    LiquidCrystal::setCursor(8, 1);
    break;
  case 2: 
    LiquidCrystal::setCursor(12, 1);
    break;
  case 3: 
    LiquidCrystal::setCursor(4, 0);
    break;
  case 4: 
    LiquidCrystal::setCursor(8, 0);
    break;
  case 5: 
    LiquidCrystal::setCursor(12, 0);
    break;
  }
}

void LCD::updateDisplayValue(byte cursor_position, byte display_val)
{
  updateCursorPosition(cursor_position);
  
  switch (cursor_position)
  {
  case 0: case 3: // means we are changing channel number
    printLeadingZeroes(display_val, 2);
    LiquidCrystal::print(display_val);
    break;
  case 1: case 4: // means we are changing cc number
    printLeadingZeroes(display_val, 3);
    LiquidCrystal::print(display_val);
    break;
  case 2: case 5: // means we are changing test pot val
    printLeadingZeroes(display_val, 3);
    LiquidCrystal::print(display_val);
    break;
  }
}
