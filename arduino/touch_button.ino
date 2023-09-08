#connects a touch button sensor to the controller
#include <Wire.h>
#include <PCF8574.h>
#include "Arduino.h"


PCF8574 addr2(0x20);
PCF8574 addr1(0x26);

int state1=0;
int state2=0;
int state3=0;
int state4=0;
int state5=0;
int state6=0;
int state7=0;
int state8=0;

int touchbuttonstate1=LOW;
int touchbuttonstate2=LOW;
int touchbuttonstate3=LOW;
int touchbuttonstate4=LOW;
int touchbuttonstate5=LOW;
int touchbuttonstate6=LOW;
int touchbuttonstate7=LOW;
int touchbuttonstate8=LOW;

#define RELAY_PIN_1      0
#define RELAY_PIN_2      1
#define RELAY_PIN_3      2
#define RELAY_PIN_4      3
#define RELAY_PIN_5      4
#define RELAY_PIN_6      5
#define RELAY_PIN_7      6
#define RELAY_PIN_8      7

#define TOUCH_PIN_1      0
#define TOUCH_PIN_2      1
#define TOUCH_PIN_3      2
#define TOUCH_PIN_4      3
#define TOUCH_PIN_5      4
#define TOUCH_PIN_6      5
#define TOUCH_PIN_7      6
#define TOUCH_PIN_8      7

int parity=0;
int astate=0;

void setup()
{
  Serial.begin(9600);
  addr1.pinMode(RELAY_PIN_1, OUTPUT); 
  addr1.pinMode(RELAY_PIN_2, OUTPUT);
  addr1.pinMode(RELAY_PIN_3, OUTPUT); 
  addr1.pinMode(RELAY_PIN_4, OUTPUT);
  addr1.pinMode(RELAY_PIN_5, OUTPUT);
  addr1.pinMode(RELAY_PIN_6, OUTPUT);
  addr1.pinMode(RELAY_PIN_7, OUTPUT);
  addr1.pinMode(RELAY_PIN_8, OUTPUT);
  addr2.pinMode(TOUCH_PIN_1, INPUT); 
  addr2.pinMode(TOUCH_PIN_2, INPUT); 
  addr2.pinMode(TOUCH_PIN_3, INPUT); 
  addr2.pinMode(TOUCH_PIN_4, INPUT); 
  addr2.pinMode(TOUCH_PIN_5, INPUT); 
  addr2.pinMode(TOUCH_PIN_6, INPUT); 
  addr2.pinMode(TOUCH_PIN_7, INPUT); 
  addr2.pinMode(TOUCH_PIN_8, INPUT); 

  addr1.begin();
  addr2.begin();
  state1 = addr2.digitalRead(TOUCH_PIN_1);
  state2 = addr2.digitalRead(TOUCH_PIN_2);
  state3 = addr2.digitalRead(TOUCH_PIN_3);
  state4 = addr2.digitalRead(TOUCH_PIN_4);
  state5 = addr2.digitalRead(TOUCH_PIN_5);
  state6 = addr2.digitalRead(TOUCH_PIN_6);
  state7 = addr2.digitalRead(TOUCH_PIN_7);
  state8 = addr2.digitalRead(TOUCH_PIN_8);
  astate=state1;

}



void loop()
{  

  state1 = addr2.digitalRead(TOUCH_PIN_1);
  state2 = addr2.digitalRead(TOUCH_PIN_2);
  state3 = addr2.digitalRead(TOUCH_PIN_3);
  state4 = addr2.digitalRead(TOUCH_PIN_4);
  state5 = addr2.digitalRead(TOUCH_PIN_5);
  state6 = addr2.digitalRead(TOUCH_PIN_6);
  state7 = addr2.digitalRead(TOUCH_PIN_7);
  state8 = addr2.digitalRead(TOUCH_PIN_8);
  Serial.println(state1);     //01
  if(state1==1)
  {
   parity++;
   delay(1000);
  }
  if(parity%2==0)
  {
   addr1.digitalWrite(RELAY_PIN_1, LOW);
  }
  if(parity%2!=0)
  {
   addr1.digitalWrite(RELAY_PIN_1, HIGH);
  }
  else
  {
    //touchbuttonstate1=HIGH;
  }
  if (state2==1){
    addr1.digitalWrite(RELAY_PIN_2, LOW);
  }
  if (state3==1){
    addr1.digitalWrite(RELAY_PIN_3, LOW);
  }
  if (state4==1){
    addr1.digitalWrite(RELAY_PIN_7, LOW);
    addr1.digitalWrite(RELAY_PIN_2, LOW);
    addr1.digitalWrite(RELAY_PIN_4, LOW);
    addr1.digitalWrite(RELAY_PIN_6, LOW);
    addr1.digitalWrite(RELAY_PIN_8, LOW);
    }
    /*addr1.digitalWrite(RELAY_PIN_1, HIGH);
    addr1.digitalWrite(RELAY_PIN_2, HIGH);
    addr1.digitalWrite(RELAY_PIN_3, HIGH);
    addr1.digitalWrite(RELAY_PIN_4, HIGH);
    addr1.digitalWrite(RELAY_PIN_5, HIGH);
    addr1.digitalWrite(RELAY_PIN_6, HIGH);
    addr1.digitalWrite(RELAY_PIN_7, HIGH);
    addr1.digitalWrite(RELAY_PIN_8, HIGH);*/
    delay(50);
  
}
