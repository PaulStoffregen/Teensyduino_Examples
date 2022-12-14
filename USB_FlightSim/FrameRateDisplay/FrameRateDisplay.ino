#include <DogLcd.h>

DogLcd lcd = DogLcd(10, 9, 7, 8);    // DogM LCD on pins 7, 8, 9, 10

// variables
FlightSimElapsedFrames frameCount; // increases each simulation frame
elapsedMillis milliSeconds;        // increases 1000 per second


// setup runs once, when Teensy boots.
//
void setup() {
  lcd.begin(DOG_LCD_M162);
  pinMode(LED_BUILTIN, OUTPUT);
}

// loop runs repetitively, as long as Teensy is powered up
//
void loop() {
  // receive any incoming X-Plane data (necessary for frame update)
  FlightSim.update();

  // the LED shows if X-Plane is running and plugin is enabled
  if (FlightSim.isEnabled()) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  // every 10 frames, update the display with frame rate
  if (frameCount >= 10) {
    // read the elapsed frames and elapsed time
    int frames = frameCount;
    int ms = milliSeconds;
    // reset both to zero (immediately after reading)
    milliSeconds = 0;
    frameCount = 0;
    // compute and show the frames per second
    float fps = (float)frames / (float)ms * 1000.0;
    lcd.setCursor(0, 0);
    lcd.print(fps);
    lcd.print(" fsp    ");
  }
}
