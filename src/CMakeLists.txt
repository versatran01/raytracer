cc_library(
  NAME shapes
  SRCS shapes/shape.cpp
       shapes/cone.cpp
       shapes/cube.cpp
       shapes/cylinder.cpp
       shapes/group.cpp
       shapes/triangle.cpp
       shapes/smooth_triangle.cpp
       shapes/sphere.cpp
  DEPS rt_base Eigen3::Eigen)

cc_library(
  NAME utils
  SRCS utils/timer.cpp
  DEPS rt_base absl::time absl::strings absl::flat_hash_map)

add_library(
  raytracer SHARED
  canvas.cpp
  intersection.cpp
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
         rt_shapes
         rt_utils)
