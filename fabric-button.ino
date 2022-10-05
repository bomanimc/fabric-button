#include "MIDIUSB.h"

// NOTE: Button 2 Untested, but generally a simple version of the 
// code might look like this.

const int button1Pin = 14;
const int button2Pin = 15;
bool isButton1On = false;
bool isButton2On = false;

void setup() {
  Serial.begin(115200);
  pinMode(button1Pin, INPUT_PULLDOWN);
  pinMode(button2Pin, INPUT_PULLDOWN);
}

void loop() {
  int button1State = digitalRead(button1Pin);
  int button2State = digitalRead(button2Pin);

  if (button1State == LOW && !isButton1On) {
    isButton1On = true;
    Serial.println("Trigger Note 1");
    noteOn(0, 48, 64);
  } else if (button1State == HIGH) {
    isButton1On = false;
  }

  if (button2State == LOW && !isButton2On) {
    isButton2On = true;
    Serial.println("Trigger Note 2");
    noteOn(0, 48, 64);
  } else if (button2State == HIGH) {
    isButton2On = false;
  }

  delay(50);
}

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}
