#ifndef INCLUDE_POINT_HPP_
#define INCLUDE_POINT_HPP_
#include <array>

enum { // enum for RGB
  RED   = 0,
  GREEN = 1,
  BLUE  = 2,
};

enum { // enum for HSV
  HUE        = 0,
  SATURATION = 1,
  VALUE      = 2,
};

struct point3D { // data structure to handle point
  std::array<uint16_t, 2> _points2D; // data structure to store 2Dpoints
  std::array<double, 4> _points3D; // data structure to store 3Dpoints
  std::array<uint16_t, 3> _rgb; // data structure to store RGB values
  bool _is_in_range = false; // boolean to indicate whether this point need to be displayed
};

#endif  // INCLUDE_POINT_HPP_
