#include "MIDIUSB.h"

const int button1Pin = 14;
const int numRecordings = 8;

bool isButtonOn = false;
unsigned long buttonPressCount = 0;

void setup() {
  Serial.begin(115200);
  pinMode(button1Pin, INPUT_PULLDOWN);
}

void loop() {
  int buttonState = digitalRead(button1Pin);
  Serial.println(buttonState);
 
  int buttonSampleIndex = buttonPressCount % numRecordings;
  int midiNote = 48 - buttonSampleIndex;

  if (buttonState == HIGH && !isButtonOn) {
    isButtonOn = true;
    buttonPressCount++;
  
    Serial.print("Button Press Count: ");
    Serial.println(buttonPressCount);
    Serial.print("Button Sample Index: ");
    Serial.println(buttonSampleIndex);

    // Turn off the prior MIDI note so that the sounds don't overlap.
    noteOff(4, midiNote + 1, 64);

    // Play the new MIDI note!   
    noteOn(4, midiNote, 64);
  } else if (buttonState == LOW) {
    isButtonOn = false;
  }

  delay(50);
}

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity) {
  Serial.print("Midi Note On: ");
  Serial.println(pitch);
  
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  Serial.print("Midi Note Off: ");
  Serial.println(pitch);
  
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
