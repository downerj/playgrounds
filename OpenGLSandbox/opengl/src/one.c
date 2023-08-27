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
#include "one-player.h"

/****************************************************************************
 * 
 ****************************************************************************/
void * init(void);
void   input(void * ptr);
void   update(void * ptr);
void   render(void * ptr);
void   tick(void * ptr);
void   cleanUp(void * ptr);

/****************************************************************************
 * 
 ****************************************************************************/
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
int main(int argc, char ** argv) {
    struct Player * player = init();

    if (!player) {
        utilDebug("Error constructing player", ANSI_RED);
        return EXIT_FAILURE;
    }

    boolean success = utilCreateWindow();
    if (!success) {
        utilDebug("Error creating window", ANSI_RED);
        return EXIT_FAILURE;
    }

    utilMainLoop();
    cleanUp(player);
    return EXIT_SUCCESS;
}

/****************************************************************************
 * 
 ****************************************************************************/
#define GLYPH_MARGIN_X  0
#define GLYPH_MARGIN_Y  1
#define GLYPH_SCALING   6
#define GLYPH_TAB_WIDTH 4
void * init() {
    if (!utilInitEngine()) {
        utilDebug("Error initializing engine", ANSI_YELLOW);
        return NULL;
    }

    // init user data
    struct Player * player = initPlayer();

    if (player) {
        utilSetWinDims(WIN_WIDTH, WIN_HEIGHT);
        utilSetWinTitle(WIN_TITLE);
        utilSetFramerate(WIN_FRAMERATE);
        utilSetBGColor(WIN_BG_COLOR);
        utilSetTickFunc(tick);
        utilSetUserData(player);
        utilSetCursorVisible(player->showCursor);
        utilSetGlyphMargins(GLYPH_MARGIN_X, GLYPH_MARGIN_Y);
        utilSetGlyphScaling(GLYPH_SCALING);
        utilSetGlyphTabWidth(GLYPH_TAB_WIDTH);
    }

    return player;
}

#include <stdio.h>
/****************************************************************************
 * 
 ****************************************************************************/
#define WASD_SPEED    10.0f
#define ROTATE_SPEED  5.0f
#define JOYSTICK      GLFW_JOYSTICK_1
#define JOY_AXIS_L    0
#define JOY_AXIS_R    1
#define JOY_DEAD_ZONE 0.10f
#define BT_PAUSE      9
void input(void * ptr) {
    struct Player * player = (struct Player *) ptr;
    
    boolean cmdPressed = (
        utilGetKey(GLFW_KEY_LEFT_CONTROL)  ||
        utilGetKey(GLFW_KEY_RIGHT_CONTROL) ||
        utilGetKey(GLFW_KEY_LEFT_SUPER)    ||
        utilGetKey(GLFW_KEY_RIGHT_SUPER)
    );
    if (cmdPressed) {
        if (utilGetKey(GLFW_KEY_W) || utilGetKey(GLFW_KEY_Q)) {
            utilEnd();
            return;
        }
    }

    if (utilIsKey(GLFW_KEY_P) || utilIsJoyButton(JOYSTICK, BT_PAUSE)) {
        player->paused = !player->paused;
    }
    utilDebounceKey(GLFW_KEY_P);
    utilDebounceJoyButton(JOYSTICK, BT_PAUSE);

    if (utilIsMouseRight()) {
        player->showCursor = !player->showCursor;
        utilSetCursorVisible(player->showCursor);
    }
    utilDebounceMouseRight();

    // defaults (in case not moving)
    float dx = 0.0;
    float dy = 0.0;
    float da = 0.0;

    if (!player->paused) {
        if (utilJoysticks[JOYSTICK].available) {
            utilSetDeadZoneX(JOYSTICK, JOY_AXIS_L, JOY_DEAD_ZONE);
            utilSetDeadZoneY(JOYSTICK, JOY_AXIS_L, JOY_DEAD_ZONE);
            utilSetDeadZoneX(JOYSTICK, JOY_AXIS_R, JOY_DEAD_ZONE);
            utilSetDeadZoneY(JOYSTICK, JOY_AXIS_R, JOY_DEAD_ZONE);

            float axisX = utilGetAxisX(JOYSTICK, JOY_AXIS_L);
            float axisY = utilGetAxisY(JOYSTICK, JOY_AXIS_L);
            float axisA = utilGetAxisX(JOYSTICK, JOY_AXIS_R);

            // move left/right (left x-axis)
            dx = WASD_SPEED * axisX;
            // move up/down (left y-axis)
            dy = WASD_SPEED * axisY;
            // rotate (right x-axis)
            da = ROTATE_SPEED * axisA;
        } else {
            if (utilGetKey(GLFW_KEY_LEFT)) {
                dx = -WASD_SPEED;
            } else if (utilGetKey(GLFW_KEY_RIGHT)) {
                dx = +WASD_SPEED;
            }

            if (utilGetKey(GLFW_KEY_UP)) {
                dy = -WASD_SPEED;
            } else if (utilGetKey(GLFW_KEY_DOWN)) {
                dy = +WASD_SPEED;
            }

            if (utilGetKey(GLFW_KEY_A)) {
                da = -ROTATE_SPEED;
            } else if (utilGetKey(GLFW_KEY_D)) {
                da = +ROTATE_SPEED;
            }
        }
    }
    
    player->velocity->dx = dx;
    player->velocity->dy = dy;
    player->degreesToRotateImage = da;
}

