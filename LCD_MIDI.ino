#include "MidiSender.h"
#include "Constants.h"
#include "TestController.h"
#include <LiquidCrystal.h>

MidiSender      midiSender;
TestController  testPot(Constants::POT1_PIN);
LiquidCrystal   lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  // start midi sender
  midiSender.Start();
  midiSender.SendCC(1, 7, 100);

  // start lcd display
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print(testPot.GetVal());
  if(testPot.hasChanged())
    midiSender.SendCC(1, 7, 110);
  delay(10);
}
