#include <Arduino.h>
#include "Button.h"

Button::Button(byte buttonPin)
{
  _buttonPin = buttonPin;
  pinMode(_buttonPin, INPUT);
  _lastState = 1;
}

Button::~Button()
{
}

bool Button::isPressed()
{
  if (digitalRead(_buttonPin) == 0 && _lastState == 1)
  {
    _lastState = 0;
    return true;
  } else if (digitalRead(_buttonPin) == 1 && _lastState == 0)
  {
    _lastState = 1;
  }
  return false;
}
