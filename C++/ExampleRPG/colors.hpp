#ifndef COLORS_HH
#define COLORS_HH

#include <initializer_list>
#include <iostream>

namespace ansicolor {
  namespace fg {
    namespace dark {
      constexpr const char* black = "30";
      constexpr const char* red = "31";
      constexpr const char* green = "32";
      constexpr const char* yellow = "33";
      constexpr const char* blue = "34";
      constexpr const char* magenta = "35";
      constexpr const char* cyan = "36";
      constexpr const char* white = "37";
      constexpr const char* def = "39";
    }
    namespace light {
      constexpr const char* black = "90";
      constexpr const char* red = "91";
      constexpr const char* green = "92";
      constexpr const char* yellow = "93";
      constexpr const char* blue = "94";
      constexpr const char* magenta = "95";
      constexpr const char* cyan = "96";
      constexpr const char* white = "97";
      constexpr const char* def = "99";
    }
    constexpr const char* bold = "1";
    constexpr const char* bit8 = "38;5";
    constexpr const char* bit24 = "38;2";
  }
  namespace bg {
    namespace dark {
      constexpr const char* black = "40";
      constexpr const char* red = "41";
      constexpr const char* green = "42";
      constexpr const char* yellow = "43";
      constexpr const char* blue = "44";
      constexpr const char* magenta = "45";
      constexpr const char* cyan = "46";
      constexpr const char* white = "47";
      constexpr const char* def = "49";
    }
    namespace light {
      constexpr const char* black = "100";
      constexpr const char* red = "101";
      constexpr const char* green = "102";
      constexpr const char* yellow = "103";
      constexpr const char* blue = "104";
      constexpr const char* magenta = "105";
      constexpr const char* cyan = "106";
      constexpr const char* white = "107";
      constexpr const char* def = "109";
    }
    constexpr const char* bit8 = "48;5";
    constexpr const char* bit24 = "48;2";
  }

  std::ostream& colorize(std::ostream& out, const char* const code) {
    out << "\x1b[" << code << "m";
    return out;
  }

  std::ostream& colorize(std::ostream& out, std::initializer_list<const char*> codes) {
    out << "\x1b[";
    std::initializer_list<const char*>::iterator it = codes.begin();
    out << *it;
    it++;
    for (; it != codes.end(); ++it) {
      out << ";" << *it;
    }
    out << "m";
    return out;
  }

  std::ostream& reset(std::ostream& out) {
    out << "\x1b[0m";
    return out;
  }

  std::ostream& clear(std::ostream& out) {
    out << "\x1b" << "c" << "\x1b[3J";
    return out;
  }
} // namespace color

#endif // COLORS_HH
