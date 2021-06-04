cc_library(
  NAME doctest_main
  SRCS doctest_main.cpp
  DEPS doctest::doctest)

add_subdirectory(core)
add_subdirectory(shapes)
add_subdirectory(utils)
add_subdirectory(render)

# these tests depends on shapes so we have to pull them out
cc_test(
  NAME extra_test
  SRCS core/intersection_test.cpp core/material_test.cpp core/pattern_test.cpp
  DEPS rt_core rt_shapes rt_doctest_main
  OTHER)
