#include "Arduino.h"
#include "MidiSender.h"
#include "Constants.h"
#include "LCD.h"
#include "RoutingMatrix.h"
#include "System.h"

System::System (/* args */)
{
}

System::~System()
{
}

void System::init()
{
  // start midi sender
  midiSender.start();
  
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

void System::nextMode(byte* current_mode)
{
  *current_mode = (*current_mode + 1) > (Constants::NUM_MODES - 1) ? 0 : *current_mode + 1;
}

void System::updateCursorPosition(byte* cursor_pos)
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
void System::increaseValue(byte input_midi_channel, byte input_cc, byte cursor_pos)
{
  int lookup_address = (input_midi_channel * Constants::NUM_CONTROLLERS) 
                                                                  + input_cc;
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

void System::decreaseValue(byte input_midi_channel, byte input_cc, byte cursor_pos)
{
  int lookup_address = (input_midi_channel * Constants::NUM_CONTROLLERS) 
                                                                  + input_cc;
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

void System::send(byte input_midi_channel, byte input_cc, byte input_value)
{
  int lookup_address = (input_midi_channel * Constants::NUM_CONTROLLERS) 
                                                                      + input_cc;
      
      byte output_midi_channel = routingMatrix.getDestination(lookup_address) / 
                                                      Constants::NUM_CONTROLLERS;

      byte output_cc = routingMatrix.getDestination(lookup_address) %
                                                      Constants::NUM_CONTROLLERS;
      
      midiSender.sendCC(output_midi_channel, output_cc, input_value);

}