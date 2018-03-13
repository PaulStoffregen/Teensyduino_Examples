/* Buttons to USB Mouse Example

   You must select Mouse from the "Tools > USB Type" menu

   This example code is in the public domain.
*/

#include <Bounce.h>

const int moveDistance = 5;  // how much to move the mouse on each button press

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.

// Five buttons to control the 5 mouse clicks
Bounce button2 = Bounce(2, 10);
Bounce button3 = Bounce(3, 10);  // if a button is too "sensitive"
Bounce button4 = Bounce(4, 10);  // to rapid touch, you can
Bounce button5 = Bounce(5, 10);  // increase this time.
Bounce button6 = Bounce(6, 10);

// Four more buttons to move the mouse
Bounce button7 = Bounce(7, 10);
Bounce button8 = Bounce(8, 10);
Bounce button9 = Bounce(9, 10);
Bounce button10 = Bounce(10, 10);

// And still more buttons for the scroll wheel
Bounce button14 = Bounce(14, 10);
Bounce button15 = Bounce(15, 10);
Bounce button16 = Bounce(16, 10);
Bounce button17 = Bounce(17, 10);

// Even more buttons to jump the mouse to a fixed coordinate
Bounce button21 = Bounce(21, 10);
Bounce button22 = Bounce(22, 10);
Bounce button23 = Bounce(23, 10);

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
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);

  // If your screen is a different size, edit this to set the size.
  // Even if the size does not match, mouse.moveTo(x, y) will still
  // work, but the results will be scaled as if the x,y coordinate
  // was on this screen.  Setting the correct screen size allows you
  // to use the actual pixel coordinates of your screen.
  Mouse.screenSize(1920, 1080);
  // screenSize() is not supported on Teensy 2.0 & Teensy++ 2.0.
  // Delete this line to run on 8 bit Teensy boards.
}


void loop() {
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  button2.update();
  button3.update();
  button4.update();
  button5.update();
  button6.update();
  button7.update();
  button8.update();
  button9.update();
  button10.update();
  button14.update();
  button15.update();
  button16.update();
  button17.update();
  button21.update();
  button22.update();
  button23.update();

  // Check each input for "falling" edge.  Normally the pin is high
  // due to the INPUT_PULLUP.  It goes "falling" to low when your
  // connect connects the pin to GND.

  if (button7.fallingEdge()) {
    Mouse.move(-moveDistance, 0); // move Left
  }
  if (button8.fallingEdge()) {
    Mouse.move(moveDistance, 0);  // move Right
  }
  if (button9.fallingEdge()) {
    Mouse.move(0, -moveDistance); // move Up
  }
  if (button10.fallingEdge()) {
    Mouse.move(0, moveDistance);  // move Down
  }

  if (button14.fallingEdge()) {
    Mouse.scroll(1);  // scroll wheel Up
  }
  if (button15.fallingEdge()) {
    Mouse.scroll(-1);   // scroll wheel Down
  }
  if (button16.fallingEdge()) {
    Mouse.scroll(0, 1);  // scroll horizontal right
  }
  if (button17.fallingEdge()) {
    Mouse.scroll(0, -1);  // scroll horizontal left
  }

  if (button21.fallingEdge()) {
    Mouse.moveTo(10, 10);  // move near upper left corner (Apple menu)
    // moveTo() is not supported on Teensy 2.0 & Teensy++ 2.0.
    // Delete this line to run on 8 bit Teensy boards.
  }
  if (button22.fallingEdge()) {
    Mouse.moveTo(960, 540);   // move to the screen center
  }
  if (button23.fallingEdge()) {
    Mouse.moveTo(24, 1066);  // move near lower left corner (Windows Start menu)
  }

  // For the mouse buttons, we must detect both the falling and rising edges,
  // to press the mouse button when the button on our digital pin is pressed,
  // and to later release it when the physical button releases (the pin rises
  // from low back to high, thanks to INPUT_PULLUP).

  if (button2.fallingEdge()) {
    Mouse.press(MOUSE_LEFT);
  }
  if (button2.risingEdge()) {
    Mouse.release(MOUSE_LEFT);
  }
  if (button3.fallingEdge()) {
    Mouse.press(MOUSE_MIDDLE);
  }
  if (button3.risingEdge()) {
    Mouse.release(MOUSE_MIDDLE);
  }
  if (button4.fallingEdge()) {
    Mouse.press(MOUSE_RIGHT);
  }
  if (button4.risingEdge()) {
    Mouse.release(MOUSE_RIGHT);
  }
  if (button5.fallingEdge()) {
    Mouse.press(MOUSE_BACK);
  }
  if (button5.risingEdge()) {
    Mouse.release(MOUSE_BACK);
  }
  if (button6.fallingEdge()) {
    Mouse.press(MOUSE_FORWARD);
  }
  if (button6.risingEdge()) {
    Mouse.release(MOUSE_FORWARD);
  }





}

