#include <LiquidCrystal.h>
#include <DHT.h>
#include <Wire.h> 
#include <BMP085.h>

// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       home_weather_station_.ino
    Created:	10/6/2019 8:28:55 PM
    Author:     DEV\User
*/

#define DHTPIN A8     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)


BMP085 dps = BMP085();
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
DHT dht(DHTPIN, DHTTYPE);


float d;
long p = 0;
String o;
uint8_t curs;
// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
void setup()
{
	lcd.begin(16,2);
	lcd.setCursor(0, 0);
	lcd.print("Home Weather");
	lcd.setCursor(0, 1);
	lcd.print("  Station  ");
	dht.begin();
	delay(2000);
	Wire.begin();
	dps.init();
}

// Add the main program code into the continuous loop() function
void loop()
{
	d = measureT();
	lcd.setCursor(1, 0);
	printV(d, "Temperature", "oC");
	delay(5000);
	d = measureH();
	printV(d, "Humidity", "%");
	delay(5000);
	d = measureP();
	printV(d, "Air Pressure", "mmHg");
	delay(5000);




}

void printV(float d, String s1, String s2) {
	lcd.clear();
	lcd.setCursor(1, 0);
	lcd.print(s1);
	o = String(d);
	curs = 16 - o.length() - s2.length() - 2;
	lcd.setCursor(curs, 1);
	lcd.print(o + " " + s2);
}

float measureP() {
	dps.calcTruePressure(&p);
	return p / 133.3;
}

float measureT() {
	return dht.readTemperature();
}

float measureH() {
	return dht.readHumidity();
}
