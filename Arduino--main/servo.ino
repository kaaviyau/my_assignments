#include <Servo.h>

Servo pin1;

void setup() {
  pin1.attach(D4);
}

void loop() {
  pin1.write(90);
  delay(10);
}
