/* USB Keyboard Layout Test

   You must select Keyboard from the "Tools > USB Type" menu

   Select the the correct layout from "Tools > Keyboard Layout"

   If you discover incorrect results for your country's layout,
   please email Paul Stoffregen <paul@pjrc.com> with the results
   of this test and an explanation of which keys are wrong.  If
   your layout is not available, please find the layout which
   is closest, and email Paul Stoffregen.
*/

const int ledPin = 6;   // Teensy 2.0 = Pin 11, Teensy++ 2.0 = Pin 6

void setup() {
  Serial.begin(9600);

  // Blink the LED for 10 seconds, to give time to open 
  // a word processor or text editor to receive the test
  pinMode(ledPin, OUTPUT);
  for (int i=0; i < 10; i++) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }

  // Type all possible characters.  Many countries do not use all
  // characters.  Unsupported characters will be skipped
  //
  Keyboard.println("Teensy USB Keyboard Layout Test");
  delay(100);
  Keyboard.println("Lowercase:  abcdefghijklmnopqrstuvwxyz");
  delay(100);
  Keyboard.println("Uppercase:  ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  delay(100);
  Keyboard.println("Numbers:    0123456789");
  delay(100);
  Keyboard.println("Symbols1:   !\"#$%&'()*+,-./");
  delay(100);
  Keyboard.println("Symbols2:   :;<=>?[\\]^_`{|}~");
  delay(100);
  Keyboard.println("Symbols3:   ¡¢£¤¥¦§¨©ª«¬­®¯°±");
  delay(100);
  Keyboard.println("Symbols4:   ²³´µ¶·¸¹º»¼½¾¿×÷");
  delay(100);
  Keyboard.println("Grave:      ÀÈÌÒÙàèìòù");
  delay(100);
  Keyboard.println("Acute:      ÁÉÍÓÚÝáéíóúý");
  delay(100);
  Keyboard.println("Circumflex: ÂÊÎÔÛâêîôû");
  delay(100);
  Keyboard.println("Tilde:      ÃÑÕãñõ");
  delay(100);
  Keyboard.println("Diaeresis:  ÄËÏÖÜäëïöüÿ");
  delay(100);
  Keyboard.println("Cedilla:    Çç");
  delay(100);
  Keyboard.println("Ring Above: Åå");
  delay(100);
  Keyboard.println("AE:         Ææ");
  delay(100);
  Keyboard.println("Thorn:      Þþ");
  delay(100);
  Keyboard.println("Sharp S:    ß");
  delay(100);
  Keyboard.println("O-Stroke:   Øø");
  delay(100);
  Keyboard.println("Eth:        Ðð");
  delay(100);
  Keyboard.println("Euro:       €");
}

void loop() {
  // Do nothing after the test
}
