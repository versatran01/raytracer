enable_testing(true)

set(TEST_SOURCES
    tuple_test.cpp
    color_test.cpp
    canvas_test.cpp
    ray_test.cpp
    intersection_test.cpp
    transform_test.cpp
    sphere_test.cpp
    light_test.cpp
    material_test.cpp
    world_test.cpp
    camera_test.cpp
    plane_test.cpp
    pattern_test.cpp
    cube_test.cpp
    cylinder_test.cpp
    render_test.cpp)

add_executable(raytracer_test_main raytracer_test_main.cpp ${TEST_SOURCES})
target_link_libraries(raytracer_test_main PRIVATE doctest::doctest raytracer)
