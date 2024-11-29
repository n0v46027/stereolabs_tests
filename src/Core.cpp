#include <array>
#include <vector>
#include <iostream>

#include "Point.hpp"
#include "Core.hpp"

Core::Core() : _parser(Parser()) {
}

void Core::transform_matrix(const std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE> &matrix, const std::vector<point3D> &points, std::vector<point3D> &transform_points) {
    point3D new_point = {0};
    
    for (auto &point: points) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                new_point._points3D.at(i) += point._points3D.at(j) * matrix.at(i).at(j);
            }
        }
        transform_points.push_back(new_point);
        new_point = {0};
    }
}

void Core::compute_distance(std::vector<point3D> &transform_points) {
    for (auto &point: transform_points) {
        double distance = std::sqrt((point._points3D.at(0) * point._points3D.at(0)) + (point._points3D.at(1) * point._points3D.at(1)) + (point._points3D.at(2) * point._points3D.at(2)));
        if (distance >= 1 && distance <= 2) {
            point._is_in_range = true;
        }
    }
}

void Core::run() {
    transform_matrix(_parser.get_matrix().at(CLOUD_POINT_1), _parser.get_points().at(CLOUD_POINT_1), _transform_points.at(CLOUD_POINT_1));
    transform_matrix(_parser.get_matrix().at(CLOUD_POINT_2), _parser.get_points().at(CLOUD_POINT_2), _transform_points.at(CLOUD_POINT_2));
    compute_distance(_transform_points.at(CLOUD_POINT_1));
    compute_distance(_transform_points.at(CLOUD_POINT_2));
}

Core::~Core() {
}
