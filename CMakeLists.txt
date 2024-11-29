cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(stereo_test VERSION 1.0)

set(SRCS
    src/main.cpp
    src/Core.cpp
    src/parsing/Parser.cpp
)

add_executable(stereo ${SRCS})

target_include_directories(stereo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)