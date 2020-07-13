#ifndef UsbController_h
#define UsbController_h

#include "Arduino.h"
#include "SPI.h"
#include "usbhub.h"
#include "usbh_midi.h"

class UsbController
{
private:
public:
USB Usb;
USBH_MIDI  Midi(&Usb);
UsbController()
  {
    if (Usb.Init() == -1) {
      while (1); //halt
      }//if (Usb.Init() == -1...
      delay( 200 );
  }
};

#endif