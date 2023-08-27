#ifndef UTIL_TYPES_H
#define UTIL_TYPES_H

/****************************************************************************
 * 
 ****************************************************************************/
#include <GLFW/glfw3.h>

/****************************************************************************
 * 
 ****************************************************************************/
#ifndef uint
typedef unsigned int uint;
#endif // uint

/****************************************************************************
 * 
 ****************************************************************************/
#ifndef uchar
typedef unsigned char uchar;
#endif // uchar

/****************************************************************************
 * 
 ****************************************************************************/
#ifndef bool
typedef uchar boolean;
#define FALSE 0
#define TRUE  1
#else
typedef bool boolean;
#define FALSE false
#define TRUE  true
#endif // bool

/****************************************************************************
 * 
 ****************************************************************************/
struct UtilPoint2f {
   float x;
   float y;
};

/****************************************************************************
 * 
 ****************************************************************************/
struct UtilPath2f {
   uint length;
   struct UtilPoint2f * center;
   struct UtilPoint2f * vertices;
};

#endif // UTIL_TYPES_H