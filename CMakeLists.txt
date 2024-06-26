cmake_minimum_required(VERSION 3.29 FATAL_ERROR)
project(RayTracing VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set(CMAKE_FIND_FRAMEWORK NEVER)
#set(SFML_STATIC_LIBRARIES False)

#if(NOT CMAKE_BUILD_TYPE)
#  set(CMAKE_BUILD_TYPE Debug
#    CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
#endif()

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

configure_file(config.h.in config.h)

add_executable(RayTracing)

target_link_libraries(RayTracing PRIVATE sfml-graphics)

add_subdirectory(src)
