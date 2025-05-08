#ifndef UTIL_DEBUG_H
#define UTIL_DEBUG_H

/****************************************************************************
 * 
 ****************************************************************************/
#include <stdio.h> // printf

/****************************************************************************
 * 
 ****************************************************************************/
typedef const char * UtilAnsiColor;
#define ANSI_RED     "\x1b[1;31m"
#define ANSI_GREEN   "\x1b[1;32m"
#define ANSI_YELLOW  "\x1b[1;33m"
#define ANSI_BLUE    "\x1b[1;34m"
#define ANSI_MAGENTA "\x1b[1;35m"
#define ANSI_CYAN    "\x1b[1;36m"
#define ANSI_WHITE   "\x1b[1;37m"
#define ANSI_DEFAULT "\x1b[1;39m"
#define ANSI_RESET   "\x1b[0m"

/****************************************************************************
 * 
 ****************************************************************************/
void utilDebug(const char * message, UtilAnsiColor color);

#endif // UTIL_DEBUG_H