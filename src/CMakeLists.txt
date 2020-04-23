add_library(
  raytracer SHARED
  intersection.cpp
  material.cpp
  world.cpp
  camera.cpp
  render.cpp
  pattern.cpp
  shapes/shape.cpp
  shapes/cube.cpp
  shapes/cylinder.cpp
  shapes/cone.cpp
  shapes/group.cpp
  shapes/triangle.cpp
  shapes/sphere.cpp
  utils/timer.cpp)
target_include_directories(raytracer PUBLIC . utils shapes)
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
