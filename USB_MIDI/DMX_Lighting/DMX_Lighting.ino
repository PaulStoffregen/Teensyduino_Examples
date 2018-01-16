/* Control DMX lighting with MIDI control change messages.  DJ and
   stage lighting can be easily controlled by software with can
   send MIDI messages.

   https://github.com/jmej/MIDI2DMX

   Teensy TX1 (pin 1 on Teensy LC and 3.x)  must be connected to a
   RS422/RS485 transmitter capable of driving a DMX lighting cable.
*/



#include "leddmx.h"

void setup() {
  Serial1.begin(250000);
  usbMIDI.setHandleControlChange(OnControlChange);
}

void OnControlChange(byte channel, byte control, byte value) {
  led_channel(control, value*2);
  // Serial.println("got midi ");
  // Serial.println(value);
}

void loop() {
  leds_update();
  usbMIDI.read(); // USB MIDI receive
}

