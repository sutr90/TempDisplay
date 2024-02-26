#include <Arduino.h>
// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0
#include <SPI.h>
#include <GxEPD2_BW.h>
#include "BebasNeue_Limited72pt7b.h"

// RP2040-Zero CS(SS)=1,SCL(SCK)=2,SDA(MOSI)=3,BUSY=6,RES(RST)=5,DC=4

// 1.54'' EPD WeAct Module
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=1*/ 1, /*DC=*/ 4, /*RES=*/ 5, /*BUSY=*/ 6)); // GDEH0154D67 200x200, SSD1681

const char HelloWorld[] = "-44*";

void helloWorld()
{
  display.setRotation(1);
  display.setTextWrap(false);
  display.setFont(&BebasNeue_Limited72pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh; // boundary box window
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh); // it works for origin 0, 0, fortunately (negative tby!)
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE); // set the background to white (fill the buffer with value for white)
  display.setCursor(x, y); // set the postition to start printing text
  display.print(HelloWorld); // print some text
  // tell the graphics class to transfer the buffer content (page) to the controller buffer
  // and to refresh to the screen
  display.display(false); // full update
}


void setup()
{
  SPI.setRX(0);
  SPI.setCS(1);
  SPI.setSCK(2);
  SPI.setTX(3);

  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);

  display.init(115200, true, 50, false);
  helloWorld();
  display.hibernate();
}


void loop() {
  
  Serial.print(display.width());
  Serial.print("  ");
  Serial.print(display.height());
  Serial.println();
  delay(2000);
}
