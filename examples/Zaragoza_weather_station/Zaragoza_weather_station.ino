// Weather Station
//
//
//
//
// (c) Arduino Verkstad AB 2013
// Author: Clara Leivas
//



#include <WeatherStation.h>
#include <SD.h>

WeatherStation ws;

double humidity = 0;
double temperature = 0;
int windRotTime = 0;

int cameraPin = 8;

void setup(){
  Serial.begin(9600);
  ws.begin(); //initialize the weather station sensors
    
  Serial.print("Initializing SD card ... ");
  pinMode(10, OUTPUT);
  if (!SD.begin(4)) Serial.println("Card failed, or not present");
  else Serial.println("Card initialized.");
  
  pinMode(cameraPin, OUTPUT);
}

void loop(){
  
  windRotTime = ws.getWindRotationTime(); 
   
  if (ws.readRTH() == WSLIB_OK){
    humidity = ws.getHumidity();
    temperature = ws.getTemperature();
  }
  else Serial.println("Error");

  
  
  digitalWrite(cameraPin, HIGH); //Take a photo
  delay(300);
  digitalWrite(cameraPin, LOW);
  
  String dataString = ws.dataToString(temperature, humidity, windRotTime); //convert the gathered data to text
  writeToSD(dataString); //Save data to "datalog.txt" on SD card
  Serial.println(dataString);
  
  Serial.println("Wait 30 seconds");
  delay(30000); 
}



void writeToSD(String data){
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }    
}
