/* RGB Analog Example, Teensyduino Tutorial #2
   http://www.pjrc.com/teensy/tutorial2.html

   This example code is in the public domain.
*/

const int redPin =  12;
const int greenPin =  15;
const int bluePin =  14;

void setup()   {                
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()                     
{
  analogWrite(redPin, 30);
  delay(500);
  analogWrite(greenPin, 200);
  delay(500);
  analogWrite(bluePin, 40);
  delay(500);
  analogWrite(redPin, 150);
  delay(500);
  analogWrite(greenPin, 0);
  delay(500);
  analogWrite(bluePin, 250);
  delay(500);
}

