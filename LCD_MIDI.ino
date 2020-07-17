#include "MidiSender.h"
#include "Constants.h"
#include "TestController.h"
#include "Button.h"
#include "LCD.h"
#include "RoutingMatrix.h"
// #include "UsbController.h"
#include "SPI.h"
#include "usbhub.h"
#include "usbh_midi.h"

// interaction buttons
Button up(Constants::UP_BUTTON_PIN);
Button down(Constants::DOWN_BUTTON_PIN);
Button left(Constants::LEFT_BUTTON_PIN);
Button right(Constants::RIGHT_BUTTON_PIN);

// object responsible for sending midi data through midi out port
MidiSender midiSender;

// object that controls LCD display (wraps built-in liquid crystal library)
LCD lcd(Constants::LCD_RS, Constants::LCD_E, 
        Constants::LCD_D4, Constants::LCD_D5,
        Constants::LCD_D6, Constants::LCD_D7);

// test potentiometer used to emulate single pot of usb controller
TestController testPot(Constants::POT1_PIN);

// this object stores all the midi routings
// RoutingMatrix routingMatrix;

// this object interfaces with usb controller
// UsbController usbController;
USB Usb;
USBH_MIDI Midi (&Usb);
void setup()
{
      if (Usb.Init() == -1) 
      {
        while (1); //halt
      }//if (Usb.Init() == -1...
      delay( 200 );
  // start midi sender
  midiSender.start();

  // start usb controller
  // usbController.start();

  // start lcd display 16 chars 2 line mode
  lcd.begin(16, 2);

  // print some initial data
  lcd.setCursor(0, 0);
  // lcd.print("->ch01cc000v000");
  lcd.setCursor(0, 1);
  // lcd.print("<-ch01cc000v000");
  
  //enable blinking cursor
  lcd.cursor();
  lcd.blink();
}

void loop()
{
  // these variables are updated by usbController.readController()
  static byte input_midi_channel;
  static byte input_cc;
  static byte input_value;

  // these variables are uodated by routingMatrix.lookup()
  static byte output_midi_channel;
  static byte output_cc;

  // this variable is updated by cursor button left/right
  static byte cursor_pos = 0;
  static int vals_received = 0;
  static byte counter = 0;
  Usb.Task();

  uint8_t outBuf[ 3 ];
  uint8_t size;

  do {
    if ( (size = Midi.RecvData(outBuf)) > 0 ) {
      //MIDI Output
      Serial.write(outBuf, size);
      vals_received++;
      lcd.updateDisplayValue(1, vals_received);
      // midiSender.sendCC(outBuf[0], outBuf[1], outBuf[2]);
    }
  } while (size > 0);

  // while((size = Midi.RecvData(outBuf)) > 0 )
  //   {
  //     Serial.write(outBuf, size);
  //     vals_received++;
  //     lcd.updateDisplayValue(1, vals_received);
  //   }
  // main usb task 
  // usbController.task();
  
  // debug with text controller

  // byte test_pot_val = testPot.GetVal();
  // if (testPot.hasChanged())
  // {
  //   // shpw current input and output value
  //   // later I'm planning to add value transform
  //   // hence 2 different functions
  //   cursor_pos = 2; // hardcoded for now, don't know how to make it prettier
  //   lcd.updateCursorPosition(cursor_pos);
  //   lcd.updateDisplayValue(cursor_pos, test_pot_val);
  // }
  
  if(right.isPressed())
  {
    cursor_pos = (cursor_pos >= Constants::NUM_CURSOR_POS - 1) ? 0 
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
    // byte display_val = routingMatrix.changeRouting(cursor_pos, 
                                            // input_midi_channel, input_cc);
    // lcd.updateDisplayValue(cursor_pos, display_val);
  }

  // was used to send test midi message. Currently unused
  if(down.isPressed())
  {
    vals_received = 0;
    lcd.updateDisplayValue(1, vals_received);
  }

  // if(usbController.hasChanged())
  // {
  //   /*
  //     When interacting with usb controller:
  //     1. Read data from controller 
  //     2. Update display value from controller
  //     3. Lookup corresponding routing from routingMatrix
  //     4. Update corresponding output value
  //     5. Send data to midi out port
  //   */

  //   usbController.readController(&input_midi_channel, &input_cc, &input_value);
    
  //   // add 1 because we used to 1 to 16 midi channel enumeration
  //   lcd.updateDisplayValue(3, input_midi_channel + 1); 
  //   lcd.updateDisplayValue(4, input_cc);
  //   lcd.updateDisplayValue(5, input_value);

  //   routingMatrix.lookup(input_midi_channel, input_cc, &output_midi_channel, &output_cc);
    
  //   // add 1 because we used to 1 to 16 midi channel enumeration
  //   lcd.updateDisplayValue(0, output_midi_channel + 1);
  //   lcd.updateDisplayValue(1, output_cc);
  //   lcd.updateDisplayValue(2, input_value);
    
  //   midiSender.sendCC(output_midi_channel, output_cc, input_value);
  // }
    // usbController.recv
  // if(usbController.hasChanged())
  {
  //   usbController.readController(&input_midi_channel, &input_cc, &input_value);
  //   vals_received++;
  //   midi_data[0] = Constants::CC_START_ADDRESS + input_midi_channel;
  //   midi_data[1] = input_cc;
  //   midi_data[2] = input_value;
  //   Serial.write(midi_data, 3);
  //   // Serial.write(Constants::CC_START_ADDRESS + input_midi_channel);
  //   // Serial.write(input_cc);
  //   // Serial.write(input_value);
  //   // midiSender.sendCC(output_midi_channel, output_cc, input_value);
  //   lcd.updateDisplayValue(1, vals_received);
  // }
  // // not sure if it's needed, just for stability  
  // delay(1);
}
