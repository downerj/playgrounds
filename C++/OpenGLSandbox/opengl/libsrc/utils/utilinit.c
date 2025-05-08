/****************************************************************************
 * 
 ****************************************************************************/
#include <unistd.h> // usleep

/****************************************************************************
 * 
 ****************************************************************************/
#include <GLFW/glfw3.h>

/****************************************************************************
 * 
 ****************************************************************************/
#include "utilinit.h"
#include "utiltypes.h"
#include "utilinput.h"
#include "utildraw.h"
#include "utiltext.h"

/****************************************************************************
 * 
 ****************************************************************************/
boolean utilInitEngine() {
    __utilInitialized__ = FALSE;

    if (glfwInit()) {
        // initialize defaults
        utilSetWinDims(640, 480);
        utilSetWinTitle("GLSandbox");
        utilSetFramerate(60);
        utilSetBGColor(0x000000);
        utilSetTickFunc(NULL);
        utilInit2DGlyphs();
        __utilInitialized__ = TRUE;
    }

    return __utilInitialized__;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetWinDims(const uint width, const uint height) {
    __utilWinWidth__  = width;
    __utilWinHeight__ = height;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetWinTitle(char * title) {
    __utilWinTitle__ = title;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetFramerate(const uint framerate) {
    __utilFramerate__ = framerate;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetBGColor(const uint color) {
    __utilBGColor__ = color;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetUserData(void * pointer) {
    __utilUserData__ = pointer;
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilSetTickFunc(void (func(void *))) {
    __utilTickFunc__ = func;
}

/****************************************************************************
 * 
 ****************************************************************************/
boolean utilCreateWindow() {
    __utilWindow__ = glfwCreateWindow(
        __utilWinWidth__,
        __utilWinHeight__,
        __utilWinTitle__,
        NULL,
        NULL
    );
    if (!__utilWindow__) {
        glfwTerminate();
        return FALSE;
    } else {
        return TRUE;
    }
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilMainLoop(void) {
    glfwMakeContextCurrent(__utilWindow__);

    // initialize local utilities
    utilInitInputHandlers();
    utilInitRenderer(__utilWinWidth__, __utilWinHeight__, __utilBGColor__);
    
    __utilRunning__ = TRUE;
    while (!glfwWindowShouldClose(__utilWindow__)) {
        // run user function
        if (__utilTickFunc__) {
            __utilTickFunc__(__utilUserData__);
        }
        
        // check if still running
        if (!__utilRunning__) {
            glfwSetWindowShouldClose(__utilWindow__, TRUE);
            break;
        }

        glfwSwapBuffers(__utilWindow__);
        glfwPollEvents();
        utilUpdateInputHandlers();
        
        usleep(1000000 / __utilFramerate__);
    }

    glfwTerminate();
    utilReleaseInputHandlers();
}

/****************************************************************************
 * 
 ****************************************************************************/
void utilEnd(void) {
    __utilRunning__ = FALSE;
}
