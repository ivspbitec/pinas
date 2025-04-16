// gauge_bar.h
#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "widget.h"

#define COLOR(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))

class GaugeBar : public Widget
{
public:
  GaugeBar(int w, int h, const String &label, uint16_t bgColor = 0)
      : Widget(w, h, bgColor), _label(label) {}

  void update(int percent, const String &value)
  {
    _percent = percent;
    _value = value;
  }



uint16_t mixColor(uint16_t c1, uint16_t c2, float ratio)
{
    // RGB565 → компоненты
    uint8_t r1 = (c1 >> 11) & 0x1F;
    uint8_t g1 = (c1 >> 5) & 0x3F;
    uint8_t b1 = c1 & 0x1F;

    uint8_t r2 = (c2 >> 11) & 0x1F;
    uint8_t g2 = (c2 >> 5) & 0x3F;
    uint8_t b2 = c2 & 0x1F;

    // смешиваем
    uint8_t r = roundf(r1 * ratio + r2 * (1 - ratio));
    uint8_t g = roundf(g1 * ratio + g2 * (1 - ratio));
    uint8_t b = roundf(b1 * ratio + b2 * (1 - ratio));

    return (r << 11) | (g << 5) | b;
}



  void render() override
  {
    GFXcanvas16 &canvas = getCanvas();
    U8G2_FOR_ADAFRUIT_GFX &u8g2 = getU8g2();

    canvas.fillScreen(_bgColor);

    int cx = _w / 2;
    int cy = _h / 2;
    int outerR = min(_w, _h) / 2 - 4;
    int thickness = roundf(12.0f * _w / 80.0f);
    int innerR = outerR - thickness;

    float startAngle = 180.0f;
    float endAngle = 360.0f;
    float range = endAngle - startAngle;
    float maxAngle = startAngle + range * (_percent / 100.0f);

    // Цвет целиком
    uint8_t rC = 0, gC = 0, bC = 0;
    float ratio = _percent / 100.0f;
    if (ratio <= 0.5f)
    {
      rC = roundf(ratio * 2.0f * 255.0f);
      gC = 255;
    }
    else
    {
      rC = 255;
      gC = roundf((1.0f - ratio) * 2.0f * 255.0f);
    }
    uint16_t color = COLOR(rC, gC, bC);

    for (int x = cx - outerR; x <= cx + outerR; x++)
    {
      float dx = x - cx;
      float dx2 = dx * dx;

      if (dx2 > outerR * outerR)
        continue;

      float dyOuter = sqrtf(outerR * outerR - dx2);
      float dyInner = sqrtf(innerR * innerR - dx2);

      for (int sign = -1; sign <= 1; sign += 2)
      {
        float yOuter = cy + dyOuter * sign;
        float yInner = cy + dyInner * sign;

        float angle = atan2f(yOuter - cy, dx) * 180.0f / PI;
        if (angle < 0)
          angle += 360.0f;

        if (angle < startAngle || angle > maxAngle)
          continue;

        int y0 = round(yInner);
        int y1 = round(yOuter);

        // исправление направления
        int y_top = min(y0, y1);
        int height = abs(y1 - y0) + 1;


// корректировка: если x за пределами внутреннего кольца, линии начинаются от cy
if (x < cx - innerR || x > cx + innerR)
{
    // рисуем от yOuter до cy
    int y_start = round(yOuter);
    int y_end = cy;

    if (y_start > y_end)
        std::swap(y_start, y_end);

    y_top = y_start;
    height = y_end - y_start + 1;
}
     







     

        canvas.drawFastVLine(x, y_top, height, color);





 



      }
    }

    // Центрированный текст
    u8g2.setFontMode(0);
    u8g2.setBackgroundColor(_bgColor);
    u8g2.setForegroundColor(COLOR(255, 255, 255));

    // Процент
    u8g2.setFont(u8g2_font_8x13_t_cyrillic);
    String percentText = String(_percent) + "%";
    int pw = u8g2.getUTF8Width(percentText.c_str());
    u8g2.setCursor((_w - pw) / 2, cy + 6);
    u8g2.print(percentText);

    // Заголовок
    u8g2.setFont(u8g2_font_6x13_t_cyrillic);
    int lw = u8g2.getUTF8Width(_label.c_str());
    u8g2.setCursor((_w - lw) / 2, 10);
    u8g2.print(_label);

    // Значение
    int vw = u8g2.getUTF8Width(_value.c_str());
    u8g2.setCursor((_w - vw) / 2, _h - 6);
    u8g2.print(_value);
  }

private:
  String _label;
  String _value;
  int _percent = 0;
};
