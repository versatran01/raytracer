set(TEST_SOURCES
    canvas_test.cpp
    world_test.cpp
    camera_test.cpp
    render_test.cpp)

add_executable(raytracer_test_main raytracer_test_main.cpp ${TEST_SOURCES})
target_link_libraries(raytracer_test_main PRIVATE doctest::doctest raytracer)

add_test(NAME raytracer_test_main COMMAND raytracer_test_main)
