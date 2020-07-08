#include "MidiSender.h"
#include "Constants.h"
#include "TestController.h"
#include "Button.h"
#include "LCD.h"
#include "RoutingMatrix.h"


// initialize interface navigation buttons
Button up(Constants::UP_BUTTON_PIN);
Button down(Constants::DOWN_BUTTON_PIN);
Button left(Constants::LEFT_BUTTON_PIN);
Button right(Constants::RIGHT_BUTTON_PIN);

MidiSender midiSender;

LCD lcd(Constants::LCD_RS, Constants::LCD_E, 
        Constants::LCD_D4, Constants::LCD_D5,
        Constants::LCD_D6, Constants::LCD_D7);

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

  // start lcd display 16 chars 2 line mode
  lcd.begin(16, 2);

  // print some initial data
  lcd.setCursor(0, 0);
  lcd.print("->ch01cc007v100");
  lcd.setCursor(0, 1);
  lcd.print("<-ch01cc007v100");
  
  //enable blinking cursor
  lcd.cursor();
  lcd.blink();
}

void loop()
{

  static byte cursor_pos = 0;
  byte test_pot_val = testPot.GetVal();
  if (testPot.hasChanged())
  {
    // shpw current input and output value
    // later I'm planning to add value transform
    // hence 2 different functions
    cursor_pos = 2; // hardcoded for now, don't know how to make it prettier
    lcd.updateCursorPosition(cursor_pos);
    lcd.updateDisplayValue(cursor_pos, test_pot_val);
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
    byte display_val = matrix.changeRouting(cursor_pos, 
                                            input_midi_channel, input_cc);
    lcd.updateDisplayValue(cursor_pos, display_val);
  }

  // send test midi message
  if(down.isPressed())
  {
    // all this code is for testing purposes only. 
    // down button is being used as a midi trigger
    byte output_midi_channel;
    byte output_cc;
    matrix.route(input_midi_channel, input_cc, &output_midi_channel, &output_cc);
    midiSender.SendCC(output_midi_channel, output_cc, test_pot_val);
  }

    
  delay(10);
}
