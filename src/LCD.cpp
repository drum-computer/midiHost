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
  LiquidCrystal::print(F("-> ch01 cc___ val___"));
  LiquidCrystal::setCursor(0, 3);
  LiquidCrystal::print(F("<- ch01 cc___ val___"));
  
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
    LiquidCrystal::print(F("-> ch01 cc___ val___"));
    LiquidCrystal::setCursor(0, 3);
    LiquidCrystal::print(F("<- ch01 cc___ val___"));
    break;
  
  case Constants::WORK_MODES::EDIT:
    LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(F("mode: edit"));
    LiquidCrystal::setCursor(0, 2);
    LiquidCrystal::print(F("usb  -> ch__ cc___"));
    LiquidCrystal::setCursor(0, 3);
    LiquidCrystal::print(F("midi <- ch__ cc___"));
    break;

  case Constants::WORK_MODES::SAVE:
    LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(F("mode: save"));
    LiquidCrystal::setCursor(0, 2);
    LiquidCrystal::print(F("press UP to save"));
    LiquidCrystal::setCursor(0, 3);
    LiquidCrystal::print(F("current state"));
    break;
  
  case Constants::WORK_MODES::RESET :
    LiquidCrystal::setCursor(0, 0);
    LiquidCrystal::print(F("mode: reset"));
    LiquidCrystal::setCursor(0, 2);
    LiquidCrystal::print(F("press UP to reset"));
    LiquidCrystal::setCursor(0, 3);
    LiquidCrystal::print(F("to default state"));
    break;

  case Constants::WORK_MODES::CONFIRM_RESET :
  LiquidCrystal::clear();
  LiquidCrystal::setCursor(2, 0);
  LiquidCrystal::print(F("Reset: Confirm?"));
  LiquidCrystal::setCursor(5, 2);
  LiquidCrystal::print(F("Yes No"));
  LiquidCrystal::setCursor(9, 2);
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

void LCD::refresh(byte mode, byte input_midi_channel, byte input_cc, 
                  byte input_value, byte output_midi_channel, byte output_cc)
{
  byte cursor_x = Constants::CURSOR_POSITIONS[work_mode][cursor_position][0];
  byte cursor_y = Constants::CURSOR_POSITIONS[work_mode][cursor_position][1];
  
  switch (mode)
  {
  case Constants::WORK_MODES::PERFORM:
    LiquidCrystal::setCursor(5, 2);
    printLeadingZeroes(input_midi_channel, 2);
    LiquidCrystal::print(input_midi_channel + 1);
    LiquidCrystal::setCursor(10, 2);
    printLeadingZeroes(input_cc, 3);
    LiquidCrystal::print(input_cc);
    LiquidCrystal::setCursor(17, 2);
    printLeadingZeroes(input_value, 3);
    LiquidCrystal::print(input_value);

    LiquidCrystal::setCursor(5, 3);
    printLeadingZeroes(output_midi_channel, 2);
    LiquidCrystal::print(output_midi_channel + 1);
    LiquidCrystal::setCursor(10, 3);
    printLeadingZeroes(output_cc, 3);
    LiquidCrystal::print(output_cc);
    LiquidCrystal::setCursor(17, 3);
    printLeadingZeroes(input_value, 3);
    LiquidCrystal::print(input_value);
    break;
  
  case Constants::WORK_MODES::EDIT:
    LiquidCrystal::setCursor(10, 2);
    printLeadingZeroes(input_midi_channel, 2);
    LiquidCrystal::print(input_midi_channel + 1);
    LiquidCrystal::setCursor(15, 2);
    printLeadingZeroes(input_cc, 3);
    LiquidCrystal::print(input_cc);

    LiquidCrystal::setCursor(10, 3);
    printLeadingZeroes(output_midi_channel, 2);
    LiquidCrystal::print(output_midi_channel + 1);
    LiquidCrystal::setCursor(15, 3);
    printLeadingZeroes(output_cc, 3);
    LiquidCrystal::print(output_cc);
    break;
  }
  LiquidCrystal::setCursor(cursor_x, cursor_y);
}

void LCD::showSuccess()
{
  LiquidCrystal::clear();
  LiquidCrystal::setCursor(5, 2);
  LiquidCrystal::print(F("Saved!"));
  delay(1000);
  switchMode(Constants::WORK_MODES::SAVE);
}


void LCD::showResetSuccess()
{
  LiquidCrystal::clear();
  LiquidCrystal::setCursor(2, 2);
  LiquidCrystal::print(F("Reset Complete!"));
  delay(1000);
  switchMode(Constants::WORK_MODES::RESET);
}