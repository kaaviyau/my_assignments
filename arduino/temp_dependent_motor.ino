#uses a controller to read temperature data from a Dallas DS18B20 temperature sensor and control a servo motor
#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define tempPin D2

Servo pin1;
OneWire oneWire(tempPin);
DallasTemperature sensors(&oneWire);

float Celsius = 0;

void setup() {
  pin1.attach(D4);
  sensors.begin();
  Serial.begin(9600);
  delay(750); 
}

void loop() {
  sensors.requestTemperatures();
  Celsius = sensors.getTempCByIndex(0);
  int servoPosition = map(Celsius, 30, 40, 0, 180);
  Serial.print("Temperature (Celsius): ");
  Serial.println(Celsius);
  Serial.print("Servo Position: ");
  Serial.println(servoPosition);
  pin1.write(servoPosition);
  delay(100);
}
