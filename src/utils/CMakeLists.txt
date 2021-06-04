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
