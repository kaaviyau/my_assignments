#include <Adafruit_Fingerprint.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define FINGERPRINT_RX D6
#define FINGERPRINT_TX D5

LiquidCrystal_I2C lcd(0x27, 16, 2); // Change the I2C address to match your LCD module

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(FINGERPRINT_RX, FINGERPRINT_TX);
#else
#define mySerial Serial1
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

const int MAX_USERS = 10; // Maximum number of enrolled users
uint8_t enrolledUsers[MAX_USERS]; // Array to store the enrolled fingerprint IDs
uint8_t numEnrolled = 0; // Number of enrolled fingerprints

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  delay(100);
  
  lcd.begin(16, 2); // Initialize the LCD
  lcd.clear();     // Clear the LCD

  lcd.print("Adafruit Fingerprint");
  lcd.setCursor(0, 1);
  lcd.print("sensor enroll");

  finger.begin(57600);

  if (finger.verifyPassword())
  {
    lcd.clear(); // Clear the LCD
    lcd.print("Fingerprint sensor");
    lcd.setCursor(0, 1);
    lcd.print("found!");
    delay(2000);
  }
  else
  {
    lcd.clear(); // Clear the LCD
    lcd.print("No sensor found!");
    while (1) { delay(1); }
  }

  lcd.clear(); // Clear the LCD
  lcd.print("Place your finger");
  lcd.setCursor(0, 1);
  lcd.print("on the sensor...");

  finger.getParameters();
  // ... Display fingerprint sensor parameters as before
}

uint8_t readnumber()
{
  uint8_t num = 0;

  while (num == 0)
  {
    while (!Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

bool isEnrolled(uint8_t id)
{
  for (uint8_t i = 0; i < numEnrolled; i++)
  {
    if (enrolledUsers[i] == id)
    {
      return true; // Fingerprint is already enrolled
    }
  }
  return false; // Fingerprint is not enrolled
}

void enrollFingerprint(uint8_t id)
{
  lcd.clear(); // Clear the LCD
  lcd.print("Enrolling ID #");
  lcd.print(id);

  while (!getFingerprintEnroll(id));
}

bool getFingerprintEnroll(uint8_t id)
{
  // ... Fingerprint enrollment process as before

  // OK success!
  lcd.clear(); // Clear the LCD
  lcd.print("Creating model");
  lcd.setCursor(0, 1);
  lcd.print("for #");
  lcd.print(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK)
  {
    lcd.clear(); // Clear the LCD
    lcd.print("Prints matched!");
    enrolledUsers[numEnrolled] = id;
    numEnrolled++;
    delay(2000);
  }
  else if (p == FINGERPRINT_PACKETRECIEVEERR)
  {
    lcd.clear(); // Clear the LCD
    lcd.print("Communication error");
    delay(2000);
    return false;
  }
  else if (p == FINGERPRINT_ENROLLMISMATCH)
  {
    lcd.clear(); // Clear the LCD
    lcd.print("Fingerprints did");
    lcd.setCursor(0, 1);
    lcd.print("not match");
    delay(2000);
    return false;
  }
  else
  {
    lcd.clear(); // Clear the LCD
    lcd.print("Unknown error");
    delay(2000);
    return false;
  }

  lcd.clear(); // Clear the LCD
  lcd.print("ID ");
  lcd.print(id);
  lcd.print(" enrolled!");
  delay(2000);

  return true;
}

void loop()
{
  lcd.clear(); // Clear the LCD
  lcd.print("Place your finger");
  lcd.setCursor(0, 1);
  lcd.print("on the sensor...");

  int p = finger.getImage();

  if (p == FINGERPRINT_OK)
  {
    lcd.clear(); // Clear the LCD
    lcd.print("Image taken");

    uint8_t id = finger.fingerID();

    if (id == 0) // ID #0 indicates no match found
    {
      lcd.setCursor(0, 1);
      lcd.print("No match found,");
      lcd.print("enroll new?");
      delay(2000);

      lcd.clear(); // Clear the LCD
      lcd.print("Type ID (1-127)");

      lcd.setCursor(0, 1);
      lcd.print("to enroll:");
      
      id = readnumber();

      if (id > 0 && id <= 127
