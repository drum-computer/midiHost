#ifndef MidiSender_h
#define MidiSender_h
#include <Arduino.h>

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

    void MidiSender::Start()
    {
        Serial.begin(31250);
    }

    void MidiSender::SendCC(int channel, int cc, int value)
    {
        Serial.write(176 + (channel - 1));
        Serial.write(cc);
        Serial.write(value);
    }
};
#endif