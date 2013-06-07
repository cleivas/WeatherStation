/* 
Weather Station
(c) Arduino Verkstad AB 2013
Author: Clara Leivas

This weather station reads the temperature, air humidity, wind speed
and sound pollution of the close envionment. Every fifth second a 
photo is taken and the data is saved to an micro sd Card.

For more instructions, please see
http://cuartielles.com/verkstad/edu/CoursesSummerCampZGZEs/Ballooning

*/



#include <WeatherStation.h>
#include <SD.h>

WeatherStation ws;

//Data variables
double humidity = 0;
double temperature = 0;
double windRPS = 0; //Rotations per second
int soundPollution = 0;

//Camera variables
int cameraPin = 8; 
//An LED will indicate when the camera will take a picture
int LED = 9;

//Timer varibales
long previousMillis = 0;
long currentMillis = 0;
long interval = 5000;


void setup(){
  Serial.begin(9600); //Start serial communication
  ws.begin(); //initialize the weather station sensors
    
  //Initialize SD card  
  Serial.print("Initializing SD card ... ");
  pinMode(10, OUTPUT);
  if (!SD.begin(4)) Serial.println("Card failed, or not present");
  else Serial.println("Card initialized.");
  
  //Set camera and LED pins to output
  pinMode(cameraPin, OUTPUT);
  pinMode(LED, OUTPUT); 
}

void loop(){
  
  windRPS = ws.getWindRPS(); //Read the wind speed in RPS 
  soundPollution = ws.getSoundPollution(); //read data from the microphone
  
  //Check if the HT sensor is running
  if (ws.readRHT03() == WSLIB_OK){ 
    humidity = ws.getHumidity(); //Read the humidity in %
    temperature = ws.getTemperature(); //Read the temperature in C
  }

  
  
  //Timer. After every interval, take a photo and store the weather data to the micro sd card
  currentMillis = millis();
  if(currentMillis-previousMillis > interval){ 
    //Blink LED 
    for(int i=3; i>0; i--){
      digitalWrite(LED, LOW);
      delay(200);
      digitalWrite(LED, HIGH);
      delay(200);
    }
    
    //Take a photo
    digitalWrite(cameraPin, HIGH); 
    delay(500);
    digitalWrite(cameraPin, LOW);
    
    //convert the gathered data to text
    String dataString = ws.dataToString(temperature, humidity, windRPS, soundPollution); 
    writeToSD(dataString); //Save data to "datalog.txt" on SD card
    Serial.println(dataString);
    previousMillis = millis(); // Reset timer
    digitalWrite(LED, LOW); //Turn off LED 
  }
}

//Write the string of weather data to the text file "datalog.txt"
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
