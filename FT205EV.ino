/*
  VCC -> 5V
  GND -> Gnd
  CS -> 8
  DI -> 11
  SCK -> 13
  DO ->12
  CD -> 9
*/

#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;
char windSpeed[11] = {'$','0','1','W','V','?','*','/','/','\r','\n'};
char temp[11] = {'$','0','1','A','T','?','*','/','/','\r','\n'};
String reply;
Sd2Card card;
const int chipSelect = 8;
char fileName[] = "T.txt"; //All caps required
void setup() {
  Serial.begin(9600);
  // Open serial communications and wait for port to open:
  while (!Serial);
  // wait for Serial Monitor to connect. Needed for native USB port boards only:
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  Serial.print("Initializing SD card...");
  //pinMode(10,OUTPUT);
  //digitalWrite(9,HIGH);
  //pinMode(8,OUTPUT);
  //digitalWrite(8,HIGH);

  if (!SD.begin(SPI_HALF_SPEED, chipSelect)) {
    pinMode(13,INPUT);

    Serial.println("initialization failed. Things to check:");

    Serial.println("1. is a card inserted?");

    Serial.println("2. is your sodering good");

    Serial.println("3. did you change the chipSelect pin to match your shield or module?");

    Serial.println("Note: press reset or reopen this serial monitor after fixing your issue!");

    while (1);

  }
  pinMode(13,OUTPUT);
  Serial.println("initialization done.");
}

void loop() {
  pinMode(10,OUTPUT);

  // open the file. note that only one file can be open at a time,

  // so you have to close this one before opening another.

  File dataFile = SD.open(fileName, FILE_WRITE);


  // if the file is available, write to it:

  if (dataFile) {
    pinMode(13,INPUT);
    pinMode(13,OUTPUT);
    DateTime now = rtc.now();
    dataFile.print(now.year(), DEC);
    dataFile.print('/');
    dataFile.print(now.month(), DEC);
    dataFile.print('/');
    dataFile.print(now.day(), DEC);
    dataFile.print(' ');
    dataFile.print(now.hour() - 7, DEC);
    dataFile.print(':');
    dataFile.print(now.minute(), DEC);
    dataFile.print(':');
    dataFile.print(now.second(), DEC);
    dataFile.print(' ');
    
    Serial.print(windSpeed);
    if (Serial.available()) {
      reply = Serial.readStringUntil("\n");  //reads reply from sensor until EOL symbol. Type=String
      dataFile.print(reply);
    }
    
    dataFile.print(' ');
    
    Serial.print(temp);
    if (Serial.available()) {
      reply = Serial.readStringUntil("\n");  //reads reply from sensor until EOL symbol. Type=String
      dataFile.print(reply);
    }
    
    dataFile.println();
    dataFile.close();
  }

  // if the file isn't open, pop up an error:

  else {

    pinMode(13,OUTPUT);

  }
  delay(3000);
}

