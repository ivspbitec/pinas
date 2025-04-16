// gauge.h
#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "widget.h"

#define COLOR(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))

class Gauge : public Widget
{
public:
  Gauge(int w, int h, const String &label, uint16_t bgColor = 0)
      : Widget(w, h, bgColor), _label(label) {}

  void update(int percent, const String &value)
  {
    _percent = percent;
    _value = value;
  }

  void render() override
  {
    GFXcanvas16 &canvas = getCanvas();
    U8G2_FOR_ADAFRUIT_GFX &u8g2 = getU8g2();

    canvas.fillScreen(_bgColor);

    int cx = _w / 2;
    int cy = _h / 2 + 0.1 * _h;
    int r = min(_w, _h) / 2 - 4;

    float startAngle = 180.0;
    float endAngle = 360.0;
    float range = endAngle - startAngle;

    int thickness = roundf(12.0f * _w / 80.0f);
    int steps = 60; // оптимальный баланс между скоростью и плотностью

    // Определяем цвет в зависимости от процентов
    uint16_t activeColor;
    if (_percent <= 50)
    {
        activeColor = COLOR(0, 255, 0); // Зеленый
    }
    else if (_percent <= 80)
    {
        activeColor = COLOR(255, 255, 0); // Желтый
    }
    else
    {
        activeColor = COLOR(255, 0, 0); // Красный
    }

    uint16_t inactiveColor = COLOR(10, 10, 10); // Серый для неактивных частей

    // Быстрая отрисовка дуги: одна линия на угол
    for (int i = 0; i < steps; i++)
    {
        float angle = startAngle + (range * i / steps);
        float rad = radians(angle);

        // Если неактивная часть — выходим из цикла
        if (i >= (_percent * steps) / 100)
            break;

        uint16_t color = activeColor;

        // Первая линия (основная дуга)
        int x0 = cx + cos(rad) * (r - thickness + 1);
        int y0 = cy + sin(rad) * (r - thickness + 1);
        int x1 = cx + cos(rad) * (r - 1);
        int y1 = cy + sin(rad) * (r - 1);
        canvas.drawLine(x0, y0, x1, y1, color);

        
    }

    u8g2.setBackgroundColor(_bgColor);

    // Текст процентов
    u8g2.setFont(u8g2_font_7x13_t_cyrillic);
    String percentText = String(_percent) + "%";
    int pw = u8g2.getUTF8Width(percentText.c_str());
    u8g2.setCursor((_w - pw) / 2, cy + 6);
    u8g2.setForegroundColor(COLOR(255, 255, 255));
    u8g2.print(percentText);

    // Заголовок
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
