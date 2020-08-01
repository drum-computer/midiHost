#ifndef System_h
#define System_h

#include "Arduino.h"

#include "MidiSender.h"
#include "Constants.h"
#include "Button.h"
#include "LCD.h"
#include "RoutingMatrix.h"
#include "UsbController.h"

class System
{
private:
  // object responsible for sending midi data through midi out port
  MidiSender midiSender;

  // object that controls LCD display (wraps built-in liquid crystal library)
  LCD lcd = LCD(Constants::LCD_RS, Constants::LCD_E, 
          Constants::LCD_D4, Constants::LCD_D5,
          Constants::LCD_D6, Constants::LCD_D7);

  // this object stores all the midi routings
  RoutingMatrix routingMatrix;

  // this object interfaces with usb controller
  UsbController usbController;

  Constants::working_mode working_mode;

  Constants::menu_entries menu_entry;

public:
  System(/* args */);
  ~System();
  void Init();
};

System::System (/* args */)
{

}

System::~System()
{
}

void System::Init()
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

#endif