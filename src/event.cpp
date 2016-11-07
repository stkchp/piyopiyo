
#include "event.h"

namespace piyopiyo
{
event::event(bool _m, bool _k, int _v)
{
  mouse = _m;
  key = _k;
  value = _v;
  x = 0;
  y = 0;
}
event::event(double _x, double _y)
{
  mouse = false;
  key = false;
  value = 0;
  x = _x;
  y = _y;
}
}
