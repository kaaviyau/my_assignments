
#include <Adafruit_Fingerprint.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define FINGERPRINT_RX D6
#define FINGERPRINT_TX D5

LiquidCrystal_I2C lcd(0x27, 16, 2); // Change the I2C address and pin configuration to match your LCD module

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

  // Set up the LCD with the correct pins and columns/rows
  lcd.begin(16, 2); // Initialize the LCD
  lcd.clear();     // Clear the LCD

  lcd.print("Adafruit Fingerprint");
  lcd.setCursor(0, 1);
  lcd.print("sensor enroll");
  delay(2000);

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
  delay(2000);

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
  int p = -1;
  lcd.clear(); // Clear the LCD
  lcd.print("Waiting for valid");
  lcd.setCursor(0, 1);
  lcd.print("finger to enroll as #");
  lcd.print(id);

  while (p != FINGERPRINT_OK)
  {
    p = finger.getImage();
    switch (p)
    {
    case FINGERPRINT_OK:
      lcd.clear(); // Clear the LCD
      lcd.print("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      lcd.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.clear(); // Clear the LCD
      lcd.print("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      lcd.clear(); // Clear the LCD
      lcd.print("Imaging error");
      break;
    default:
      lcd.clear(); // Clear the LCD
      lcd.print("Unknown error");
      break;
    }
  }

  // OK success!
  p = finger.image2Tz(1);
  switch (p)
  {
    case FINGERPRINT_OK:
      lcd.clear(); // Clear the LCD
      lcd.print("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      lcd.clear(); // Clear the LCD
      lcd.print("Image too messy");
      return false;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.clear(); // Clear the LCD
      lcd.print("Communication error");
      return false;
    case FINGERPRINT_FEATUREFAIL:
      lcd.clear(); // Clear the LCD
      lcd.print("Could not find fingerprint features");
      return false;
    case FINGERPRINT_INVALIDIMAGE:
      lcd.clear(); // Clear the LCD
      lcd.print("Could not find fingerprint features");
      return false;
    default:
      lcd.clear(); // Clear the LCD
      lcd.print("Unknown error");
      return false;
  }

  lcd.clear(); // Clear the LCD
  lcd.print("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER)
  {
    p = finger.getImage();
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

    uint8_t id = finger.fingerFastSearch();

    if (id == FINGERPRINT_NOTFOUND)
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

      if (id > 0 && id <= 127 && !isEnrolled(id))
      {
        enrollFingerprint(id);
      }
      else
      {
        lcd.clear(); // Clear the LCD
        lcd.print("Invalid ID or fingerprint");
        lcd.setCursor(0, 1);
        lcd.print("already enrolled.");
        delay(2000);
      }
    }
    else
    {
      lcd.clear(); // Clear the LCD
      lcd.print("User ID #");
      lcd.print(id);
      lcd.print(" recognized!");
      delay(2000);

      lcd.clear(); // Clear the LCD
      lcd.print("ACCESS GRANTED");
      lcd.setCursor(0, 1);
      lcd.print("User ID #");
      lcd.print(id);
      delay(2000);
    }
  }

  // ... The rest of the loop function, which waits for the next fingerprint image, remains unchanged
}
