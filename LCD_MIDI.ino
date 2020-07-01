#include "MidiSender.h"
#include "Constants.h"
#include "TestController.h"
#include "Button.h"
#include <LiquidCrystal.h>

Button up(Constants::UP_BUTTON_PIN);
Button down(Constants::DOWN_BUTTON_PIN);
Button left(Constants::LEFT_BUTTON_PIN);
Button right(Constants::RIGHT_BUTTON_PIN);
MidiSender midiSender;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
TestController testPot(Constants::POT1_PIN);

void setup()
{
  // start midi sender
  midiSender.Start();

  // start lcd display
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print(testPot.GetVal());
  if(down.isPressed())
    midiSender.SendCC(1, 7, 110);
  delay(10);
}
