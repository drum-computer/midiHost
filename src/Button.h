#ifndef Button_h
#define Button_h
#include <Arduino.h>

class Button
{
private:
  byte _buttonPin;
  byte _lastState;

public:
  Button::Button(byte buttonPin);

  Button::~Button();

  bool Button::isPressed();
};

#endif