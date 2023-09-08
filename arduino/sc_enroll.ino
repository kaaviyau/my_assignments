#include <Adafruit_Fingerprint.h>
#include <Arduino.h> // Include Arduino core library
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define outputA D2
#define outputB D3

#define FINGERPRINT_RX D6
#define FINGERPRINT_TX D1

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
  Serial.println("\n\nAdafruit Fingerprint sensor enrollment");
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  finger.begin(57600);

  if (finger.verifyPassword())
  {
    lcd.
    Serial.println("Found fingerprint sensor!");
    lcd.setCursor(0,0);
    lcd.print("Found fingerprint sensor!");
  }
  else
  {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  Serial.println(F("Reading sensor parameters"));
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
  Serial.print("Enrolling ID #");
  Serial.println(id);

  while (!getFingerprintEnroll(id));
}

bool getFingerprintEnroll(uint8_t id)
{
  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK)
  {
    p = finger.getImage();
    switch (p)
    {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.println(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p)
  {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return false;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return false;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return false;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return false;
    default:
      Serial.println("Unknown error");
      return false;
  }

  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER)
  {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK)
  {
    p = finger.getImage();
    switch (p)
    {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p)
  {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return false;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return false;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return false;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return false;
    default:
      Serial.println("Unknown error");
      return false;
  }

  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK)
  {
    Serial.println("Prints matched!");
    enrolledUsers[numEnrolled] = id;
    numEnrolled++;
  }
  else if (p == FINGERPRINT_PACKETRECIEVEERR)
  {
    Serial.println("Communication error");
    return false;
  }
  else if (p == FINGERPRINT_ENROLLMISMATCH)
  {
    Serial.println("Fingerprints did not match");
    return false;
  }
  else
  {
    Serial.println("Unknown error");
    return false;
  }

  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK)
  {
    Serial.println("Stored!");
  }
  else if (p == FINGERPRINT_PACKETRECIEVEERR)
  {
    Serial.println("Communication error");
    return false;
  }
  else if (p == FINGERPRINT_BADLOCATION)
  {
    Serial.println("Could not store in that location");
    return false;
  }
  else if (p == FINGERPRINT_FLASHERR)
  {
    Serial.println("Error writing to flash");
    return false;
  }
  else
  {
    Serial.println("Unknown error");
    return false;
  }

  return true;
}

void loop()
{
  Serial.println("Place your finger on the sensor...");

  int p = finger.getImage();

  if (p == FINGERPRINT_OK)
  {
    Serial.println("Image taken");

    uint8_t id = finger.fingerID();

    if (id == 0) // ID #0 indicates no match found
    {
      Serial.println("No match found, attempting enrollment...");
      Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
      id = readnumber();

      if (id > 0 && id <= 127 && !isEnrolled(id))
      {
        enrollFingerprint(id);
      }
      else
      {
        Serial.println("Invalid ID or fingerprint already enrolled.");
      }
    }
    else
    {
      Serial.print("User ID #");
      Serial.print(id);
      Serial.println(" recognized!");
    }
  }
  else if (p == FINGERPRINT_NOFINGER)
  {
    Serial.println("No finger detected.");
  }
  else
  {
    Serial.println("Unknown error");
  }

  delay(1000);
}
