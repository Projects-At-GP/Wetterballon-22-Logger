#include <SD.h>

#define PIN_SD_SS 4

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(PIN_SD_SS)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  SD.remove("log.csv");
  
  File file = SD.open("log.csv", FILE_WRITE);
  Serial.println("file's there");

  if (file)
  {
    file.println("Hi, Bitch!");
    file.close();
    Serial.println("Done!");
  }
}

void loop() {}
