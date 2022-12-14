#include <Servo.h>

Servo motor;                      // an RC Servo motor
FlightSimFloat throttle;          // access to X-Plane's throttle
const int motorPin = 2;
const int potentiometerPin = A0;  // Analog 0: Teensy = 23, T++ = 38
int previousAnalog = -100;

// setup runs once, when Teensy boots.
//
void setup() {
  motor.attach(motorPin);
  throttle = XPlaneRef("sim/flightmodel/engine/ENGN_thro[0]");
  throttle.onChange(viewThrottle);
  Serial.begin(9600);
  Serial.println("Throttle Demo");
}

// loop runs repetitively, as long as Teensy is powered up
//
void loop() {
  // normally the first step in loop() should update from X-Plane
  FlightSim.update();

  // when human motion chances the port, change throttle
  int analog = analogRead(potentiometerPin);
  
  // "more than 6" allows for some noise
  if (analog < previousAnalog - 6 || analog > previousAnalog + 6) {
    throttle = analog / 1023.0;
    previousAnalog = analog;
    int angle = throttle * 70.0 + 30.0;
    motor.write(angle);
    Serial.print("(Analog)  Throttle = ");
    Serial.println(throttle);
  }
}

// When X-Plane changes the throttle....
//
void viewThrottle(float val)
{
  int angle = val * 70.0 + 30.0;
  motor.write(angle);
  Serial.print("(X-Plane) Throttle = ");
  Serial.println(throttle);
}
