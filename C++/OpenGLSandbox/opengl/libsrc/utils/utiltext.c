/****************************************************************************
 * 
 ****************************************************************************/
#include <math.h>  // log*
#include <stdio.h> // *print*

/****************************************************************************
 * 
 ****************************************************************************/
#include "utiltext.h"
#include "utiltypes.h"
#include "utildraw.h"

/****************************************************************************
 * 
 ****************************************************************************/
void utilInit2DGlyphs(void) {
    // set defaults for glyphs
    utilSetGlyphCursorXY(0, 0);
    utilSetGlyphMargins(1, 1);
    utilSetGlyphScaling(1);
    utilSetGlyphTabWidth(1);
    utilSetGlyphColorInt(0xffffff);
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetGlyphMargins(uint marginX, uint marginY) {
    __utilGlyphMarginX__  = marginX;
    __utilGlyphMarginY__  = marginY;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetGlyphScaling(uint scaling) {
    __utilGlyphScaling__  = scaling;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetGlyphTabWidth(uint tabWidth) {
    __utilGlyphTabWidth__ = tabWidth;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetGlyphColorInt(uint color) {
    struct UtilColorRGB rgb = utilParseColor(color);

    __utilGlyphColor__.r = rgb.r;
    __utilGlyphColor__.g = rgb.g;
    __utilGlyphColor__.b = rgb.b;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetGlyphColorRGB(struct UtilColorRGB * rgb) {
    __utilGlyphColor__.r = rgb->r;
    __utilGlyphColor__.g = rgb->g;
    __utilGlyphColor__.b = rgb->b;
}

/****************************************************************************
 * 
 ****************************************************************************/
const uint __UTIL_GLYPH_A__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
};
const uint __UTIL_GLYPH_B__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 1}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
    {0, 2}, {2, 2},
    // diag
    {1, 1}, {2, 0},
};
const uint __UTIL_GLYPH_C__[][2] = {
    // vert
    {0, 0}, {0, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_D__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 1},
    // horiz
    {0, 0}, {2, 0},
    {0, 2}, {1, 2},
    // diag
    {1, 2}, {2, 1},
};
const uint __UTIL_GLYPH_E__[][2] = {
    // vert
    {0, 0}, {0, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {1, 1},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_F__[][2] = {
    // vert
    {0, 0}, {0, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {1, 1},
};
const uint __UTIL_GLYPH_G__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 1}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {1, 1}, {2, 1},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_H__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 2},
    // horiz
    {0, 1}, {2, 1},
};
const uint __UTIL_GLYPH_I__[][2] = {
    // vert
    {1, 0}, {1, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_J__[][2] = {
    // vert
    {0, 1}, {0, 2},
    {2, 0}, {2, 2},
    // horiz
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_K__[][2] = {
    // vert
    {0, 0}, {0, 2},
    // diag
    {0, 1}, {2, 0},
    {0, 1}, {2, 2},
};
const uint __UTIL_GLYPH_L__[][2] = {
    // vert
    {0, 0}, {0, 2},
    // horiz
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_M__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 2},
    // diag
    {0, 0}, {1, 2},
    {1, 2}, {2, 0},
};
const uint __UTIL_GLYPH_N__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 2},
    // diag
    {0, 0}, {2, 2},
};
const uint __UTIL_GLYPH_O__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_P__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 1},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
};
const uint __UTIL_GLYPH_Q__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 1},
    // horiz
    {0, 0}, {2, 0},
    {0, 2}, {1, 2},
    // diag
    {1, 1}, {2, 2},
    {1, 2}, {2, 1},
};
const uint __UTIL_GLYPH_R__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 1},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
    // diag
    {1, 1}, {2, 2},
};
const uint __UTIL_GLYPH_S__[][2] = {
    // vert
    {0, 0}, {0, 1},
    {2, 1}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_T__[][2] = {
    // vert
    {1, 0}, {1, 2},
    // horiz
    {0, 0}, {2, 0},
};
const uint __UTIL_GLYPH_U__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 2},
    // horiz
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_V__[][2] = {
    // diag
    {0, 0}, {1, 2},
    {1, 2}, {2, 0},
};
const uint __UTIL_GLYPH_W__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 2},
    // diag
    {0, 2}, {1, 1},
    {1, 1}, {2, 2},
};
const uint __UTIL_GLYPH_X__[][2] = {
    // diag
    {0, 0}, {2, 2},
    {0, 2}, {2, 0},
};
const uint __UTIL_GLYPH_Y__[][2] = {
    // vert
    {1, 1}, {1, 2},
    // diag
    {0, 0}, {1, 1},
    {1, 1}, {2, 0},
};
const uint __UTIL_GLYPH_Z__[][2] = {
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
    {0, 2}, {2, 2},
    // diag
    {0, 2}, {2, 0},
};
const uint __UTIL_GLYPH_0__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 2}, {2, 2},
    // diag
    {0, 2}, {2, 0},
};
const uint __UTIL_GLYPH_1__[][2] = {
    // vert
    {1, 0}, {1, 2},
    // horiz
    {0, 2}, {2, 2},
    // diag
    {0, 1}, {1, 0},
};
const uint __UTIL_GLYPH_2__[][2] = {
    // vert
    {0, 1}, {0, 2},
    {2, 0}, {2, 1},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_3__[][2] = {
    // vert
    {2, 1}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {1, 1}, {2, 1},
    {0, 2}, {2, 2},
    // diag
    {1, 1}, {2, 0},
};
const uint __UTIL_GLYPH_4__[][2] = {
    // vert
    {1, 0}, {1, 2},
    // horiz
    {0, 1}, {2, 1},
    // diag
    {0, 1}, {1, 0},
};
const uint __UTIL_GLYPH_5__[][2] = {
    // vert
    {0, 0}, {0, 1},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
    {0, 2}, {1, 2},
    // diag
    {1, 2}, {2, 1},
};
const uint __UTIL_GLYPH_6__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 1}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_7__[][2] = {
    // horiz
    {0, 0}, {2, 0},
    // diag
    {1, 2}, {2, 0},
};
const uint __UTIL_GLYPH_8__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {2, 0}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_9__[][2] = {
    // vert
    {0, 0}, {0, 1},
    {2, 0}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
};
const uint __UTIL_GLYPH_TILDE__[][2] = {
    // vert
    {1, 0}, {1, 1},
    // diag
    {0, 1}, {1, 0},
    {1, 1}, {2, 0},
};
const uint __UTIL_GLYPH_GRAVE__[][2] = {
    // diag
    {1, 0}, {2, 1},
};
const uint __UTIL_GLYPH_EMARK__[][2] = {
    // vert
    {1, 0}, {1, 1},
    // dot
    {1, 2}, {1, 2},
};
const uint __UTIL_GLYPH_AT__[][2] = {
    // vert
    {0, 1}, {0, 2},
    {1, 1}, {1, 2},
    {2, 0}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {1, 1},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_POUND__[][2] = {
    // vert
    {0, 0}, {0, 2},
    {1, 0}, {1, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
};
const uint __UTIL_GLYPH_DOLLAR__[][2] = {
    // vert
    {0, 0}, {0, 1},
    {1, 0}, {1, 2},
    {2, 1}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 1}, {2, 1},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_PERCENT__[][2] = {
    // vert
    {0, 0}, {0, 1},
    {2, 1}, {2, 2},
    // horiz
    {0, 0}, {1, 0},
    {1, 2}, {2, 2},
    // diag
    {0, 1}, {1, 0},
    {0, 2}, {2, 0},
    {1, 2}, {2, 1},
};
const uint __UTIL_GLYPH_CARET__[][2] = {
    // diag
    {0, 1}, {1, 0},
    {1, 0}, {2, 1},
};
const uint __UTIL_GLYPH_AND__[][2] = {
    // vert
    {2, 1}, {2, 2},
    // horiz
    {0, 0}, {2, 0},
    {0, 2}, {2, 2},
    // diag
    {0, 0}, {1, 2},
    {0, 2}, {2, 0},
};
const uint __UTIL_GLYPH_ASTER__[][2] = {
    // vert
    {1, 0}, {1, 2},
    // horiz
    {0, 1}, {2, 1},
    // diag
    {0, 0}, {2, 2},
    {0, 2}, {2, 0},
};
const uint __UTIL_GLYPH_PAREN_OPEN__[][2] = {
    // vert
    {1, 0}, {1, 1},
    // horiz
    {1, 0}, {2, 0},
    // diag
    {1, 1}, {2, 2},
};
const uint __UTIL_GLYPH_PAREN_CLOSE__[][2] = {
    // vert
    {2, 1}, {2, 2},
    // horiz
    {1, 2}, {2, 2},
    // diag
    {1, 0}, {2, 1},
};
const uint __UTIL_GLYPH_BRACK_OPEN__[][2] = {
    // vert
    {1, 0}, {1, 2},
    // horiz
    {1, 0}, {2, 0},
    {1, 2}, {2, 2},
};
const uint __UTIL_GLYPH_BRACK_CLOSE__[][2] = {
    // vert
    {1, 0}, {1, 2},
    // horiz
    {0, 0}, {1, 0},
    {0, 2}, {1, 2},
};
const uint __UTIL_GLYPH_ANGLE_OPEN__[][2] = {
    // diag
    {1, 1}, {2, 0},
    {1, 1}, {2, 2},
};
const uint __UTIL_GLYPH_ANGLE_CLOSE__[][2] = {
    // diag
    {0, 0}, {1, 1},
    {0, 2}, {1, 1},
};
const uint __UTIL_GLYPH_CURLY_OPEN__[][2] = {
    // vert
    {1, 0}, {1, 2},
    // horiz
    {0, 1}, {1, 1},
    {1, 0}, {2, 0},
    {1, 2}, {2, 2},
};
const uint __UTIL_GLYPH_CURLY_CLOSE__[][2] = {
    // vert
    {1, 0}, {1, 2},
    // horiz
    {0, 0}, {1, 0},
    {1, 1}, {2, 1},
    {0, 2}, {1, 2},
};
const uint __UTIL_GLYPH_VBAR__[][2] = {
    // vert
    {1, 0}, {1, 2},
};
const uint __UTIL_GLYPH_HYPHEN__[][2] = {
    // horiz
    {0, 1}, {2, 1},
};
const uint __UTIL_GLYPH_USCORE__[][2] = {
    // horiz
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_PLUS__[][2] = {
    // vert
    {1, 0}, {1, 2},
    // horiz
    {0, 1}, {2, 1},
};
const uint __UTIL_GLYPH_EQUALS__[][2] = {
    // horiz
    {0, 1}, {2, 1},
    {0, 2}, {2, 2},
};
const uint __UTIL_GLYPH_FSLASH__[][2] = {
    // diag
    {0, 2}, {2, 0},
};
const uint __UTIL_GLYPH_BSLASH__[][2] = {
    // diag
    {0, 0}, {2, 2},
};
const uint __UTIL_GLYPH_DQUOTE_OPEN__[][2] = {
    // vert
    {1, 0}, {1, 1},
    {2, 0}, {2, 1},
};
const uint __UTIL_GLYPH_DQUOTE_CLOSE__[][2] = {
    // vert
    {0, 0}, {0, 1},
    {1, 0}, {1, 1}, 
};
const uint __UTIL_GLYPH_SQUOTE__[][2] = {
    // vert
    {1, 0}, {1, 1},
};
const uint __UTIL_GLYPH_QMARK__[][2] = {
    // vert
    {2, 0}, {2, 1},
    // horiz
    {0, 0}, {2, 0},
    {1, 1}, {2, 1},
    // dot
    {1, 2}, {1, 2},
};
const uint __UTIL_GLYPH_PERIOD__[][2] = {
    // dot
    {1, 2}, {1, 2},
};
const uint __UTIL_GLYPH_COLON__[][2] = {
    // dot
    {1, 1}, {1, 1},
    {1, 2}, {1, 2},
};
const uint __UTIL_GLYPH_SCOLON__[][2] = {
    // horiz
    {0, 2}, {1, 2},
    // dot
    {1, 1}, {1, 1},
};
const uint __UTIL_GLYPH_COMMA__[][2] = {
    // vert
    {1, 1}, {1, 2},
    // horiz
    {0, 2}, {1, 2},
};

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetGlyphCursorXY(float x, float y) {
    __utilGlyphCursorCurrent__.x = x;
    __utilGlyphCursorCurrent__.y = y;
    __utilGlyphCursorStart__.x   = x;
    __utilGlyphCursorStart__.y   = y;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetGlyphCursorPt(struct UtilPoint2f * pt) {
    utilSetGlyphCursorXY(pt->x, pt->y);
}

/****************************************************************************
 * 
 ****************************************************************************/
void __utilAdvanceGlyphCursorX__(int numChars) {
    int w = __UTIL_GLYPH_WIDTH__ * __utilGlyphScaling__;
    int m = __utilGlyphMarginX__ - 1;
    __utilGlyphCursorCurrent__.x += (w + m) * numChars;
}

/****************************************************************************
 * 
 ****************************************************************************/
void __utilAdvanceGlyphCursorY__(int numLines) {
    __utilGlyphCursorCurrent__.x = __utilGlyphCursorStart__.x;
    
    int h = __UTIL_GLYPH_HEIGHT__ * __utilGlyphScaling__;
    int m = __utilGlyphMarginY__ - 1;
    __utilGlyphCursorCurrent__.y += (h + m) * numLines;
}

/****************************************************************************
 * 
 ****************************************************************************/
void __utilEraseGlyphs__(uint numGlyphs) {
    __utilAdvanceGlyphCursorX__(-numGlyphs);
    uint w  = __UTIL_GLYPH_WIDTH__  * __utilGlyphScaling__;
    uint h  = __UTIL_GLYPH_HEIGHT__ * __utilGlyphScaling__;
    uint m  = __utilGlyphMarginX__ - 1;
    uint x1 = __utilGlyphCursorCurrent__.x;
    uint y1 = __utilGlyphCursorCurrent__.y;
    uint x2 = x1 + (w + m) * numGlyphs;
    uint y2 = y1 + h * numGlyphs;

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON); {
        glVertex2i(x1, y1);
        glVertex2i(x1, y2);
        glVertex2i(x2, y2);
        glVertex2i(x2, y1);
    } glEnd();
    struct UtilColorRGB * rgb = &__utilGlyphColor__;
    glColor3f(rgb->r, rgb->g, rgb->b);
}

/****************************************************************************
 * 
 ****************************************************************************/
void __utilDrawGlyph__(const uint ** glyph, uint numLines) {
    if (!glyph || numLines == 0) {
        return;
    }

    uint numVertices = numLines * 2;
    uint x = (uint) __utilGlyphCursorCurrent__.x;
    uint y = (uint) __utilGlyphCursorCurrent__.y;

    struct UtilColorRGB * rgb = &__utilGlyphColor__;
    glColor3f(rgb->r, rgb->g, rgb->b);
    glBegin(GL_LINES); {
        for (uint v = 0; v < numVertices; v += 2) {
            uint * v1 = (uint *) &glyph[v];     // (uint *) glyph + (v * 2)
            uint * v2 = (uint *) &glyph[v + 1]; // (uint *) glyph + (v * 2) + 2
            // it's a dot
            if (v1[X] == v2[X] && v1[Y] == v2[Y]) {
                glEnd();
                glBegin(GL_POLYGON); {
                    uint v1x = v1[X] * __utilGlyphScaling__ - 1;
                    uint v1y = v1[Y] * __utilGlyphScaling__ - 1;
                    uint v2x = v1x + 3;
                    uint v2y = v1y + 3;
                    glVertex2i(v1x + x, v1y + y);
                    glVertex2i(v1x + x, v2y + y);
                    glVertex2i(v2x + x, v2y + y);
                    glVertex2i(v2x + x, v1y + y);
                } glEnd();
                glBegin(GL_LINES);
            // it's a line
            } else {
                uint v1x = v1[X] * __utilGlyphScaling__;
                uint v1y = v1[Y] * __utilGlyphScaling__;
                uint v2x = v2[X] * __utilGlyphScaling__;
                uint v2y = v2[Y] * __utilGlyphScaling__;

                glVertex2i(v1x + x, v1y + y);
                glVertex2i(v2x + x, v2y + y);
            }
        }
    } glEnd();

    __utilAdvanceGlyphCursorX__(1);
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilDrawText(const char * text) {
    uint numDoubleQuotes = 0;
    for (const char * c = text; *c; c++) {
        switch (*c) {
            case 'A':
            case 'a':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_A__, 4);
                break;
            
            case 'B':
            case 'b':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_B__, 8);
                break;

            case 'C':
            case 'c':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_C__, 3);
                break;
            
            case 'D':
            case 'd':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_D__, 5);
                break;
                
            case 'E':
            case 'e':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_E__, 4);
                break;
                
            case 'F':
            case 'f':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_F__, 3);
                break;
            
            case 'G':
            case 'g':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_G__, 5);
                break;
            
            case 'H':
            case 'h':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_H__, 3);
                break;
            
            case 'I':
            case 'i':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_I__, 3);
                break;
            
            case 'J':
            case 'j':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_J__, 3);
                break;
            
            case 'K':
            case 'k':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_K__, 3);
                break;
            
            case 'L':
            case 'l':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_L__, 2);
                break;
            
            case 'M':
            case 'm':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_M__, 4);
                break;
            
            case 'N':
            case 'n':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_N__, 3);
                break;
            
            case 'O':
            case 'o':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_O__, 4);
                break;
            
            case 'P':
            case 'p':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_P__, 4);
                break;
            
            case 'Q':
            case 'q':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_Q__, 6);
                break;
            
            case 'R':
            case 'r':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_R__, 5);
                break;
            
            case 'S':
            case 's':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_S__, 5);
                break;
            
            case 'T':
            case 't':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_T__, 2);
                break;
            
            case 'U':
            case 'u':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_U__, 3);
                break;
            
            case 'V':
            case 'v':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_V__, 2);
                break;
            
            case 'W':
            case 'w':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_W__, 4);
                break;
            
            case 'X':
            case 'x':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_X__, 2);
                break;
            
            case 'Y':
            case 'y':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_Y__, 3);
                break;
            
            case 'Z':
            case 'z':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_Z__, 4);
                break;

            case '0':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_0__, 5);
                break;
            
            case '1':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_1__, 3);
                break;
            
            case '2':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_2__, 5);
                break;
            
            case '3':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_3__, 5);
                break;
            
            case '4':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_4__, 3);
                break;
            
            case '5':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_5__, 5);
                break;
            
            case '6':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_6__, 5);
                break;
            
            case '7':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_7__, 2);
                break;
            
            case '8':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_8__, 5);
                break;
            
            case '9':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_9__, 4);
                break;
            
            case '\b':
                __utilEraseGlyphs__(1);
                break;
            
            case '\t':
                __utilAdvanceGlyphCursorX__(__utilGlyphTabWidth__);
                break;
            
            case '\n':
                __utilAdvanceGlyphCursorY__(1);
                continue;
            
            case ' ':
                __utilAdvanceGlyphCursorX__(1);
                break;
            
            case '!':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_EMARK__, 2);
                break;
            
            case '"':
                if (++numDoubleQuotes % 2 == 1) {
                    __utilDrawGlyph__((const uint **) __UTIL_GLYPH_DQUOTE_OPEN__, 2);
                } else {
                    __utilDrawGlyph__((const uint **) __UTIL_GLYPH_DQUOTE_CLOSE__, 2);
                }
                break;
            
            case '#':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_POUND__, 4);
                break;
            
            case '$':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_DOLLAR__, 6);
                break;
            
            case '%':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_PERCENT__, 7);
                break;
            
            case '&':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_AND__, 5);
                break;
            
            case '\'':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_SQUOTE__, 1);
                break;
            
            case '(':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_PAREN_OPEN__, 3);
                break;
            
            case ')':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_PAREN_CLOSE__, 3);
                break;
            
            case '*':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_ASTER__, 4);
                break;
            
            case '+':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_PLUS__, 2);
                break;
            
            case ',':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_COMMA__, 2);
                break;
            
            case '-':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_HYPHEN__, 1);
                break;
            
            case '.':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_PERIOD__, 1);
                break;
            
            case '/':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_FSLASH__, 1);
                break;
            
            case ':':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_COLON__, 2);
                break;
            
            case ';':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_SCOLON__, 2);
                break;
            
            case '<':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_ANGLE_OPEN__, 2);
                break;
            
            case '=':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_EQUALS__, 2);
                break;
            
            case '>':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_ANGLE_CLOSE__, 2);
                break;
            
            case '?':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_QMARK__, 4);
                break;
            
            case '@':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_AT__, 6);
                break;
            
            case '[':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_BRACK_OPEN__, 3);
                break;
            
            case '\\':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_BSLASH__, 1);
                break;
            
            case ']':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_BRACK_CLOSE__, 3);
                break;
            
            case '^':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_CARET__, 2);
                break;
            
            case '_':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_USCORE__, 1);
                break;
            
            case '`':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_GRAVE__, 1);
                break;
            
            case '{':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_CURLY_OPEN__, 4);
                break;
            
            case '|':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_VBAR__, 1);
                break;
            
            case '}':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_CURLY_CLOSE__, 4);
                break;
            
            case '~':
                __utilDrawGlyph__((const uint **) __UTIL_GLYPH_TILDE__, 3);
                break;
            
            default:
                continue;
        }
    }
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilDrawCharacter(const char c) {
    char text[] = {c, '\0'};
    utilDrawText(text);
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilDrawInteger(long int num) {
    char digits[__UTIL_BUFFER_LENGTH__];
    sprintf(digits, "%ld", num);
    utilDrawText(digits);
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilDrawFloat(long double num) {
    char digits[__UTIL_BUFFER_LENGTH__];
    sprintf(digits, "%Lf", num);
    utilDrawText(digits);
}