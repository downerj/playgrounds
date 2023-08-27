/****************************************************************************
 * 
 ****************************************************************************/
#include <utils/utiltypes.h>
#include <utils/utilinit.h>
#include <utils/utildraw.h>
#include <utils/utilinput.h>
#include <utils/utildebug.h>
#include <utils/utiltext.h>

/****************************************************************************
 * 
 ****************************************************************************/
#include "one-game.hpp"
#include "one-player.hpp"

/****************************************************************************
 * 
 ****************************************************************************/
void tick(void * ptr);

/****************************************************************************
 * 
 ****************************************************************************/
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
int main(int argc, char ** argv) {
    Game game;
    if (!utilCreateWindow()) {
        utilDebug("Error creating window", ANSI_RED);
        return EXIT_FAILURE;
    }

    utilMainLoop();
    return EXIT_SUCCESS;
}

/****************************************************************************
 * 
 ****************************************************************************/
void tick(void * ptr) {
    Game * pGame = (Game *) ptr;
    pGame->input();
    pGame->update();
    pGame->render();
}