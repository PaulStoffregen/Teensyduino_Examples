/* Transmit every possible USB MIDI message.  Each time a
   button is pressed, send another message.

   This very long example demonstrates all possible usbMIDI
   message send functions.  It's mostly meant for testing
   and as a reference to easily copy-and-paste the code for
   every message send function.

   A pushbutton (ordinary momentary type) needs to be
   connected between pin 0 and GND.

   You must select MIDI from the "Tools > USB Type" menu

   This example code is in the public domain.
*/

#include <Bounce.h>

// the MIDI channel number to send messages
const int channel = 1;

// the MIDI virtual cable to use
int cable = 0;

// Create a Bounce object for the button.
const int pin = 0;
Bounce button1 = Bounce(pin, 10);

// remember when a note-on message has been sent
int note=0;

// which message will we do next
int state=0;

// sysex message to send
uint8_t buf[] = {0xF0, 6, 24, 64, 5, 1, 0xF7};

void setup() {
  pinMode(pin, INPUT_PULLUP);
}

void loop() {
  button1.update();
  if (button1.fallingEdge()) {
    // when the button is pressed, send another message
    sendNextMessage();
  }
  if (button1.risingEdge()) {
    // when the button is release, send note off if we left a note on
    if (note > 0) {
      usbMIDI.sendNoteOff(note, 0, channel, cable);
      note = 0;
    }
  }

  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}

void sendNextMessage() {
  switch (state) {
    case 0:
      note = analogRead(A0) / 8;
      if (note == 0) note = 1;
      usbMIDI.sendNoteOn(note, 99, channel, cable);
      break;
    case 1:
      usbMIDI.sendAfterTouchPoly(65, 110, channel, cable);
      break;
    case 2:
      usbMIDI.sendControlChange(7, 100, channel, cable);
      break;
    case 3:
      usbMIDI.sendProgramChange(2, channel, cable);
      break;
    case 4:
      usbMIDI.sendAfterTouch(108, channel, cable);
      break;
    case 5:
      usbMIDI.sendPitchBend(911, channel, cable);
      break;
    case 6:
      usbMIDI.sendSysEx(sizeof(buf), buf, true, cable);
      break;
    case 7:
      usbMIDI.sendSysEx(sizeof(buf)-2, buf+1, false, cable);
      break;
    case 8:
      usbMIDI.sendRealTime(usbMIDI.Clock, cable);
      break;
    case 9:
      usbMIDI.sendRealTime(usbMIDI.Start, cable);
      break;
    case 10:
      usbMIDI.sendRealTime(usbMIDI.Continue, cable);
      break;
    case 11:
      usbMIDI.sendRealTime(usbMIDI.Stop, cable);
      break;
    case 12:
      usbMIDI.sendRealTime(usbMIDI.ActiveSensing, cable);
      break;
    case 13:
      usbMIDI.sendRealTime(usbMIDI.SystemReset, cable);
      break;
    case 14:
      usbMIDI.sendTimeCodeQuarterFrame(0, 3, cable);
      usbMIDI.sendTimeCodeQuarterFrame(1, 1, cable);
      usbMIDI.sendTimeCodeQuarterFrame(2, 7, cable);
      usbMIDI.sendTimeCodeQuarterFrame(3, 4, cable);
      usbMIDI.sendTimeCodeQuarterFrame(4, 1, cable);
      usbMIDI.sendTimeCodeQuarterFrame(5, 1, cable);
      usbMIDI.sendTimeCodeQuarterFrame(6, 0, cable);
      usbMIDI.sendTimeCodeQuarterFrame(7, 0, cable);
      break;
    case 15:
      usbMIDI.sendTuneRequest(cable);
      break;
    case 16:
      usbMIDI.sendSongPosition(2531, cable);
      break;
    case 17:
      usbMIDI.sendSongSelect(107, cable);
      break;
    case 18:
      usbMIDI.beginRpn(1, channel, cable);
      usbMIDI.sendRpnValue(6489, channel, cable);
      usbMIDI.endRpn(channel, cable);
      break;
    case 19:
      usbMIDI.beginRpn(1, channel, cable);
      usbMIDI.sendRpnIncrement(14, channel, cable);
      usbMIDI.endRpn(channel, cable);
      break;
    case 20:
      usbMIDI.beginRpn(1, channel, cable);
      usbMIDI.sendRpnDecrement(9, channel, cable);
      usbMIDI.endRpn(channel, cable);
      break;
    case 21:
      usbMIDI.beginNrpn(417, channel, cable);
      usbMIDI.sendRpnValue(6489, channel, cable);
      usbMIDI.endRpn(channel, cable);
      break;
    case 22:
      usbMIDI.beginNrpn(417, channel, cable);
      usbMIDI.sendRpnIncrement(3, channel, cable);
      usbMIDI.endRpn(channel, cable);
      break;
    case 23:
      usbMIDI.beginNrpn(417, channel, cable);
      usbMIDI.sendRpnDecrement(2, channel, cable);
      usbMIDI.endRpn(channel, cable);
      break;
  }
  state = state + 1;
  if (state > 23) state = 0;
}

