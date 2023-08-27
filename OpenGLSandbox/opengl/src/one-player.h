#ifndef PLAYER_H
#define PLAYER_H

/****************************************************************************
 * 
 ****************************************************************************/
#include <utils/utiltypes.h>

/****************************************************************************
 * 
 ****************************************************************************/
struct Velocity {
    float dx;
    float dy;
};

/****************************************************************************
 * 
 ****************************************************************************/
struct Player {
    struct  UtilPath2f * image;
    struct  UtilPoint2f * position;
    struct  Velocity * velocity;
    float   rotation;
    float   direction;
    float   degreesToRotateImage;
    boolean paused;
    boolean showCursor;
    uint    color;
};

/****************************************************************************
 * 
 ****************************************************************************/
#define WIN_WIDTH     600
#define WIN_HEIGHT    600
#define WIN_TITLE     "GLSandbox #1"
#define WIN_FRAMERATE 60
#define WIN_BG_COLOR  0x000000

/****************************************************************************
 * 
 ****************************************************************************/
struct Player * initPlayer(void);

/****************************************************************************
 * 
 ****************************************************************************/
void updatePlayer(struct Player * player);

/****************************************************************************
 * 
 ****************************************************************************/
void drawPlayer(struct Player * player);

/****************************************************************************
 * 
 ****************************************************************************/
void releasePlayer(struct Player * player);

#endif // PLAYER_H
