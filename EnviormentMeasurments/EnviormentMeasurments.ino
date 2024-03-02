#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

//// set LCD address, number of columns and rows
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

//Defining the temperture pin
#define SENSOR_PIN 17
//
OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);
//initializing the tempC value
float tempC;
//initializing the sensor values
int sensorValue;
int digitalValue;



void setup() {
  Serial.begin(9600); // initialize serial
  // put your setup code here, to run once:
  lcd.init();
  //turn on  LCD backlight
  lcd.backlight();
  // initialize the DS18B20 sensor
  DS18B20.begin(); 
  //set up the pinMode
  pinMode(36, OUTPUT);
  pinMode(26, INPUT);   
}

void loop() {
  // put your main code here, to run repeatedly:

  getSensorValue();
  getTemp();
  printOnLCD(tempC, sensorValue);
}

void getTemp(){
  DS18B20.requestTemperatures();       // send the command to get temperatures
  tempC = DS18B20.getTempCByIndex(0);  // read temperature in °C
  Serial.print("Temperature: ");
  Serial.print(tempC);    // print the temperature in °C
  Serial.print("°C");
  delay(500);
}

void getSensorValue(){
  sensorValue = analogRead(36);
  digitalValue = digitalRead(26);

  if (sensorValue > 400)
  {
    digitalWrite(A0, HIGH);
  }
  else
    digitalWrite(26, LOW);
  Serial.println(sensorValue, DEC); // prints the value read
  Serial.println(digitalValue, DEC);
  delay(1000); // wait 100ms for next reading
}

void printOnLCD(float tempC, int sensorValue){
   // Convert float to string with 1 decimal place
  String tempCString = String(tempC, 1);

  // Convert integer to string
  String sensorValueString = String(sensorValue);
     // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Temp: " + tempCString + " C");
  delay(2000);
  // clears the display to print new message
  //lcd.clear();
  // set cursor to first column, second row
  lcd.setCursor(0,1);

  lcd.print("Air Quality: " + sensorValueString);
  delay(2000);
  lcd.clear(); 
}