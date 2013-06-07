/*
  Test the RPR220 sensor, that we use as a windspeed sensor. 
  
  Make sure the sensor is alligned with the top edge.
  Upload the code to your board. Turn the anemometer to
  see if the sensor detects white and black. When it reads
  black the tinkerkit LED is turned on.
  
  If the sensor isn't detecting properly, adjust the possition 
  of the RPR220 until it does. 
  
  Plug in the battery and test the anemometer outside. The IR
  light from the sun could interfere with readings.
*/

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  //Initialize RPR 220 sensor
  pinMode(15, INPUT_PULLUP);
  //Initialize the tinkerkit LED
  pinMode(9, OUTPUT);
}

void loop() {
  //Read the RPR 220 value  
  int sensorValue = digitalRead(A1);
  // print out the value you read:
  Serial.println(sensorValue);
  
  //If the sensor detects white, turn the LED off
  if(sensorValue==LOW) digitalWrite(9, LOW);
  //If the sensor detects black, turn the LED on  
  else digitalWrite(9, HIGH);
  
  delay(1);        // delay in between reads for stability
}
