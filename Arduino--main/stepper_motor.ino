#define StepperPin A0

void setup() {
  pinMode(StepperPin, OUTPUT);
  analogWrite(StepperPin, 0);
  delay(5000);
}

void loop() {
  for (int x=0; x<100; x++)
  {
    analogWrite(StepperPin, x);
    delay(1);
  }

}
