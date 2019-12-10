/* Receive Incoming USB MIDI using functions.  As usbMIDI
   reads incoming messages, handler functions are run.
   See the InputRead example for the non-function alterative.

   This very long example demonstrates all possible handler
   functions.  Most applications need only some of these.
   This example is meant to allow easy copy-and-paste of the
   desired functions.  See InputFunctionsBasic for a smaller
   example using only the most common function.

   Use the Arduino Serial Monitor to view the messages
   as Teensy receives them by USB MIDI

   You must select MIDI from the "Tools > USB Type" menu

   On Linux systems, use "amidi" to send from command line:
     amidi -p hw:3,0,0 -S '90 68 64'
     amidi -p hw:3,0,0 -S 'F0 43 10 4C 00 00 7E 00 F7'

   This example code is in the public domain.
*/


void setup() {
  Serial.begin(115200);
  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleAfterTouchPoly(myAfterTouchPoly);
  usbMIDI.setHandleControlChange(myControlChange);
  usbMIDI.setHandleProgramChange(myProgramChange);
  usbMIDI.setHandleAfterTouchChannel(myAfterTouchChannel);
  usbMIDI.setHandlePitchChange(myPitchChange);
  // Only one of these System Exclusive handlers will actually be
  // used.  See the comments below for the difference between them.
  usbMIDI.setHandleSystemExclusive(mySystemExclusiveChunk);
  usbMIDI.setHandleSystemExclusive(mySystemExclusive); 
  usbMIDI.setHandleTimeCodeQuarterFrame(myTimeCodeQuarterFrame);
  usbMIDI.setHandleSongPosition(mySongPosition);
  usbMIDI.setHandleSongSelect(mySongSelect);
  usbMIDI.setHandleTuneRequest(myTuneRequest);
  usbMIDI.setHandleClock(myClock);
  usbMIDI.setHandleStart(myStart);
  usbMIDI.setHandleContinue(myContinue);
  usbMIDI.setHandleStop(myStop);
  usbMIDI.setHandleActiveSensing(myActiveSensing);
  usbMIDI.setHandleSystemReset(mySystemReset);
  // This generic System Real Time handler is only used if the
  // more specific ones are not set.
  usbMIDI.setHandleRealTimeSystem(myRealTimeSystem);
}

void loop() {
  // The handler functions are called when usbMIDI reads data.  They
  // will not be called automatically.  You must call usbMIDI.read()
  // regularly from loop() for usbMIDI to actually read incoming
  // data and run the handler functions as messages arrive.
  usbMIDI.read();
}


void myNoteOn(byte channel, byte note, byte velocity) {
  // When using MIDIx4 or MIDIx16, usbMIDI.getCable() can be used
  // to read which of the virtual MIDI cables received this message.
  Serial.print("Note On, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
}

void myNoteOff(byte channel, byte note, byte velocity) {
  Serial.print("Note Off, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
}

void myAfterTouchPoly(byte channel, byte note, byte velocity) {
  Serial.print("AfterTouch Change, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
}

void myControlChange(byte channel, byte control, byte value) {
  Serial.print("Control Change, ch=");
  Serial.print(channel, DEC);
  Serial.print(", control=");
  Serial.print(control, DEC);
  Serial.print(", value=");
  Serial.println(value, DEC);
}

void myProgramChange(byte channel, byte program) {
  Serial.print("Program Change, ch=");
  Serial.print(channel, DEC);
  Serial.print(", program=");
  Serial.println(program, DEC);
}

void myAfterTouchChannel(byte channel, byte pressure) {
  Serial.print("After Touch, ch=");
  Serial.print(channel, DEC);
  Serial.print(", pressure=");
  Serial.println(pressure, DEC);
}

void myPitchChange(byte channel, int pitch) {
  Serial.print("Pitch Change, ch=");
  Serial.print(channel, DEC);
  Serial.print(", pitch=");
  Serial.println(pitch, DEC);
}


// This 3-input System Exclusive function is more complex, but allows you to
// process very large messages which do not fully fit within the usbMIDI's
// internal buffer.  Large messages are given to you in chunks, with the
// 3rd parameter to tell you which is the last chunk.  This function is
// a Teensy extension, not available in the Arduino MIDI library.
//
void mySystemExclusiveChunk(const byte *data, uint16_t length, bool last) {
  Serial.print("SysEx Message: ");
  printBytes(data, length);
  if (last) {
    Serial.println(" (end)");
  } else {
    Serial.println(" (to be continued)");
  }
}

// This simpler 2-input System Exclusive function can only receive messages
// up to the size of the internal buffer.  Larger messages are truncated, with
// no way to receive the data which did not fit in the buffer.  If both types
// of SysEx functions are set, the 3-input version will be called by usbMIDI.
//
void mySystemExclusive(byte *data, unsigned int length) {
  Serial.print("SysEx Message: ");
  printBytes(data, length);
  Serial.println();
}

void myTimeCodeQuarterFrame(byte data) {
  static char SMPTE[8]={'0','0','0','0','0','0','0','0'};
  static byte fps=0;
  byte index = data >> 4;
  byte number = data & 15;
  if (index == 7) {
    fps = (number >> 1) & 3;
    number = number & 1;
  }
  if (index < 8 || number < 10) {
    SMPTE[index] = number + '0';
    Serial.print("TimeCode: ");  // perhaps only print when index == 7
    Serial.print(SMPTE[7]);
    Serial.print(SMPTE[6]);
    Serial.print(':');
    Serial.print(SMPTE[5]);
    Serial.print(SMPTE[4]);
    Serial.print(':');
    Serial.print(SMPTE[3]);
    Serial.print(SMPTE[2]);
    Serial.print('.');
    Serial.print(SMPTE[1]);  // perhaps add 2 to compensate for MIDI latency?
    Serial.print(SMPTE[0]);
    switch (fps) {
      case 0: Serial.println(" 24 fps"); break;
      case 1: Serial.println(" 25 fps"); break;
      case 2: Serial.println(" 29.97 fps"); break;
      case 3: Serial.println(" 30 fps"); break;
    }
  } else {
    Serial.print("TimeCode: invalid data = ");
    Serial.println(data, HEX);
  }
}

void mySongPosition(uint16_t beats) {
  Serial.print("Song Position, beat=");
  Serial.println(beats);
}

void mySongSelect(byte songNumber) {
  Serial.print("Song Select, song=");
  Serial.println(songNumber, DEC);
}

void myTuneRequest() {
  Serial.println("Tune Request");
}

void myClock() {
  Serial.println("Clock");
}

void myStart() {
  Serial.println("Start");
}

void myContinue() {
  Serial.println("Continue");
}

void myStop() {
  Serial.println("Stop");
}

void myActiveSensing() {
  Serial.println("Actvice Sensing");
}

void mySystemReset() {
  Serial.println("System Reset");
}

void myRealTimeSystem(uint8_t realtimebyte) {
  Serial.print("Real Time Message, code=");
  Serial.println(realtimebyte, HEX);
}



void printBytes(const byte *data, unsigned int size) {
  while (size > 0) {
    byte b = *data++;
    if (b < 16) Serial.print('0');
    Serial.print(b, HEX);
    if (size > 1) Serial.print(' ');
    size = size - 1;
  }
}

