#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <U8g2_for_Adafruit_GFX.h>


#include "widget.h"
#include "gauge.h"
#include "gauge_bar.h"


//#define TFT_CS   D8
//#define TFT_RST  D4
//#define TFT_DC   D3
//#define TFT_CS   4
//#define TFT_RST  1
//#define TFT_DC   5

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
 


void setup() {  
  setCpuFrequencyMhz(160); // уже максимум для ESP32-C3
  SPI.begin(2, -1, 3); // SCK = 2, MOSI = 3

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
delay(100);
tft.fillScreen(ST77XX_BLUE);
delay(100);
tft.fillScreen(ST77XX_RED);
delay(100);
tft.fillScreen(ST77XX_GREEN);
delay(100);
tft.fillScreen(ST77XX_BLACK);
}

 

GaugeBar gauge1(80, 120, "Диск");
GaugeBar gauge2(80, 120, "Температура");
  
void loop() {
  int percent = random(0, 101);
  float valueGB = 1000.0 * (100 - percent) / 100.0;

  int percent2 = random(0, 101);
  float valueGB2 = 1000.0 * (100 - percent2) / 100.0;

  gauge1.update(percent, String(valueGB, 1) + " ГБ");
  gauge2.update(percent2, String(valueGB2, 1) + " грд");

  gauge1.drawTo(tft, 0, 0);
  gauge2.drawTo(tft, 80, 0);

  //delay(100);
}
