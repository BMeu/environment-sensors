#include "lib/CCS811/CCS811.h"
#include <LiquidCrystal.h>

                              // A13 -> A4
                              // A14 -> A5
const int temperaturePin = 0; // A24 -> A0
const int rs = 12;            // G39 -> 12
const int en = 11;            // G41 -> 11
const int d4 = 5;             // G46 -> 5
const int d5 = 4;             // I47 -> 4
const int d6 = 3;             // G48 -> 3
const int d7 = 2;             // I49 -> 2

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
CCS811 sensor;

const byte degree[8] = {
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

void setup() {
  lcd.createChar(0, degree);
  lcd.begin(16, 2);
  while (sensor.begin() != 0) {
    lcd.setCursor(0, 0);
    lcd.print("Initializing...");
    delay(500);
  }
}

void loop() {
  lcd.clear();
  if (sensor.checkDataReady() == true) {
    lcd.setCursor(0, 0);
    lcd.print("CO2:   ");
    lcd.print(sensor.getCO2PPM());
    lcd.print("ppm");

    /*lcd.setCursor(0, 1);
    lcd.print("TVOC: ");
    lcd.print(sensor.getTVOCPPB());
    lcd.print("ppb");*/
  }

  lcd.setCursor(0, 1);
  lcd.print("Temp.: ");
  lcd.print(round(getTemperatureInCelsius(temperaturePin)));
  lcd.write(byte(0));
  lcd.print("C");

  delay(1000);
}

float getVoltage(int pin) {
  return analogRead(pin) * 5.0 / 1024.0;
}

float getTemperatureInCelsius(int pin) {
  float voltage = getVoltage(pin);
  return (voltage - 0.5) * 100.0;
}
