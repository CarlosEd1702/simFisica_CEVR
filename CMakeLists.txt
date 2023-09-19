cmake_minimum_required(VERSION 3.26)
project(tema1)

set(CMAKE_CXX_STANDARD 17)

add_executable(tema1 main.cpp)

find_package(box2d CONFIG REQUIRED)
target_link_libraries(tema1 PRIVATE box2d::box2d)