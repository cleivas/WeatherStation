/*
  Test the RHT03 humidity and temperature sensor
  
  Upload the code and open the serial monitor. If the sensors
  is connected correctly the air humidiry and temperature will
  be printed to the serial monitor. If you get an "Error" message, 
  check the connections again:
  http://cuartielles.com/verkstad/edu/CoursesSummerCampZGZEs/Ballooning
  
 */


#include <WeatherStation.h>

WeatherStation ws;

void setup(){
  Serial.begin(9600); //Start serial communication
  ws.begin(); //initialize the weather station sensors
}

void loop(){
  //If the sensor is OK read humidity and temperature
  //and print it to the serial monitor
  if (ws.readRHT03() == WSLIB_OK){
      Serial.print("H: ");
      Serial.print(ws.getHumidity());
      Serial.print(",\t");
      Serial.print("T: ");
      Serial.println(ws.getTemperature());
  }
  //If the sensor is not OK, print "Error" to the serial monitor
  else{
    Serial.print("Error");
  }

  delay(1000); //Wait one second between readings

}
