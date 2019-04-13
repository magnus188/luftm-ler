#include "dht.h"
#include <SDS011.h>
#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#define PM_TX 2
#define PM_RX 3
#define dht_apin A0

SDS011 sds;
dht DHT;
int pinCS = 53; // Pin 10 on Arduino Uno

void setup(void)
{
  sds.begin(PM_TX, PM_RX);

  // Start logging on serial port 9600
  Serial.begin(9600);

  // Initialize SD card writing
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }

  // Create CSV headers
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
  // Variables for pm2.5, pm10 and error
  float pm25, pm10;
  int error;
  do {
    error = sds.read(&pm25, &pm10);
    } while (error != 0);
  
  // Read humidity and temperature
  DHT.read11(dht_apin);

// Write data to CSV file
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
    i++;

  // Delay for 300 000ms = 5 min
  delay(300000);

}
