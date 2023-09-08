#include <Arduino.h> // Include Arduino core library
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define encoderPinCLK D3  // CLK pin of the encoder
#define encoderPinDT D2   // DT pin of the encoder
#define encoderPinSW D4   // SW pin of the encoder

volatile long encoderCount = 0;
int previousEncoderValue = 0;
int targetRPM = 0;
int currentRPM = 0;
int inputRPM = 0;
unsigned long previousTime = 0;
const unsigned long interval = 1000; // 1000ms = 1 second

void IRAM_ATTR encoderInterrupt() { // Add IRAM_ATTR attribute here
  int CLK_state = digitalRead(encoderPinCLK);
  int DT_state = digitalRead(encoderPinDT);
  int encoderState = (CLK_state << 1) | DT_state;

  if (encoderState == 0b01 || encoderState == 0b10)
    encoderCount++;
  else if (encoderState == 0b11 || encoderState == 0b00)
    encoderCount--;
}

void calculateRPM() {
  currentRPM = (encoderCount * 60) / 32; // Change '32' to the number of encoder counts per revolution
  Serial.print("Current RPM: ");
  Serial.println(currentRPM);
  encoderCount = 0; // Reset the encoder count
}

void setup() {
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  pinMode(encoderPinCLK, INPUT);
  pinMode(encoderPinDT, INPUT);
  pinMode(encoderPinSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPinCLK), encoderInterrupt, CHANGE);
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;
    calculateRPM();
  }
}
