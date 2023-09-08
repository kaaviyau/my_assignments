#reads the position of a physical motor and displays the value on a LCD display 

#include <Arduino.h> // Include Arduino core library
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

 #define outputA D5
 #define outputB D6
 #define relayPin1 D4


 int counter = 0; 
 int aState;
 int aLastState;  

 void setup() { 
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   pinMode(relayPin1, OUTPUT);
   digitalWrite(relayPin1, HIGH);
   lcd.init();                      // initialize the lcd 
   lcd.backlight();
   Serial.begin (9600);
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA);   
 } 

 void loop() { 
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){ lcd.clear();    
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
     Serial.print("Position: ");
     Serial.println(counter);
     lcd.setCursor(0,0);
     lcd.print("Counter");
     lcd.setCursor(8,0);
     lcd.print(counter);
     lcd.setCursor(0,1);
     lcd.print("RUN");
     lcd.setCursor(0,2);
     lcd.print("STOP");
     lcd.setCursor(0,3);
     lcd.print("APPLE");
          
     if (counter>=200){
       Serial.println("Stop");
       digitalWrite(relayPin1, LOW);
     }
     else{
       digitalWrite(relayPin1, HIGH);
       Serial.println("RUN");
     }
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
 }
