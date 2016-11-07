#include <cstdlib>

#include "piyopiyo.h"

int main(int argc, char **argv)
{
  piyopiyo::piyopiyo p;

  return p.run() ? EXIT_SUCCESS : EXIT_FAILURE;
}
