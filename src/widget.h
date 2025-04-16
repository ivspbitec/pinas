// widget.h
#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <U8g2_for_Adafruit_GFX.h>
#define COLOR(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))

class Widget {
public:
  Widget(int w, int h, uint16_t bgColor = 0)
    : _w(w), _h(h), _bgColor(bgColor) {
    static int id_counter = 0;
    _id = "w" + String(id_counter++);

    _canvas = new GFXcanvas16(w, h);
      
    _u8g2 = new U8G2_FOR_ADAFRUIT_GFX();
    _u8g2->begin(*_canvas);
  }

  

  virtual void render() = 0;

  virtual void drawTo(Adafruit_GFX& display, int x, int y) {
    render();
    //display.fillRect(x, y, _w, _h, _bgColor);
    display.drawRGBBitmap(x, y, getCanvas().getBuffer(), _w, _h);
  }

  virtual GFXcanvas16& getCanvas() {
    return *_canvas;
  }

  virtual U8G2_FOR_ADAFRUIT_GFX& getU8g2() {
    return *_u8g2;
  }

protected:
  String _id;
  int _w, _h;
  uint16_t _bgColor;

  GFXcanvas16* _canvas;
  U8G2_FOR_ADAFRUIT_GFX* _u8g2;

  // Calculate a single color based on the percentage (0-100)
  uint16_t percentColor(uint8_t percent) {
    uint8_t rC, gC;
    float ratio = float(percent) / 100.0f;
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
    // COLOR macro must be defined elsewhere, e.g., #define COLOR(r,g,b) ...
    return COLOR(rC, gC, 0);
  }
};
