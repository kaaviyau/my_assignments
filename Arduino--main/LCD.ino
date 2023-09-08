#creates a design on an LCD display
#include <Arduino.h>
#include <SPI.h>

#include "Adafruit_ILI9341esp.h"
#include "Adafruit_GFX.h"
#include "XPT2046.h"
#define TFT_DC D4
#define TFT_CS D2

/*************COLORS**************
 
#define ILI9341_BLACK       0x0000     
#define ILI9341_NAVY        0x000F     
#define ILI9341_DARKGREEN   0x03E0      
#define ILI9341_DARKCYAN    0x03EF    
#define ILI9341_MAROON      0x7800      
#define ILI9341_PURPLE      0x780F      
#define ILI9341_OLIVE       0x7BE0     
#define ILI9341_LIGHTGREY   0xC618     
#define ILI9341_DARKGREY    0x7BEF     
#define ILI9341_BLUE        0x001F    
#define ILI9341_GREEN       0x07E0    
#define ILI9341_CYAN        0x07FF     
#define ILI9341_RED         0xF800     
#define ILI9341_MAGENTA     0xF81F     
#define ILI9341_YELLOW      0xFFE0     
#define ILI9341_WHITE       0xFFFF      
#define ILI9341_ORANGE      0xFD20     
#define ILI9341_GREENYELLOW 0xAFE5  
#define ILI9341_PINK        0xF81F
**********************************/

/******************* UI details */
#define BUTTON_X 40
#define BUTTON_Y 100
#define BUTTON_W 60
#define BUTTON_H 30
#define BUTTON_SPACING_X 20
#define BUTTON_SPACING_Y 20
#define BUTTON_TEXTSIZE 2

// text box where numbers go
#define TEXT_X 10
#define TEXT_Y 10
#define TEXT_W 220
#define TEXT_H 50
//#define TEXT_TSIZE 3

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
//XPT2046 touch(/*cs=*/ 4, /*irq=*/ 5);

void setup() 
{
  Serial.begin(115200);
  SPI.setFrequency(ESP_SPI_FREQ);
  tft.begin();
  //touch.begin(tft.width(), tft.height());  // Must be done before setting rotation
  Serial.print("tftx ="); Serial.print(tft.width()); Serial.print(" tfty ="); Serial.println(tft.height());
  tft.fillScreen(ILI9341_WHITE);
  //touch.setCalibration(1904, 314, 245, 1755);
}

void loop() 
{
 //tft.drawRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, ILI9341_WHITE);
 tft.setCursor(TEXT_X+10, TEXT_Y+10);
 tft.setTextColor(ILI9341_BLACK, ILI9341_WHITE);
 tft.setTextSize(2);
 tft.print("LETS GO");
}
