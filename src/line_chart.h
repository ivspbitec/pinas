#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "widget.h"

class LineChart : public Widget
{
public:
  LineChart(int w, int h, uint16_t fillColor, uint16_t bgColor = 0)
      : Widget(w, h, bgColor), _fillColor(fillColor) {}

  void update(const std::vector<int> &data, int maxValue)
  {
    _data = data;
    _maxValue = max(1, maxValue); // чтобы избежать деления на 0
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
  }

private:
  std::vector<int> _data;
  int _maxValue = 100;
  uint16_t _fillColor;
};
