#ifndef Constants_h
#define Constants_h
#include "Arduino.h"

namespace Constants
{
  // arduino pins
  const byte POT1_PIN =            A1;
  
  const byte MODE_BUTTON_PIN =     A5;
  const byte SELECT_BUTTON_PIN =     A4;
  const byte UP_BUTTON_PIN =       A3;
  const byte DOWN_BUTTON_PIN =     A2;

  const byte LCD_RS =              A0;
  const byte LCD_E =                6;
  const byte LCD_D4 =               5;
  const byte LCD_D5 =               4;
  const byte LCD_D6 =               3;
  const byte LCD_D7 =               2;

  // display number of possible positions for the display cursor 
  const byte NUM_CURSOR_POS =       2;
  const byte SCREEN_REFRESH_RATE = 100;
  
  enum menu_entries { Output_channel,
                      Output_cc,
                      Init,
                      Input_channel,
                      Input_cc,
                      Input_value,
                      Output_value};        

  // midi and matrix settings
  const byte NUM_CHANNELS =         4;
  const byte NUM_CONTROLLERS =    128;
  const int MATRIX_SIZE = NUM_CHANNELS * NUM_CONTROLLERS;

  // working mode
  const byte NUM_MODES;
  enum working_mode {monitor, edit, save, reset};
}

#endif