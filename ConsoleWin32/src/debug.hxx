#ifndef DEBUG_HXX
#define DEBUG_HXX

#ifdef _DEBUG
#define DEBUG
#endif // _DEBUG

#ifdef DEBUG

#ifdef _WIN32
#include "debug_win.hxx"
#else // if !defined(_WIN32)
#include "debug_unix.hxx"
#endif // _WIN32

#else // if !defined(DEBUG)

#define LOG(x)
#define LOG_ERROR(x)
#define LOG_FG(x)
#define LOG_BG(x)
#define LOG_FG_ERROR(x)
#define LOG_BG_ERROR(x)
#define LOG_RESET()
#define LOG_RESET_ERROR()

#endif // DEBUG

#endif // DEBUG_HXX
