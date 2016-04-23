/* USB to Serial - Teensy becomes a USB to Serial converter
   http://dorkbotpdx.org/blog/paul/teensy_as_benito_at_57600_baud

   You must select Serial from the "Tools > USB Type" menu

   This example code is in the public domain.
*/

// set this to the hardware serial port you wish to use
#define HWSERIAL Serial1

unsigned long baud = 19200;
const int reset_pin = 4;
const int led_pin = 13;  // 13 = Teensy 3.X & LC
                         // 11 = Teensy 2.0
                         //  6 = Teensy++ 2.0
void setup()
{
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  digitalWrite(reset_pin, HIGH);
  pinMode(reset_pin, OUTPUT);
  Serial.begin(baud);	// USB, communication to PC or Mac
  HWSERIAL.begin(baud);	// communication to hardware serial
}

long led_on_time=0;
byte buffer[80];
unsigned char prev_dtr = 0;

void loop()
{
  unsigned char dtr;
  int rd, wr, n;

  // check if any data has arrived on the USB virtual serial port
  rd = Serial.available();
  if (rd > 0) {
    // check if the hardware serial port is ready to transmit
    wr = HWSERIAL.availableForWrite();
    if (wr > 0) {
      // compute how much data to move, the smallest
      // of rd, wr and the buffer size
      if (rd > wr) rd = wr;
      if (rd > 80) rd = 80;
      // read data from the USB port
      n = Serial.readBytes((char *)buffer, rd);
      // write it to the hardware serial port
      HWSERIAL.write(buffer, n);
      // turn on the LED to indicate activity
      digitalWrite(led_pin, HIGH);
      led_on_time = millis();
    }
  }

  // check if any data has arrived on the hardware serial port
  rd = HWSERIAL.available();
  if (rd > 0) {
    // check if the USB virtual serial port is ready to transmit
    wr = Serial.availableForWrite();
    if (wr > 0) {
      // compute how much data to move, the smallest
      // of rd, wr and the buffer size
      if (rd > wr) rd = wr;
      if (rd > 80) rd = 80;
      // read data from the hardware serial port
      n = HWSERIAL.readBytes((char *)buffer, rd);
      // write it to the USB port
      Serial.write(buffer, n);
      // turn on the LED to indicate activity
      digitalWrite(led_pin, HIGH);
      led_on_time = millis();
    }
  }

  // check if the USB virtual serial port has raised DTR
  dtr = Serial.dtr();
  if (dtr && !prev_dtr) {
    digitalWrite(reset_pin, LOW);
    delayMicroseconds(250);
    digitalWrite(reset_pin, HIGH);
  }
  prev_dtr = dtr;

  // if the LED has been left on without more activity, turn it off
  if (millis() - led_on_time > 3) {
    digitalWrite(led_pin, LOW);
  }

  // check if the USB virtual serial wants a new baud rate
  if (Serial.baud() != baud) {
    baud = Serial.baud();
    if (baud == 57600) {
      // This ugly hack is necessary for talking
      // to the arduino bootloader, which actually
      // communicates at 58824 baud (+2.1% error).
      // Teensyduino will configure the UART for
      // the closest baud rate, which is 57143
      // baud (-0.8% error).  Serial communication
      // can tolerate about 2.5% error, so the
      // combined error is too large.  Simply
      // setting the baud rate to the same as
      // arduino's actual baud rate works.
      HWSERIAL.begin(58824);
    } else {
      HWSERIAL.begin(baud);
    }
  }
}

