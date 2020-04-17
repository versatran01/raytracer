add_library(
  raytracer SHARED
  intersection.cpp
  material.cpp
  world.cpp
  camera.cpp
  render.cpp
  sphere.cpp
  pattern.cpp
  shape.cpp
  cube.cpp
  cylinder.cpp
  timer.cpp)
target_include_directories(raytracer PUBLIC .)
target_link_libraries(
  raytracer
  PUBLIC glog::glog
         fmt::fmt
         Eigen3::Eigen
         Boost::boost
         Boost::timer
         opencv_core
         opencv_imgproc
         opencv_imgcodecs
         opencv_highgui
         absl::time
         absl::container)
