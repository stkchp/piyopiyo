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

    // event
    while (window.events.size() > 0) {
      auto ev = window.events.front();
      window.events.pop();
      std::cout << "event:" << ev.mouse << " " << ev.key << " " << ev.value
                << " " << ev.x << " " << ev.y << std::endl;
      if (!ev.mouse && !ev.key) {
        if (ev.y < 0) {
          cursor.shift();
        } else if (ev.y > 0) {
          cursor.bigger();
        }
      }
    }
    // cursor move
    if (frame % 4 == 0) {
      cursor.move(window.cx, window.cy);
      if (ox != window.cx || oy != window.cy) {
        if (0 <= window.cx && window.cx <= window.vwidth) {
          if (0 <= window.cy && window.cy <= window.vheight) {
            std::uint8_t s = std::hypot(window.cx - ox, window.cy - oy);
            boxes.add(window.cx, window.cy, s, cursor.cr, cursor.cg, cursor.cb);
          }
        }
        ox = window.cx;
        oy = window.cy;
      }
    }
    cursor.draw();
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
