/* USB Touchscreen, Ten Finger Circle Example

   When a button is pressed, Teensy sends a sequence of
   touchscreen presses for 10 fingers simultaneously
   drawing ten 36 degree arcs, which form a circle.

   This example is meant to test whether your computer
   can properly handle multi-touch with 10 simultaneous
   points.  If you encounter problems, please run the
   simpler SingleFingerLine example.

   A pushbutton needs to be connected between pin 14 and GND.
   Or a wire or paperclip may be touched between GND and pin
   14 to start the drawing.

   To see the result, open this page with Goolge Chrome:
   http://www.repaa.net/draw.html

   After pressing the button 5 times, you should see this:
   https://forum.pjrc.com/attachment.php?attachmentid=12750&d=1516978091

   This example has been tested on Windows 10 and Ubuntu 14.04.
   Macintosh High Sierra 10.13.2 does not work, and also does not
   respond properly to a Dell P2314T touch-enabled monitor.

   You must select Touch Screen in the "Tools > USB Type" menu

   This example code is in the public domain.
*/

#include <Bounce.h>

Bounce mybutton = Bounce(14, 10);
int yoffset = 8000;

void setup() {
  pinMode(14, INPUT_PULLUP);
  TouchscreenUSB.begin();
}

void drawcircle(int x, int y) {
  float arc = 2.0 * PI / 10.0;
  float r = 3000.0;
  for (float angle=0; angle < arc; angle += 0.01) {
    for (int i=0; i < 10; i++) {
      float ph = arc * (float)i;
      TouchscreenUSB.press(i, r * cosf(angle+ph) + x, r * sinf(angle+ph) + y);
    }
    delay(10);
  }
  for (int i=0; i < 10; i++) {
    TouchscreenUSB.release(i);
  }
}

void loop() {
  mybutton.update();
  if (mybutton.fallingEdge()) {
    Serial.println("press");
    drawcircle(16000, yoffset);
    yoffset += 4200;
    if (yoffset > 24000) yoffset = 8000;
  }
}


