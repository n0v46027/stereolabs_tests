#ifndef INCLUDE_PARSING_PARSER_HPP_
#define INCLUDE_PARSING_PARSER_HPP_

#include <array>
#include <vector>

#include "Point.hpp"

static const uint8_t MATRIX_SIZE = 4;  // matrix size

// class to handle parsing
enum {  // enum to determine which file we are processing
  CLOUD_POINT_1 = 0,
  CLOUD_POINT_2 = 1,
};

class Parser {
public:
  Parser();  // constructor
  std::array<std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE>, 2>
  get_matrix() const;  // getter method for matrix
  std::array<std::vector<point3D>, 2> get_points()
      const;  // getter fmethod for points

protected:
private:
  void parse(int);  // private method to parse file
  std::array<std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE>, 2>
      _matrix;  // data structure to store both matrix
  std::array<std::vector<point3D>, 2>
      _points;  // data structure to store points
};

#endif  // INCLUDE_PARSING_PARSER_HPP_
