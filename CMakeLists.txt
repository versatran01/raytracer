cmake_minimum_required(VERSION 3.15)
project(raytracer CXX)
set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(Cache)
include(StaticAnalyzers)
include(CompilerWarnings)
add_library(${PROJECT_NAME}_warnings INTERFACE)
set_project_warnings(${PROJECT_NAME}_warnings)

add_library(${PROJECT_NAME}_options INTERFACE)
target_compile_features(${PROJECT_NAME}_options INTERFACE cxx_std_17)

option(BUILD_SHARED_LIBS "Build shared libraries" On)
option(BUILD_TESTING "Build testing" On)

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
