cmake_minimum_required(VERSION 3.15)
project(raytracer CXX)
set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CC_TARGET_PREFIX rt)
include(CMakeHelpers)
add_library(rt_options INTERFACE)
enable_warnings(rt_options)
enable_sanitizers(rt_options)

option(BUILD_SHARED_LIBS "Build shared libraries" On)
option(BUILD_TESTING "Build testing" On)

find_package(TBB REQUIRED)
find_package(fmt REQUIRED)
find_package(absl REQUIRED)
find_package(glog REQUIRED)
find_package(Eigen3 REQUIRED NO_MODULE)
find_package(OpenCV 4 REQUIRED)
find_package(doctest REQUIRED)

cc_library(
  NAME base
  DEPS fmt::fmt glog::glog rt_options
  INCDIRS ${CMAKE_CURRENT_SOURCE_DIR}
  INTERFACE)

enable_testing()
add_subdirectory(rt)
add_subdirectory(examples)
