#controlling physical motors using a controller 
#define BLYNK_PRINT Serial
#define motorPin1 D2
#define motorPin2 D3
#define motorSpeed1 D7
#define motorPin3 D5
#define motorPin4 D6
#define motorSpeed2 D8

int up1 = 0;
int up2 = 0;
int down1 = 0;
int down2=0;
int Speed1=0;
int Speed2=0;

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Arduino.h"

char auth[] = "z5odjg6Yj5RTeOjrKpzxvpRz0M0Jr9v0";
char ssid[] = "wifi";
char pass[] = "12345678";

BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  timer.setInterval(100L, myTimerEvent);
  Blynk.begin(auth, ssid, pass,IPAddress(143,110,248,130),8080);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorSpeed1, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(motorSpeed2, OUTPUT);

}

void loop() {
  Blynk.run();
  timer.run();
  
}

void myTimerEvent() 
{
  analogWrite(motorSpeed1, Speed1);
  analogWrite(motorSpeed2, Speed2);

  if (up1==1&&up2==1&&down1==0&&down2==0)
  {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  
  Serial.println("UP");
  }
  else if (up1==1&&down1==1&&up2==0&&down2==0)
  {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  Serial.println("LEFT");
  }
  else if (up2==1&&down2==1)
  {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  Serial.println("RIGHT");
  }
  else if (up1==0&&up2==0&&down1==1&&down2==1)
  {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  
  Serial.println("BACK");
  }
  else
  {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  Serial.println("STOP");
  }

}

BLYNK_WRITE(V4) 
{
  up1 = param.asInt();
}

BLYNK_WRITE(V5) 
{
  down1 = param.asInt();
}

BLYNK_WRITE(V6) 
{
  up2 = param.asInt();
}

BLYNK_WRITE(V7) 
{
  down2 = param.asInt();
}

BLYNK_WRITE(V8)
{
  Speed1=param.asInt();
}
BLYNK_WRITE(V9)
{
  Speed2=param.asInt();
}

