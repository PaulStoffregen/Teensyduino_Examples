/* Simple USB Keyboard Example
   Teensy becomes a USB keyboard and types characters

   You must select Keyboard from the "Tools > USB Type" menu

   This example code is in the public domain.
*/

int count = 0;

void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  // Your computer will receive these characters from a USB keyboard.
  Keyboard.print("Hello World "); 
  Keyboard.println(count);

  // You can also send to the Arduino Serial Monitor
  Serial.println(count);

  // increment the count
  count = count + 1;

  // typing too rapidly can overwhelm a PC
  delay(5000);
}
