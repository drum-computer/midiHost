#ifndef System_h
#define System_h

#include "Arduino.h"

#include "MidiSender.h"
#include "Constants.h"
#include "LCD.h"
#include "RoutingMatrix.h"

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

  Constants::working_mode working_mode;

  Constants::menu_entries menu_entry;
public:
  System(/* args */);
  ~System();
  void System::init();
  void System::nextMode(byte* current_mode);
  void System::updateCursorPosition(byte* cursor_pos);
  void System::increaseValue(byte input_midi_channel, byte input_cc, byte cursor_pos);
  void System::decreaseValue(byte input_midi_channel, byte input_cc, byte cursor_pos);
  void System::send(byte input_midi_channel, byte input_cc, byte input_value);
};

#endif
