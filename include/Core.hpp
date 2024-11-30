#ifndef INCLUDE_CORE_HPP_
#define INCLUDE_CORE_HPP_
#include <vector>
#include <array>
#include <tuple>
#include "parsing/Parser.hpp"

class Core {
public:
  Core();
  void run();
  ~Core();

protected:
private:
  void compute_distance(std::vector<point3D> &);
  void save_img(const char[], std::vector<point3D> &);
  void transform_matrix(
      const std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE> &,
      const std::vector<point3D> &, std::vector<point3D> &);
  bool is_red(std::array<uint16_t, 3> &);
  Parser _parser;
  std::array<std::vector<point3D>, 2> _transform_points;
};

#endif  // INCLUDE_CORE_HPP_
