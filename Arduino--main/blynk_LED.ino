#uses blynk iot to connect a virtual LED on the blynk app to a physical LED on the controller
#define BLYNK_PRINT Serial
#define LedPin D4

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Arduino.h"

BlynkTimer timer;

char auth[] = "z5odjg6Yj5RTeOjrKpzxvpRz0M0Jr9v0";
char ssid[] = "wifi";
char pass[] = "12345678";

WidgetLED ledStatus(V2);

int bState=0;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass,IPAddress(143,110,248,130),8080);
  pinMode(LedPin, OUTPUT);
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  Blynk.run();
  timer.run();
}

void myTimerEvent()
{
  if (bState == 1) {
    ledStatus.on();
    digitalWrite(LedPin,HIGH);
    Serial.println(1);
  } else { 
    ledStatus.off();
    digitalWrite(LedPin,LOW);
    Serial.println(0);
  }
}

BLYNK_WRITE(V1) 
{
  bState = param.asInt();
}
