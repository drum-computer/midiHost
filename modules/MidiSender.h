#ifndef MidiSender_h
#define MidiSender_h
#include <Arduino.h>
#include "Constants.h"

class MidiSender
{
private:
    // this value is always 176 for cc
    const byte cc_start_offset = 176;
public:

    MidiSender::MidiSender(/* args */)
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
};
#endif