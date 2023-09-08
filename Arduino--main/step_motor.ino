#define StepperPin D2

void setup() {
  pinMode(StepperPin, OUTPUT);

}

void loop() {
  for (int x=0; x<200; x++)
  {
    digitalWrite(StepperPin, HIGH);
    delayMicroseconds(5000);
    digitalWrite(StepperPin, LOW);
    delayMicroseconds(5000);
  }
  delay(5000);


}
