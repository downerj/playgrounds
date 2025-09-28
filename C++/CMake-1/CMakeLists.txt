cmake_minimum_required(VERSION 3.28)
project(game VERSION 0.0.1 LANGUAGES CXX)

set(GLAD_INCLUDE_DIR "include" CACHE STRING "Parent directory of the directory containing the GLAD header")
set(SDL_STATIC_LINK OFF CACHE BOOL "Statically link SDL library into executable")
set(VERBOSE_MAKEFILE OFF CACHE BOOL "Use verbose output when using Makefiles")

find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ${VERBOSE_MAKEFILE})

set(SRC_DIR "src")
set(SOURCES
  ${SRC_DIR}/app.cxx
  ${SRC_DIR}/main.cxx
)

add_executable(game ${SOURCES})

target_include_directories(game PRIVATE
  "${GLAD_INCLUDE_DIR}"
)

# Symbolic debugging & optimization
target_compile_options(game PRIVATE
  $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
    $<$<CONFIG:Debug>:-Og>
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O3>
  >
  $<$<CXX_COMPILER_ID:MSVC>:
    $<$<CONFIG:Debug>:/Zi>
    $<$<CONFIG:Release>:/O2>
  >
)

# Debug macros
target_compile_definitions(game PRIVATE
  $<$<CONFIG:Debug>:DEBUG>
  $<$<CONFIG:Release>:NDEBUG>
)

# Warning levels
target_compile_options(game PRIVATE
  $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wunreachable-code
  >
  $<$<CXX_COMPILER_ID:MSVC>:
    /W4
    /permissive-
  >
)

target_link_libraries(game PRIVATE
  $<IF:$<BOOL:${SDL_STATIC_LINK}>,SDL3::SDL3-static,SDL3::SDL3>
  OpenGL::GL
)

install(FILES $<TARGET_RUNTIME_DLLS:game> TYPE BIN)
install(TARGETS game RUNTIME DESTINATION bin)
