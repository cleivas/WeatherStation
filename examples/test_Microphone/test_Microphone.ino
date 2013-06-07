/*
  Test the microphone
  
  Upload the code, connect a 9V battery to the Arduino board
  and open the serial monitor. Make some loud noises. If the
  Numbers in the serial monitor doesn't increase please make
  sure that you have connected everything correct at:
  http://cuartielles.com/verkstad/edu/CoursesSummerCampZGZEs/Ballooning
  
 */


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  // read the input on analog pin 2   :
  int sensorValue = analogRead(A2);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(1);        // delay in between reads for stability
}
