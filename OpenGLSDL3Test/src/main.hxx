#ifndef MAIN_HXX
#define MAIN_HXX

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

/**
 * Declarations.
 */

auto SDL_AppInit(void** appState, int argc, char** argv) -> SDL_AppResult;
auto SDL_AppIterate(void* appState) -> SDL_AppResult;
auto SDL_AppEvent(void* appState, SDL_Event* event) -> SDL_AppResult;
auto SDL_AppQuit(void* appState, SDL_AppResult result) -> void;

#endif // MAIN_HXX
