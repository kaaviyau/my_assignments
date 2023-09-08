#uses blynk iot to send a value to the blynk app 
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Arduino.h"

char auth[] = "z5odjg6Yj5RTeOjrKpzxvpRz0M0Jr9v0";
char ssid[] = "wifi";
char pass[] = "12345678";

int value1=15;

void setup() 
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass,IPAddress(143,110,248,130),8080);
  Blynk.syncAll();
}

void loop() 
{
  Blynk.run();
  Blynk.virtualWrite(V0,value1);
}
