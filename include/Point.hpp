#ifndef INCLUDE_CLOUD_POINT_HPP_
#define INCLUDE_CLOUD_POINT_HPP_
#include <array>

struct point3D {
       std::array<uint16_t, 2> _points2D;
       std::array<double, 3> _points3D;
       std::array<uint16_t, 3> _rgb;
};

#endif // INCLUDE_CLOUD_POINT_HPP_
