#include <ModbusRTU.h>
#include <SoftwareSerial.h>
 
SoftwareSerial S(D3, D2); //RO D1


ModbusRTU mb;

bool cb(Modbus::ResultCode event, uint16_t transactionId, void* data) { // Callback to monitor errors
  if (event != Modbus::EX_SUCCESS) {
    Serial.print("Request result: 0x");
    Serial.print(event, HEX);
    Serial.println();
  }
  return true;
}

void setup() {
  Serial.begin(9600); // This serial for debug prints
  S.begin(9600, SWSERIAL_8N1);
  mb.begin(&S,D0); // RE/DE connected to D0 of ESP8266
  mb.master();
  
}

void loop() 
{
  if (!mb.slave()) 
  {
    mb.writeHreg(1,10,11,cb);
    while(mb.slave())
    {
      mb.task();
    }
    delay(10); 
  }
  if (!mb.slave()) 
  {
    mb.writeHreg(1,20,13,cb);
    while(mb.slave())
    {
      mb.task();
    }
    delay(10); 
  }
}
