cmake_minimum_required(VERSION 3.3)

set(CMAKE_C_STANDARD 99)

project(example C)

add_executable(example example.c)
target_link_libraries(example plutosvg m)

FILE(COPY camera.svg DESTINATION "${CMAKE_BINARY_DIR}/example")
