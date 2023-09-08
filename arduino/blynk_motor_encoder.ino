#uses Blynk IOT to connect a motor to the Blynk App and control the RPM
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "z5odjg6Yj5RTeOjrKpzxvpRz0M0Jr9v0";
char ssid[] = "wifi ";
char pass[] = "p#A1306";

BlynkTimer timer;
#define BLYNK_PRINT Serial

#define encoderPinCLK D2 
#define encoderPinST D3   
#define encoderPinSW D4  

volatile long encoderCount = 0;
int previousEncoderValue = 0;
int targetRPM = 0;
int currentRPM = 0;
int inputRPM = 0;

void encoderInterrupt() {
  int CLK_state = digitalRead(encoderPinCLK);
  int ST_state = digitalRead(encoderPinST);
  int encoderState = (CLK_state << 1) | ST_state;

  if (encoderState == 0b01 || encoderState == 0b10)
    encoderCount++;
  else if (encoderState == 0b11 || encoderState == 0b00)
    encoderCount--;
}

void calculateRPM() {
  currentRPM = (encoderCount * 60) / 32; 
  Serial.println(currentRPM);
  encoderCount = 0; 
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, IPAddress(143, 110, 248, 130), 8080);
  pinMode(encoderPinCLK, INPUT);
  pinMode(encoderPinST, INPUT);
  pinMode(encoderPinSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPinCLK), encoderInterrupt, CHANGE);

  timer.setInterval(1000, calculateRPM);
}

void loop() {
  Blynk.run();
  timer.run();

  int pwmValue = map(targetRPM, 0, 1023, 0, 255);
  analogWrite(D1, pwmValue);
}

BLYNK_WRITE(V10) {
  targetRPM = param.asInt();
}
