#include <cstddef>
#include <exception>
#include <iostream>

#include "app.hxx"

// TODO: Add debug header, wrap cout & cerr in log functions.

auto main(int, char**) -> int {
  try {
    my::Application app{};
    while (app.handleEvents()) {
      app.render();
    }
  } catch([[maybe_unused]] std::exception& ex) {
#ifdef DEBUG
    std::cerr << "Caught exception: " << ex.what() << '\n';
#endif
    return EXIT_FAILURE;
  }
}
