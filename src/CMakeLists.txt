cc_library(
  NAME doctest_main
  SRCS doctest_main.cpp
  DEPS doctest::doctest)

cc_library(
  NAME intersection
  SRCS intersection.cpp
  DEPS rt_base Eigen3::Eigen)

add_subdirectory(shapes)

cc_library(
  NAME utils
  SRCS utils/timer.cpp
  DEPS rt_base absl::time absl::strings absl::flat_hash_map)

add_library(
  raytracer SHARED
  canvas.cpp
  material.cpp
  world.cpp
  camera.cpp
  render.cpp
  pattern.cpp
  parser.cpp)
target_include_directories(raytracer PUBLIC . utils shapes)
target_link_libraries(
  raytracer
  PUBLIC opencv_core
         opencv_imgproc
         opencv_imgcodecs
         opencv_highgui
         TBB::tbb
         rt_intersection
         rt_shapes
         rt_utils)
