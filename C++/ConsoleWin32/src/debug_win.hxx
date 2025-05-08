#ifndef DEBUG_WIN_HXX
#define DEBUG_WIN_HXX

#ifdef DEBUG
#ifdef _WIN32

#include <iostream>

#include <windows.h>

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

class LogFormatter {
public:
  LogFormatter();
  void setForeground(std::ostream& out, Color color);
  void setBackground(std::ostream& out, Color color);
  void resetColors(std::ostream& out);

private:
  HANDLE _hConsole;
  CONSOLE_SCREEN_BUFFER_INFO _consoleInfo;
  WORD _defaultAttributes;
  bool _supportsANSI;
  
  void setForegroundWinAPI(Color color);
  void setBackgroundWinAPI(Color color);
  void resetColorsWinAPI();
  void setForegroundANSI(std::ostream& out, Color color);
  void setBackgroundANSI(std::ostream& out, Color color);
  void resetColorsANSI(std::ostream& out);
};

static LogFormatter gLog;

} // namespace my

#define LOG(x) do { std::cout << x; } while (false);
#define LOG_ERROR(x) do { std::cerr << x; } while (false);
#define LOG_FG(x) do { my::gLog.setForeground(std::cout, x); } while (false);
#define LOG_BG(x) do { my::gLog.setBackground(std::cout, x); } while (false);
#define LOG_FG_ERROR(x) do { my::gLog.setForeground(std::cerr, x); } while (false);
#define LOG_BG_ERROR(x) do { my::gLog.setBackground(std::cerr, x); } while (false);
#define LOG_RESET() do { my::gLog.resetColors(std::cout); } while (false);
#define LOG_RESET_ERROR() do { my::gLog.resetColors(std::cerr); } while (false);

#endif // _WIN32
#endif // DEBUG

#endif // DEBUG_WIN_HXX
