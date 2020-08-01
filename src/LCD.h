#ifndef LCD_h
#define LCD_h
#include "Arduino.h"
#include "LiquidCrystal.h"

class LCD : public LiquidCrystal
{
private:

  void LCD::printLeadingZeroes(int val, byte max_digits);

public:
  LCD(byte p1, byte p2, byte p3, byte p4, byte p5, byte p6)
  : LiquidCrystal(p1, p2, p3, p4, p5, p6)
  {}
  
  void LCD::updateCursorPosition(byte cursor_position);

  void LCD::updateDisplayValue(byte cursor_position, byte display_val);
};


#endif