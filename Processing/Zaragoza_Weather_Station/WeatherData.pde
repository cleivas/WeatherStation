/*
  Weather Station
  (c) Arduino Verkstad AB 2013
  Author: Clara Leivas
  
  This program visualizes the data gathered from a weather station. 
  The data is wind speed in RPS (rotations per seconds), temperature 
  in celsius, air humidity in %, sound pollution (this data is not of 
  a particular unit) and pictures taken with a small camera mounted 
  on the weather station.
  
  For more instructions on the weather station please see:
  http://cuartielles.com/verkstad/edu/CoursesSummerCampZGZEs/Ballooning
  
  Use left and right arrow key to scroll through the pictures and data.
*/

/** Translate Strings of data to variables **/
void parseData(String lines[]) {
  //nmbOfLines = lines.length;

  //loop for each line of data in "datalog.txt"
  for (int i = 0; i < nmbOfLines; i++) {
    println(lines[i]);
    int h = lines[i].indexOf("H:");
    int t = lines[i].indexOf("T:");
    int w = lines[i].indexOf("W:");
    int s = lines[i].indexOf("S:");

    String humidity = "";
    String temperature = "";
    String windSpeed = "";
    String soundPollution = "";
    
    //Separate each weather data type
    for (int j=3; j<7; j++) {
      if (lines[i].charAt(h+j)==' '|| lines[i].charAt(t+j)==' ')j=8;
      humidity += lines[i].charAt(h+j);
      temperature += lines[i].charAt(t+j);
      windSpeed += lines[i].charAt(w+j);
    }
    for (int j=s+3; j<lines[i].length(); j++) {
      soundPollution += lines[i].charAt(j);
    }
    
    //Translate from String to float or integer
    humi[i] = Float.parseFloat(humidity);
    temp[i] = Float.parseFloat(temperature);
    wind[i] = Float.parseFloat(windSpeed);
    sound[i] = int(soundPollution);

    println(temp[i]);
    println(humi[i]);
    println(wind[i]);
    println(sound[i]);
  }
}

