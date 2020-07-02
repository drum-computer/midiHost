#include "MidiSender.h"
#include "Constants.h"
#include "TestController.h"
#include "Button.h"
#include "LCD.h"
#include "RoutingMatrix.h"

Button up(Constants::UP_BUTTON_PIN);
Button down(Constants::DOWN_BUTTON_PIN);
Button left(Constants::LEFT_BUTTON_PIN);
Button right(Constants::RIGHT_BUTTON_PIN);
MidiSender midiSender;
LCD lcd(12, 11, 5, 4, 3, 2);
TestController testPot(Constants::POT1_PIN);
RoutingMatrix matrix;

void setup()
{
  // start midi sender
  midiSender.Start();

  // start lcd display
  lcd.begin(16, 2);
  // print some initial data
  lcd.setCursor(0, 0);
  lcd.print("->ch10cc127v100");
  lcd.setCursor(0, 1);
  lcd.print("<-ch10cc127v100");
}

void loop()
{
  // lcd.setCursor(0, 0);
  lcd.printInputVal(testPot.GetVal());
  delay(1);
  lcd.printOutputVal(testPot.GetVal());
  if(down.isPressed())
  {
    byte cc = matrix.matrix[0][7];
    midiSender.SendCC(1, cc, 110);
  }

    
  delay(10);
}
