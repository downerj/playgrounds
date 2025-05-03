#include "main.hxx"

#include <cstddef>
#include <exception>

#include "app.hxx"
#include "debug.hxx"

/**
 * Defintions.
 */

auto main(int, char**) -> int {
  try {
    Application app{};
    while (app.handleEvents()) {
      app.render();
    }
  } catch (std::exception&) {
    return EXIT_FAILURE;
  }
}
