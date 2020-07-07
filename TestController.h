#ifndef TestController_h
#define TestController_h
#include <Arduino.h>

class TestController
{
  int _controllerPin;
  byte _prevVal = 0;
  byte val = 0;
private:
  /* data */
public:

  TestController::TestController(int contollerPin)
  {
    _controllerPin = contollerPin;
    pinMode(_controllerPin, INPUT);
  }

  TestController::~TestController()
  {
  }

  byte TestController::GetVal()
  { 
    val = map(analogRead(_controllerPin), 0, 1023, 0, 127);
    return val;
  }

  bool hasChanged()
  {
    if(val != _prevVal)
    {
      _prevVal = val;
      return true;
    }
    else
      return false;
  }
};

#endif

