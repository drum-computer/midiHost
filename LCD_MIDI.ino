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
const byte input_midi_channel = 0;
const byte input_cc = 7;


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
    int new_val = matrix.increaseValue(cursor_pos, input_midi_channel, input_cc);
    lcd.updateDisplayValue(cursor_pos, new_val);
  }

  // send test midi message
  if(down.isPressed())
  {
    // all this code is for testing purposes only. 
    // down button is being used as a midi trigger
    byte output_midi_channel;
    byte output_cc;
    matrix.route(input_midi_channel, input_cc, &output_midi_channel, &output_cc);
    midiSender.SendCC(output_midi_channel, output_cc, 110);
  }

    
  delay(10);
}
