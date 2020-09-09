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

void LCD::switchMode(byte mode)
{
  printModeText(mode);
}

void LCD::printModeText(byte mode)
{
  LiquidCrystal::clear();
  switch (mode)
  {
  case 0:
    LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(F("mode: perform"));
    LiquidCrystal::setCursor(0, 2);
    LiquidCrystal::print(F("-> ch01 cc000 val000"));
    LiquidCrystal::setCursor(0, 3);
    LiquidCrystal::print(F("<- ch01 cc000 val000"));
    break;
  
  case 1:
    LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(F("mode: edit"));
    LiquidCrystal::setCursor(0, 2);
    LiquidCrystal::print(F("usb -> ch01 cc000"));
    LiquidCrystal::setCursor(0, 3);
    LiquidCrystal::print(F("midi <- ch01 cc000"));
    break;

  case 2:
    LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(F("mode: save"));
    LiquidCrystal::setCursor(0, 2);
    LiquidCrystal::print(F("press UP to save"));
    LiquidCrystal::setCursor(0, 3);
    LiquidCrystal::print(F("current state"));
    break;
  
  case 3:
    LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(F("mode: reset"));
    LiquidCrystal::setCursor(0, 2);
    LiquidCrystal::print(F("press UP to reset"));
    LiquidCrystal::setCursor(0, 3);
    LiquidCrystal::print(F("to default state"));
    break;

  default:
    break;
  }
}