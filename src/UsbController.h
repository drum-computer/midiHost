#ifndef UsbController_h
#define UsbController_h

#include "Arduino.h"
#include "SPI.h"
#include "usbhub.h"
#include "usbh_midi.h"


class UsbController
{
private:
  USB Usb;
  USBH_MIDI Midi;
  byte midi_buffer[3];
  byte cc_start_offset = 176;

public:
  UsbController() : Midi(&Usb)
  {}

  void UsbController::start();

  void UsbController::task();

  bool UsbController::hasChanged();

  void UsbController::readController(byte *midi_channel, byte *cc, byte *value);
};

#endif