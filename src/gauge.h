#pragma once
#include <Adafruit_GFX.h>
#include <U8g2_for_Adafruit_GFX.h>

//BGR
//#define COLOR(r, g, b) (((b & 0xF8) << 8) | ((g & 0xFC) << 3) | (r >> 3))

//RGB
#define COLOR(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))


// Отрисовка gauge в указанный canvas, в прямоугольник (x, y, w, h)
void drawGauge(GFXcanvas16 &canvas, U8G2_FOR_ADAFRUIT_GFX &u8g2, int x, int y, int w, int h, int percent, const String &label, const String &value) {
  int cx = x + w / 2;
  int cy = y + h / 2;
  int r = min(w, h) / 2 - 4;



  float startAngle = 180.0;
  float endAngle = 360.0;
  float range = endAngle - startAngle;

  int thickness=roundf(12*w/80);
  int steps = 300; 
  for (int i = 0; i < steps; i++) {
    float angle = startAngle + (range * i / steps);
    float rad = radians(angle);

    uint8_t rC = 0, gC = 0, bC = 0;
    float ratio = float(i) / float(steps);

    if (i < (percent * steps) / 100) {
      if (ratio <= 0.5f) {
        rC = roundf(ratio * 2.0f *  255.0f); 
        gC = 255; 
      } else {
        rC = 255;
        gC = ((1-ratio)* 2.0f)*255.0f   ;  // от 255 до 0
      }
    } else {
      rC = gC = bC = 10;
    }

    uint16_t color = COLOR(rC, gC, bC);
    //uint16_t color = COLOR(255, 0, 0);

    for (int thick = r - 1; thick >= r - thickness; thick--) {
      int x0 = cx + cos(rad) * thick;
      int y0 = cy + sin(rad) * thick;
      canvas.drawPixel(x0, y0, color);
    }
  }



  // Текст процентов
  u8g2.setFont(u8g2_font_8x13_t_cyrillic);
  u8g2.setCursor(cx - 18, cy + 6);
  u8g2.setForegroundColor(COLOR(255, 255, 255));
  u8g2.print(String(percent) + "%");

  // Заголовок
  u8g2.setFont(u8g2_font_6x13_t_cyrillic);
  u8g2.setCursor(x + 4, y + 10);
  u8g2.print(label);

  // Значение
  u8g2.setCursor(x + 4, y + h - 6);
  u8g2.print(value);
}
