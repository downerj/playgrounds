#ifndef DEBUG_UNIX_HXX
#define DEBUG_UNIX_HXX

#ifdef DEBUG
#ifndef _WIN32

#include <iostream>

enum Color {
  Black,
  Red,
  Yellow,
  Green,
  Cyan,
  Blue,
  Magenta,
  White
};

namespace my {

void setForeground(std::ostream& out, Color color);
void setBackground(std::ostream& out, Color color);
void resetColors(std::ostream& out);

} // namespace my

#define LOG(x) do { std::cout << x; } while (false);
#define LOG_ERROR(x) do { std::cerr << x; } while (false);
#define LOG_FG(x) do { my::setForeground(std::cout, x); } while (false);
#define LOG_BG(x) do { my::setBackground(std::cout, x); } while (false);
#define LOG_FG_ERROR(x) do { my::setForeground(std::cerr, x); } while (false);
#define LOG_BG_ERROR(x) do { my::setBackground(std::cerr, x); } while (false);
#define LOG_RESET() do { my::resetColors(std::cout); } while (false);
#define LOG_RESET_ERROR() do { my::resetColors(std::cerr); } while (false);

#endif // !defined(_WIN32)
#endif // DEBUG

#endif // DEBUG_UNIX_HXX
