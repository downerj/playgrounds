#include "debug_unix.hxx"

#ifdef DEBUG
#ifndef _WIN32

void my::setForeground(std::ostream& out, Color color) {
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

void my::setBackground(std::ostream& out, Color color) {
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

void my::resetColors(std::ostream& out) {
  out << "\x1b[0m";
}

#endif // !defined(_WIN32)
#endif // DEBUG
