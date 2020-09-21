#ifndef Constants_h
#define Constants_h
#include "Arduino.h"

namespace Constants
{
  // arduino pins
  const byte MODE_BUTTON_PIN =     A3;
  const byte SELECT_BUTTON_PIN =   A2;
  const byte UP_BUTTON_PIN =       A0;
  const byte DOWN_BUTTON_PIN =     A1;

  const byte LCD_RS =               7;
  const byte LCD_E =                6;
  const byte LCD_D4 =               5;
  const byte LCD_D5 =               4;
  const byte LCD_D6 =               3;
  const byte LCD_D7 =               2;

  // midi and matrix settings
  const byte NUM_CHANNELS =        2;
  const byte NUM_CONTROLLERS =    128;
  const int MATRIX_SIZE = NUM_CHANNELS * NUM_CONTROLLERS;
  const byte BUFFER_SIZE = 4;

  const byte MEM_CHIP_ADDR = 0x50;
  const byte MEM_PAGE_SIZE = 16;
 
  // display number of possible positions for the display cursor 
  const byte SCREEN_REFRESH_RATE = 100;     
  const byte CURSOR_POSITIONS[5][2][2]{
                                  {{0, 0}, {0, 0}}, 
                                  {{10, 3}, {15, 3}}, 
                                  {{6, 2}, {6, 2}},
                                  {{6, 2}, {6, 2}},
                                  {{5, 2}, {9, 2}}};
  
  // number of available cursor pos for each work mode (basically array lengths)
  const byte NUM_CURSOR_POS[5]{2, 2, 2, 2, 2};
  // working mode
  const byte NUM_WORKING_MODES = 4;

  enum WORK_MODES{PERFORM, EDIT, SAVE, RESET, CONFIRM_RESET};
}

#endif