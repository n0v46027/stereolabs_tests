#ifndef INCLUDE_CORE_HPP_
#define INCLUDE_CORE_HPP_
#include <vector>
#include <array>
#include "parsing/Parser.hpp"

class Core {
public:
  Core();

  void transform_matrix(const std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE> &, const std::vector<point3D> &, std::vector<point3D> &);
  void run();
  ~Core();

protected:
private:
    Parser _parser;
    std::array<std::vector<point3D>, 2> _transform_points;

};

#endif  // INCLUDE_CORE_HPP_
