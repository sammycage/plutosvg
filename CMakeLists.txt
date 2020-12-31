cmake_minimum_required(VERSION 3.3)

set(CMAKE_C_STANDARD 11)

project(plutosvg C)

set(PLUTOSVG_SOURCE
    plutosvg.c
    plutosvg.h)

add_library(plutosvg STATIC ${PLUTOSVG_SOURCE})

set(PLUTOVG_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/plutovg/include)
add_subdirectory(plutovg)
target_include_directories(plutosvg PUBLIC ${PLUTOVG_HEADER})
