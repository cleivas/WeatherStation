//
// FILE: WeatherStation.cpp
// PURPOSE: Library for a weather station used in Arduino Verkstad summer camp 2013 in Zaragoza
// Based on DHT Temperature & Humidity Sensor library for Arduino by Rob Tillaart (01/04/2011)
//
// Clara Leivas 19/04/2013
//

#include "WeatherStation.h"

#define TIMEOUT 10000

/////////////////////////////////////////////////////
//
// PUBLIC
//

void WeatherStation::begin(int ir)
{
    IR = ir;
    Serial.print("Default wind sensor value ... ");
    delay(2000);
    Serial.println(analogRead(IR));

    pinMode(IR, INPUT);
    digitalWrite(IR, HIGH);
    threshhold = analogRead(IR)+100;
}

// return values:
// WSTLIB_OK
// WSTLIB_ERROR_CHECKSUM
// WSTLIB_ERROR_TIMEOUT
int WeatherStation::readRHT03(uint8_t pin)
{
	// READ VALUES
	int rv = read(pin);
	if (rv != WSLIB_OK)
    {
		humidity    = WSLIB_INVALID_VALUE;  // invalid value, or is NaN prefered?
		temperature = WSLIB_INVALID_VALUE;  // invalid value
		return rv;
	}

	// CONVERT AND STORE
	humidity    = word(bits[0], bits[1]) * 0.1;

	if (bits[2] & 0x80) // negative temperature
	{
			temperature = word(bits[2]&0x7F, bits[3]) * 0.1;
			temperature *= -1.0;
	}
	else
	{
			temperature = word(bits[2], bits[3]) * 0.1;
	}

	// TEST CHECKSUM
	uint8_t sum = bits[0] + bits[1] + bits[2] + bits[3];
	if (bits[4] != sum) return WSLIB_ERROR_CHECKSUM;

	return WSLIB_OK;
}
int WeatherStation::getWindRotationTime(){
    int n = 0;
    int rotations = 3;
    int rotTime[rotations];
    long previousMillis = 0;

    //Read ir 10 times
    while(n<rotations){

        if(analogRead(IR)>threshhold){
            while(analogRead(IR)>threshhold);
            rotTime[n] = millis()-previousMillis;
            previousMillis = millis();
            n++;
        }

    }
    //calculate average rotation time, ignore first time
    int s = 0;
    for(int i=1; i<rotations; i++){
        s += rotTime[i];
    }

    int windspeed = s/rotations;
    return windspeed;
    //return n;
}

double WeatherStation::getTemperature(){
    return temperature;
}

double WeatherStation::getHumidity(){
    return humidity;
}

String WeatherStation::dataToString(double t, double h, int w){
    String data = "";
    data += "T: ";
    data += doubleToString(t, 1);
    data += "\t H: ";
    data += doubleToString(h, 1);
    data += "\t W: ";
    data += String(w);

    return data;
}

/////////////////////////////////////////////////////
//
// PRIVATE
//

// return values:
// WSTLIB_OK
// WSLIB_ERROR_TIMEOUT
int WeatherStation::read(uint8_t pin)
{
	// INIT BUFFERVAR TO RECEIVE DATA
	uint8_t cnt = 7;
	uint8_t idx = 0;

	// EMPTY BUFFER
	for (int i=0; i< 5; i++) bits[i] = 0;

	// REQUEST SAMPLE
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	delay(20);
	digitalWrite(pin, HIGH);
	delayMicroseconds(40);
	pinMode(pin, INPUT);

	// GET ACKNOWLEDGE or TIMEOUT
	unsigned int loopCnt = TIMEOUT;
	while(digitalRead(pin) == LOW)
		if (loopCnt-- == 0) return WSLIB_ERROR_TIMEOUT;

	loopCnt = TIMEOUT;
	while(digitalRead(pin) == HIGH)
		if (loopCnt-- == 0) return WSLIB_ERROR_TIMEOUT;

	// READ THE OUTPUT - 40 BITS => 5 BYTES
	for (int i=0; i<40; i++)
	{
		loopCnt = TIMEOUT;
		while(digitalRead(pin) == LOW)
			if (loopCnt-- == 0) return WSLIB_ERROR_TIMEOUT;

		unsigned long t = micros();

		loopCnt = TIMEOUT;
		while(digitalRead(pin) == HIGH)
			if (loopCnt-- == 0) return WSLIB_ERROR_TIMEOUT;

		if ((micros() - t) > 40) bits[idx] |= (1 << cnt);
		if (cnt == 0)   // next byte?
		{
			cnt = 7;
			idx++;
		}
		else cnt--;
	}

	return WSLIB_OK;
}


String WeatherStation::doubleToString(double input, int decimalPlaces){
    if(decimalPlaces!=0){
        String string = String((int)(input*pow(10,decimalPlaces)));
        if(abs(input)<1){
            if(input>0) string = "0"+string;
            else if(input<0) string = string.substring(0,1)+"0"+string.substring(1);
        }
        return string.substring(0,string.length()-decimalPlaces)+"."+string.substring(string.length()-decimalPlaces);
    }
    else {
        return String((int)input);
    }
}

//
// END OF FILE
//
