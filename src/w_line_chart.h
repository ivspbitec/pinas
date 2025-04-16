#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "widget.h"

class LineChart : public Widget
{
public:
  LineChart(int w, int h, const String &title, uint16_t fillColor, uint16_t bgColor = 0, uint16_t titleColor = COLOR(255, 255, 255))
      : Widget(w, h, bgColor), _fillColor(fillColor), _title(title), _titleColor(titleColor) {}

  void update(const std::vector<int> &data, int maxValue, const String &value = "", int percent = 0)
  {
    _data = data;
    _maxValue = max(1, maxValue); // чтобы избежать деления на 0
    _value = value;
    _percent = constrain(percent, 0, 100);
  }

  void setTitleColor(uint16_t color)
  {
    _titleColor = color;
  }

  void render() override
  {
    GFXcanvas16 &canvas = getCanvas();
    canvas.fillScreen(_bgColor);

    int dataSize = _data.size();
    if (dataSize < 2) return;

    float xStep = float(_w) / float(dataSize - 1);

    for (int i = 0; i < dataSize - 1; i++)
    {
      int x0 = roundf(i * xStep);
      int x1 = roundf((i + 1) * xStep);

      int y0 = map(_data[i], 0, _maxValue, _h - 1, 0);
      int y1 = map(_data[i + 1], 0, _maxValue, _h - 1, 0);

      for (int x = x0; x <= x1; x++)
      {
        float t = (x1 == x0) ? 0 : float(x - x0) / float(x1 - x0);
        int y = roundf(y0 + (y1 - y0) * t);

        canvas.drawFastVLine(x, y, _h - y, _fillColor);
      }
    }
 
    U8G2_FOR_ADAFRUIT_GFX &u8g2 = getU8g2();
    u8g2.setBackgroundColor(_bgColor);
   
    // Заголовок диаграммы
    u8g2.setFont(u8g2_font_6x13_t_cyrillic);
    u8g2.setForegroundColor(_titleColor);
    int tw = u8g2.getUTF8Width(_title.c_str());
    u8g2.setCursor((_w - tw) / 2, _h - 6);
    u8g2.print(_title);

    // Текущее значение
    String valueText = _value + " (" + String(_percent) + "%)";
    int vw = u8g2.getUTF8Width(valueText.c_str());
    u8g2.setCursor((_w - vw) / 2, 10);
    u8g2.print(valueText);
  }

private:
  std::vector<int> _data;
  int _maxValue = 100;
  uint16_t _fillColor;
  String _title;
  uint16_t _titleColor;
  String _value;
  int _percent = 0;
};
