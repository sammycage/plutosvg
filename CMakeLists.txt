cmake_minimum_required(VERSION 3.15)

set(PLUTOSVG_VERSION_MAJOR 0)
set(PLUTOSVG_VERSION_MINOR 0)
set(PLUTOSVG_VERSION_MICRO 2)

project(plutosvg LANGUAGES C VERSION ${PLUTOSVG_VERSION_MAJOR}.${PLUTOSVG_VERSION_MINOR}.${PLUTOSVG_VERSION_MICRO})

include(FetchContent)
FetchContent_Declare(plutovg
    GIT_REPOSITORY https://github.com/sammycage/plutovg.git
    GIT_TAG main
    GIT_SHALLOW ON
    FIND_PACKAGE_ARGS 0.0.3
)

FetchContent_MakeAvailable(plutovg)

set(plutosvg_sources source/plutosvg.c)
set(plutosvg_headers source/plutosvg.h)

add_library(plutosvg ${plutosvg_sources} ${plutosvg_headers})
add_library(plutosvg::plutosvg ALIAS plutosvg)

set_target_properties(plutosvg PROPERTIES
    SOVERSION ${PLUTOSVG_VERSION_MAJOR}
    C_VISIBILITY_PRESET hidden
    C_STANDARD_REQUIRED ON
    C_STANDARD 99
)

target_include_directories(plutosvg PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/source
)

target_include_directories(plutosvg PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
    $<INSTALL_INTERFACE:include/plutosvg>
)

target_link_libraries(plutosvg PUBLIC plutovg::plutovg)
target_compile_definitions(plutosvg PRIVATE PLUTOSVG_BUILD)
if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(plutosvg PUBLIC PLUTOSVG_BUILD_STATIC)
endif()

option(PLUTOSVG_ENABLE_FREETYPE "Enable Freetype integration" OFF)
if(PLUTOSVG_ENABLE_FREETYPE)
    find_package(Freetype 2.12 REQUIRED)
    target_compile_definitions(plutosvg PUBLIC PLUTOSVG_HAS_FREETYPE)
    target_include_directories(plutosvg PUBLIC ${FREETYPE_INCLUDE_DIRS})
    target_link_libraries(plutosvg PRIVATE ${FREETYPE_LIBRARIES})
endif()

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/plutosvgConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/plutosvgConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/plutosvg
)

write_basic_package_version_file(plutosvgConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

include(GNUInstallDirs)
install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/plutosvg.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/plutosvg
)

install(TARGETS plutosvg
    EXPORT plutosvgTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(EXPORT plutosvgTargets
    FILE plutosvgTargets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/plutosvg
    NAMESPACE plutosvg::
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/plutosvgConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/plutosvgConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/plutosvg
)

export(EXPORT plutosvgTargets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/plutosvgTargets.cmake
    NAMESPACE plutosvg::
)

option(PLUTOSVG_BUILD_EXAMPLES "Build examples" ON)
if(PLUTOSVG_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
