cmake_minimum_required(VERSION 3.3)

set(CMAKE_C_STANDARD 11)

project(plutosvg C)

set(PLUTOSVG_SOURCE
    plutosvg.c
    plutosvg.h
)

add_library(plutosvg STATIC ${PLUTOSVG_SOURCE})

add_subdirectory(plutovg)
add_subdirectory(example)

target_include_directories(plutosvg
PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/plutovg/include"
)
