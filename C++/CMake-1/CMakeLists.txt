cmake_minimum_required(VERSION 3.28)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GLAD_INCLUDE_DIR "" CACHE STRING "Parent directory (e.g. \"include\") of the directory containing the GLAD 2 header")
set(SDL3_INCLUDE_DIR "" CACHE STRING "Parent directory (e.g. \"include\") of the directory containing the SDL 3 headers")
set(SDL3_LIB_DIR "" CACHE STRING "Directory containing the compiled SDL3 library")
set(SDL3_STATIC_LINK OFF CACHE BOOL "Statically link SDL3 library into executable")
set(VERBOSE_MAKEFILE OFF CACHE BOOL "Use verbose output when using Makefiles")

set(CMAKE_VERBOSE_MAKEFILE ${VERBOSE_MAKEFILE})

include_directories(
  "${GLAD_INCLUDE_DIR}"
)

link_directories(
  "${SDL3_LIB_DIR}"
)

set(SRC_DIR "src")
set(SOURCES
  ${SRC_DIR}/app.cxx
  ${SRC_DIR}/main.cxx
)

if(NOT MSVC)
  # Debug build.
  add_compile_options($<$<CONFIG:Debug>:-Og>)
  add_compile_definitions($<$<CONFIG:DEBUG>:DEBUG>)

  # Release build.
  add_compile_options($<$<CONFIG:Release>:-O3>)

  # Options for all builds.
  add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wshadow
    -Wunreachable-code
  )
endif()

add_executable(game ${SOURCES})
if (SDL3_STATIC_LINK)
  target_link_libraries(game SDL3.a)
else()
  target_link_libraries(game SDL3)
endif()
