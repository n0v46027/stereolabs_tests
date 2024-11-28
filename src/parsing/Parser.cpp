#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

#include "parsing/Parser.hpp"
#include "Point.hpp"

static const char CLOUD_POINT_PATH[2][18] = {"conf/ptcloud1.txt", "conf/ptcloud2.txt"};

Parser::Parser() {
    parse(CLOUD_POINT_1);
    parse(CLOUD_POINT_2);
}

void Parser::parse(int cloud_nb) {
    std::ifstream file(CLOUD_POINT_PATH[cloud_nb]);
    std::string line;
    point3D point;

    if (!file.is_open())
        throw std::runtime_error("Unable to open file");
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
