/* Use MTP to share Teensy's SD card with your computer

   You must select MTP from the "Tools > USB Type" menu

   This example code is in the public domain.
*/

#include <SD.h>

// Edit chipSelect for the way your SD card connects
//  Teensy audio board: pin 10
//  Teensy 3.5 & 3.6 & 4.1 on-board: BUILTIN_SDCARD
const int chipSelect = 10;

void setup() {
  Serial.begin(9600);
  MTP.begin();
  SD.begin(chipSelect);
  // Even if SD.begin() fails, you can still add it to MTP.
  // MTP will treat SD as removable media, periodically
  // monitoring whether a SD card has been inserted.
  MTP.addFilesystem(SD, "SD Card");
}

void loop() {
  MTP.loop(); // Perform media access when PC wants access
}
