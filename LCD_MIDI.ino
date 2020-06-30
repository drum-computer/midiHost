#include "MidiSender.h"

#define POT1_PIN           A0 
#define LEFT_BUTTON_PIN    10
#define RIGHT_BUTTON_PIN    9
#define UP_BUTTON_PIN       8
#define DOWN_BUTTON_PIN     7

MidiSender midiSender;

void setup()
{
    midiSender.Start();
    midiSender.SendCC(1, 7, 100);
}

void loop()
{

}
