#ifndef Constants_h
#define Constants_h

namespace Constants
{
  // arduino pins
  const byte POT1_PIN =            A0;
  const byte LEFT_BUTTON_PIN =     10;
  const byte RIGHT_BUTTON_PIN =     9;
  const byte UP_BUTTON_PIN =        8;
  const byte DOWN_BUTTON_PIN =      7;

  // display number of possible positions for the display cursor 
  const byte NUM_CURSOR_POS =       2;

  // midi and matrix settings
  const byte NUM_CHANNELS = 4;
  const byte NUM_CONTROLLERS = 128;
  const int MATRIX_SIZE = NUM_CHANNELS * NUM_CONTROLLERS;
}

#endif