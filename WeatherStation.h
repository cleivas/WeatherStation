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
	int getWindRotationTime();
	String dataToString(double t, double h, int w);

private:
    int threshhold;
    int IR;
	uint8_t bits[5];  // buffer to receive data
	int read(uint8_t pin);
	double humidity;
	double temperature;
	String doubleToString(double input, int decimalPlaces);
};
#endif
//
// END OF FILE
//
