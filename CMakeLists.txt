cmake_minimum_required(VERSION 3.15)
project(fractal CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

add_library(${PROJECT_NAME}_options INTERFACE)
target_compile_features(${PROJECT_NAME}_options INTERFACE cxx_std_17)

add_library(${PROJECT_NAME}_warnings INTERFACE)

include(cmake/Cache.cmake)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(${PROJECT_NAME}_warnings)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" ON)
option(BUILD_TESTING "Enable Test Builds" OFF)

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
