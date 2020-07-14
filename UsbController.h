#ifndef UsbController_h
#define UsbController_h

#include "Arduino.h"
#include "SPI.h"
#include "usbhub.h"
#include "usbh_midi.h"
#include "Constants.h"

class UsbController
{
private:
  USB Usb;
  USBH_MIDI Midi;
  byte midi_buffer[3];

public:
  UsbController() : Midi(&Usb)
  {
    
  }

  void start()
  {
    if (Usb.Init() == -1) 
      {
        while (1); //halt
      }//if (Usb.Init() == -1...
      delay( 200 );
  }

  void task()
  {
    Usb.Task();
  }

  bool hasChanged()
  {
    return Usb.getUsbTaskState() == USB_STATE_RUNNING && 
                Midi.RecvData(midi_buffer) > 0;
  }

  void readController(byte *midi_channel, byte *cc, byte *value)
  {
    do
    {
      *midi_channel = midi_buffer[0] - Constants::CC_START_ADDRESS;
      *cc = midi_buffer[1];
      *value = midi_buffer[2];
    } while (Midi.RecvData(midi_buffer) > 0);
  }
};

#endif