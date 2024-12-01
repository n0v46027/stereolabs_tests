cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(stereo_test VERSION 1.0)

set(SRCS # set SRCS variable which contains the source files
    src/main.cpp
    src/Core.cpp
    src/parsing/Parser.cpp
)

find_package(OpenCV REQUIRED) # find the package OpenCv

add_executable(stereo ${SRCS}) # add the executable

target_include_directories(stereo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) # target the include directory to  avoir relative path
target_link_libraries(stereo ${OpenCV_LIBS}) # link the libraries