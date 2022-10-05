//#include "MIDIUSB.h"

const int buttonPin = 14;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLDOWN);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
}
