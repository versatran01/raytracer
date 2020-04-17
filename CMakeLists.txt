cmake_minimum_required(VERSION 3.15)
project(raytracer_challenge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(doctest REQUIRED)
find_package(Eigen3 REQUIRED NO_MODULE)
find_package(OpenCV 4 REQUIRED)
find_package(absl REQUIRED)
find_package(glog REQUIRED)
find_package(Boost REQUIRED COMPONENTS timer)
find_package(fmt REQUIRED)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)
