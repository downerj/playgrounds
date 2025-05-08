/****************************************************************************
 * 
 ****************************************************************************/
#ifdef __APPLE__
#define LIBGL <OpenGL/gl.h>
#endif // __apple__
#ifdef __linux__
#define LIBGL <GL/gl.h>
#endif // __linux__

#include LIBGL
#include <math.h>

/****************************************************************************
 * 
 ****************************************************************************/
#include "utiltypes.h"
#include "utildraw.h"
#include "utilinit.h"
#include "utildebug.h"
#include "utiltext.h"

/****************************************************************************
 * 
 ****************************************************************************/
void utilInitRenderer(uint width, uint height, uint color) {
    // this sets the canvas coordinates
    // args: left, right, bottom, top, near, far
	glOrtho(0, width, height, 0, 0, 1);

    // set clear color
    struct UtilColorRGB rgb = utilParseColor(color);
    glClearColor(rgb.r, rgb.g, rgb.b, 0);
}

/****************************************************************************
 * 
 ****************************************************************************/
struct UtilColorRGB utilParseColor(uint color) {
    struct UtilColorRGB rgb;

    rgb.r = ((color >> 16) & 0xff) / 255.0;
    rgb.g = ((color >>  8) & 0xff) / 255.0;
    rgb.b = ( color        & 0xff) / 255.0;
    
    return rgb;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetStrokeColorInt(uint color) {
    struct UtilColorRGB rgb = utilParseColor(color);

    glColor3f(rgb.r, rgb.g, rgb.b);
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetStrokeColorRGB(struct UtilColorRGB * rgb) {
    glColor3f(rgb->r, rgb->g, rgb->b);
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilClearScreen(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilStrokeLine(struct UtilPoint2f endpoints[2]) {
    glBegin(GL_LINES); {
        glVertex2f(endpoints[0].x, endpoints[0].y);
        glVertex2f(endpoints[1].x, endpoints[1].y);
    } glEnd();
}

/****************************************************************************
 * 
 ****************************************************************************/
void __utilIterateVertices__(const struct UtilPath2f * path) {
    for (uint p = 0; p < path->length; p++) {
        struct UtilPoint2f * pt  = path->vertices + p;
        struct UtilPoint2f * ctr = path->center;
        glVertex2f(pt->x + ctr->x, pt->y + ctr->y);
    }
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilStrokePolyline(const struct UtilPath2f * path) {
    glBegin(GL_LINE_STRIP); {
        __utilIterateVertices__(path);
    } glEnd();
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilStrokePolygon(const struct UtilPath2f * path) {
    glBegin(GL_LINE_LOOP); {
        __utilIterateVertices__(path);
    } glEnd();
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilFillPolygon(const struct UtilPath2f * path) {
    glBegin(GL_POLYGON); {
        __utilIterateVertices__(path);
    } glEnd();
}

/****************************************************************************
 * 
 ****************************************************************************/
#define POINT_RADIUS 2
void utilFillPoint(const struct UtilPoint2f * point) {
    float x1 = point->x - POINT_RADIUS;
    float y1 = point->y - POINT_RADIUS;
    float x2 = point->x + POINT_RADIUS;
    float y2 = point->y + POINT_RADIUS;

    // draw a rectangle
    glBegin(GL_POLYGON); {
        glVertex2f(x1, y1);
        glVertex2f(x1, y2);
        glVertex2f(x2, y2);
        glVertex2f(x2, y1);
    } glEnd();
}

/****************************************************************************
 * 
 ****************************************************************************/
float __utilDegToRad__(float degrees) {
    return (degrees * PI) / 180.0;
}

/****************************************************************************
 * 
 ****************************************************************************/
float __utilRadToDeg__(float radians) {
    return (radians * 180.0) / PI;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilRotatePoint(struct UtilPoint2f * point, float degrees) {
    float xp = point->x;
    float yp = point->y;

    float rad  = __utilDegToRad__(degrees);
    float cosA = cos(rad);
    float sinA = sin(rad);

    point->x = xp * cosA - yp * sinA;
    point->y = xp * sinA + yp * cosA;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilTranslatePolygon(struct UtilPath2f * polygon, float dx, float dy) {
    polygon->center->x += dx;
    polygon->center->y += dy;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilRotatePolygonAboutCenter(struct UtilPath2f * polygon, float degrees) {
    for (uint p = 0; p < polygon->length; p++) {
        utilRotatePoint(polygon->vertices + p, degrees);
    }
}
