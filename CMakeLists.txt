cmake_minimum_required(VERSION 3.3)

set(CMAKE_C_STANDARD 99)

project(plutosvg C)

set(PLUTOSVG_SOURCE
    source/plutosvg.c
    source/plutosvg.h
)

add_library(plutosvg STATIC ${PLUTOSVG_SOURCE})

add_subdirectory(plutovg)
add_subdirectory(example)

target_include_directories(plutosvg PUBLIC source)
target_link_libraries(plutosvg PUBLIC plutovg)
