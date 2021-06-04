cc_library(
  NAME render
  SRCS camera.cpp canvas.cpp world.cpp render.cpp
  DEPS rt_base
       rt_core
       rt_shapes
       rt_timer
       rt_parser
       opencv_core
       opencv_imgcodecs
       opencv_highgui)

cc_test(
  NAME render_test
  SRCS camera_test.cpp canvas_test.cpp render_test.cpp world_test.cpp
  DEPS rt_render rt_doctest_main
  OTHER)
