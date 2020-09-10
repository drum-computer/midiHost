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


  byte edit_mode_cursor_positions[2][2]{{0, 0}, {1, 0}};
  byte perform_mode_cursor_positions[2][2]{{0, 1}, {1, 1}};
  byte save_mode_cursor_positions[2][2]{{0, 2}, {1, 2}};
  byte reset_mode_cursor_positions[2][2]{{0, 3}, {1, 3}};
  byte test[1]{0};
  byte *current_mode_cursor_positions_ptr[1];

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