/* Temperature Sensor, Raw Numbers, Teensyduino Tutorial #4
   http://www.pjrc.com/teensy/tutorial4.html

   This example code is in the public domain.
*/

void setup()
{                
  Serial.begin(38400);
}

int val;

void loop()                     
{
  val = analogRead(1);
  Serial.print("analog 1 is: ");
  Serial.println(val);
  delay(1000);
}

