#ifndef INCLUDE_PARSING_PARSER_HPP_
#define INCLUDE_PARSING_PARSER_HPP_

#include <array>
#include <vector>

#include "Point.hpp"

static const int MATRIX_SIZE = 4;

enum {
  CLOUD_POINT_1 = 0,
  CLOUD_POINT_2 = 1,
};

class Parser {
public:
  Parser();
  std::array<std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE>, 2>
  get_matrix() const;
  std::array<std::vector<point3D>, 2> get_points() const;
  ~Parser();

protected:
private:
  void parse(int);
  std::array<std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE>, 2>
      _matrix;
  std::array<std::vector<point3D>, 2> _points;
};

#endif  // INCLUDE_PARSING_PARSER_HPP_
