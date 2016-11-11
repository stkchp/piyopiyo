#pragma once

#include <cstdint>
#include <vector>

namespace piyopiyo
{
class particle
{
private:
  double x;
  double y;
  double vx;
  double vy;
  std::uint64_t frame;
  std::uint8_t span;

public:
  bool eol;
  particle(std::int32_t, std::int32_t);
  void draw();
};
class ppParticles
{
private:
  std::vector<particle> particles;

public:
  void add(std::int32_t, std::int32_t);
  void draw();
  void erase();
};
}
