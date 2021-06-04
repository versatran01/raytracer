cc_library(
  NAME doctest_main
  SRCS doctest_main.cpp
  DEPS doctest::doctest)

cc_library(
  NAME core
  HDRS color.h light.h ray.h transform.h tuple.h types.h
  SRCS intersection.cpp material.cpp pattern.cpp
  DEPS rt_base Eigen3::Eigen)

cc_test(
  NAME core_test
  SRCS color_test.cpp light_test.cpp ray_test.cpp tuple_test.cpp
       transform_test.cpp
  DEPS rt_core rt_doctest_main
  OTHER)

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
  DEPS rt_base rt_core)

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
  DEPS rt_shapes rt_doctest_main
  OTHER)

cc_test(
  NAME extra_test
  SRCS intersection_test.cpp material_test.cpp pattern_test.cpp
  DEPS rt_core rt_shapes rt_doctest_main
  OTHER)

cc_library(
  NAME timer
  SRCS timer.cpp
  DEPS rt_base absl::time absl::strings absl::flat_hash_map)

cc_test(
  NAME timer_test
  SRCS timer_test.cpp
  DEPS rt_timer rt_doctest_main
  OTHER)

cc_library(
  NAME parser
  SRCS parser.cpp
  DEPS rt_base rt_core rt_shapes)

cc_test(
  NAME parser_test
  SRCS parser_test.cpp
  DEPS rt_parser rt_doctest_main
  OTHER)

cc_library(
  NAME render
  SRCS camera.cpp canvas.cpp world.cpp render.cpp
  DEPS rt_base
       rt_core
       rt_shapes
       rt_timer
       rt_parser
       opencv_core
       opencv_highgui
       TBB::tbb)

cc_test(
  NAME render_test
  SRCS camera_test.cpp canvas_test.cpp render_test.cpp world_test.cpp
  DEPS rt_render rt_doctest_main
  OTHER)
