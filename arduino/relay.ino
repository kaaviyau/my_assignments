#define relayPin1 D1
#define relayPin2 D2
#define relayPin3 D3
#define relayPin4 D4
#define relayPin5 D5
#define relayPin6 D6
#define relayPin7 D7
#define relayPin8 D8

void setup() {
  pinMode(relayPin1 ,OUTPUT);
  pinMode(relayPin2 ,OUTPUT);
  pinMode(relayPin3 ,OUTPUT);
  pinMode(relayPin4 ,OUTPUT);
  pinMode(relayPin5 ,OUTPUT);
  pinMode(relayPin6 ,OUTPUT);
  pinMode(relayPin7 ,OUTPUT);
  pinMode(relayPin8 ,OUTPUT);
}

void loop() {
  digitalWrite(relayPin1, HIGH);
  digitalWrite(relayPin8, LOW);
  delay(1000);
  digitalWrite(relayPin2, HIGH);
  digitalWrite(relayPin1, LOW);
  delay(1000);
  digitalWrite(relayPin3, HIGH);
  digitalWrite(relayPin2, LOW);
  delay(1000);
  digitalWrite(relayPin4, HIGH);
  digitalWrite(relayPin3, LOW);
  delay(1000);
  digitalWrite(relayPin5, HIGH);
  digitalWrite(relayPin4, LOW);
  delay(1000);
  digitalWrite(relayPin6, HIGH);
  digitalWrite(relayPin5, LOW);
  delay(1000);
  digitalWrite(relayPin7, HIGH);
  digitalWrite(relayPin6, LOW);
  delay(1000);
  digitalWrite(relayPin8, HIGH);
  digitalWrite(relayPin7, LOW);
  delay(1000);
}
