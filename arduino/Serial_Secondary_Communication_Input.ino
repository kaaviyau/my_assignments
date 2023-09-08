#Input for Serial Secondary Communication
#include <SoftwareSerial.h>

SoftwareSerial Software(3, 1);

String incomingByte;

void setup()
{
  Software.begin(115200);
}

void loop()
{
  Software.println("Here");
  delay(500);
}
