#include <Arduino.h>
#include <SoftwareSerial.h>
#include <QMC5883LCompass.h>
#include <TinyGPS++.h>
#include <TimeLib.h>
#include <SD.h>
#include <SPI.h>
#define time_offset 32400
void smartDelay(unsigned long ms);
QMC5883LCompass compass;
TinyGPSPlus  tinyGPS;
SoftwareSerial gps(8, 3);
File myFile;
bool Start = true;
void setup()
{
  gps.begin(9600);
  compass.init();
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println(F("Card failed, or not present"));
    while(1);
  }
  Serial.println(F("ok."));

  delay(100);
}
void loop()
{
  setTime(tinyGPS.time.hour(), tinyGPS.time.minute(), tinyGPS.time.second(), tinyGPS.date.day(), tinyGPS.date.month(), tinyGPS.date.year());
  adjustTime(time_offset);   //JST変換
  File dataFile = SD.open("DATALOG.txt", FILE_WRITE);
  if(dataFile){
    if(Start)
    {
      //dataFile.println("Time,latitude,longitude,Wind");
      Start = false;
    }else{
      dataFile.print(year());dataFile.print("/");
      dataFile.print(month());dataFile.print("/");
      dataFile.print(day());dataFile.print("(");
      dataFile.print(hour());dataFile.print(":");
      dataFile.print(minute());dataFile.print(":");
      dataFile.print(second());dataFile.print(")");
      dataFile.print(",");
      dataFile.print(tinyGPS.location.lat(),6);dataFile.print(",");
      dataFile.print(tinyGPS.location.lng(),6);dataFile.print(",");
      dataFile.println(GetAzmus());
      Serial.println(GetAzmus());
      dataFile.println();
      Serial.println("done");
    }
  }else{
    //datalog.txt を開くことができなければエラーを表示する
    Serial.println(F("error opening datalog.txt"));
  }
  //ファイルを閉じる
  dataFile.close();
  smartDelay(1000);
}
int GetAzmus()
{
  compass.read();
  return compass.getAzimuth();
}
void smartDelay(unsigned long ms){
    unsigned long start = millis();
    do{
        while(gps.available())
            tinyGPS.encode(gps.read());
    }while(millis()-start<ms);
}
