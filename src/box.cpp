#include <cstdint>

#include <GL/gl.h>

#include <boost/range/adaptor/reversed.hpp>

#include "box.h"

#define BOX_INTERVAL (2)

namespace piyopiyo
{
box::box()
{
  x = 0;
  y = 0;
  width = 1;
  start = 1;
  frame = 0;
}
box::box(std::int32_t _x, std::int32_t _y, std::uint8_t _w)
{
  x = _x;
  y = _y;
  width = _w;
  start = _w;
  frame = 0;
}
void box::draw()
{
  short left = x - ((width - 1) / 2);
  short bottom = y - ((width - 1) / 2);
  short right = x + ((width + 1) / 2);
  short top = y + ((width + 1) / 2);

  float c = ((float)start - frame) / (float)(start);
  glColor3f(c, c, c);
  glBegin(GL_QUADS);
  glVertex2s(left, bottom);
  glVertex2s(left, top);
  glVertex2s(right, top);
  glVertex2s(right, bottom);
  glEnd();
  frame++;
  // if (frame % BOX_INTERVAL != 0) return;
  width--;
}

void ppBoxes::add(std::int32_t x, std::int32_t y, std::uint8_t w)
{
  boxes.push_back(box(x, y, w));
}
void ppBoxes::draw()
{
  for (auto &b : boost::adaptors::reverse(boxes)) {
    b.draw();
  }
}
void ppBoxes::erase()
{
  auto itr = boxes.begin();
  while (itr != boxes.end()) {
    if (itr->width == 0) {
      itr = boxes.erase(itr);
    } else {
      itr++;
    }
  }
}
}
