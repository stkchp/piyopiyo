
#include <random>

#include <GL/gl.h>

#include "cursor.h"

namespace piyopiyo
{
ppCursor::ppCursor()
{
  width = 1;
  frame = 0;
  cr = 255;
  cg = 255;
  cb = 255;
}
void ppCursor::move(int _x, int _y)
{
  x = _x;
  y = _y;
}

void ppCursor::bigger() { width += 5; }
void ppCursor::shift()
{
  std::random_device rd;
  cr = rd() % 256;
  cg = rd() % 256;
  cb = rd() % 256;
}

void ppCursor::draw()
{
  short left = x - ((width - 1) / 2);
  short bottom = y - ((width - 1) / 2);
  short right = x + ((width + 1) / 2);
  short top = y + ((width + 1) / 2);

  glColor3ub(cr, cg, cb);
  glBegin(GL_QUADS);
  glVertex2s(left, bottom);
  glVertex2s(left, top);
  glVertex2s(right, top);
  glVertex2s(right, bottom);
  glEnd();
  frame++;
  if (frame % 5 != 0) return;
  width--;
  if (width == 0) width = 1;
}
}
