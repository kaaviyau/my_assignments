#include <Wire.h>

void setup() {
 Serial.begin(9600); /* begin serial for debug */
 Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
}

void loop() {
  //Serial.println("here1");
  Wire.beginTransmission(8); /* begin with device address 8 */
  Wire.write("Hello Arduino");  /* sends hello string */
  Wire.endTransmission();    /* stop transmitting */
  //Serial.println("here2");
  Wire.requestFrom(8,13);
  while(Wire.available()){
      char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();
  delay(1000);
}
