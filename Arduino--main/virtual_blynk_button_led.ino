#uses blynk iot to connect a virtual button to a virtual led on the blynk app
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "z5odjg6Yj5RTeOjrKpzxvpRz0M0Jr9v0";
char ssid[] = "wifi";
char pass[] = "123#A1306";

const int buttonPin = V1;
const int ledPin = V2;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  pinMode(buttonPin, INPUT);
}

void loop() {
  Blynk.run();
}

BLYNK_WRITE(buttonPin) {
  int bState = param.asInt();
    if (bState == 1) {
    Blynk.virtualWrite(ledPin, HIGH);
  } else { 
    Blynk.virtualWrite(ledPin, LOW);
  }
}
