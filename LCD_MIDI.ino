#include "src/Constants.h"
#include "src/Button.h"
#include "src/UsbController.h"
#include "src/MidiSender.h"
#include "src/LCD.h"
#include "src/RoutingMatrix.h"
#include "src/Mem.h"
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

// eeprom
Mem mem(Constants::MEM_CHIP_ADDR);

// screen refresh timer
unsigned long time;

// these variables are updated by usbController.readController()
static byte input_midi_channel = 0;
static byte input_cc = 0;
static byte input_value = 0;

static byte output_midi_channel = 0;
static byte output_cc = 0;

// mode counter
static byte work_mode = 0; // perform
#pragma endregion

void setup()
{
  midiSender.start();
  lcd.start();
  usbController.start();
  // load last saved state on startup
  mem.recallAll(routingMatrix.matrix);
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
    lcd.switchMode(work_mode);
  }
  
  if(select.isPressed())
  {
    lcd.cycleCursorPosition();
  }
  
  if(up.isPressed())
  {
    switch (work_mode)
    {
    case Constants::WORK_MODES::PERFORM:
      // do nothing
      break;
    
    case Constants::WORK_MODES::EDIT:
      {
        // lcd return cursor position
        byte cursor_position = lcd.getCursorPosition();
        if(cursor_position == 0)
        {
          byte display_val = 
                  routingMatrix.increaseChannel(&input_midi_channel, &input_cc);
          lcd.updateDisplayValue(cursor_position, display_val);
        } else if(cursor_position == 1)
        {
          byte display_val = 
                    routingMatrix.increaseCC(&input_midi_channel, &input_cc);
          lcd.updateDisplayValue(cursor_position, display_val);
        }
        break;
      }

    case Constants::WORK_MODES::SAVE:
      // memory save state
      mem.storeAll(routingMatrix.matrix);
      lcd.showSuccess();
      break;

    case Constants::WORK_MODES::RESET:
      {
        // display confirmation
        work_mode = Constants::WORK_MODES::CONFIRM_RESET;
        lcd.switchMode(work_mode);
        break;
      }  
    
    case Constants::WORK_MODES::CONFIRM_RESET:
      {
        if(lcd.getCursorPosition() == 0)
        {
          routingMatrix.clear();
          // save cleared matrix to eeprom
          mem.storeAll(routingMatrix.matrix);
          lcd.showResetSuccess();
          work_mode = Constants::WORK_MODES::RESET;
        }
        else
        {
          work_mode = Constants::WORK_MODES::RESET;
          lcd.switchMode(work_mode);
        }
        break;
      }
    }
  }

  if(down.isPressed())
  {
    switch (work_mode)
    {
    case Constants::WORK_MODES::PERFORM:
      // do nothing
      break;
    
    case Constants::WORK_MODES::EDIT:
    {
      byte cursor_position = lcd.getCursorPosition();
      if(cursor_position == 0)
      {
        byte display_val = 
                  routingMatrix.decreaseChannel(&input_midi_channel, &input_cc);
        lcd.updateDisplayValue(cursor_position, display_val);
      } else if(cursor_position == 1)
      {
        byte display_val = 
                  routingMatrix.decreaseCC(&input_midi_channel, &input_cc);
        lcd.updateDisplayValue(cursor_position, display_val);
      }
      break;
    }

    case Constants::WORK_MODES::SAVE:
      // do nothing
      break;

    case Constants::WORK_MODES::RESET:
      // do nothing
      break;
    
    case Constants::WORK_MODES::CONFIRM_RESET:
      // do nothing
      break;
    } 
  }
  
  if(usbController.hasChanged())
  {
    usbController.readController(&input_midi_channel, &input_cc, &input_value);
    int lookup_address = (input_midi_channel * Constants::NUM_CONTROLLERS) 
                                                                     + input_cc;
      
    output_midi_channel = routingMatrix.getDestination(lookup_address) / 
                                                  Constants::NUM_CONTROLLERS;

    output_cc = routingMatrix.getDestination(lookup_address) %
                                                  Constants::NUM_CONTROLLERS;
    
    midiSender.sendCC(output_midi_channel, output_cc, input_value);  

    if(work_mode == Constants::WORK_MODES::EDIT)
    {
      lcd.refresh(work_mode, input_midi_channel, input_cc, input_value,
                                                output_midi_channel, output_cc);
    }
  }

  // check if it's time to refresh the screen
  if((time - last_screen_update) > Constants::SCREEN_REFRESH_RATE
                                && work_mode == Constants::WORK_MODES::PERFORM)
  {
    lcd.refresh(work_mode, input_midi_channel, input_cc, input_value,
                                                output_midi_channel, output_cc);
    last_screen_update = time;
  }
}
