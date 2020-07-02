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

// hardcoded for now, but should get 
// automatically picked from midi controller
const byte midiChannel = 0;
const byte cc = 7;


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
  lcd.cursor();
  lcd.blink();
}

void loop()
{
  static byte cursor_pos = 0;
  // lcd.setCursor(0, 0);
  if (testPot.hasChanged())
  {
    lcd.printInputVal(testPot.GetVal());
    delay(1);
    lcd.printOutputVal(testPot.GetVal());
  }
  
  if(right.isPressed())
  {
    cursor_pos = (cursor_pos == Constants::NUM_CURSOR_POS - 1) ? 0 
                                                              : cursor_pos + 1;
    lcd.updateCursorPosition(cursor_pos);
  }
  
  if(left.isPressed())
  {
    cursor_pos = (cursor_pos == 0) ? Constants::NUM_CURSOR_POS - 1 
                                                              : cursor_pos - 1;
    lcd.updateCursorPosition(cursor_pos);
  }
  
  if(up.isPressed())
  {
    byte val = matrix.increaseValue(cursor_pos, midiChannel, cc);
    lcd.updateDisplayValue(cursor_pos, val);
  }

  // send test midi message
  if(down.isPressed())
  {
    byte cc = matrix.matrix[0][7];
    midiSender.SendCC(1, cc, 110);
  }

    
  delay(10);
}
