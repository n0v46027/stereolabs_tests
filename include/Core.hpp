#ifndef INCLUDE_CORE_HPP_
#define INCLUDE_CORE_HPP_
#include "parsing/Parser.hpp"

class Core {
public:
  Core();
  void run();
  ~Core();

protected:
private:
    Parser _parser;

};

#endif  // INCLUDE_CORE_HPP_
