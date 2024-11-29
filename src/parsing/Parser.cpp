#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

#include "parsing/Parser.hpp"
#include "Point.hpp"

static const char CLOUD_POINT_PATH[2][18] = {"conf/ptcloud1.txt", "conf/ptcloud2.txt"};
static const char FILE_ERROR[] = "Unable to open file";

Parser::Parser() {
    parse(CLOUD_POINT_1);
    parse(CLOUD_POINT_2);
}

std::array<std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE>, 2> Parser::get_matrix() const {
    return _matrix;
}

std::array<std::vector<point3D>, 2> Parser::get_points() const {
    return _points;
}

void Parser::parse(int cloud_nb) {
    std::ifstream file(CLOUD_POINT_PATH[cloud_nb]);
    std::string line;
    point3D point;

    if (!file.is_open())
        throw std::runtime_error(FILE_ERROR);
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            file >> _matrix[cloud_nb][i][j];
        }
    }
    while (getline(file, line)) {
        for (int i = 0; i < 2; i++) {
            file >> point._points2D[i];
        }
        for (int i = 0; i < 3; i++) {
            file >> point._points3D[i];
        }
        point._points3D[3] = 1;
        for (int i = 0; i < 3; i++) {
            file >> point._rgb[i];
        }
        if(!std::isnan(point._points3D[0]) && !std::isnan(point._points3D[1]) && !std::isnan(point._points3D[2])) {
            _points[cloud_nb].push_back(point);
        }
    }
    file.close();
}

Parser::~Parser() {
}
