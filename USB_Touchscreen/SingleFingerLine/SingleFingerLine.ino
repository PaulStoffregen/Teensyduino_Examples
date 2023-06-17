/* USB Touchscreen, Single Finger Line Example

   When a button is pressed, Teensy sends a sequence of
   touchscreen presses which draw diagonal line with a
   slight downward slope.

   A pushbutton needs to be connected between pin 14 and GND.
   Or a wire or paperclip may be touched between GND and pin
   14 to start the drawing.

   To see the result, open this page with Google Chrome:
   http://www.repaa.net/draw.html

   Alternate test site if repaa.net is down:
   https://naqtn.github.io/WBBMTT/
   (Thanks to PaulS on the forum for this tip)
   https://forum.pjrc.com/threads/71464?p=315652&viewfull=1#post315652

   After pressing the button 14 times, you should see this:
   https://forum.pjrc.com/attachment.php?attachmentid=12748&d=1516976598

   You must select Touch Screen in the "Tools > USB Type" menu

   This example code is in the public domain.
*/

#include <Bounce.h>

Bounce mybutton = Bounce(14, 10);
int yoffset = 4000;

void setup() {
  pinMode(14, INPUT_PULLUP);
  TouchscreenUSB.begin();
}

void drawline(int x, int y) {
 for (int i=0; i < 6000; i += 100) {
   TouchscreenUSB.press(0, x + i, y + i/13);
   delay(10);
 }
 TouchscreenUSB.release(0);
}

void loop() {
  mybutton.update();
  if (mybutton.fallingEdge()) {
    Serial.println("press");
    drawline(16000, yoffset);
    yoffset += 1200;
    if (yoffset > 24000) yoffset = 4000;
  }
}
