#ifndef TestController_h
#define TestController_h
#include "Arduino.h"

class TestController
{
private:
  int _controllerPin;
  byte _prevVal;
  byte val;
public:

  TestController::TestController(int contollerPin);

  TestController::~TestController();

  byte TestController::GetVal();

  bool TestController::hasChanged();

};

#endif

