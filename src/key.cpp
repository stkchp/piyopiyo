#include <iostream>

#include "key.h"

namespace piyopiyo
{
ppKey::ppKey() { state.fill(0); }
uint64_t ppKey::get(uint8_t _key) { return state.at(_key); }
void ppKey::set(uint8_t _key, int _code) { config.at(_key) = _code; }
void ppKey::callback(int _key, bool _press)
{
  if (_press) {
    for (auto i = 0; i < state.size(); i++) {
      if (_key == config.at(i)) {
        state.at(i) = 1;
        std::cout << "ppKey: pressed ->" << i << std::endl;
      }
    }
  } else {
    for (auto i = 0; i < state.size(); i++) {
      if (_key == config.at(i)) {
        state.at(i) = 0;
        std::cout << "ppKey: released ->" << i << std::endl;
      }
    }
  }
}
}
