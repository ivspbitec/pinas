// vertical_bar.h
#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "widget.h"

#define COLOR(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))

class VerticalBar : public Widget
{
public:
  VerticalBar(int w, int h, const String &label, uint16_t bgColor = 0)
      : Widget(w, h, bgColor), _label(label) {}

  void update(int percent, const String &value)
  {
    _percent = constrain(percent, 0, 100);
    _value = value;
  }

  void render() override
  {
    GFXcanvas16 &canvas = getCanvas();
    U8G2_FOR_ADAFRUIT_GFX &u8g2 = getU8g2();

    canvas.fillScreen(_bgColor);

    int barWidth = _w * 0.4;
    int barX = (_w - barWidth) / 2;
    int barY = 20;
    int barHeight = _h - 40;

    int filledHeight = (barHeight * _percent) / 100;
    int emptyHeight = barHeight - filledHeight;

    for (int y = 0; y < barHeight; y++)
    {
      float ratio = float(y) / float(barHeight);
      uint8_t rC, gC;

      if (y >= emptyHeight)
      {
        // filled part
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
      }
      else
      {
        // empty part
        rC = gC = 10;
      }

      uint16_t color = COLOR(rC, gC, 0);
      canvas.drawFastHLine(barX, barY + y, barWidth, color);
    }

    u8g2.setBackgroundColor(_bgColor);
    u8g2.setFont(u8g2_font_7x13_t_cyrillic);

    // Текст процентов
    String percentText = String(_percent) + "%";
    int pw = u8g2.getUTF8Width(percentText.c_str());
    u8g2.setCursor((_w - pw) / 2, 12);
    u8g2.setForegroundColor(COLOR(255, 255, 255));
    u8g2.print(percentText);

    // Значение
    int vw = u8g2.getUTF8Width(_value.c_str());
    u8g2.setCursor((_w - vw) / 2, _h - 6);
    u8g2.print(_value);

    // Подпись
    int lw = u8g2.getUTF8Width(_label.c_str());
    u8g2.setCursor((_w - lw) / 2, _h - 18);
    u8g2.print(_label);
  }

private:
  String _label;
  String _value;
  int _percent = 0;
};
