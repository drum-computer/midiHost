#ifndef MidiSender_h
#define MidiSender_h
#include "Arduino.h"

class MidiSender
{
private:
  // this value is always 176 for cc
  const static byte cc_start_offset = 176;
public:
  MidiSender::MidiSender();
  MidiSender::~MidiSender();

  void MidiSender::start();
  void MidiSender::sendCC(byte channel, byte cc, byte value);
};

#endif
