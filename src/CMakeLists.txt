cc_library(
  NAME doctest_main
  SRCS doctest_main.cpp
  DEPS doctest::doctest)

add_subdirectory(core)

cc_library(
  NAME intersection
  SRCS intersection.cpp
  DEPS rt_core)

add_subdirectory(shapes)
add_subdirectory(utils)

add_library(raytracer SHARED canvas.cpp material.cpp world.cpp camera.cpp
                             render.cpp pattern.cpp)
target_include_directories(raytracer PUBLIC . utils shapes)
target_link_libraries(
  raytracer
  PUBLIC opencv_core
         opencv_imgproc
         opencv_imgcodecs
         opencv_highgui
         TBB::tbb
         rt_core
         rt_shapes
         rt_timer
         rt_intersection
         rt_parser)
