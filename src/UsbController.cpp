#include "Arduino.h"
#include "SPI.h"
#include "usbhub.h"
#include "usbh_midi.h"
#include "UsbController.h"

void UsbController::start()
{
  if (Usb.Init() == -1) 
    {
      while (1); //halt
    }//if (Usb.Init() == -1...
    delay( 200 );
}

void UsbController::task()
{
  Usb.Task();
}

bool UsbController::hasChanged()
{
  return Usb.getUsbTaskState() == USB_STATE_RUNNING && 
                                                Midi.RecvData(midi_buffer) > 0;
}

void UsbController::readController(byte *midi_channel, byte *cc, byte *value)
{
  *midi_channel = midi_buffer[0] - cc_start_offset;
  *cc = midi_buffer[1];
  *value = midi_buffer[2];
}
