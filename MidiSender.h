#ifndef MidiSender_h
#define MidiSender_h
#include <Arduino.h>
#include "Constants.h"

class MidiSender
{
private:
    /* data */
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
        Serial.write(Constants::CC_START_ADDRESS + channel);
        Serial.write(cc);
        Serial.write(value);
    }
};
#endif