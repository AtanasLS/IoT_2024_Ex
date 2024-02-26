#include <OneWire.h>
#include <DallasTemperature.h>

#define SENSOR_PIN 16

OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);

float tempC;
float tempF;
float tempR;


void setup() {
  Serial.begin(9600); // initialize serial
  DS18B20.begin();    // initialize the DS18B20 sensor
}


void loop() {
  DS18B20.requestTemperatures();       // send the command to get temperatures
  tempC = DS18B20.getTempCByIndex(0);  // read temperature in °C
  tempF = tempC * 9 / 5 + 32; // convert °C to °F
  tempR = tempC * 1.8 / 491.67;

  Serial.print("Temperature: ");
  Serial.print(tempC);    // print the temperature in °C
  Serial.print("°C");
  Serial.print("  ~  ");  // separator between °C and °F
  Serial.print(tempF);    // print the temperature in °F
  Serial.println("°F");
    Serial.print("  ~  ");  // separator between °C and °F
  Serial.print(tempR);    // print the temperature in °F
  Serial.println("°R");

  delay(500);
}
