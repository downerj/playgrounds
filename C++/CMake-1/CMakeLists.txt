cmake_minimum_required(VERSION 3.28)
project(game VERSION 0.0.1 LANGUAGES CXX)

# Options
option(SDL_STATIC_LINK "Statically link SDL library into executable" OFF)
option(VERBOSE_MAKEFILE "Use verbose output when using Makefiles" OFF)
set(CMAKE_VERBOSE_MAKEFILE ${VERBOSE_MAKEFILE})

# Third-party libraries
find_package(SDL3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
set(GLAD_INCLUDE_DIR "include")

# C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Sources
set(SRC_DIR "src")
set(SOURCES
  ${SRC_DIR}/app.cxx
  ${SRC_DIR}/main.cxx
)

# Target executable
add_executable(game ${SOURCES})

# Third-party headers
target_include_directories(game PRIVATE
  "${GLAD_INCLUDE_DIR}"
)

# Warning levels, symbolic debugging & optimization
target_compile_options(game PRIVATE
  # GCC-like
  $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wunreachable-code
    $<$<CONFIG:Debug>:-Og>
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O3>
  >
  # MSVC
  $<$<CXX_COMPILER_ID:MSVC>:
    /W4
    /permissive-
    $<$<CONFIG:Debug>:/Zi>
    $<$<CONFIG:Release>:/O2>
  >
)

# Debug macros
target_compile_definitions(game PRIVATE
  $<$<CONFIG:Debug>:DEBUG>
  $<$<CONFIG:Release>:NDEBUG>
)

# Linking
target_link_libraries(game PRIVATE
  $<IF:$<BOOL:${SDL_STATIC_LINK}>,SDL3::SDL3-static,SDL3::SDL3>
  OpenGL::GL
)

# Installation, copy DLLs/shared libaries
install(TARGETS game RUNTIME DESTINATION bin)
if(NOT ${SDL_STATIC_LINK})
  if(MSVC)
    install(FILES $<TARGET_RUNTIME_DLLS:game> TYPE BIN)
  else()
    # TODO: Fix missing symlinks, rpath, etc.
    install(FILES
      $<TARGET_LINKER_FILE:SDL3::SDL3>
      $<TARGET_SONAME_FILE:SDL3::SDL3>
      DESTINATION bin
    )
  endif()
endif()
