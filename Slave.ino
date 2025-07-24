#include <Wire.h>
#include <Servo.h>
Servo shutter;

#define servoPin 9
#define redLED 4
#define blueLED 3
#define greenLED 2

int lightReading = 0;
int8_t tempReading = 0;

void setup() {
  Wire.begin(8); 
  Wire.onReceive(handleReceive);

  shutter.attach(servoPin);

  Serial.begin(9600);

  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop() {
  if (lightReading > 190) {
    shutter.write(0);
  } else if (lightReading > 140) {
    shutter.write(90);
  } else {
    shutter.write(180);
  }

  if (tempReading <= 15) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
  } else if (tempReading >= 40) {
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
  } else {
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, HIGH);
  }

  delay(200);
}

void handleReceive(int count) {
  if (count >= 2) {
    lightReading = Wire.read();
    tempReading = (int8_t)Wire.read();

    Serial.print("Light: ");
    Serial.print(lightReading);
    Serial.print(" | Temp: ");
    Serial.println(tempReading);
  }
}
