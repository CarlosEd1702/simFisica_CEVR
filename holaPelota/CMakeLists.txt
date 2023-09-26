cmake_minimum_required(VERSION 3.26)
project(holaPelota)

set(CMAKE_CXX_STANDARD 17)

add_executable(holaPelota main.cpp)
find_package(box2d CONFIG REQUIRED)
target_link_libraries(holaPelota PRIVATE box2d::box2d)