// widget.h
#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <U8g2_for_Adafruit_GFX.h>

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
};
 