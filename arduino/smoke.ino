#define pin1 D4
int a=0;

void setup() {
  pinMode(pin1, INPUT);
  Serial.begin(9600);

}

void loop() {
  a= digitalRead(pin1);
  Serial.println(a);
  delay(100);
}
