#include "Arduino.h"
#include "MidiSender.h"

MidiSender::MidiSender()
{
}

MidiSender::~MidiSender()
{
}

void MidiSender::start()
{
  Serial.begin(31250);
}

void MidiSender::sendCC(byte channel, byte cc, byte value)
{
  Serial.write(cc_start_offset + channel);
  Serial.write(cc);
  Serial.write(value);
}
