#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace {
#ifdef DEBUG
  constexpr bool debug = true;
#else
  constexpr bool debug = false;
#endif
}

namespace my {
  constexpr const char* green{"\x1b[92m"};
  constexpr const char* reset{"\x1b[0m"};

  template<typename... Args>
  auto log(Args&&... args) -> void {
    if constexpr (debug) {
      std::cout << green << "DEBUG: ";
      (std::cout << ... << std::forward<Args>(args));
      std::cout << reset;
    }
  }
}

auto main(int argc, char** argv) -> int {
  my::log("Hello!\n");
  std::vector<std::string> args{
    argv + 1, argc + argv
  };
  std::cout << argv[0];
  for (const auto& arg : args) {
    std::cout << ' ' << arg;
  }
  std::cout << '\n';
}
