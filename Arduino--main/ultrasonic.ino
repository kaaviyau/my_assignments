#connects an ultrasonic sensor to the controller 
#define ECHOPIN D6
#define BLYNK_PRINT Serial
#define TRIGPIN D5

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Arduino.h"

char auth[] = "z5odjg6Yj5RTeOjrKpzxvpRz0M0Jr9v0";
char ssid[] = "wifi";
char pass[] = "12345678";

BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  timer.setInterval(1000L, myTimerEvent);
  Blynk.begin(auth, ssid, pass,IPAddress(143,110,248,130),8080);
  pinMode(ECHOPIN,INPUT_PULLUP);
  pinMode(TRIGPIN, OUTPUT);
  digitalWrite(ECHOPIN, HIGH);
}

void loop() {
  Blynk.run();
  timer.run();
  
}

void myTimerEvent(){
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(15);
  digitalWrite(TRIGPIN, LOW);
  int distance = pulseIn(ECHOPIN, HIGH, 26000);
  distance=distance/58;
  Blynk.virtualWrite(V3,distance);
  Serial.print(distance);
  Serial.println("   cm");
  delay(10);
}
