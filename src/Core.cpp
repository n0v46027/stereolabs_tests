#include <array>
#include <vector>
#include <iostream>

#include "Point.hpp"
#include "Core.hpp"

Core::Core()
: _parser(Parser()){
}

void Core::transform_matrix(const std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE> &matrix, const std::vector<point3D> &points, std::vector<point3D> &transform_points) {
    point3D new_point = {0};
    
    for (auto &point: points) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                std::cout << point._points3D.at(j) << " " << matrix.at(i).at(j) << std::endl;
                new_point._points3D.at(i) += point._points3D.at(j) * matrix.at(i).at(j);
            }
        }
        std::cout << new_point._points3D.at(0) << " " << new_point._points3D.at(1) << " " << new_point._points3D.at(2) << " " << new_point._points3D.at(3) << std::endl;
        break;
    }
}

void Core::run() {
    transform_matrix(_parser.get_matrix().at(CLOUD_POINT_1), _parser.get_points().at(CLOUD_POINT_1), _transform_points.at(CLOUD_POINT_1));
}

Core::~Core() {
}
