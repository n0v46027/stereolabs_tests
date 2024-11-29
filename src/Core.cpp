#include <array>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <opencv2/opencv.hpp>

#include "Point.hpp"
#include "Core.hpp"

Core::Core() : _parser(Parser()) {
}

void Core::transform_matrix(
    const std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE> &matrix,
    const std::vector<point3D> &points,
    std::vector<point3D> &transform_points) {
  point3D new_point = {0};

  for (auto &point : points) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
      for (int j = 0; j < MATRIX_SIZE; j++) {
        new_point._points3D.at(i) += point._points3D.at(j) * matrix.at(i).at(j);
      }
    }
    new_point._points2D = point._points2D;
    new_point._rgb = point._rgb;
    transform_points.push_back(new_point);
    new_point = {0};
  }
}

bool Core::is_red(std::array<uint16_t, 3> &rgb) {
    cv::Mat rgb_pixel(1, 1, CV_8UC3, cv::Scalar(rgb[2], rgb[1], rgb[0]));
    cv::Mat hsv_pixel;
    cv::cvtColor(rgb_pixel, hsv_pixel, cv::COLOR_BGR2HSV);

    cv::Vec3b hsv = hsv_pixel.at<cv::Vec3b>(0, 0);
    int h = hsv[0];
    int s = hsv[1];
    int v = hsv[2];

    bool hueInRange = (h >= 0 && h <= 10) || (h >= 160 && h <= 180);
    bool saturationInRange = (s > 100);
    bool valueInRange = (v > 100);
    
    return hueInRange && saturationInRange && valueInRange;
}
  

void Core::compute_distance(std::vector<point3D> &transform_points) {
  for (auto &point : transform_points) {
    double distance =
        std::sqrt((point._points3D.at(0) * point._points3D.at(0)) +
                  (point._points3D.at(1) * point._points3D.at(1)) +
                  (point._points3D.at(2) * point._points3D.at(2)));
    if (distance >= 1 && distance <= 2 && is_red(point._rgb)) {
      point._is_in_range = true;
    }
  }
}

void Core::run() {
  transform_matrix(_parser.get_matrix().at(CLOUD_POINT_1),
                   _parser.get_points().at(CLOUD_POINT_1),
                   _transform_points.at(CLOUD_POINT_1));
  transform_matrix(_parser.get_matrix().at(CLOUD_POINT_2),
                   _parser.get_points().at(CLOUD_POINT_2),
                   _transform_points.at(CLOUD_POINT_2));
  compute_distance(_transform_points.at(CLOUD_POINT_1));
  compute_distance(_transform_points.at(CLOUD_POINT_2));
}

Core::~Core() {
}
