#ifndef Button_h
#define Button_h
#include <Arduino.h>

class Button
{
  int _buttonPin;
  int _lastState = 1;
private:
  /* data */
public:
  Button::Button(int buttonPin)
  {
    _buttonPin = buttonPin;
    pinMode(_buttonPin, INPUT);
  }

  Button::~Button()
  {
  }

  bool isPressed()
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
};

#endif