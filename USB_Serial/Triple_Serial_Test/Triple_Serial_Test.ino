

void setup() {
	Serial1.begin(115200);
  delay(800);
  send_to_all("Triple Serial Test", 0);
} 

void loop() {
	if (Serial.available() > 0) {
    send_to_all("Main Serial", Serial.read());
	}
	if (Serial1.available() > 0) {
    send_to_all("Hardware Serial", Serial1.read());
	}
#if defined(USB_DUAL_SERIAL) || defined(USB_TRIPLE_SERIAL)
  if (SerialUSB1.available() > 0) {
    send_to_all("Serial USB1", SerialUSB1.read());
  }
#endif
#if defined(USB_TRIPLE_SERIAL)
  if (SerialUSB2.available() > 0) {
    send_to_all("Serial USB2", SerialUSB2.read());
  }
#endif
}

void send_to_all(const char *name, int c)
{
  char buf[128];

  if (c) {
    snprintf(buf, sizeof(buf), "%s received: %u\r\n", name, c);
  } else {
    snprintf(buf, sizeof(buf), "%s\r\n", name);
  }
  Serial.print(buf);
  Serial1.print(buf);
#ifdef USB_DUAL_SERIAL
  SerialUSB1.print(buf);
#endif
#ifdef USB_TRIPLE_SERIAL
  SerialUSB1.print(buf);
  SerialUSB2.print(buf);
#endif
  
}
