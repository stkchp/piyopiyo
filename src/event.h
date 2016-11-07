#pragma once

#include <queue>

namespace piyopiyo
{
class event
{
public:
  bool mouse;
  bool key;
  int value;
  double x;
  double y;

  event(bool, bool, int);
  event(double, double);
};

using ppEvents = std::queue<event>;
}
