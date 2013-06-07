/*
  Test the camera
  
  Upload the code, and turn the camera on with the button
  without the cables. A yellow LED lights up. Every two seconds 
  the LED is turned off for a fex milliseconds. This indicates 
  that a photo is taken. If the LED never turns off, please make 
  sure the connections are correct at:
  http://cuartielles.com/verkstad/edu/CoursesSummerCampZGZEs/Ballooning
  
 */

int cameraPin = 8; 

void setup(){
  pinMode(cameraPin, OUTPUT);
}

void loop(){
    //Take a photo
    digitalWrite(cameraPin, HIGH); 
    delay(500);
    digitalWrite(cameraPin, LOW);
    
    delay(2000); //wait two seconds
}
