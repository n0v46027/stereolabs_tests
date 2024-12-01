#include <fstream>
#include <string>
#include <cmath>

#include "parsing/Parser.hpp"
#include "Point.hpp"

static const char CLOUD_POINT_PATH[2][18] = {"conf/ptcloud1.txt",
                                             "conf/ptcloud2.txt"}; // files name
static const char FILE_ERROR[]            = "Unable to open file"; // error unable to open file

Parser::Parser() { // Parser class's constructor
  parse(CLOUD_POINT_1); // launch parsing for cloud point 1
  parse(CLOUD_POINT_2); // launch parsing for cloud point 2
}


/*
getter method for matrix
this method takes a as parameter:
    - a matrix
*/
std::array<std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE>, 2>
Parser::get_matrix() const {
  return _matrix;
}

/*
getter fmethod for points
this method takes a as parameter:
    - a matrix
*/
std::array<std::vector<point3D>, 2> Parser::get_points() const {
  return _points;
}

/*
method to parse a file
this method takes a as parameter:
    - a matrix
*/
void Parser::parse(int cloud_nb) {
  std::ifstream file(CLOUD_POINT_PATH[cloud_nb]); // load the file 
  std::string line; // line to load data from getline function
  point3D point = {0}; // temporary point to load data 

  if (!file.is_open()) // check if file is well opened
    throw std::runtime_error(FILE_ERROR);
  for (int i = 0; i < MATRIX_SIZE; i++) { // iterate trough the first line to get the matrix
    for (int j = 0; j < MATRIX_SIZE; j++) {
      file >> _matrix[cloud_nb][i][j];
    }
  }
  while (getline(file, line)) { // iterate through all the files to get the points
    for (int i = 0; i < 2; i++) {
      file >> point._points2D[i]; // get 2d coordinate
    }
    for (int i = 0; i < 3; i++) {
      file >> point._points3D[i]; // get 3d coordinate
    }
    point._points3D[3] = 1; // add manually 1 for homogenous coordianate and easier computation 
    for (int i = 0; i < 3; i++) {
      file >> point._rgb[i]; // get rgb value 
    }
    if (!std::isnan(point._points3D[0]) && !std::isnan(point._points3D[1]) &&
        !std::isnan(point._points3D[2])) { // check if value are correct
      _points[cloud_nb].push_back(point); // add value to the vector atribbute
    }
    point = {0};
  }
  file.close(); // close the file
}
