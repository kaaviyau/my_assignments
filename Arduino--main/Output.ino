#include <SoftwareSerial.h>

SoftwareSerial Software(3, 1);  

void setup()
{
  Serial.begin(9600);      
  Software.begin(9600);   
}

void loop()
{
  if (Software.available() > 0)
  {
    char incomingByte = Software.read(); 
    Serial.print("Received: ");
    Serial.println(incomingByte);        
}
}