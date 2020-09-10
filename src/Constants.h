#ifndef Constants_h
#define Constants_h
#include "Arduino.h"

namespace Constants
{
  // arduino pins
  const byte MODE_BUTTON_PIN =     A5;
  const byte SELECT_BUTTON_PIN =   A4;
  const byte UP_BUTTON_PIN =       A2;
  const byte DOWN_BUTTON_PIN =     A3;

  const byte LCD_RS =               7;
  const byte LCD_E =                6;
  const byte LCD_D4 =               5;
  const byte LCD_D5 =               4;
  const byte LCD_D6 =               3;
  const byte LCD_D7 =               2;

  // midi and matrix settings
  const byte NUM_CHANNELS =         4;
  const byte NUM_CONTROLLERS =    128;
  const int MATRIX_SIZE = NUM_CHANNELS * NUM_CONTROLLERS;
 
  // display number of possible positions for the display cursor 
  const byte SCREEN_REFRESH_RATE = 100;     
  const byte CURSOR_POSITIONS[4][2][2]{
                                  {{0, 0}, {0, 0}}, 
                                  {{11, 3}, {17, 3}}, 
                                  {{6, 2}, {6, 2}},
                                  {{6, 2}, {6, 2}}};
  
  // number of available cursor pos for each work mode (basically array lengths)
  const byte NUM_CURSOR_POS[4]{2, 2, 2, 2};
  // working mode
  const byte NUM_WORKING_MODES = 4;
}

#endif