
#include <Wire.h>
#define LDR_PIN A0
#define TEMP_PIN A1

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  int rawLight = analogRead(LDR_PIN);
  uint8_t lightLevel = rawLight / 4;

  if (lightLevel > 255) lightLevel = 255;

  int rawTemp = analogRead(TEMP_PIN);
  float voltage = (rawTemp * 5.0) / 1023.0;
  int8_t tempCelsius = (int8_t)((voltage - 0.5) * 100);

  Serial.print("Temp: ");
  Serial.print(tempCelsius);
  Serial.print(" °C | Light: ");
  Serial.println(lightLevel);

  Wire.beginTransmission(8);
  Wire.write(lightLevel);
  Wire.write(tempCelsius);
  Wire.endTransmission();

  delay(600);
}
