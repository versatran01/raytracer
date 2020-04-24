add_executable(tuple_demo tuple_demo.cpp)
target_link_libraries(tuple_demo PRIVATE raytracer)

add_executable(canvas_demo canvas_demo.cpp)
target_link_libraries(canvas_demo PRIVATE raytracer)

add_executable(ray_sphere_demo ray_sphere_demo.cpp)
target_link_libraries(ray_sphere_demo PRIVATE raytracer)

add_executable(shading_demo shading_demo.cpp)
target_link_libraries(shading_demo PRIVATE raytracer)

add_executable(render_demo render_demo.cpp)
target_link_libraries(render_demo PRIVATE raytracer)

add_executable(group_demo group_demo.cpp)
target_link_libraries(group_demo PRIVATE raytracer)

add_executable(triangle_demo triangle_demo.cpp)
target_link_libraries(triangle_demo PRIVATE raytracer)

add_executable(parser_demo parser_demo.cpp)
target_link_libraries(parser_demo PRIVATE raytracer)
