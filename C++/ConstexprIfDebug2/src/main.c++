#include <iostream>
#include <string_view>

namespace debug {
#ifdef DEBUG
  constexpr bool enabled{ true };
#else
  constexpr bool enabled{ false };
#endif

  enum class Level {
    Debug,
    Info,
    Warning,
    Error
  };

  namespace ansi {
    constexpr const char* red{ "\x1b[31m" };
    constexpr const char* green{ "\x1b[32m" };
    constexpr const char* yellow{ "\x1b[33m" };
    constexpr const char* blue{ "\x1b[34m" };
    constexpr const char* magenta{ "\x1b[35m" };
    constexpr const char* cyan{ "\x1b[36m" };
    constexpr const char* white{ "\x1b[37m" };
    constexpr const char* def{ "\x1b[39m" };
    constexpr const char* reset{ "\x1b[0m" };
  }

  template <Level level = Level::Debug, typename... Args>
  auto log(Args&&... args) -> void {
    if constexpr (!enabled) {
      return;
    }
    if constexpr (level == Level::Debug || level == Level::Info) {
      std::cout << ansi::reset;
      if constexpr (level == Level::Debug) {
        std::cout << ansi::reset << ansi::green << "DEBUG: ";
      }
      else if constexpr (level == Level::Info) {
        std::cout << ansi::reset << ansi::cyan << "INFO: ";
      }
      (std::cout << ... << std::forward<Args>(args));
      std::cout << ansi::reset;
    }
    else if constexpr (level == Level::Warning || level == Level::Error) {
      std::cerr << ansi::reset;
      if constexpr (level == Level::Warning) {
        std::cerr << ansi::reset << ansi::yellow << "WARNING: ";
      }
      else if constexpr (level == Level::Error) {
        std::cerr << ansi::reset << ansi::red << "ERROR: ";
      }
      (std::cerr << ... << std::forward<Args>(args));
      std::cerr << ansi::reset;
    }
  }
}

auto main(int, char**) -> int {
  using Level = debug::Level;

  std::cout << "Hello, there!\n";
  debug::log("This is a message\n");
  debug::log<Level::Info>("Something something\n");
  debug::log<Level::Warning>("Careful!\n");
  debug::log<Level::Error>("Oops\n");
}

