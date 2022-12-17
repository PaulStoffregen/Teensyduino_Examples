 /* Basic Raw HID Example
   Teensy can send/receive 64 byte packets with a
   dedicated program running on a PC or Mac.

   You must select Raw HID from the "Tools > USB Type" menu

   Optional: LEDs should be connected to pins 0-7,
   and analog signals to the analog inputs.

   This example code is in the public domain.
*/


void setup() {
  Serial.begin(9600);
  Serial.println(F("RawHID Example"));
  for (int i=0; i<7; i++) {
    pinMode(i, OUTPUT);
  }
}

// RawHID packets are always 64 bytes
byte buffer[64];
elapsedMillis msUntilNextSend;
unsigned int packetCount = 0;

void loop() {
  int n;
  n = RawHID.recv(buffer, 0); // 0 timeout = do not wait
  if (n > 0) {
    // the computer sent a message.  Display the bits
    // of the first byte on pin 0 to 7.  Ignore the
    // other 63 bytes!
    Serial.print(F("Received packet, first byte: "));
    Serial.println((int)buffer[0]);
    for (int i=0; i<8; i++) {
      int b = buffer[0] & (1 << i);
      digitalWrite(i, b);
    }
  }
  // every 2 seconds, send a packet to the computer
  if (msUntilNextSend > 2000) {
    msUntilNextSend = msUntilNextSend - 2000;
    // first 2 bytes are a signature
    buffer[0] = 0xAB;
    buffer[1] = 0xCD;
    // next 24 bytes are analog measurements
    for (int i=0; i<12; i++) {
      int val = analogRead(i);
      buffer[i * 2 + 2] = highByte(val);
      buffer[i * 2 + 3] = lowByte(val);
    }
    // fill the rest with zeros
    for (int i=26; i<62; i++) {
      buffer[i] = 0;
    }
    // and put a count of packets sent at the end
    buffer[62] = highByte(packetCount);
    buffer[63] = lowByte(packetCount);
    // actually send the packet
    n = RawHID.send(buffer, 100);
    if (n > 0) {
      Serial.print(F("Transmit packet "));
      Serial.println(packetCount);
      packetCount = packetCount + 1;
    } else {
      Serial.println(F("Unable to transmit packet"));
    }
  }
}
