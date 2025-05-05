#include "debug_win.hxx"

#ifdef DEBUG
#ifdef _WIN32

#include <cstdlib>
#include <cstring>

my::LogFormatter::LogFormatter()
: _hConsole(GetStdHandle(STD_OUTPUT_HANDLE)) {
  GetConsoleScreenBufferInfo(_hConsole, &_consoleInfo);
  _defaultAttributes = _consoleInfo.wAttributes;
  const char* envTerm = std::getenv("TERM");
  if (!envTerm) {
    _supportsANSI = false;
  } else {
    _supportsANSI = std::strncmp(envTerm, "xterm", 5) == 0;
  }
}

void my::LogFormatter::setForeground(std::ostream& out, Color color) {
  if (!_supportsANSI) {
    setForegroundWinAPI(color);
  } else {
    setForegroundANSI(out, color);
  }
}

void my::LogFormatter::setBackground(std::ostream& out, Color color) {
  if (!_supportsANSI) {
    setBackgroundWinAPI(color);
  } else {
    setBackgroundANSI(out, color);
  }
}

void my::LogFormatter::resetColors(std::ostream& out) {
  if (!_supportsANSI) {
    resetColorsWinAPI();
  } else {
    resetColorsANSI(out);
  }
}

void my::LogFormatter::setForegroundWinAPI(Color color) {
  GetConsoleScreenBufferInfo(_hConsole, &_consoleInfo);
  WORD attrib = _consoleInfo.wAttributes;
  WORD attribFG = attrib & 0x000f;
  WORD attribBG = attrib & 0x00f0;
  switch (color) {
    case Black:
      attribFG = 0;
      break;
    case Red:
      attribFG = FOREGROUND_RED | FOREGROUND_INTENSITY;
      break;
    case Yellow:
      attribFG = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
      break;
    case Green:
      attribFG = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
      break;
    case Cyan:
      attribFG = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
      break;
    case Blue:
      attribFG = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
      break;
    case Magenta:
      attribFG = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
      break;
    case White:
      attribFG = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
      break;
  }
  SetConsoleTextAttribute(_hConsole, attribFG | attribBG);
}

void my::LogFormatter::setBackgroundWinAPI(Color color) {
  GetConsoleScreenBufferInfo(_hConsole, &_consoleInfo);
  WORD attrib = _consoleInfo.wAttributes;
  WORD attribFG = attrib & 0x000f;
  WORD attribBG = attrib & 0x00f0;
  switch (color) {
    case Black:
      attribBG = 0;
      break;
    case Red:
      attribBG = BACKGROUND_RED | BACKGROUND_INTENSITY;
      break;
    case Yellow:
      attribBG = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
      break;
    case Green:
      attribBG = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
      break;
    case Cyan:
      attribBG = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
      break;
    case Blue:
      attribBG = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
      break;
    case Magenta:
      attribBG = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
      break;
    case White:
      attribBG = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
      break;
  }
  SetConsoleTextAttribute(_hConsole, attribFG | attribBG);
}

void my::LogFormatter::resetColorsWinAPI() {
  SetConsoleTextAttribute(_hConsole, _defaultAttributes);
  GetConsoleScreenBufferInfo(_hConsole, &_consoleInfo);
}

void my::LogFormatter::setForegroundANSI(std::ostream& out, Color color) {
  switch (color) {
    case Black:
      out << "\x1b[30m";
      break;
    case Red:
      out << "\x1b[91m";
      break;
    case Yellow:
      out << "\x1b[93m";
      break;
    case Green:
      out << "\x1b[92m";
      break;
    case Cyan:
      out << "\x1b[96m";
      break;
    case Blue:
      out << "\x1b[94m";
      break;
    case Magenta:
      out << "\x1b[95m";
      break;
    case White:
      out << "\x1b[97m";
      break;
  }
}

void my::LogFormatter::setBackgroundANSI(std::ostream& out, Color color) {
  switch (color) {
    case Black:
      out << "\x1b[40m";
      break;
    case Red:
      out << "\x1b[41m";
      break;
    case Yellow:
      out << "\x1b[43m";
      break;
    case Green:
      out << "\x1b[42m";
      break;
    case Cyan:
      out << "\x1b[46m";
      break;
    case Blue:
      out << "\x1b[44m";
      break;
    case Magenta:
      out << "\x1b[45m";
      break;
    case White:
      out << "\x1b[47m";
      break;
  }
}

void my::LogFormatter::resetColorsANSI(std::ostream& out) {
  out << "\x1b[0m";
}

#endif // _WIN32
#endif // DEBUG
