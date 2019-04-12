#include "dht.h"
#include <SDS011.h>
#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>


#define PM_TX 2
#define PM_RX 3
#define dht_apin A0

SDS011 sds;
int pinCS = 53; // Pin 10 on Arduino Uno
dht DHT;

void setup(void)
{
  sds.begin(PM_TX, PM_RX);
  Serial.begin(9600);
  
  
//  delay(500);//Delay to let system boot
//  delay(1000);//Wait before accessing Sensor

  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }

  File logFile = SD.open("logs.csv", FILE_WRITE); 
  if (logFile){
    String header = "Iteration, Temp., Humidity, PM2.5, PM10";
    logFile.println(header);
    logFile.close();
  }else {
    Serial.println("Couldn't open log file");
  }
 
}
int i = 1;
void loop(void)
{ 
  float pm25, pm10;
  int error;
  do {
    error = sds.read(&pm25, &pm10);
    } while (error != 0);
  
  DHT.read11(dht_apin);

File logFile = SD.open("logs.csv", FILE_WRITE); 
  if (logFile){
    logFile.print(i);
    logFile.print(",");
    logFile.print(DHT.temperature);
    logFile.print(",");
    logFile.print(DHT.humidity);
    logFile.print(",");
    logFile.print(pm25);
    logFile.print(",");
    logFile.println(pm10);
    logFile.close();
  }else {
    Serial.println("Couldn't open log file");
  }
    Serial.print(i);
    Serial.print(",");
    Serial.print(DHT.temperature);
    Serial.print(",");
    Serial.print(DHT.humidity);
    Serial.print(",");
    Serial.print(pm25);
    Serial.print(",");
    Serial.println(pm10);

    i++;
  delay(300000);

}
