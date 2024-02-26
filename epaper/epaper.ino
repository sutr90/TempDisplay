#include <Arduino.h>
#define ENABLE_GxEPD2_GFX 0

#include <SPI.h>
#include <GxEPD2_BW.h>
#include "BebasNeue_Limited72pt7b.h"
#include <Fonts/Picopixel.h>

// RP2040-Zero CS(SS)=1,SCL(SCK)=2,SDA(MOSI)=3,BUSY=6,RES(RST)=5,DC=4

// 1.54'' EPD WeAct Module
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=1*/ 1, /*DC=*/ 4, /*RES=*/ 5, /*BUSY=*/ 6)); // GDEH0154D67 200x200, SSD1681

void drawTemp(bool neg)
{
  char temperature[] = " 29*";

  if (neg) {
    temperature[0] = '-';
  } else {
    temperature[0] = ' ';
  }
  
  display.setRotation(1);
  display.setTextWrap(false);
  display.setFont(&BebasNeue_Limited72pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh; // boundary box window
  display.getTextBounds(temperature, 0, 0, &tbx, &tby, &tbw, &tbh); // it works for origin 0, 0, fortunately (negative tby!)
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE); // set the background to white (fill the buffer with value for white)
  
  display.setCursor(x + 15, y); // set the postition to start printing text
  display.print(temperature); // print some text

  char timestamp[] = "2024-01-01 23:59";

  display.setFont(&Picopixel);
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(0, 4); // set the postition to start printing text
  display.print(timestamp); // print some text
  
  display.display(false); // full update
}

void setup()
{
  SPI.setRX(0);
  SPI.setCS(1);
  SPI.setSCK(2);
  SPI.setTX(3);

  display.init(115200, true, 50, false);
  drawTemp(true);
  display.hibernate();
}


void loop() {

  delay(5000);
//
//  display.init(115200, true, 50, false);
//  drawTemp(true);
//  drawTimestamp();
//  display.hibernate();
//  delay(5000);
}
