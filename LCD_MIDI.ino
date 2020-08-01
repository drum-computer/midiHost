#include "src/Constants.h"
#include "src/Button.h"
#include "src/UsbController.h"
#include "src/System.h"

// interaction buttons
Button mode(Constants::MODE_BUTTON_PIN);
Button select(Constants::SELECT_BUTTON_PIN);
Button up(Constants::UP_BUTTON_PIN);
Button down(Constants::DOWN_BUTTON_PIN);

// korg nano kontrol
UsbController usbController;

// all project-specific code is in here
System pSystem;

// current state (monitor/edit/save/reset)
Constants::working_mode working_mode;

// screen refresh timer
unsigned long time;

void setup()
{
  // init system
  pSystem.init();

  // start usb controller
  usbController.start();
}

void loop()
{
  //keep track of elapsed time for screen refresh
  time = millis();
  static unsigned long last_screen_update = 0;

  // these variables are updated by usbController.readController()
  static byte input_midi_channel = 0;
  static byte input_cc = 0;
  static byte input_value = 0;

  // this variable is updated by next button
  static byte cursor_pos = 0;

  // mode counter
  static byte current_mode = 0; // monitor

  // main usb task 
  usbController.task();
  
  if(mode.isPressed())
  {
    pSystem.nextMode(&current_mode); //mode cycle
  }
  
  if(select.isPressed())
  {
    pSystem.updateCursorPosition(&cursor_pos);
  }
  
  if(up.isPressed())
  {
    pSystem.increaseValue(input_midi_channel, input_cc, cursor_pos); 
  }

  if(down.isPressed())
  {
    pSystem.decreaseValue(input_midi_channel, input_cc, cursor_pos); 
  }
  
  if(usbController.hasChanged())
  {
    usbController.readController(&input_midi_channel, &input_cc, &input_value);
    pSystem.send(input_midi_channel, input_cc, input_value);   
  }

  // check if it's time to refresh the screen
  // in the future this will be main lcd loop for everything screen-related
  if((time - last_screen_update) > Constants::SCREEN_REFRESH_RATE
                            && working_mode == Constants::working_mode::monitor)
  {
    // add 1 because we used to 1 to 16 midi channel enumeration
    // lcd.updateDisplayValue(3, input_midi_channel + 1); 
    // lcd.updateDisplayValue(4, input_cc);
    // lcd.updateDisplayValue(5, input_value);
    
    // // add 1 because we used to 1 to 16 midi channel enumeration
    // lcd.updateDisplayValue(0, output_midi_channel + 1);
    // lcd.updateDisplayValue(1, output_cc);
    // lcd.updateDisplayValue(2, input_value);

    // // reset the timer
    // last_screen_update = time;
  }

  // not sure if it's needed, just for stability  
  // delay(1);
}


