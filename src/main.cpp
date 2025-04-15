#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <U8g2_for_Adafruit_GFX.h>

#include "gauge.h"

#define TFT_CS   D8
#define TFT_RST  D4
#define TFT_DC   D3

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
//GFXcanvas1 canvas(160, 128); // монохромный буфер, экономит память
U8G2_FOR_ADAFRUIT_GFX u8g2;
GFXcanvas16 canvasg(160,128);  // размер буфера 
    
void setup() {  
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.setSPISpeed(40000000); // максимум для ST7735
  //tft.setAddrWindow(0, 0, 160, 128); // левый верхний угол — (0,0)
/* 
  u8g2.begin(canvas); // подключаем u8g2 к буферу

  canvas.fillScreen(0); // чёрный фон

  u8g2.setFontMode(0); // отключить сглаживание (быстрее)
  u8g2.setFontDirection(0);
  u8g2.setForegroundColor(1); // белый цвет (1 = белый в GFXcanvas1)
  u8g2.setBackgroundColor(0); // чёрный фон

  int y = 5; 
  u8g2.setFont(u8g2_font_6x13_t_cyrillic);
  u8g2.setCursor(0, y += 13);
  u8g2.print("6x13: Привет, мир!");

  u8g2.setFont(u8g2_font_9x15_t_cyrillic);
  u8g2.setCursor(0, y += 16);
  u8g2.print("9x15: Привет, мир!");

  u8g2.setFont(u8g2_font_7x13_t_cyrillic);
  u8g2.setCursor(0, y += 15);
  u8g2.print("7x13: Привет, мир!");

  u8g2.setFont(u8g2_font_8x13_t_cyrillic);
  u8g2.setCursor(0, y += 15);
  u8g2.print("8x13: Привет, мир!");

  // выводим буфер на экран
  tft.fillScreen(ST77XX_BLACK);
  tft.drawBitmap(0, 0, canvas.getBuffer(), canvas.width(), canvas.height(), ST77XX_WHITE);
*/
  tft.fillScreen(ST77XX_BLACK);
  u8g2.begin(canvasg);


}

 

  
void loop() {
  int percent = random(0, 101);
  float valueGB = 1000.0 * (100 - percent) / 100.0;

  int percent2 = random(0, 101);
  float valueGB2 = 1000.0 * (100 - percent) / 100.0;

  // Очистка буфера
  //canvasg.fillRect(0, 0, canvasg.width(), canvasg.height(), COLOR(150, 0, 0));  
  canvasg.fillRect(0, 0, 50  , 100, COLOR(150, 0, 0)); 

  drawGauge(canvasg, u8g2, 0, 0, 80 , 80, percent, "Диск", String(valueGB, 1) + " ГБ");
  drawGauge(canvasg, u8g2, 80, 0, 80, 80, percent, "Температура", String(valueGB2, 1) + " грд");

//rotateBuffer90CW(canvasg.getBuffer(), rotated, 128, 160);
//tft.drawRGBBitmap(0, 0, rotated, 160, 128);
  tft.drawRGBBitmap(0, 0, canvasg.getBuffer(), 160  ,128); 
 

  //delay(100);
} 