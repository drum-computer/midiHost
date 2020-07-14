#ifndef LCD_h
#define LCD_h
#include "Arduino.h"
#include "LiquidCrystal.h"
#include "Constants.h"

class LCD : public LiquidCrystal
{
private:

  void printLeadingZeroes(int val, byte max_digits)
  {
    int max_value = 1;
    for(byte i = 0; i < max_digits - 1; i++)
    {
      if (val == 0)
        LiquidCrystal::print("0");
      else
        max_value *= 10; 
    }

    max_value--;
    if (val != 0)
      while (val < max_value)
      {
        LiquidCrystal::print("0");
        val *= 10;
      }
  }

public:
  LCD(byte p1, byte p2, byte p3, byte p4, byte p5, byte p6)
  : LiquidCrystal(p1, p2, p3, p4, p5, p6)
  {
  }
  
  void updateCursorPosition(byte cursor_position)
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

  void updateDisplayValue(byte cursor_position, byte display_val)
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
};


#endif