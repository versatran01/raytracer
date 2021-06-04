cc_library(
  NAME shapes
  SRCS shape.cpp
       plane.cpp
       cone.cpp
       cube.cpp
       sphere.cpp
       cylinder.cpp
       triangle.cpp
       smooth_triangle.cpp
       group.cpp
  DEPS rt_base Eigen3::Eigen)

cc_test(
  NAME shapes_test
  SRCS cone_test.cpp
       cube_test.cpp
       sphere_test.cpp
       cylinder_test.cpp
       group_test.cpp
       plane_test.cpp
       shape_test.cpp
       triangle_test.cpp
       smooth_triangle_test.cpp
  DEPS rt_shapes rt_intersection rt_doctest_main
  OTHER)
