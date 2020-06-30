#ifndef Button_h
#define Button_h
#include <Arduino.h>

class Button
{
  int _buttonPin;
private:
  /* data */
public:
  Button::Button(int buttonPin)
  {
    _buttonPin = buttonPin;
    pinMode(_buttonPin, INPUT_PULLUP);
  }

  Button::~Button()
  {
  }

  bool isPressed()
  {
    return !digitalRead(_buttonPin);
  }
};

#endif