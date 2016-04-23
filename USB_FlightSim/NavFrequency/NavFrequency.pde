#include <Bounce.h>
#include <Encoder.h>
#include <DogLcd.h>

// hardware objects, for accessing the buttons, rotary encoder and LCD
//
Bounce buttonUp = Bounce(3, 5);      // Pushbutton on pin 3, 5ms debounce
Bounce buttonDown = Bounce(4, 5);    // Pushbutton on pin 4, 5ms debounce
Encoder wheel = Encoder(5, 6);       // Rotary Encoder on pin 5 and 6
DogLcd lcd = DogLcd(10, 9, 7, 8);    // DogM LCD on pins 7, 8, 9, 10

// X-Plane objects, 3 command refs and 1 data ref
FlightSimCommand NavCoarseUp;
FlightSimCommand NavCoarseDown;
FlightSimCommand NavFineUp;
FlightSimInteger NavFrequencyHz;

// variables
long encoder_prev=0;    // for detecting rotary position change
elapsedMillis inactivityTimeout;// an inactivity timeout


// setup runs once, when Teensy boots.
//
void setup() {
  // initialize all hardware
  pinMode(3, INPUT_PULLUP);  // input pullup mode allows connecting
  pinMode(4, INPUT_PULLUP);  // buttons and switches from the pins
  pinMode(5, INPUT_PULLUP);  // to ground, and the chip provide the
  pinMode(6, INPUT_PULLUP);  // required pullup resistor :-)
  lcd.begin(DOG_LCD_M162);
  lcd.print("nav1:");

  // configure the X-Plane variables
  NavCoarseUp = XPlaneRef("sim/radios/actv_nav1_coarse_up");
  NavCoarseDown = XPlaneRef("sim/radios/actv_nav1_coarse_down");
  NavFineUp = XPlaneRef("sim/radios/actv_nav1_fine_up");
  NavFrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/nav1_frequency_hz");
  NavFrequencyHz.onChange(update_lcd);  // update the LCD when X-Plane changes
}

// loop runs repetitively, as long as Teensy is powered up
//
void loop() {
  // normally the first step in loop() should update from X-Plane
  FlightSim.update();

  // read the rotary encoder, if it's changed, write to NavFrequencyHz
  long enc = wheel.read();
  if (enc != encoder_prev) {
    NavFrequencyHz = NavFrequencyHz + (enc - encoder_prev);
    encoder_prev = enc;
    update_lcd(NavFrequencyHz);
    inactivityTimeout = 0;   // reset the inactivity timeout
  }

  // read the pushbuttons, and send X-Plane commands when they're pressed
  buttonUp.update();
  buttonDown.update();
  if (buttonUp.fallingEdge()) {
    NavCoarseUp = 1;
    inactivityTimeout = 0;
  }
  if (buttonUp.risingEdge()) {
    NavCoarseUp = 0;
  }
  if (buttonDown.fallingEdge()) {
    NavCoarseDown = 1;
    inactivityTimeout = 0;
  }
  if (buttonDown.risingEdge()) {
    NavCoarseDown = 0;
  }

  // if there's no user activity for 2 seconds, send the NavFineUp.
  // admittedly this is not very useful, but it's meant to demonstrate
  // possibility of automated actions in addition to driving everything
  // directly from physical user inputs.
  if (inactivityTimeout > 2000) {
    NavFineUp.once();
    inactivityTimeout = 0;
  }
}

// write a number onto the LCD, first row, starting at 6th column
void update_lcd(long val)
{
  lcd.setCursor(6, 0);
  lcd.print(val);
  lcd.print("  ");
}