/****************************************************************************
 * 
 ****************************************************************************/
void update(void * ptr) {
    updatePlayer((struct Player *) ptr);
}

/****************************************************************************
 * 
 ****************************************************************************/
#define CURSOR_WIDTH   20
#define CURSOR_HEIGHT  20
void render(void * ptr) {
    struct Player * player = (struct Player *) ptr;

    utilClearScreen();

    // write some text
    struct UtilPoint2f textCursor = {1, 400};
    utilSetGlyphCursorPt(&textCursor);
    utilSetGlyphColorInt(0xffaa00);
    utilDrawText("The quick brown fox jumps\bed\nover the lazy dog\n");
    utilDrawText("0123456789\n");
    utilDrawText("`~!@#$%^&*()[]{}<>\n-=_+\\|/,.:;\n'\"yeet?\"");

    // if paused, then write "PAUSED"
    if (player->paused) {
        utilDrawText("\n");
        utilSetGlyphColorInt(0xff0000);
        utilDrawText("PAUSED");
    }

    struct UtilJoystick * joystick = &utilJoysticks[JOYSTICK];
    if (joystick->available) {
        utilDrawText("\n");
        utilSetGlyphColorInt(0x00aaff);

        for (uint b = 0; b < joystick->numButtons; b++) {
            if (!joystick->buttons[b]) {
                continue;
            }

            utilDrawInteger(b);
            utilDrawCharacter(' ');
        }
    }

    drawPlayer(player);
    // draw a point on the player's center
    utilSetStrokeColorInt(0xff0000);
    utilFillPoint(player->position);
    
    // draw a cursor (crosshairs)
    struct UtilPoint2f crossHairs[2][2] = {
        {{utilMouse.x + 0, utilMouse.y - CURSOR_HEIGHT},
         {utilMouse.x + 0, utilMouse.y + CURSOR_HEIGHT}},
        {{utilMouse.x - CURSOR_WIDTH, utilMouse.y + 0},
         {utilMouse.x + CURSOR_WIDTH, utilMouse.y + 0}},
    };
    utilSetStrokeColorInt(0x00aaff);
    utilStrokeLine(crossHairs[0]);
    utilStrokeLine(crossHairs[1]);
}

/****************************************************************************
 * 
 ****************************************************************************/
void tick(void * ptr) {
    input(ptr);
    update(ptr);
    render(ptr);
}

/****************************************************************************
 * 
 ****************************************************************************/
void cleanUp(void * ptr) {
    releasePlayer((struct Player *) ptr);
}
