#pragma once

#include <array>
#include <cstdint>
#include <string>

#include "box.h"
#include "cursor.h"
#include "window.h"

namespace piyopiyo
{
class piyopiyo
{
private:
  std::uint32_t state;
  std::uint64_t frame;
  ppWindow window;
  ppBoxes boxes;
  ppCursor cursor;

  bool init();
  void loop();
  void destroy();

public:
  bool run();
};
}
