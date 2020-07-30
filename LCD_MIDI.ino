#include "MidiSender.h"
#include "Constants.h"
#include "TestController.h"
#include "Button.h"
#include "LCD.h"
#include "RoutingMatrix.h"
#include "UsbController.h"

// interaction buttons
Button up(Constants::UP_BUTTON_PIN);
Button down(Constants::DOWN_BUTTON_PIN);
Button left(Constants::LEFT_BUTTON_PIN);
Button next(Constants::NEXT_BUTTON_PIN);

// object responsible for sending midi data through midi out port
MidiSender midiSender;

// object that controls LCD display (wraps built-in liquid crystal library)
LCD lcd(Constants::LCD_RS, Constants::LCD_E, 
        Constants::LCD_D4, Constants::LCD_D5,
        Constants::LCD_D6, Constants::LCD_D7);

// test potentiometer used to emulate single pot of usb controller
TestController testPot(Constants::POT1_PIN);

// this object stores all the midi routings
RoutingMatrix routingMatrix;

// this object interfaces with usb controller
UsbController usbController;

Constants::working_mode working_mode;

Constants::menu_entries menu_entry;

unsigned long time;

void setup()
{
  // start midi sender
  midiSender.start();
  
  // start usb controller
  usbController.start();

  // start lcd display 16 chars 2 line mode
  lcd.begin(16, 2);

  // init working mode
  working_mode = Constants::working_mode::edit;

  // print some initial data
  lcd.setCursor(0, 0);
  lcd.print(F("->ch01cc000v000"));
  lcd.setCursor(0, 1);
  lcd.print(F("<-ch01cc000v000"));
  
  //enable blinking cursor
  lcd.cursor();
  lcd.blink();
}

void loop()
{
  time = millis();
  static unsigned long last_screen_update = 0;

  // these variables are updated by usbController.readController()
  static byte input_midi_channel = 0;
  static byte input_cc = 0;
  static byte input_value = 0;

  // these variables are uodated by routingMatrix.lookup()
  static byte output_midi_channel = 0;
  static byte output_cc = 0;

  // this variable is updated by next button
  static byte cursor_pos = 0;

  // main usb task 
  usbController.task();
  
  if(next.isPressed())
  {
    updateCursorPosition(&cursor_pos);
  }
  
  if(up.isPressed())
  {
    int lookup_address = (input_midi_channel * Constants::NUM_CONTROLLERS) 
                          + input_cc;;
    int old_value = routingMatrix.getDestination(lookup_address);
    int new_value;
    //fjgure what needs to be changed
    //change it 
    //update display value
    switch (cursor_pos)
    {
    case Constants::menu_entries::Output_channel:
      new_value = 
            (old_value + Constants::NUM_CONTROLLERS) >= Constants::MATRIX_SIZE 
                                      ? old_value % Constants::NUM_CONTROLLERS
                                      : old_value + Constants::NUM_CONTROLLERS;
      
      // put it back
      routingMatrix.setDestination(lookup_address, new_value);

      // update screen
      lcd.updateDisplayValue(0, (new_value / Constants::NUM_CONTROLLERS) + 1);
      break;

    case Constants::menu_entries::Output_cc:
      byte channel_offset = old_value / Constants::NUM_CONTROLLERS;
      new_value = 
            (old_value + 1) >= ((Constants::NUM_CONTROLLERS * channel_offset) 
             + Constants::NUM_CONTROLLERS) ? 
                (Constants::NUM_CONTROLLERS * channel_offset) : (old_value + 1);

      // put it back
      routingMatrix.setDestination(lookup_address, new_value);

      // update screen
      lcd.updateDisplayValue(1, new_value % Constants::NUM_CONTROLLERS);
      break;
    }
  }

  // was used to send test midi message. Currently unused
  if(down.isPressed())
  {
    int lookup_address = (input_midi_channel * Constants::NUM_CONTROLLERS) 
                          + input_cc;;
    int old_value = routingMatrix.getDestination(lookup_address);
    int new_value;
    //fjgure what needs to be changed
    //change it 
    //update display value
    switch (cursor_pos)
    {
    case Constants::menu_entries::Output_channel:
      new_value = (old_value - Constants::NUM_CONTROLLERS) < 0 ? 
              Constants::MATRIX_SIZE - Constants::NUM_CONTROLLERS + old_value: 
              old_value - Constants::NUM_CONTROLLERS;
      
      // put it back
      routingMatrix.setDestination(lookup_address, new_value);

      // update screen
      lcd.updateDisplayValue(0, (new_value / Constants::NUM_CONTROLLERS) + 1);
      break;

    case Constants::menu_entries::Output_cc:
      byte channel_offset = old_value / Constants::NUM_CONTROLLERS;
      new_value = 
            (old_value - 1) < (Constants::NUM_CONTROLLERS * channel_offset) ? 
                ((Constants::NUM_CONTROLLERS * (channel_offset + 1)) - 1) : 
                  (old_value - 1);

      // put it back
      routingMatrix.setDestination(lookup_address, new_value);

      // update screen
      lcd.updateDisplayValue(1, new_value % Constants::NUM_CONTROLLERS);
      break;
    }
  }

  if(usbController.hasChanged())
  {
    usbController.readController(&input_midi_channel, &input_cc, &input_value);
    
    int lookup_address = (input_midi_channel * Constants::NUM_CONTROLLERS) 
                          + input_cc;;
    
    output_midi_channel = routingMatrix.getDestination(lookup_address) / 
                                                    Constants::NUM_CONTROLLERS;

    output_cc = routingMatrix.getDestination(lookup_address) %
                                                    Constants::NUM_CONTROLLERS;
    // routingMatrix.route(input_midi_channel, input_cc, 
    //                      &output_midi_channel, &output_cc);
    
    midiSender.sendCC(output_midi_channel, output_cc, input_value);
  }

  // check if it's time to refresh the screen
  // in the future this will be main lcd loop for everything screen-related
  if((time - last_screen_update) > Constants::SCREEN_REFRESH_RATE
      && working_mode == Constants::working_mode::monitor)
  {
    // add 1 because we used to 1 to 16 midi channel enumeration
    lcd.updateDisplayValue(3, input_midi_channel + 1); 
    lcd.updateDisplayValue(4, input_cc);
    lcd.updateDisplayValue(5, input_value);
    
    // add 1 because we used to 1 to 16 midi channel enumeration
    lcd.updateDisplayValue(0, output_midi_channel + 1);
    lcd.updateDisplayValue(1, output_cc);
    lcd.updateDisplayValue(2, input_value);

    // reset the timer
    last_screen_update = time;
  }

  // not sure if it's needed, just for stability  
  delay(1);
}

void updateCursorPosition(byte* cursor_pos)
{ 
  *cursor_pos = (*cursor_pos >= Constants::NUM_CURSOR_POS - 1) ? 
                                            0 : *cursor_pos + 1;
  switch (*cursor_pos)
  {
  case Constants::menu_entries::Output_channel:
    lcd.setCursor(4, 1);
    break;
  
  case Constants::menu_entries::Output_cc:
    lcd.setCursor(8, 1);
    break;

  default:
    lcd.setCursor(0, 0);
    lcd.print(*cursor_pos);
    break;
  }
}