/* Buttons to USB Keyboard Example - Special Media Player Keys

   You must select Keyboard from the "Tools > USB Type" menu

   This example code is in the public domain.
*/

#include <Bounce.h>

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
Bounce button0 = Bounce(0, 10);
Bounce button1 = Bounce(1, 10);  // 10 ms debounce time is appropriate
Bounce button2 = Bounce(2, 10);  // for most mechanical pushbuttons
Bounce button3 = Bounce(3, 10);
Bounce button4 = Bounce(4, 10);  // if a button is too "sensitive" 
Bounce button5 = Bounce(5, 10);  // you can increase this time.

void setup() {
  // Configure the pins for input mode with pullup resistors.
  // The pushbuttons connect from each pin to ground.  When
  // the button is pressed, the pin reads LOW because the button
  // shorts it to ground.  When released, the pin reads HIGH
  // because the pullup resistor connects to +5 volts inside
  // the chip.
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
}

void loop() {
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  button0.update();
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  button5.update();

  // Check each button for "falling" edge.
  // falling = high (not pressed - voltage from pullup resistor)
  //           to low (pressed - button connects pin to ground)
  if (button0.fallingEdge()) {
    Keyboard.set_media(KEY_MEDIA_PREV_TRACK);
    Keyboard.send_now();	// send the button press
    Keyboard.set_media(0);
    Keyboard.send_now();	// send the button release
  }
  if (button1.fallingEdge()) {
    Keyboard.set_media(KEY_MEDIA_PLAY_PAUSE);
    Keyboard.send_now();
    Keyboard.set_media(0);
    Keyboard.send_now();
  }
  if (button2.fallingEdge()) {
    Keyboard.set_media(KEY_MEDIA_NEXT_TRACK);
    Keyboard.send_now();
    Keyboard.set_media(0);
    Keyboard.send_now();
  }
  if (button3.fallingEdge()) {
    Keyboard.set_media(KEY_MEDIA_VOLUME_DEC);
    Keyboard.send_now();
    Keyboard.set_media(0);
    Keyboard.send_now();
  }
  if (button4.fallingEdge()) {
    Keyboard.set_media(KEY_MEDIA_VOLUME_INC);
    Keyboard.send_now();
    Keyboard.set_media(0);
    Keyboard.send_now();
  }
  if (button5.fallingEdge()) {
    Keyboard.set_media(KEY_MEDIA_EJECT);
    Keyboard.send_now();
    delay(300);  // Mac OS-X will not recognize a very short eject press
    Keyboard.set_media(0);
    Keyboard.send_now();
  }

}

