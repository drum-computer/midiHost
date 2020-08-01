#include "src/Constants.h"
#include "src/Button.h"
#include "src/UsbController.h"
#include "src/System.h"

// interaction buttons
Button up(Constants::UP_BUTTON_PIN);
Button down(Constants::DOWN_BUTTON_PIN);
Button left(Constants::LEFT_BUTTON_PIN);
Button next(Constants::NEXT_BUTTON_PIN);

UsbController usbController;

Constants::working_mode working_mode;

Constants::menu_entries menu_entry;

unsigned long time;

System pSystem;

void setup()
{
  pSystem.Init();
    // start usb controller
  usbController.start();
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


