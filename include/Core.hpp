#ifndef INCLUDE_CORE_HPP_
#define INCLUDE_CORE_HPP_
#include <vector>
#include <array>
#include <tuple>
#include "parsing/Parser.hpp"


// class to handle computation
class Core {
public:
  Core();      // default constructor
  void run();  // method to coordinate all the program

protected:
private:
  void compute_distance(
      std::vector<point3D> &);  // method to compute the distancce of all points
  void save_img(const char[],
                std::vector<point3D> &);  // method to save the result image
  void transform_point_with_matrix(  // method to transform the points wirh the
                                     // matrix
      const std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE> &,
      const std::vector<point3D> &, std::vector<point3D> &);
  bool is_red(std::array<uint16_t, 3> &);  // method to check if a point is red
  Parser _parser;
  std::array<std::vector<point3D>, 2> _transform_points;
};

#endif  // INCLUDE_CORE_HPP_
