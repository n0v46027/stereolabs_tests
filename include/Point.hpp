#ifndef INCLUDE_POINT_HPP_
#define INCLUDE_POINT_HPP_
#include <array>

enum {
       RED = 0,
       GREEN = 1,
       BLUE = 2,
};

enum {
       HUE = 0,
       SATURATION = 1,
       VALUE = 2,
};

struct point3D {
  std::array<uint16_t, 2> _points2D;
  std::array<double, 4> _points3D;
  std::array<uint16_t, 3> _rgb;
  bool _is_in_range = false;
};

#endif  // INCLUDE_POINT_HPP_
