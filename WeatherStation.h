//
// FILE: WeatherStation.cpp
// PURPOSE: Library for a weather station used in Arduino Verkstad summer camp 2013 in Zaragoza
// Based on DHT Temperature & Humidity Sensor library for Arduino by Rob Tillaart (01/04/2011)
//
// Clara Leivas 19/04/2013
//

#ifndef WeatherStation_h
#define WeatherStation_h

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif


#define WSLIB_OK				0
#define WSLIB_ERROR_CHECKSUM	-1
#define WSLIB_ERROR_TIMEOUT	-2
#define WSLIB_INVALID_VALUE	-999

class WeatherStation
{
public:
    void begin(int ir = A1);
    int readRHT03(uint8_t pin = 5);
	double getHumidity();
	double getTemperature();
	double getWindRPS();
	int getSoundPollution();
	String dataToString(double t, double h, double w, int s);

private:
    int IR;
	uint8_t bits[5];  // buffer to receive data
	int read(uint8_t pin);
	double humidity;
	double temperature;
	double windRotations;
	int sound;
	long soundSum;
	int soundCount;
	int wr;
	long startTime;
	String doubleToString(double input, int decimalPlaces);

	long currentMillis;
	long previousMillis;
	long previousSoundMillis;
	long interval;
};
#endif
//
// END OF FILE
//
