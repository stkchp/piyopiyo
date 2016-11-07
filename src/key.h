#pragma once

#include <array>
#include <cstdint>

namespace piyopiyo
{
// enum
namespace gameKey
{
enum Type : uint8_t {
  Up,
  Down,
  Left,
  Right,
  Start,
  Select,
  Action,
  Cancel,
  Menu,
  Info,
  Menu_left,
  Menu_right
};
}
// alias
using keyType = gameKey::Type;

class ppKey
{
private:
  std::array<std::uint64_t, 0x100> state;
  std::array<int, 0x100> config;

public:
  ppKey();
  uint64_t get(uint8_t);
  void set(uint8_t, int);
  void callback(int, bool);
};
}
