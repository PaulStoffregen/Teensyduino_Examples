/* Temperature Sensor, Simple Scaling, Teensyduino Tutorial #4
   http://www.pjrc.com/teensy/tutorial4.html

   This example code is in the public domain.
*/

void setup()
{                
  Serial.begin(38400);
}

float code;
float celsius;
float fahrenheit;

void loop()                     
{
  code = analogRead(1);
  celsius = 25 + (code - 512) / 11.3;
  fahrenheit = celsius * 1.8 + 32;
  Serial.print("temperature: ");
  Serial.print(celsius);
  Serial.print(" Celsius, ");
  Serial.print(fahrenheit);
  Serial.println(" Fahrenheit");
  delay(1000);
}

