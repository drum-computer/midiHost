#include "Arduino.h"
#include "TestController.h"


TestController::TestController(int contollerPin)
{
  _controllerPin = contollerPin;
  pinMode(_controllerPin, INPUT);
  val = 0;
  _prevVal = 0;
}

TestController::~TestController()
{
}

byte TestController::GetVal()
{ 
  val = map(analogRead(_controllerPin), 0, 1023, 0, 127);
  return val;
}

bool TestController::hasChanged()
{
  if(val != _prevVal)
  {
    _prevVal = val;
    return true;
  }
  else
    return false;
}
