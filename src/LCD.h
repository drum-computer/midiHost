#ifndef LCD_h
#define LCD_h
#include "Arduino.h"
#include "LiquidCrystal.h"

class LCD : public LiquidCrystal
{
private:

  void LCD::printLeadingZeroes(int val, byte max_digits);
  void LCD::printModeText(byte mode);

  // maybe should replace it with enum in constants, but don't know how yet
  byte work_mode = 0; // 0 = perform, 1 = edit, 2 = save, 3 = reset
  byte cursor_position = 0;

public:
  LCD(byte p1, byte p2, byte p3, byte p4, byte p5, byte p6)
  : LiquidCrystal(p1, p2, p3, p4, p5, p6)
  {}

  void LCD::start();
  
  void LCD::cycleCursorPosition();

  void LCD::updateDisplayValue(byte cursor_position, byte display_val);

  void LCD::switchMode(byte mode);
};


#endif