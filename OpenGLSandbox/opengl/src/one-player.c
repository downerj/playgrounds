/****************************************************************************
 * 
 ****************************************************************************/
#include <stdlib.h> // *alloc, free

/****************************************************************************
 * 
 ****************************************************************************/
#include <utils/utildraw.h>

/****************************************************************************
 * 
 ****************************************************************************/
#include "one-player.h"

/****************************************************************************
 * 
 ****************************************************************************/
struct UtilPoint2f gPlayerPosition   = {WIN_WIDTH / 2.0, WIN_HEIGHT / 2.0};
struct UtilPoint2f gPlayerVertices[] = {{0, -10}, {-20, 20}, {20, 20}};
struct UtilPath2f  gPlayerImage      = {3, &gPlayerPosition, gPlayerVertices};
struct Velocity    gPlayerVelocity   = {0.0, 0.0};
float gPlayerRotation  = 0.0;
float gPlayerDirection = 0.0;
float gPlayerDA        = 0.0;
uint  gPlayerColor     = 0x00ff00;

/****************************************************************************
 * 
 ****************************************************************************/
struct Player * initPlayer(void) {
    struct Player * player = (struct Player *) malloc(sizeof(struct Player));
    
    if (player) {
        player->image      = &gPlayerImage;
        player->position   = &gPlayerPosition;
        player->velocity   = &gPlayerVelocity;
        player->rotation   = gPlayerRotation;
        player->direction  = gPlayerDirection;
        player->degreesToRotateImage = gPlayerDA;
        player->color      = gPlayerColor;
        player->paused     = FALSE;
        player->showCursor = FALSE;
    }

    return player;
}

/****************************************************************************
 * 
 ****************************************************************************/
void updatePlayer(struct Player * player) {
    struct Velocity * vel = player->velocity;

    if (vel->dx || vel->dy) {
        player->position->x += vel->dx;
        player->position->y += vel->dy;
    }
    
    float dr = player->degreesToRotateImage;
    if (dr) {
        utilRotatePolygonAboutCenter(player->image, dr);
    }
}

/****************************************************************************
 * 
 ****************************************************************************/
void drawPlayer(struct Player * player) {
    utilSetStrokeColorInt(player->color);
    utilStrokePolygon(player->image);
}

/****************************************************************************
 * 
 ****************************************************************************/
void releasePlayer(struct Player * player) {
    free(player);
    player = NULL;
}
