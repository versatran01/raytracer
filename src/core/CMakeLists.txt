cc_library(
  NAME core
  HDRS color.h light.h ray.h transform.h tuple.h types.h
  DEPS rt_base Eigen3::Eigen
  INTERFACE)

cc_test(
  NAME core_test
  SRCS color_test.cpp light_test.cpp ray_test.cpp transform_test.cpp
       tuple_test.cpp
  DEPS rt_core rt_doctest_main
  OTHER)
