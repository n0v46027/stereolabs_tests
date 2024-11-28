#include <iostream>

#include "Core.hpp"

static const int KO = 84;
static const int OK = 0;

int main(void) {
  try {
    Core core = Core();
    core.run();
    return OK;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return KO;
  }
  return OK;
}