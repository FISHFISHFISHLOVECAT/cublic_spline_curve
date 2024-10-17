cmake_minimum_required(VERSION 3.22)
project(demo1)

set(SRC
    cubic_spline_curve.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${SRC})
target_link_libraries(${PROJECT_NAME} m)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")