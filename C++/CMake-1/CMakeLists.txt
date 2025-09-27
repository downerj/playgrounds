cmake_minimum_required(VERSION 3.28)
project(example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(VERBOSE_MAKEFILE OFF CACHE BOOL "Whether to use verbose output when using Makefiles")
set(CMAKE_VERBOSE_MAKEFILE ${VERBOSE_MAKEFILE})

set(SRC_DIR "src")
set(SOURCES
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

add_executable(example ${SOURCES})
