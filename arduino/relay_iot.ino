#define relayPin1 D1
#define relayPin2 D2
#define relayPin3 D3
#define relayPin4 D4

int relay1 = 0;
int relay2 = 0;
int relay3 = 0;
int relay4 = 0;

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Arduino.h"

char auth[] = "z5odjg6Yj5RTeOjrKpzxvpRz0M0Jr9v0";
char ssid[] = "Danger";
char pass[] = "12345678";

BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  timer.setInterval(100L, myTimerEvent);
  Blynk.begin(auth, ssid, pass,IPAddress(143,110,248,130),8080);
  pinMode(relayPin1 ,OUTPUT);
  pinMode(relayPin2 ,OUTPUT);
  pinMode(relayPin3 ,OUTPUT);
  pinMode(relayPin4 ,OUTPUT);
}

void loop() {
  Blynk.run();
  timer.run();
}

void myTimerEvent()
{
  if (relay1==1)
  {
    digitalWrite(relayPin1, LOW);
  }
  if (relay2==1)
  {
    digitalWrite(relayPin2, LOW);
  }
  if (relay3==1)
  {
    digitalWrite(relayPin3, LOW);
  }
  if (relay4==1)
  {
    digitalWrite(relayPin4, LOW);
  }
   if (relay1==0)
  {
    digitalWrite(relayPin1, HIGH);
  }
  if (relay2==0)
  {
    digitalWrite(relayPin2, HIGH);
  }
  if (relay3==0)
  {
    digitalWrite(relayPin3, HIGH);
  }
  if (relay4==0)
  {
    digitalWrite(relayPin4, HIGH);
  }
}

BLYNK_WRITE(V6) 
{
  relay1 = param.asInt();
}

BLYNK_WRITE(V7) 
{
  relay2 = param.asInt();
}

BLYNK_WRITE(V8) 
{
  relay3 = param.asInt();
}

BLYNK_WRITE(V9) 
{
  relay4 = param.asInt();
}
