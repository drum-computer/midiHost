#include "Arduino.h"
#include "LiquidCrystal.h"
#include "LCD.h"
#include "Constants.h"

void LCD::start()
{
  // start lcd display 20 chars 4 line mode
  LiquidCrystal::begin(20, 4);
  // print some initial data
  LiquidCrystal::setCursor(0, 0);
  LiquidCrystal::print(F("mode: perform"));
  LiquidCrystal::setCursor(0, 2);
  LiquidCrystal::print(F("-> ch01 cc000 val000"));
  LiquidCrystal::setCursor(0, 3);
  LiquidCrystal::print(F("<- ch01 cc000 val000"));
  
  //enable blinking cursor
  LiquidCrystal::cursor();
  LiquidCrystal::blink();
}

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

void LCD::cycleCursorPosition()
{
  cursor_position = (cursor_position + 1) % Constants::NUM_CURSOR_POS[work_mode];
  byte cursor_x = Constants::CURSOR_POSITIONS[work_mode][cursor_position][0];
  byte cursor_y = Constants::CURSOR_POSITIONS[work_mode][cursor_position][1];
  LiquidCrystal::setCursor(cursor_x, cursor_y);
}

void LCD::updateDisplayValue(byte cursor_position, byte display_val)
{
  // cycleCursorPosition();
  
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
  // return cursor back to origin
  LiquidCrystal::setCursor
                    (Constants::CURSOR_POSITIONS[work_mode][cursor_position][0], 
                    Constants::CURSOR_POSITIONS[work_mode][cursor_position][1]);
}

void LCD::switchMode(byte mode)
{
  // change global mode
  work_mode = mode;
  printModeText(mode);
}

void LCD::printModeText(byte mode)
{
  LiquidCrystal::clear();
  switch (mode)
  {
  case Constants::WORK_MODES::PERFORM:
    LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(F("mode: perform"));
    LiquidCrystal::setCursor(0, 2);
    LiquidCrystal::print(F("-> ch01 cc000 val000"));
    LiquidCrystal::setCursor(0, 3);
    LiquidCrystal::print(F("<- ch01 cc000 val000"));
    break;
  
  case Constants::WORK_MODES::EDIT:
    LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(F("mode: edit"));
    LiquidCrystal::setCursor(0, 2);
    LiquidCrystal::print(F("usb -> ch01 cc000"));
    LiquidCrystal::setCursor(0, 3);
    LiquidCrystal::print(F("midi <- ch01 cc000"));
    break;

  case Constants::WORK_MODES::SAVE:
    LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(F("mode: save"));
    LiquidCrystal::setCursor(0, 2);
    LiquidCrystal::print(F("press UP to save"));
    LiquidCrystal::setCursor(0, 3);
    LiquidCrystal::print(F("current state"));
    break;
  
  case Constants::WORK_MODES::RESET:
    LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(F("mode: reset"));
    LiquidCrystal::setCursor(0, 2);
    LiquidCrystal::print(F("press UP to reset"));
    LiquidCrystal::setCursor(0, 3);
    LiquidCrystal::print(F("to default state"));
    break;
  }
  // init cursor position for selected work mode
  LiquidCrystal::setCursor(Constants::CURSOR_POSITIONS[work_mode][0][0], 
                              Constants::CURSOR_POSITIONS[work_mode][0][1]);
}

byte LCD::getCursorPosition()
{
  return cursor_position;
}