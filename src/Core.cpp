#include <array>
#include <vector>
#include <cmath>
#include <algorithm>
#include <opencv2/opencv.hpp>

#include "Point.hpp"
#include "Core.hpp"

static const uint16_t WIDTH  = 511;  // width of the image
static const uint16_t HEIGHT = 287;  // height of the image
static const char FILE_1[] =
    "img1.png";  // filename of the first cloud point render
static const char FILE_2[] =
    "img2.png";  // filename of the scnd cloud point render

Core::Core() : _parser(Parser()) {  // Core class's constructor
}

/*
method to transform the point with the matrix
This method applies the transformation matrix to the 3D points
this method takes a as parameter:
    - a matrix
    - the points
    - the data structure to store the transformaed points
*/
void Core::transform_point_with_matrix(
    const std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE> &matrix,
    const std::vector<point3D> &points,
    std::vector<point3D> &transform_points) {
  point3D new_point = {
      0};  // set a point to fill the transform_point data structure

  for (auto point : points) {                // iterate throug all the point
    for (int i = 0; i < MATRIX_SIZE; i++) {  // iterate through matrix in y
      for (int j = 0; j < MATRIX_SIZE;
           j++) {  // iterate through the matrix in x
        new_point._points3D.at(i) +=
            point._points3D.at(j) *
            matrix.at(i).at(j);  // apply transformation to the point
      }
    }
    new_point._points2D = point._points2D;  // reload the unchanged 2D point
    new_point._rgb      = point._rgb;       // reload the unchanged RGB point
    transform_points.push_back(
        new_point);   // add the new point to the trandform point
    new_point = {0};  // reset the new points no avoid corrupting value
  }
}

/*
method to check if a RGB color is red it will convert to hsv then operate the
check this method take as parameter:
    - RGB values
*/
bool Core::is_red(std::array<uint16_t, 3> &rgb) {
  cv::Mat rgb_pixel(
      1, 1, CV_8UC3,
      cv::Scalar(rgb[2], rgb[1], rgb[0]));  // set a OpenCv pixel in rgb
  cv::Mat hsv_pixel;  // set an hsv pixel to store the convert RGB value
  cv::cvtColor(
      rgb_pixel, hsv_pixel,
      cv::COLOR_BGR2HSV);  // convert RGB (OpenCv needs BGR format) in HSV

  cv::Vec3b hsv =
      hsv_pixel.at<cv::Vec3b>(0, 0);  // Extract the HSV values of the pixel
  int h = hsv[0];
  int s = hsv[1];
  int v = hsv[2];

  /*Check if the Hue (color tone) falls within the range for red
  Red in HSV is circular and split into two ranges:
  Lower red (0–10) and Upper red (160–180)*/
  bool hue_in_range = (h >= 0 && h <= 10) || (h >= 160 && h <= 180);
  /*Check if the Saturation is sufficiently high to ensure the color is not
  faded or grayish A saturation value greater than 100 indicates a strong
  color*/
  bool saturation_in_range = (s > 100);
  /*Check if the brightness (Value) is sufficiently high to ensure the color is
  visible A value greater than 100 indicates the color is bright enough*/
  bool value_in_range = (v > 100);

  return hue_in_range && saturation_in_range &&
         value_in_range;  // return true if it is a red pixel otherwise false
}

/*
method to compute the euclidian distance between camera and point
this method take as parameter:
    - RGB values
*/
void Core::compute_distance(std::vector<point3D> &transform_points) {
  double distance = 0;
  for (auto &point : transform_points) {  // iterate through all points
    /* variable to store the distance between the camera and point
    the formula is = √(p0^2) + (p1^2) + (p2^2) the camera is equal to 0 so we
    only need to compute the point*/
    distance = std::sqrt((point._points3D.at(0) * point._points3D.at(0)) +
                         (point._points3D.at(1) * point._points3D.at(1)) +
                         (point._points3D.at(2) * point._points3D.at(2)));
    if (is_red(point._rgb) && distance >= 1 &&
        distance <= 2) {  // check if the point is red and if his distance is
                          // between 1 meter and 2 meter
      point._is_in_range =
          true;  // set the boolean at true if the condition is true
    }
  }
}
void Core::save_img(
    const char filename[],
    std::vector<point3D> &transform_point) {  // method to save the image
  cv::Mat img(
      HEIGHT, WIDTH, CV_8UC3,
      cv::Scalar(0, 0, 0));  // create a OpenCv grid of inital color black
  for (auto &point : transform_point) {  // iterate troufgh the point
    if (point._is_in_range) {  // if the point's boolean data is true then we
                               // set the pixel color to red
      cv::Vec3b &pixel =
          img.at<cv::Vec3b>(point._points2D.at(0),
                            point._points2D.at(1));  // get the target pixel
      pixel[2] = 255;                                // set R at full for red
    }
  }
  cv::imwrite(filename, img);  // save the image in the designe filename
}

void Core::run() {  // method to coordinate all the program
  transform_point_with_matrix(
      _parser.get_matrix().at(
          CLOUD_POINT_1),  // call transform_point_with_matrix for first cloud
                           // point
      _parser.get_points().at(CLOUD_POINT_1),
      _transform_points.at(CLOUD_POINT_1));
  transform_point_with_matrix(
      _parser.get_matrix().at(
          CLOUD_POINT_2),  // call transform_point_with_matrix for snd cloud
                           // point
      _parser.get_points().at(CLOUD_POINT_2),
      _transform_points.at(CLOUD_POINT_2));
  compute_distance(_transform_points.at(
      CLOUD_POINT_1));  // call compute_distance for first cloud point
  compute_distance(_transform_points.at(
      CLOUD_POINT_2));  // call compute_distance for scnd cloud point
  save_img(FILE_1, _transform_points.at(
                       CLOUD_POINT_1));  // call save_img for first cloud point
  save_img(FILE_2, _transform_points.at(
                       CLOUD_POINT_2));  // call save_img for sncd cloud point
}
