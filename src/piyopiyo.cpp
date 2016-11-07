#include <cmath>
#include <iostream>

#include "piyopiyo.h"

namespace piyopiyo
{
bool piyopiyo::init()
{
  frame = 0;
  state = 1;
  window.setTitle("piyopiyo");
  if (!window.create()) return false;

  return true;
}

void piyopiyo::loop()
{
  int ox, oy;
  while (state) {
    if (window.shouldClose()) {
      state = 0;
      continue;
    }
    if (frame % 60 == 0) {
      // check window resized
      window.adjust();
    }
    window.clear();

    if (frame % 4 == 0) {
      if (ox != window.cx || oy != window.cy) {
        if (0 <= window.cx && window.cx <= window.vwidth) {
          if (0 <= window.cy && window.cy <= window.vheight) {
            std::uint8_t s = std::hypot(window.cx - ox, window.cy - oy);
            boxes.add(window.cx, window.cy, s);
          }
        }
        ox = window.cx;
        oy = window.cy;
      }
    }
    boxes.draw();
    boxes.erase();
    window.calcFps();
    window.swapBuffers();
    window.pollEvents();
    frame++;
  }
}

void piyopiyo::destroy() { window.destroy(); }
bool piyopiyo::run()
{
  if (!init()) {
    std::cerr << "Error: create window failure." << std::endl;
    return false;
  }
  loop();
  destroy();

  return true;
}
}
