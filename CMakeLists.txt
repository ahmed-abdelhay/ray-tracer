cmake_minimum_required (VERSION 3.8)
project (ray_tracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(source_list image.cpp)
add_executable(ray_tracer ${source_list})
