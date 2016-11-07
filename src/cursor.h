#pragma once

#include <cstdint>
#include <random>

namespace piyopiyo
{
class ppCursor
{
private:
  int x;
  int y;
  std::uint8_t width;
  std::uint64_t frame;

public:
  ppCursor();
  std::uint8_t cr;
  std::uint8_t cg;
  std::uint8_t cb;

  void move(int, int);
  void bigger();
  void shift();
  void draw();
};
}
