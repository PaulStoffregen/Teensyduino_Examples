/* Buttons to USB Mouse Example

   You must select Mouse from the "Tools > USB Type" menu

   This example code is in the public domain.
*/

#include <Bounce.h>

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
Bounce button3 = Bounce(3, 10);  // if a button is too "sensitive"
Bounce button4 = Bounce(4, 10);  // to rapid touch, you can
Bounce button5 = Bounce(5, 10);  // increase this time.

byte left=0;
byte middle=0;
byte right=0;

void setup() {
  // Configure the pins for input mode with pullup resistors.
  // The pushbuttons connect from each pin to ground.  When
  // the button is pressed, the pin reads LOW because the button
  // shorts it to ground.  When released, the pin reads HIGH
  // because the pullup resistor connects to +5 volts inside
  // the chip.  LOW for "on", and HIGH for "off" may seem
  // backwards, but using the on-chip pullup resistors is very
  // convenient.  The scheme is called "active low", and it's
  // very commonly used in electronics... so much that the chip
  // has built-in pullup resistors!
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
}


void loop() {
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  button3.update();
  button4.update();
  button5.update();

  // this variable will let us know if any button changes
  byte anyChange = 0;

  // Check each button for "falling" edge.
  // Change a mouse button when each button presses
  // Update the Joystick buttons only upon changes.
  // falling = high (not pressed - voltage from pullup resistor)
  //           to low (pressed - button connects pin to ground)
  if (button3.fallingEdge()) {
    left = 1;
    anyChange = 1;
  }
  if (button4.fallingEdge()) {
    middle = 1;
    anyChange = 1;
  }
  if (button5.fallingEdge()) {
    right = 1;
    anyChange = 1;
  }

  // Check each button for "rising" edge
  // Change a mouse button when each button releases.
  // For many types of projects, you only care when the button
  // is pressed and the release isn't needed.
  // rising = low (pressed - button connects pin to ground)
  //          to high (not pressed - voltage from pullup resistor)
  if (button3.risingEdge()) {
    left = 0;
    anyChange = 1;
  }
  if (button4.risingEdge()) {
    middle = 0;
    anyChange = 1;
  }
  if (button5.risingEdge()) {
    right = 0;
    anyChange = 1;
  }

  // if any changes were made, update the Mouse buttons
  if (anyChange) {
    Mouse.set_buttons(left, middle, right);
  }
}

