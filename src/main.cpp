#include <iostream>

#include "Core.hpp"

static const int KO = 84;
static const int OK = 0;

int main(void) {
  try { // try catch to handle error handling
    Core core = Core(); // instanciate core class
    core.run(); // call run method
    return OK; // return 0 if program succeeded
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return KO; // return 84 if program failed
  }
  return OK; // return 0 if program succeeded
}