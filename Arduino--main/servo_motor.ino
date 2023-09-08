#include "Servo.h"
Servo pin1;

void setup() {
  pin1.attach(D4);

}

void loop() {
  for (int i = 800; i<2000; i++)
  {pin1.write(i);
  delay(1);

}
  for (int i = 2000; i>800; i--)
  {pin1.write(i);
  delay(1);

}

}