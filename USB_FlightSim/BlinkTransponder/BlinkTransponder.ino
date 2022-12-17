// Special variable to access the transponder light
FlightSimInteger transponderLight;

// setup runs once
void setup() {
  transponderLight = XPlaneRef("sim/cockpit/radios/transponder_light");
  transponderLight.onChange(updateLED);
  pinMode(LED_BUILTIN, OUTPUT);  // pin 11 on Teensy 2.0, pin 6 on Teensy++ 2.0
}

// loop runs repetitively, as long as power is on
void loop() {
  FlightSim.update(); // causes X-Plane's changes to be received
}

// updateLED runs only when X-Plane changes transponderLight
void updateLED(long value) {
  if (value == 0) {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

