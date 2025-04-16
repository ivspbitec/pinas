#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <U8g2_for_Adafruit_GFX.h>
#include <vector>

#include "w_gauge.h"
#include "w_gauge_bar.h"
#include "w_vertical_bar.h"
#include "w_line_chart.h"

// #define TFT_CS   D8
// #define TFT_RST  D4
// #define TFT_DC   D3
// #define TFT_CS   4
// #define TFT_RST  1
// #define TFT_DC   5

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
#define BTN1_PIN 20
#define BTN2_PIN 21

bool btn1State = false;
bool btn2State = false;

volatile bool btn1Pressed = false;
volatile bool btn2Pressed = false;

void IRAM_ATTR handleBtn1Press() {
  btn1Pressed = true;
}

void IRAM_ATTR handleBtn2Press() {
  btn2Pressed = true;
}


Gauge w1(80, 60, "Диск");
// GaugeBar w2(80, 60, "Температура");
VerticalBar w3(40, 128, "CPU");
LineChart w2(120, 60, "Download speed", COLOR(0, 60, 60), COLOR(0, 0, 0));
std::vector<int> values;
const int maxPoints = 50;
unsigned long lastUpdate = 0;

void setup()
{
    pinMode(BTN1_PIN, INPUT_PULLUP);
    pinMode(BTN2_PIN, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(BTN1_PIN), handleBtn1Press, FALLING);
    attachInterrupt(digitalPinToInterrupt(BTN2_PIN), handleBtn2Press, FALLING);

    setCpuFrequencyMhz(160); // уже максимум для ESP32-C3
    SPI.begin(2, -1, 3);     // SCK = 2, MOSI = 3

    tft.initR(INITR_BLACKTAB);
    tft.setRotation(1);
    tft.setSPISpeed(40000000); // максимум для ST7735
    // tft.setAddrWindow(0, 0, 160, 128); // левый верхний угол — (0,0)
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

    w2.setTitleColor(COLOR(255, 255, 200)); // Set title color to red
}


void loop()
{
    if (btn1Pressed) {
        btn1Pressed = false;
        // например — сбросить график
        values.clear();
    }

    if (btn2Pressed) {
        btn2Pressed = false;
        // например — остановить обновление
        return;
    }

    int percent = random(0, 101);
    float valueGB = 1000.0 * (100 - percent) / 100.0;
    w1.update(percent, String(valueGB, 1) + " ГБ");

    percent = random(0, 101);
    valueGB = 1000.0 * (100 - percent) / 100.0;
    w3.update(percent, String(valueGB, 1) + " ГБ");

    values.push_back(random(0, 101));
    if (values.size() > maxPoints)
        values.erase(values.begin());

    String currentValue = String(values.back());
    w2.update(values, 100, currentValue, percent);  

    w1.drawTo(tft, 0, 0);
    w2.drawTo(tft, 0, 60);
    w3.drawTo(tft, 120, 0);
}
