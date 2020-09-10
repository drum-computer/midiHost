#include "src/Constants.h"
#include "src/Button.h"
#include "src/UsbController.h"
#include "src/MidiSender.h"
#include "src/LCD.h"
#include "src/RoutingMatrix.h"
#pragma region //objects and variables initialization 
// interaction buttons
Button mode(Constants::MODE_BUTTON_PIN);
Button select(Constants::SELECT_BUTTON_PIN);
Button up(Constants::UP_BUTTON_PIN);
Button down(Constants::DOWN_BUTTON_PIN);

// korg nano kontrol
UsbController usbController;

// midi out
MidiSender midiSender;

// LCD display (wraps built-in liquid crystal library)
LCD lcd(Constants::LCD_RS, Constants::LCD_E, 
        Constants::LCD_D4, Constants::LCD_D5,
        Constants::LCD_D6, Constants::LCD_D7);

// this object stores all the midi routings
RoutingMatrix routingMatrix;

// screen refresh timer
unsigned long time;

// these variables are updated by usbController.readController()
static byte input_midi_channel = 0;
static byte input_cc = 0;
static byte input_value = 0;

// this variable is updated by next button
static byte cursor_pos = 0;

// mode counter
static byte work_mode = 0; // perform
#pragma endregion

void setup()
{
  midiSender.start();
  lcd.start();
  usbController.start();
}

void loop()
{
  //keep track of elapsed time for screen refresh
  time = millis();
  static unsigned long last_screen_update = 0;

  // main usb task 
  usbController.task();
  
  if(mode.isPressed())
  {
    work_mode = (work_mode + 1) % Constants::NUM_WORKING_MODES;
    lcd.switchMode(work_mode); //mode cycle
  }
  
  if(select.isPressed())
  {
    lcd.cycleCursorPosition();
  }
  
  if(up.isPressed())
  {
    increaseSelectedValue(); 
  }

  if(down.isPressed())
  {
    decreaseSelectedValue(); 
  }
  
  if(usbController.hasChanged())
  {
    usbController.readController(&input_midi_channel, &input_cc, &input_value);
    sendMidiCC();   
  }

  // check if it's time to refresh the screen
  // in the future this will be main lcd loop for everything screen-related
  if((time - last_screen_update) > Constants::SCREEN_REFRESH_RATE
                            && work_mode == 0)
  {

    // dispatcher.refreshScreen();
    // // reset the timer
    // last_screen_update = time;
  }

  // not sure if it's needed, just for stability  
  // delay(1);
}


void increaseSelectedValue()
{
  // int lookup_address = (input_midi_channel * Constants::NUM_CONTROLLERS) 
  //                                                                 + input_cc;
  // int old_value = routingMatrix.getDestination(lookup_address);
  // int new_value;
  // //fjgure what needs to be changed
  // //change it 
  // //update display value
  // switch (cursor_pos)
  // {
  // case Constants::menu_entries::Output_channel:
  //   new_value = 
  //         (old_value + Constants::NUM_CONTROLLERS) >= Constants::MATRIX_SIZE 
  //                                   ? old_value % Constants::NUM_CONTROLLERS
  //                                   : old_value + Constants::NUM_CONTROLLERS;
    
  //   // put it back
  //   routingMatrix.setDestination(lookup_address, new_value);

  //   // update screen
  //   lcd.updateDisplayValue(0, (new_value / Constants::NUM_CONTROLLERS) + 1);
  //   break;

  // case Constants::menu_entries::Output_cc:
  //   byte channel_offset = old_value / Constants::NUM_CONTROLLERS;
  //   new_value = 
  //         (old_value + 1) >= ((Constants::NUM_CONTROLLERS * channel_offset) 
  //           + Constants::NUM_CONTROLLERS) ? 
  //             (Constants::NUM_CONTROLLERS * channel_offset) : (old_value + 1);

  //   // put it back
  //   routingMatrix.setDestination(lookup_address, new_value);

  //   // update screen
  //   lcd.updateDisplayValue(1, new_value % Constants::NUM_CONTROLLERS);
  //   break;
  // }
}

void decreaseSelectedValue()
{
  // int lookup_address = (input_midi_channel * Constants::NUM_CONTROLLERS) 
  //                                                                 + input_cc;
  // int old_value = routingMatrix.getDestination(lookup_address);
  // int new_value;
  // //fjgure what needs to be changed
  // //change it 
  // //update display value
  // switch (cursor_pos)
  // {
  // case Constants::menu_entries::Output_channel:
  //   new_value = (old_value - Constants::NUM_CONTROLLERS) < 0 ? 
  //             Constants::MATRIX_SIZE - Constants::NUM_CONTROLLERS + old_value: 
  //                                     old_value - Constants::NUM_CONTROLLERS;
    
  //   // put it back
  //   routingMatrix.setDestination(lookup_address, new_value);

  //   // update screen
  //   lcd.updateDisplayValue(0, (new_value / Constants::NUM_CONTROLLERS) + 1);
  //   break;

  // case Constants::menu_entries::Output_cc:
  //   byte channel_offset = old_value / Constants::NUM_CONTROLLERS;
  //   new_value = 
  //         (old_value - 1) < (Constants::NUM_CONTROLLERS * channel_offset) ? 
  //                 ((Constants::NUM_CONTROLLERS * (channel_offset + 1)) - 1) : 
  //                                                             (old_value - 1);

  //   // put it back
  //   routingMatrix.setDestination(lookup_address, new_value);

  //   // update screen
  //   lcd.updateDisplayValue(1, new_value % Constants::NUM_CONTROLLERS);
  //   break;
  // }
}

void refreshScreen()
{
  // //add 1 because we used to 1 to 16 midi channel enumeration
  // lcd.updateDisplayValue(3, input_midi_channel + 1); 
  // lcd.updateDisplayValue(4, input_cc);
  // lcd.updateDisplayValue(5, input_value);
  
  // // add 1 because we used to 1 to 16 midi channel enumeration
  // lcd.updateDisplayValue(0, output_midi_channel + 1);
  // lcd.updateDisplayValue(1, output_cc);
  // lcd.updateDisplayValue(2, input_value);
}


void sendMidiCC()
{
  int lookup_address = (input_midi_channel * Constants::NUM_CONTROLLERS) 
                                                                      + input_cc;
      
  byte output_midi_channel = routingMatrix.getDestination(lookup_address) / 
                                                  Constants::NUM_CONTROLLERS;

  byte output_cc = routingMatrix.getDestination(lookup_address) %
                                                  Constants::NUM_CONTROLLERS;
  
  midiSender.sendCC(output_midi_channel, output_cc, input_value);

}