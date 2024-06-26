cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

target_sources(RayTracing PRIVATE camera.cpp colour.cpp interval.cpp main.cpp point3.cpp random.cpp ray.cpp vector3.cpp)

add_subdirectory(Materials)
add_subdirectory(Shapes)

