#include "MidiSender.h"
#include "Constants.h"

MidiSender midiSender;

void setup()
{
    midiSender.Start();
    midiSender.SendCC(1, 7, 100);
}

void loop()
{

}
