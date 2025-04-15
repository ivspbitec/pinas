#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <U8g2_for_Adafruit_GFX.h>

#define TFT_CS   D8
#define TFT_RST  D4
#define TFT_DC   D3

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
U8G2_FOR_ADAFRUIT_GFX u8g2;

void setup() {
    tft.initR(INITR_GREENTAB);
    tft.setRotation(3);
    // после инициализации дисплея
tft.setSPISpeed(20000000); // 20 MHz

    tft.fillScreen(ST77XX_RED); // Ярко-красный экран
    delay(22);
    tft.fillScreen(ST77XX_GREEN);
    delay(22);
    tft.fillScreen(ST77XX_BLUE);
    delay(22);
    
    
  tft.fillScreen(ST77XX_BLACK);
  u8g2.setForegroundColor(ST77XX_WHITE);  // Цвет текста
  u8g2.setBackgroundColor(ST77XX_BLACK);  // Цвет фона
  
  u8g2.begin(tft);
//  u8g2.setFont(u8g2_font_cu12_t_cyrillic);

int y = 5;
// Шрифт 1
u8g2.setFont(u8g2_font_cu12_t_cyrillic);
u8g2.setCursor(0, y += 12);
u8g2.print("cu12: Привет, мир!");

// Шрифт 2
u8g2.setFont(u8g2_font_profont15_tf);
u8g2.setCursor(0, y += 15);
u8g2.print("profont15: Привет!");

// Шрифт 3
u8g2.setFont(u8g2_font_6x13_t_cyrillic);
u8g2.setCursor(0, y += 15);
u8g2.print("6x13: Привет, мир!");

// Шрифт 4
u8g2.setFont(u8g2_font_cu12_t_cyrillic);
u8g2.setCursor(0, y += 13);
u8g2.print("t0_11: Привет, мир!");

// Шрифт 5
u8g2.setFont(u8g2_font_9x15_t_cyrillic);
u8g2.setCursor(0, y += 17);
u8g2.print("9x15: Привет, мир!");

}

void loop() {}
