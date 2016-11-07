#pragma once

#include <cstdint>
#include <vector>

namespace piyopiyo
{
class box
{
private:
  std::uint8_t start;
  std::uint8_t cr;
  std::uint8_t cg;
  std::uint8_t cb;

public:
  box();
  box(std::int32_t, std::int32_t, std::uint8_t);
  box(std::int32_t, std::int32_t, std::uint8_t, std::uint8_t, std::uint8_t,
      std::uint8_t);
  std::int32_t x;
  std::int32_t y;
  std::uint8_t width;
  std::uint64_t frame;
  void draw();
};

class ppBoxes
{
private:
  std::vector<box> boxes;

public:
  void add(std::int32_t, std::int32_t, std::uint8_t);
  void add(std::int32_t, std::int32_t, std::uint8_t, std::uint8_t, std::uint8_t,
           std::uint8_t);
  void draw();
  void erase();
};
}
